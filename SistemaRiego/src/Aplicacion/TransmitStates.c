/*
 * TransmitStates.c
 *
 *  Created on: 17 de nov. de 2016
 *      Author: Martin
 */
#include "TransmitStates.h"
#include "infotronic.h"

void (*TMV[])() = {no_transmit,transmit_data,transmitAck,confirmTransmission};
enum transmitState t_state = STATE_NO_TRANS;
enum transmitData dataToTrans = NO_DATA;

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
			dataToTrans = TRANS_TEMP;
		}
		else if(TRANSMIT_H)
		{
			TRANSMIT_H = OFF;
			dataToTrans = TRANS_HUM;
		}
		else if(TRANSMIT_H2O)
		{
			TRANSMIT_H2O = OFF;
			dataToTrans = TRANS_LVLH2O;
		}
		else if(TRANSMIT_ACK)
		{
			/*En este caso particular, se pasa a un estado especial para la transmisión de Ack*/
			TRANSMIT_ACK = OFF;
			t_state = STATE_TRANS_ACK;
		}

		/*Si hay datos a transmitir pasa al estado de transmisión de datos*/
		if(dataToTrans != NO_DATA)
			t_state = STATE_TRANS_DATA;
	}
}

void transmit_data(void)
{
	uint8_t trama[BUFF_TRAMA_SZ];

	/*Se genera la trama segun el dato a transmitir*/
	if(armarTrama(trama, dataToTrans))
	{
		transmitir(trama);
		t_state = STATE_TRANS_CONFIRM; //Se pasa al estado de espera de un ACK de parte del dispositivo conectado por UART
		TimerStart(TIMER_EV_UART_ACK,50);//Iniciar timer de espera para recibir ack, sino retransmite
	}
	else
		t_state = STATE_NO_TRANS;
}

/*Para este estado de transmision en particular, no se contempla que se reciba una confirmacion desde el otro dispositivo
 * ya que en si, el envío de un ack, es una confirmación de que se recibio un mensaje.*/
void transmitAck(void)
{
	uint8_t trama[BUFF_TRAMA_SZ];

	armarTrama(trama, TRANS_ACK);
	transmitir(trama);
	t_state = STATE_NO_TRANS; //Se directamente al estado de reposo
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
		t_state = STATE_NO_TRANS;
		dataToTrans = NO_DATA;
	}
	else if(EXPIRED_ACK)
	{
		EXPIRED_ACK = OFF;

		if(reintentos--)
		{
			TimerStart(TIMER_EV_UART_ACK, 50);//reiniciar timer de ack
			t_state = STATE_TRANS_DATA;
		}
		else
		{
			//Se acabaron los reintentos
			reintentos = 2;
			TimerStop(TIMER_EV_UART_ACK);//desactivar timer ack
			t_state = STATE_NO_TRANS;
			dataToTrans = NO_DATA;
		}
	}
}
