/*
 * receive.c
 *
 *  Created on: 1 de dic. de 2016
 *      Author: Martin
 */
#include "infotronic.h"
#include "receive.h"

int recepcionOk(uint8_t * trama, uint8_t size_trama)
{
	uint8_t sz;

	//En el segunfo byte de la trama, se indica el tamaño en bytes del comando, subcomados, y el dato.
	sz = trama[1];


	//EL size de la trama - 4 es equivalente al size de los comandos, subcomandos y datos. Si son distintos ocurrio algun error.
	if(sz != size_trama - 4)
	{
		//INFORMAR ERROR
		return 0;
	}

	if(calc_checksum(trama+2, sz) != trama[2 + sz])
	{
		//ERROR EN CHECKSUM
		return 0;
	}

	return 1;
}

void recuperarDato(uint8_t * trama, uint8_t size_datos)
{
	uint8_t i,j;
	uint8_t sz_sub;

	for(i = 0; i < SIZE_COMMANDS; i++)
	{
		//Si encontro comando
		if(commands[i].command == trama[0])
			break;
	}

	//Si no encontró el comando no se realiza ninguna accion por el momento
	if(i == SIZE_COMMANDS)
		//Se debería informar error????
		return;

	switch(commands[i].command)
	{
		case COM_INFORMAR:
			sz_sub = SIZE_SUB_INFORMAR;
			break;
		case COM_ACK:
			sz_sub = SIZE_SUB_ACK;
			break;
		case COM_REGAR:
			sz_sub = SIZE_SUB_REGAR;
			break;
		case COM_CONFIG:
			sz_sub = SIZE_SUB_CONFIGURAR;
			break;
		default:
			break; //Este caso es imposible que pase
	}

	for(j = 0; j < sz_sub; j++)
	{
		//Si encontro comando
		if(commands[i].sub[j].subCommand == trama[1])
			break;
	}

	//Si no encontró el subcomando no se realiza ninguna accion por el momento
	if(j == sz_sub)
		//Se debería informar error????
		return;

	//EN este punto se encontro el comando y subcomando!!!

}
