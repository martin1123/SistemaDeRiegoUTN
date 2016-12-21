/**
	\file systick.c
	\brief Driver del systick
	\details
	\author Grupo II, curso R2053
	\version 1.0.0
*/
#include "infotronic.h"

#define DECIMAS 40

void init_systick()
{
	SYSTICK_PUNT->STRELOAD = (( SYSTICK_PUNT->STCALIB / 4) - 1);	// Recarga cada 2.5 ms
	SYSTICK_PUNT->STCURR = 0;	// Cargando con cero limpio y provoco el disparo de una intrrupcion
	// Habilito el conteo
	// Habilito interrupcion
	// Utilizamos Pclk
	SYSTICK_PUNT->STCTRL |=  ( ( 1 << 0x00 ) | ( 1 << 0x01 ) | ( 1 << 0x02 ) );
}

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
