/*
 * timers.c
 *
 *  Created on: 9 de nov. de 2016
 *      Author: Martin
 */
#include "infotronic.h"

void TIMER0_IRQHandler(void)
{
	if(T0IR & 0x01)
	{
		//Interrupcion por timer humedad
		timer_humedad = ON;
	}
	else if(T0IR & 0x02)
	{
		//Interrupcion por timer temperatura
		timer_temp = ON;
	}
	else if(T0IR & 0x04)
	{
		//Interrupcion por timer nivel H2O
		timer_h2o = ON;
	}
}

void TIMER1_IRQHandler(void)
{

}

void TIMER2_IRQHandler(void)
{

}

void TIMER3_IRQHandler(void)
{

}
