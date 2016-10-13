/*
 * System_INIC.c
 *
 *  Created on: 13 de oct. de 2016
 *      Author: Martin
 *
 * Drivers de inicialización del sistema
 */
#include "infotronic.h"

void init_systick()
{
	SYSTICK_PUNT->STRELOAD = (( SYSTICK_PUNT->STCALIB / 4) - 1);	// Recarga cada 2.5 ms
	SYSTICK_PUNT->STCURR = 0;	// Cargando con cero limpio y provoco el disparo de una intrrupcion
	// Habilito el conteo
	// Habilito interrupcion
	// Utilizamos Pclk
	SYSTICK_PUNT->STCTRL |=  ( ( 1 << 0x00 ) | ( 1 << 0x01 ) | ( 1 << 0x02 ) );
}
