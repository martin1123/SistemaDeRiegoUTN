/**
	\file EventsDrivers.c
	\brief Drivers que controlan la bomba de riego
	\details
	\author Grupo II, curso R2053
	\version 1.0.0
*/
#include "EventStates.h"
#include "infotronic.h"

void encenderRegado(void)
{
	//Driver que envía señal para encender bomba de agua
	write_pin(PORT_BOMB,PIN_BOMB,1);
}

void apagarRegado(void)
{
	//Driver que envía señal para apagar bomba de agua
	write_pin(PORT_BOMB,PIN_BOMB,0);
}
