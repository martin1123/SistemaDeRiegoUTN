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
	SCS       = SCS_Value;

	if (SCS_Value & (1 << 5))               /* If Main Oscillator is enabled      */
	while ((SCS & (1<<6)) == 0);/* Wait for Oscillator to be ready    */

	CCLKCFG   = CCLKCFG_Value;      /* Setup Clock Divider                */

	PCLKSEL0  = PCLKSEL0_Value;     /* Peripheral Clock Selection         */
	PCLKSEL1  = PCLKSEL1_Value;

	CLKSRCSEL = CLKSRCSEL_Value;    /* Select Clock Source for PLL0       */

	PLL0CFG   = PLL0CFG_Value;      /* configure PLL0                     */
	PLL0FEED  = 0xAA;
	PLL0FEED  = 0x55;

	PLL0CON   = 0x01;             /* PLL0 Enable                        */
	PLL0FEED  = 0xAA;
	PLL0FEED  = 0x55;

	while (!(PLL0STAT & (1<<26)));/* Wait for PLOCK0                    */

	PLL0CON   = 0x03;             /* PLL0 Enable & Connect              */
	PLL0FEED  = 0xAA;
	PLL0FEED  = 0x55;

	while (!(PLL0STAT & ((1<<25) | (1<<24))));/* Wait for PLLC0_STAT & PLLE0_STAT */

	PLL1CFG   = PLL1CFG_Value;
	PLL1FEED  = 0xAA;
	PLL1FEED  = 0x55;

	PLL1CON   = 0x01;             /* PLL1 Enable                        */
	PLL1FEED  = 0xAA;
	PLL1FEED  = 0x55;

	while (!(PLL1STAT & (1<<10)));/* Wait for PLOCK1                    */

	PLL1CON   = 0x03;             /* PLL1 Enable & Connect              */
	PLL1FEED  = 0xAA;
	PLL1FEED  = 0x55;

	while (!(PLL1STAT & ((1<< 9) | (1<< 8))));/* Wait for PLLC1_STAT & PLLE1_STAT */

	PCONP     = PCONP_Value;        /* Power Control for Peripherals      */

	CLKOUTCFG = CLKOUTCFG_Value;    /* Clock Output Configuration         */

	FLASHCFG  = (FLASHCFG & ~0x0000F000) | FLASHCFG_Value;

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

