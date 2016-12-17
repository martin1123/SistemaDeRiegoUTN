/*
 * AlarmMachine.c
 *
 *  Created on: 17/12/2016
 *      Author: Martin
 */
#include "infotronic.h"

/*MAV: Machine Alarm Vector*/
void (*MAV[])(void) = {alarmOff,alarmBeep};

/*Variable que indica estado*/
enum alarmStates aState = ALARM_OFF;

void Alarm_Machine(void)
{
	MAV[aState]();
}

void alarmOff(void)
{
	if(flag_alarm)
	{
		aState = ALARM_BEEP;
		TimerStart(TIMER_EV_H2O_ALARM,1);
		write_pin(BUZZ_PORT,BUZZ_PIN,BUZZ_ON);
	}
}

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
