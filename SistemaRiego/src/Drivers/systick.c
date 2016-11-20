/*
 * systick.c
 *
 *  Created on: 7 de nov. de 2016
 *      Author: Martin
 */
#include "infotronic.h"

#define DECIMAS 40

void SysTick_Handler(void)
{
	static uint8_t decimas = DECIMAS;

	decimas--;

	if(!decimas)
	{
		decimas = DECIMAS;
		AnalizarTimer();
	}
}
