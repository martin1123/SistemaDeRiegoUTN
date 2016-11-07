#include "infotronic.h"

void inicializar(void)
{
	PCONP = 0; //Se desactiva por default la alimentacion de perifericos
	InitPLL () ;
	init_systick ( ); //Inicializacion Systick
	init_rtc(0,0,0,0,0,0);//Inicializacion RTC
	InitSensores(); //Inicializacion de Puertos y pines de todos los sensores del sistema
	InitBomba(); //Inicializacion de Puertos y pines de la bomba
	InitUART0(); //Inicializacion para comunicacion UART0

	state_flag = REPOSO; //Cambio a estado de reposo
}

void reposo(void)
{
	if(timer_humedad == ON)
	{
		/*Se verifica humedad*/
		timer_humedad = OFF;
		state_flag = GET_HYT;
	}else if(timer_temp == ON)
	{
		/*Se verifica temperatura ambiente*/
		timer_temp = OFF;
		state_flag = GET_HYT_AMB;
	}else if(timer_h2o == ON)
	{
		/*Se verifica nivel de agua en tanque*/
		timer_h2o = OFF;
		state_flag = GET_H2O_LEVEL;
	}else if(timer_Riego == ON)
	{
		/*Alarma activa riego de plantas*/
		timer_h2o = OFF;
		state_flag = REGAR;
	}
	/*Falta agregar transiciones a mas estados*/
}

void obtenerHyTMaceta(void)
{

}

void obtenerHyTAmb(void)
{

}

void obtenerNivH2O(void)
{

}

void regar(void)
{

}

void alertaAgua(void)
{

}

void informarUART(void)
{

}
