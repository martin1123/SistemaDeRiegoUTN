/*
 * transmision.c
 *
 *  Created on: 10 de nov. de 2016
 *      Author: Martin
 */
#include "infotronic.h"
#include "transmision.h"

//Size de los byte de Start, tamaño, checksum, y stop
#define SZ_CONTROL 4
#define POS_INI_DATA 2

uint8_t isEnabledUART()
{
	return UART_STATUS;
}

/*Funcion que arma la trama a enviar. Retorna un puntero a la trama o en caso de error retorna NULL.
 * dato es el dato a enviar, y sz es el tamaño del dato*/

uint8_t armarTrama(uint8_t *trama, enum transmitState s)
{
	uint8_t sz, pos_command, pos_subcommand;
	trama[0] = B_START;

	switch (s)
	{
		case TRANS_TEMP:
			//Para la temperatura, se transmite en un byte.
			//El bit mas significativo indica el signo, y el resto el valor de la temperatura
			pos_command = POS_COM_INFORM; //Comando
			pos_subcommand = POS_SUBCOM_TEMP; //Sub comando
			trama[4] = 0x00; //Inicializo byte en 0

			if(temp < 0)
			{
				trama[4] |= (1<<7);  //Si es negativo, seteo en 1 el bit mas significativos
				trama[4] |= (uint8_t)(temp*(-1)); //Paso a positivo el valor de la temperatura y guardo valor en los bits menos significativos
			}
			else
			{
				trama[4] |= (uint8_t)(temp);//guardo valor en los bits menos significativos
			}

			break;
		case TRANS_HUM:
			pos_command = POS_COM_INFORM;
			pos_subcommand = POS_SUBCOM_HUMEDAD;
			trama[4] = humedad;
			break;

		case TRANS_LVLH2O:
			pos_command = POS_COM_INFORM;
			pos_subcommand = POS_SUBCOM_LVLH2O;
			trama[4] = lvlH2O;
			break;

		case TRANS_ACK:
			/*En este caso, solo se envia el comando y subcomando, sin ningun dato adicional
			 * ya que solo es una confirmacion de recepcion de un dato*/
			pos_command = POS_COM_ACK;
			pos_subcommand = POS_SUBCOM_ACK;
			break;

		default:
			break;
	}

	sz = commands[pos_command].sub[pos_subcommand].sz + 2; //Size del dato, size del comando, y size del subcomando
	trama[1] = sz;
	trama[2] = commands[pos_command].command;
	trama[3] = commands[pos_command].sub[pos_subcommand].subCommand;
	trama[2 + sz] = calc_checksum(trama+2, sz);//En trama[2] comienza el analisis de los datos. Comando, subcomando, y dato en si.
	trama[2 + sz + 1] = B_STOP;

	return 1;
}

uint8_t calc_checksum(uint8_t * dato, uint8_t size)
{
	uint32_t sum;
	uint8_t i;

	for(i = 0, sum = 0; i < size; i++)
		sum += (i+1) * dato[i];

	return (uint8_t) (sum % 256);
}

void transmitir (uint8_t *p)
{
    uint32_t i;

    for (i=0; i < BUFF_TRAMA_SZ; ++i)
         PushTx(p[i]);
}
