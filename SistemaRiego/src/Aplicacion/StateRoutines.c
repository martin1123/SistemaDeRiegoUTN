#include "infotronic.h"

void inicializar(void)
{
	InitPLL () ;
	init_systick (); //Inicializacion Systick
	init_rtc(0,0,0,0,0,0);//Inicializacion RTC
	InitLCD (); //Iniciacion LCD 16X2
	InitSensores(); //Inicializacion de Puertos y pines de todos los sensores del sistema
	InitBomba(); //Inicializacion de Puertos y pines de la bomba
//	InitUART0(); //Inicializacion para comunicacion UART0
	initTimers();
}
