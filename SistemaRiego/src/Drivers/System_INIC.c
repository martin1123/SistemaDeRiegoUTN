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
	initTimer0();
	initTimer1();
	initTimer2();
	initTimer3();
}

void initTimer0()
{
	PCONP |= (1<<1);
	PCLKSEL0 |= (1<<2);
	//Configurar MATCHS!!!
	ISER0 |= (0x01 << 1);
}

void initTimer1()
{
	PCONP |= (1<<2);
	PCLKSEL0 |= (1<<4);
	//Configurar MATCHS!!!
	ISER0 |= (0x01 << 2);
}

void initTimer2()
{
	PCONP |= (1<<22);
	PCLKSEL1 |= (1<<12);
	//Configurar MATCHS!!!
	ISER0 |= (0x01 << 3);
}

void initTimer3()
{
	PCONP |= (1<<23);
	PCLKSEL1 |= (1<<14);
	//Configurar MATCHS!!!
	ISER0 |= (0x01 << 4);
}
