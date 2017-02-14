/*
 * Alarm.h
 *
 *  Created on: 17/12/2016
 *      Author: Martin
 */

#ifndef HEADERS_ALARM_H_
#define HEADERS_ALARM_H_

#define BUZZ_PORT  0
#define BUZZ_PIN  28
#define BUZZ_ON    0
#define BUZZ_OFF   1

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
void Alarm_Machine(void);


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
void alarmOff(void);


/**
	\fn void alarmBeep(void)
	\brief Estado de alarma encendida

	\details En este estado, se analiza si el flag_alarm se desactiva. Mientras este activado dicho flag
	         va a sonar una alarma. Una vez que se encuentre el flag desactivado, se apaga la alarma y se pasa al estado alarmOff

	\return void

	\author Grupo II, curso R2053

	\version 1.0.0
*/
void alarmBeep(void);

/*Enumeracion con los estados de la maquina de estados de la alarma*/
enum alarmStates{ALARM_OFF,ALARM_BEEP};

#endif /* HEADERS_ALARM_H_ */
