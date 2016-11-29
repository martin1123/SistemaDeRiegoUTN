/*
 * TransmitStates.c
 *
 *  Created on: 17 de nov. de 2016
 *      Author: Martin
 */
#include "TransmitStates.h"
#include "infotronic.h"

void (*TMV[])() = {no_transmit,transmitTemp,transmitHum,transmitLvlH2O,transmitRegando,transmitAck,confirmTransmission};
enum transmitState t_state = NO_TRANS;
enum transmitState retransmit_state = NO_TRANS;

void Transmit_Machine(void)
{
	TMV[t_state]();
}

void no_transmit(void)
{
	/*Si no hay dispositivos conectados a la UART no transmite*/
	if(isEnabledUART())
	{
		if(TRANSMIT_TEMP)
		{
			TRANSMIT_TEMP = OFF;
			t_state = TRANS_TEMP;
		}
		else if(TRANSMIT_H)
		{
			TRANSMIT_H = OFF;
			t_state = TRANS_HUM;
		}
		else if(TRANSMIT_H2O)
		{
			TRANSMIT_H2O = OFF;
			t_state = TRANS_LVLH2O;
		}
		else if(TRANSMIT_ACK)
		{
			TRANSMIT_ACK = OFF;
			t_state = TRANS_ACK;
		}
	}
}

void transmitTemp(void)
{
	uint8_t trama[BUFF_TRAMA_SZ];

	/*CAMBIO DE DISENO: El codigo dentro del if de abajo, va a pertenece a un nuevo estado denominado
	 * ACK_STATE. Practicamente en este estado, se debe recibir de alguna forma, de que transmision
	 * se espera un ack, Por ejemplo temperatudra. Si no se llega a recibir ack, se volvera al estado
	 * de tempreratura a transmitir la temp nuevamente, hasta q se agoten reintentos. Con esto
	 * se logra eliminar el codigo duplicado en cada estado que contempla esperar un ack.*/

	/*NOTA: El dato solo debería ser la temperatura, y nada mas. Luego el protocolo  se deben definir estructuras*/
	if(armarTrama(trama, TRANS_TEMP))
	{
		transmitir(trama);
		retransmit_state = TRANS_TEMP; //En caso de retransmision, se envía este estado
		t_state = TRANS_CONFIRM; //Se pasa al estado de espera de un ACK de parte del dispositivo conectado por UART
		TimerStart(TIMER_EV_UART_ACK,50);//Iniciar timer de espera para recibir ack, sino retransmite
	}
	else
		t_state = NO_TRANS;
}

void transmitHum(void)
{
	uint8_t trama[BUFF_TRAMA_SZ];

	if(armarTrama(trama, TRANS_HUM))
	{
		transmitir(trama);
		retransmit_state = TRANS_HUM; //En caso de retransmision, se envía este estado
		t_state = TRANS_CONFIRM; //Se pasa al estado de espera de un ACK de parte del dispositivo conectado por UART
		TimerStart(TIMER_EV_UART_ACK,50);//Iniciar timer de espera para recibir ack, sino retransmite
	}
	else
		t_state = NO_TRANS;
}

void transmitLvlH2O(void)
{
	uint8_t trama[BUFF_TRAMA_SZ];

	if(armarTrama(trama, TRANS_LVLH2O))
	{
		transmitir(trama);
		retransmit_state = TRANS_LVLH2O; //En caso de retransmision, se envía este estado
		t_state = TRANS_CONFIRM; //Se pasa al estado de espera de un ACK de parte del dispositivo conectado por UART
		TimerStart(TIMER_EV_UART_ACK,50);//Iniciar timer de espera para recibir ack, sino retransmite
	}
	else
		t_state = NO_TRANS;
}

void transmitRegando(void)
{

}

/*Para este estado de transmision en particular, no se contempla que se reciba una confirmacion desde el otro dispositivo
 * ya que en si, el envío de un ack, es una confirmación de que se recibio un mensaje.*/
void transmitAck(void)
{
	uint8_t trama[BUFF_TRAMA_SZ];

	armarTrama(trama, TRANS_ACK);
	transmitir(trama);
	t_state = NO_TRANS; //Se directamente al estado de reposo
}

/*Estado que queda a la espera de que se reciba el ack por el dato transmitido*/
void confirmTransmission(void)
{
	static uint8_t reintentos = 2;

	//Se verifica si fue recibida la confirmación del dato enviado
	if(RECEIVED_ACK)
	{
		RECEIVED_ACK = OFF; //Desactiva flag
		TimerStop(TIMER_EV_UART_ACK);//desactiva timer de ack
		reintentos = 2;
		t_state = NO_TRANS;
		retransmit_state = NO_TRANS;
	}
	else if(EXPIRED_ACK)
	{
		EXPIRED_ACK = OFF;

		if(reintentos--)
		{
			TimerStart(TIMER_EV_UART_ACK, 50);//reiniciar timer de ack
			t_state = retransmit_state;
		}
		else
		{
			//Se acabaron los reintentos
			reintentos = 2;
			TimerStop(TIMER_EV_UART_ACK);//desactivar timer ack
			t_state = NO_TRANS;
			retransmit_state = NO_TRANS;
		}
	}
}
