/**
	\file eventsPrim.c
	\brief Primitivas de activacion y desactivacion de regado y alarmas
	\details
	\author Grupo II, curso R2053
	\version 1.0.0
*/

#include "EventStates.h"
#include "infotronic.h"

void activarRiego(uint8_t timer_status)
{
	encenderRegado();

	if(!timer_status)
		TimerStart(TIMER_EV_RIEGO, timer_regado);

	return;
}

void desactivarRiego(void)
{
	apagarRegado();
	timer_Riego = OFF;
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

