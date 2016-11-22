/*
 * transmision.c
 *
 *  Created on: 10 de nov. de 2016
 *      Author: Martin
 */
#include "infotronic.h"
#include <stdlib.h>

//Size de los byte de Start, tamaño, checksum, y stop
#define SZ_CONTROL 4
#define POS_INI_DATA 2

uint8_t isEnabledUART()
{
	return UART_STATUS;
}

/*Funcion que arma la trama a enviar. Retorna un puntero a la trama o en caso de error retorna NULL.
 * dato es el dato a enviar, y sz es el tamaño del dato*/
uint8_t * armarTrama(uint8_t * dato, uint8_t sz)
{
	uint8_t i, j;
	uint8_t * trama = NULL;

	trama = (uint8_t *) malloc((sz + SZ_CONTROL) * sizeof(uint8_t));

	if(trama == NULL)
		return trama;

	trama[0] = B_START;
	trama[1] = sz;

	for(i = POS_INI_DATA, j = 0; j < sz ; i++, j++)
		trama[i] = dato[j];

	trama[i] = calc_checksum(dato, sz);
	trama[++i] = B_STOP;

	return trama;
}

uint8_t calc_checksum(uint8_t * dato, uint8_t size)
{
	uint32_t sum;
	uint8_t i;

	for(i = 0, sum = 0; i < size; i++)
		sum += (i+1) * dato[i];

	return (uint8_t) (sum % 256);
}

void liberarTrama(uint8_t * trama)
{
	free((void *)trama);
}

void Transmitir (char *p)
{
    uint32_t i;

    for (i=0; p[i]; ++i)
         PushTx(p[i]);
}
