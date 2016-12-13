/**
	\file timers.c
	\brief Primitivas del manejo de la maquina de timers
	\details
	\author Grupo II, curso R2053
	\version 1.0.0
*/
#include "timers.h"
#include "infotronic.h"

void TimerEvent(void)
{

	/*Pregunto si vencio timer del refresco del display*/
	if(timer_events & ((uint8_t)0x01 << 0))
	{
		/*Borro bit indicador de evento y activo flag correspondiente*/
		timer_events &= ~(0x01 << 0);
		flag_timerDisplay = ON;
	}

	/*Pregunto si vencio timer para el envío de temperatura por UART*/
	if(timer_events & ((uint8_t)0x01 << 1))
	{
		timer_events &= ~(0x01 << 1);
		TRANSMIT_TEMP = ON;
	}

	/*Pregunto si vencio timer para el envío de humedad por UART*/
	if(timer_events & ((uint8_t)0x01 << 2))
	{
		timer_events &= ~(0x01 << 2);
		TRANSMIT_H = ON;
	}

	/*Pregunto si vencio timer para el envío de nivel de agua por UART*/
	if(timer_events & ((uint8_t)0x01 << 3))
	{
		timer_events &= ~(0x01 << 3);
		TRANSMIT_H2O = ON;
	}

	/*Pregunto si vencio timer para la rececpcion de un ack por UART*/
	if(timer_events & ((uint8_t)0x01 << 4))
	{
		timer_events &= ~(0x01 << 4);
		EXPIRED_ACK = ON;
	}

	/*Pregunto si vencio timer para el riego de la maceta*/
	if(timer_events & ((uint8_t)0x01 << 5))
	{
		timer_events &= ~(0x01 << 5);
		timer_Riego = ON;
	}

	/*Pregunto si vencio timer para la alarma por nivel bajo de agua*/
	if(timer_events & ((uint8_t)0x01 << 6))
	{
		timer_events &= ~(0x01 << 6);
		timer_h2o = ON;
	}

}

void initTimers()
{
	/* Inicializacion de timer de refresco de display
	 * En principio, este es el unico timer que se va a utilizar*/
	/*Refresco de pantalla cada 5 segundos*/
	TimerStart(TIMER_EV_DISPLAY, 50);
}

void TimerStop(uint8_t ev)
{
	SYSTICK_PUNT->STCTRL &= ~(0x01 << 1); //TINCKINT OFF
	timer_vector[ev] = 0;
	timer_events &= ~((uint8_t)0x01 << ev);
	SYSTICK_PUNT->STCTRL |= (0x01 << 1); //TINCKINT ON
}

void TimerStart(uint8_t ev, uint8_t time)
{
	SYSTICK_PUNT->STCTRL &= ~(0x01 << 1); //TINCKINT OFF
	timer_vector[ev] = time;
	/*Si el tiempo es distinto de 0, borro flag de evento
	 * Si el tiempo es igual a 0, entonces activo el flag de evento*/
	if(time)
		timer_events &= ~((uint8_t)0x01 << ev);
	else
		timer_events |= ((uint8_t)0x01 << ev);

	SYSTICK_PUNT->STCTRL |= (0x01 << 1); //TINCKINT ON
}

void TimerClose(void)
{
	uint8_t i;
	SYSTICK_PUNT->STCTRL &= ~(0x01 << 1); //TINCKINT OFF

	for(i = 0; i < TIMERS_CANT; i++)
	{
		timer_vector[i] = 0;
	}

	timer_events = 0;
	SYSTICK_PUNT->STCTRL |= (0x01 << 1); //TINCKINT ON
}

/*Funcion que decrementa timers. Si algun timer llego a 0, activa su flag en timer_events.*/
void AnalizarTimer(void)
{
	uint8_t i;

	for(i = 0; i < TIMERS_CANT; i++)
	{
		if(timer_vector[i])
		{
			timer_vector[i]--;

			if(!timer_vector[i])
			{
				timer_events |= ((uint8_t)1 << i);
			}
		}
	}
}
