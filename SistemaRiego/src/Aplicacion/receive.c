/*
 * receive.c
 *
 *  Created on: 1 de dic. de 2016
 *      Author: Martin
 */
#include "infotronic.h"
#include "receive.h"

uint8_t verificarComando(uint8_t * trama, uint8_t size_datos, uint8_t *cpos, uint8_t *scpos)
{
	uint8_t sz_sub;

	for(*cpos = 0; *cpos < SIZE_COMMANDS; *cpos++)
	{
		//Si encontro comando
		if(commands[*cpos].command == trama[0])
			break;
	}

	//Si no encontró el comando no se realiza ninguna accion por el momento
	if(*cpos == SIZE_COMMANDS)
		//Se debería informar error????
		return 0;

	switch(commands[*cpos].command)
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

	for(*scpos = 0; *scpos < sz_sub; *scpos++)
	{
		//Si encontro comando
		if(commands[*cpos].sub[*scpos].subCommand == trama[1])
			break;
	}

	//Si no encontró el subcomando no se realiza ninguna accion por el momento
	if(*scpos == sz_sub)
		//Se debería informar error????
		return 0;

	return 1;

}

void executeCommand(uint8_t comm_pos, uint8_t scomm_pos)
{

}
