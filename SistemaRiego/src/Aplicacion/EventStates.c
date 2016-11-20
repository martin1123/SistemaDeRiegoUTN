/*
 * EventStates.c
 *
 *  Created on: 17 de nov. de 2016
 *      Author: Martin
 */
#include "infotronic.h"
#include "EventStates.h"

/*MEV: Machine Event Vector*/
void (*MEV[])(void) = {no_event,regando,sinAgua};

/*Variable que indica estado*/
enum eventStates eSate = NO_EVENT;

void Event_Machine(void)
{
	MEV[eSate]();
}

void no_event(void)
{
	if(flag_H2OBajo)
	{
		eSate = ALARMA_H2O;
	}else if(flag_regar)
	{
		eSate = REGAR;
	}

}

void regando(void)
{
	activarRiego();

	/*Si vencio timer de riego*/
	if(timer_Riego == ON)
	{
		desactivarRiego();
		eSate = NO_EVENT;
	}

}

void sinAgua(void)
{
	activarAlarmaH2O();

	if(flag_H2OBajo == OFF)
	{
		desactivarAlarmaH2O();
		eSate = NO_EVENT;
	}
}
