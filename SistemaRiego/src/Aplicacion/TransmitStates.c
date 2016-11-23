/*
 * TransmitStates.c
 *
 *  Created on: 17 de nov. de 2016
 *      Author: Martin
 */
#include "infotronic.h"
#include "transmit.h"

void (*TMV[])() = {no_transmit,transmitTemp,transmitHum,transmitLvlH2O,transmitRegando, transmitAck};
enum transmitState t_state = NO_TRANS;

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
	static flagST_t transmitiendo = OFF;
	static flagST_t reintentos = 2;
	uint8_t trama[BUFF_TRAMA_SZ];

	/*Primero se verifica si se esta transmitiendo un dato y esperando una respuesta o ack, o se
	 * tiene que transmitir un dato nuevo*/
	if(transmitiendo)
	{
		//Se verifica si fue recibida la confirmación del dato enviado
		if(RECEIVED_ACK)
		{
			RECEIVED_ACK = OFF; //Desactiva flag
			//desactiva timer de ack
			transmitiendo = OFF;
			reintentos = 2;
			t_state = NO_TRANS;
		}
		else if(EXPIRED_ACK)
		{
			EXPIRED_ACK = OFF;
			transmitiendo = OFF;//Cuando vuelva a entrar a la funcion, va a volver a transmitir el dato

			if(reintentos--)
			{
				//reiniciar timer de ack
			}
			else
			{
				//Se acabaron los reintentos
				reintentos = 2;
				//desactivar timer ack
				t_state = NO_TRANS;
			}
		}
	}
	else
	{
		//Se transmite dato nuevo
		transmitiendo = ON;
/*MMA-SACAR COMENTARIO!!!
		armarMensaje();
		if(armarTrama(trama, BUFF_TRAMA_SZ, dato, szDato))
		{
			transmitir((char *)trama);
			//Iniciar timer de ack
		}
		else
		{
			transmitiendo = OFF;
		}*/
	}
}

void transmitHum(void)
{
	static flagST_t transmitiendo = OFF;

}

void transmitLvlH2O(void)
{
	static flagST_t transmitiendo = OFF;

}

void transmitRegando(void)
{

}

void transmitAck(void)
{

}


