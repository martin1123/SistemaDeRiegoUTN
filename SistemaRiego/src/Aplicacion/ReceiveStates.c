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
	uint8_t sz, cpos, scpos;


	//Si i es igual a 0 asigno el byte de start para tener la trama completa y verifico si se recibio el byte que indica size del comando, subcomando y datos
	if(!i)
	{
		trama[0] = B_START;
		dato = PopRx();


		if(dato>=0)
		{
			trama[++i] = (uint8_t)dato;
			sz = (uint8_t)dato + 4; //Size de la trama a recibir
		}
		else
			return;
	}


	//Va llenando la trama con los datos de recepción hasta que la cola quede vacía, o hasta que se encuentre byte de stop
	for(i = 2; i < sz && (dato = PopRx()) >= 0; i++)
	{
		trama[i] = (uint8_t) dato;
		//Verifico si llego byte de stop, y que además llegue en la posición esperada
		if(dato == B_STOP && i == (sz-1))
			break;
	}


	//Si se da este caso, es porque hubo una desincronización. No pueden venir mas de 255 bytes en total.
	if(i >= sz)
	{
		// Informar ERROR. No se transmite ACK. Se espera restransmision del dato.
		i = 0;
		r_state = R_REPOSO;
		return;
	}

	//Caso en que se recibio la trama hasta el byte de STOP. Se procede a realiza el checksum.
	//Luego se informa el dato recibido.
	if(dato == B_STOP && i == (sz-1))
	{
		//La proxima transición es al estado de reposo
		r_state = R_REPOSO;

		//Verifica checksum de comando, subcomando, y datos. trama[1] almacena el size de estos datos. trama[sz-2] almacena el checksum enviado.
		if(calc_checksum(trama+2, trama[1]) == trama[sz-2])
		{
			//Verifica que comando se recibio. En caso de no recibir un comando válido no se realiza ninguna acción.
			if(verificarComando(trama+2, i-3, &cpos, &scpos))
				//Verificado el comando, se procede a ejecutarlo
				executeCommand(cpos,scpos);

			i = 0;
		}
		else
		{
			//INFORMAR ERROR
			i = 0;
		}
	}
}
