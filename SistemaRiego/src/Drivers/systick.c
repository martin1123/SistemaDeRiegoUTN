/*
 * systick.c
 *
 *  Created on: 7 de nov. de 2016
 *      Author: Martin
 */
#include "infotronic.h"

#define CENTESIMAS 4

void SysTick_Handler(void)
{
	static uint8_t centesimas = CENTESIMAS;

	centesimas--;

	if(!centesimas)
	{
		centesimas = CENTESIMAS;
		//AnalizarTimers();
	}
}
