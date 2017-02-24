/**
	\file AlarmMachine.c
	\brief Maquina de estados de alarma
	\details Alarma que se activa cuando flag_alarm es ON.
	\author Grupo II, curso R2053
	\version 1.0.0
*/
#include "infotronic.h"

/*MAV: Machine Alarm Vector*/
void (*MAV[])(void) = {alarmOff,alarmBeep};

/*Variable que indica estado*/
enum alarmStates aState = ALARM_OFF;

/**
	\fn void Alarm_Machine(void)
	\brief Funcion de entrada a la máquina de estados de la alarma

	\details Esta funcion utiliza un array de punteros a funcion que determina el estado de la máquina
	         que se debe ejecutar.

	\param [in]
	\param [out]

	\return void

	\author Grupo II, curso R2053

	\version 1.0.0
*/
void Alarm_Machine(void)
{
	MAV[aState]();
}

/**
	\fn void alarmOff(void)
	\brief Estado de alarma apagada

	\details En este estado, se analiza si el flag_alarm esta activado. Mientras este desactivado
	         la máquina se va a mantener en el mismo estado sin realizar ninguna acción. En caso
	         de estar activado se pasa al estado alarmBeep.

	\return void

	\author Grupo II, curso R2053

	\version 1.0.0
*/
void alarmOff(void)
{
	if(flag_alarm)
	{
		aState = ALARM_BEEP;
		TimerStart(TIMER_EV_H2O_ALARM,1);
		write_pin(BUZZ_PORT,BUZZ_PIN,BUZZ_ON);
	}
}

/**
	\fn void alarmBeep(void)
	\brief Estado de alarma encendida

	\details En este estado, se analiza si el flag_alarm se desactiva. Mientras este activado dicho flag
	         va a sonar una alarma. Una vez que se encuentre el flag desactivado, se apaga la alarma y se pasa al estado alarmOff

	\return void

	\author Grupo II, curso R2053

	\version 1.0.0
*/
void alarmBeep(void)
{
	static uint8_t beep = 3;
	static flagST_t sound = ON;

	if(!flag_alarm){
		aState = ALARM_OFF;
		beep = 3;
		sound = ON;
		write_pin(BUZZ_PORT,BUZZ_PIN,BUZZ_OFF);
		return;
	}

	if(timer_h2o)
	{
		timer_h2o = OFF;

		if(sound == ON)
		{
			beep--;
			sound = OFF;
			write_pin(BUZZ_PORT,BUZZ_PIN,BUZZ_OFF);
		}
		else
		{
			sound = ON;
			write_pin(BUZZ_PORT,BUZZ_PIN,BUZZ_ON);
		}

		if(!beep)
		{
			beep = 3;
			TimerStart(TIMER_EV_H2O_ALARM,15);
		}
		else
		{
			TimerStart(TIMER_EV_H2O_ALARM,1);
		}
	}

}
