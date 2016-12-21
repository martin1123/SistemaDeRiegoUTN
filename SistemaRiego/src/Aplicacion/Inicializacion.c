/**
	\file Inicializacion.c
	\brief inicializacion del sistema de riego
	\details Funciones que incluyen todas las inicializaciones del sistema de riego antes de
	         su funcionamiento.
	\author Grupo II, curso R2053
	\version 1.0.0
*/
#include "infotronic.h"
#include "inicializar.h"

void initLedRGB(void);
void initAlarm(void);

void inicializar(void)
{
	InitPLL () ;
	init_systick (); //Inicializacion Systick
	init_rtc(8,5,1,15,12,2016);//Inicializacion RTC
	InitLCD (); //Iniciacion LCD 16X2
	InitSensores(); //Inicializacion de Puertos y pines de todos los sensores del sistema
	InitBomba(); //Inicializacion de Puertos y pines de la bomba
	InitUART0(); //Inicializacion para comunicacion UART0
	initTimers();//Inicializacion de la maquina de timers
	initAlarm();
	initLedRGB();
}

void initLedRGB()
{
	//Se apaga led RGB
	conf_gpio(2,1,OUT);
	conf_gpio(2,2,OUT);
	conf_gpio(2,3,OUT);
	write_pin(2,1,0);
	write_pin(2,2,0);
	write_pin(2,3,0);
}

void initAlarm(void)
{
	conf_gpio(BUZZ_PORT,BUZZ_PIN,OUT); //BUZZ_PORT 0, BUZZ_PIN 28
	write_pin(BUZZ_PORT,BUZZ_PIN,BUZZ_OFF);//Se desactiva alarma
}
