/**
	\file TransmitStates.c
	\brief Maquina de estados de transmision por puerto serie.
	\details Máquina de estados que comienza en el estado reposo. Si no se detecta algun dispositivo
	         conectado al kit, se permancera indefinidamente en este estado.
	         Cuando se detecta un dato a transmitir, se pasa al estado transmit_data, en el cual
	         se realizara el armado de la trama a transmitir, y se transmitira la misma. Una vez hecha
	         la transmision se pasará al estado confirmTransmission, en donde se va a esperar una confirmacion
	         por parte del equipo conectado al kit. En caso de no recibirse la confirmacion en un lapso de tiempo
	         determinado, se volverá a enviar el mensaje hasta 2 veces mas. Si no se llega a recibir un ACK, se
	         vuelve al estado de reposo.
	         Si se recibe el ACK por parte del equipo conectado al kit, se volvera al estado  de reposo a la espera
	         de la transmision de datos.
	\author Grupo II, curso R2053
	\version 1.0.0
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
		else if(TRANSMIT_UMBRAL_H2O)
		{
			/*Se transmite configuracion del umbral de H2O*/
			TRANSMIT_UMBRAL_H2O = OFF;
			dataToTrans = TRANS_UMBRAL_H2O;
		}
		else if(TRANSMIT_UMBRAL_HUM)
		{
			/*Se transmite configuracion del umbral de Humedad*/
			TRANSMIT_UMBRAL_HUM = OFF;
			dataToTrans = TRANS_UMBRAL_HUM;
		}
		else if(TRANSMIT_UMBRAL_TEMP)
		{
			/*Se transmite configuracion del umbral de Temperatura*/
			TRANSMIT_UMBRAL_TEMP = OFF;
			dataToTrans = TRANS_UMBRAL_TEMP;
		}
		else if(TRANSMIT_TIME_REGADO)
		{
			/*Se transmite configuracion del tiempo de regado*/
			TRANSMIT_TIME_REGADO = OFF;
			dataToTrans = TRANS_TIME_REG;
		}
		/*Si hay datos a transmitir pasa al estado de transmisión de datos*/
		if(dataToTrans != NO_DATA)
			t_state = STATE_TRANS_DATA;
	}
}

void transmit_data(void)
{
	uint8_t trama[BUFF_TRAMA_SZ];
	uint8_t sz_trama;

	/*Se genera la trama segun el dato a transmitir*/
	if((sz_trama = armarTrama(trama, dataToTrans)) > 0)
	{
		transmitir(trama, sz_trama);
		t_state = STATE_TRANS_CONFIRM; //Se pasa al estado de espera de un ACK de parte del dispositivo conectado por UART
		TimerStart(TIMER_EV_UART_ACK,1);//Iniciar timer de espera para recibir ack, sino retransmite
	}
	else
		t_state = STATE_NO_TRANS;
}

/*Para este estado de transmision en particular, no se contempla que se reciba una confirmacion desde el otro dispositivo
 * ya que en si, el envío de un ack, es una confirmación de que se recibio un mensaje.*/
void transmitAck(void)
{
	uint8_t sz;
	uint8_t trama[BUFF_TRAMA_SZ];

	sz = armarTrama(trama, TRANS_ACK);
	transmitir(trama, sz);
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
		EXPIRED_ACK = OFF; //Desactiva el flag en caso de que justo haya expirado el tiempo de espera del ack y se haya recibido el mismo
		TimerStop(TIMER_EV_UART_ACK);//desactiva timer de ack
		restartTimer();//Restartea los timers correspondientes del dato enviado
		reintentos = 2;
		t_state = STATE_NO_TRANS;
		dataToTrans = NO_DATA;
	}
	else if(EXPIRED_ACK)
	{
		EXPIRED_ACK = OFF;

		if(reintentos--)
		{
			TimerStart(TIMER_EV_UART_ACK, 1);//reiniciar timer de ack
			t_state = STATE_TRANS_DATA;
		}
		else
		{
			//Se acabaron los reintentos
			reintentos = 2;
			TimerStop(TIMER_EV_UART_ACK);//desactivar timer ack
			restartTimer();//Restartea los timers correspondientes del dato enviado
			t_state = STATE_NO_TRANS;
			dataToTrans = NO_DATA;
		}
	}
}


void restartTimer(void)
{
	switch(dataToTrans)
	{
		case TRANS_TEMP:
			TimerStart(TIMER_EV_UART_TEMP, 11);
			break;
		case TRANS_HUM:
			TimerStart(TIMER_EV_UART_HUM, 7);
			break;
		case TRANS_LVLH2O:
			TimerStart(TIMER_EV_UART_H2O, 3);
			break;
		default:
			break;
	}
}
