/**
	\file eventsPrim.c
	\brief Primitivas de activacion y desactivacion de regado y alarmas
	\details
	\author Grupo II, curso R2053
	\version 1.0.0
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
	flag_alarm = ON;
}

void desactivarAlarmaH2O(void)
{
	flag_alarm = OFF;
}

