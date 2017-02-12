/**
	\file EventStates.c
	\brief Maquina de estados de los eventos del sistema.
	\details Basicamente esta maquina de estados permanece en reposo hasta que
	         se activa un flag que indica que se debe regar, con lo cual se pasa al
	         estado de riego. En el estado de riego se activa la bomba de agua, y se
	         permanece en este estado hasta que se detecta que termino el tiempo de regado.
	         A su vez, si se activa un flag que indica un nivel de agua bajo en tanque, se
	         pasa al estado sinAgua, del cual no se podrá volver al estado de reposo hasta que
	         no se llene el tanque de agua. Este ultimo estado provoca la activacion de una alarma
	         que alerte al usuario del sistema.
	\author Grupo II, curso R2053
	\version 1.0.0
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
	static uint8_t timer_on = 0;
	activarRiego(timer_on);
	timer_on = 1;

	/*Si vencio timer de riego*/
	if(timer_RiegoFinalizado == ON)
	{
		timer_on = 0;
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
