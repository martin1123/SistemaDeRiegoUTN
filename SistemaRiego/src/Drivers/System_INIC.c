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

void init_rtc(uint8_t ss, uint8_t mm, uint8_t hh, uint8_t dd, uint8_t mo, uint16_t yy)
{
	RTCCCR = 0x01UL; //Se habilita clock
	config_date_RTC(ss,mm,hh,dd,mo,yy); //Se configura fecha y hora del reloj
	RTCCIIR = 0x01UL; //Se genera interrupcion por segundo
	RTCARM = 0xFFUL; //Inicialmente no se utiliza la alarma
	ISER0  |= (1 << 17); //Se habilita interrupcion del RTC
	PCONP |= (1 << PCRTC); //Se alimenta periferico
}

void InitPLL ( )
{

}

void InitSensores()
{

}

void InitBomba()
{

}

void InitUART0()
{

}

void initTimers()
{
	/* Inicializacion de timer de refresco de display
	 * En principio, este es el unico timer que se va a utilizar*/
	/*Refresco de pantalla cada 5 segundos*/
	TimerStart(0, 50);
}

