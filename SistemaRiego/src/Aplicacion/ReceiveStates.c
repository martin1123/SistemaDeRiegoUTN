/*
 * ReceiveStates.c
 *
 *  Created on: 17 de nov. de 2016
 *      Author: Martin
 */
#include "Receive_states.h"
#include "receive.h"
#include "infotronic.h"

void (*RMV[])(void) = {Receive_Reposo, Receiving};
enum receiveState r_state = R_REPOSO;

void Receive_Machine(void)
{
	RMV[r_state]();
}

void Receive_Reposo(void)
{
	int d;

	if((d = PopRx()) >= 0)
	{
		if(d == B_START)
		{
			r_state = R_RECEIVING;
		}
		//Si no hay un error de sincronizción
	}
}

void Receiving(void)
{
	static uint8_t i = 0;
	static uint8_t trama[BUFF_TRAMA_SZ];
	int dato;

	//Si i es igual a 0 asigno el byte de start para tener la trama completa
	if(!i)
		trama[i++] = B_START;

	//Va llenando la trama con los datos de recepción hasta que la cola quede vacía, o hasta que se encuentre byte de stop
	for(; i < 256 && (dato = PopRx()) >= 0; i++)
	{
		trama[i] = (uint8_t) dato;
		if(dato == B_STOP)
			break;
	}


	//Si se da este caso, es porque hubo una desincronización. No pueden venir mas de 255 bytes en total.
	if(i > 255)
	{
		// Informar ERROR. No se transmite ACK. Se espera restransmision del dato.
		i = 0;
		r_state = R_REPOSO;
		return;
	}

	//Caso en que se recibio la trama hasta el byte de STOP. Se procede a realiza el checksum.
	//Luego se informa el dato recibido.
	if(dato == B_STOP)
	{
		//La proxima transición es al estado de reposo
		r_state = R_REPOSO;

		//i + 1 es el tamaño en bytes de la trama
		if(recepcionOk(trama, i+1))
		{
			//Recupera desde que comienza el comando, hasta el último byte que ocupa un dato. Desde
			recuperarDato(trama + 2, i-3);
			i = 0;
		}
		else
		{
			//INFORMAR ERROR
			i = 0;
		}
	}
}
