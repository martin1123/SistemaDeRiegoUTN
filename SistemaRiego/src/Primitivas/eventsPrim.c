/*
 * eventsPrim.c
 *
 *  Created on: 20 de nov. de 2016
 *      Author: Martin
 */

#include "EventStates.h"
#include "infotronic.h"

void activarRiego(void)
{
	encenderRegado();
	/*Encender timer 6*/
	return;
}

void desactivarRiego(void)
{
	apagarRegado();
	/*Detener timer 6, reiniciarlo y setear timer_Riego en OFF;*/
	flag_regar = OFF;
	return;
}

void activarAlarmaH2O(void)
{
	return;
}

void desactivarAlarmaH2O(void)
{
	flag_H2OBajo = OFF;
	return;
}

