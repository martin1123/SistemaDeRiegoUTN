/**
	\file infotronic.h
	\brief Header general
	\details Este header provee el acceso a las funciones, registros,
	         y  variables globales del sistema de riego.
	\author Grupo II, curso R2053
	\version 1.0.0
*/

#ifndef __INFOTRONIC__
#define __INFOTRONIC__

#include "TransmitStates.h"
#include "ClockAndPll.h"
#include "types.h"
#include "gpio.h"
#include "systick.h"
#include "pinConf.h"
#include "uart1.h"
#include "serial.h"
#include "rtc.h"
#include "timers.h"
#include "sensors.h"
#include "DisplayStates.h"
#include "lcd.h"
#include "EventStates.h"
#include "Commands.h"
#include "transmision.h"
#include "receive.h"
#include "Receive_states.h"
#include "waterPump.h"
#include "uart0.h"
#include "Alarm.h"

//Humedad tierra
extern volatile uint8_t humedad;

//Temperatura ambiente
extern volatile short temp;

//Nivel de agua en tanque
extern volatile uint8_t lvlH2O;

//Porcentaje de nivel de agua en tanque
extern volatile flagST_t flag_H2OBajo;
extern volatile flagST_t flag_regar;
extern volatile flagST_t flag_timerDisplay;
extern volatile flagST_t timer_temp;
extern volatile flagST_t timer_humedad;
extern volatile flagST_t timer_h2o;
extern volatile flagST_t timer_RiegoFinalizado;
extern volatile flagST_t f_UARTRx_cHora;
extern volatile flagST_t f_UARTRx_regar;
extern volatile flagST_t f_UARTRx_cAlarma;
extern volatile flagST_t f_UARTRx_config;
extern volatile flagST_t TRANSMIT_H;
extern volatile flagST_t TRANSMIT_TEMP;
extern volatile flagST_t TRANSMIT_H2O;
extern volatile flagST_t TRANSMIT_UMBRAL_H2O;
extern volatile flagST_t TRANSMIT_UMBRAL_HUM;
extern volatile flagST_t TRANSMIT_UMBRAL_TEMP;
extern volatile flagST_t TRANSMIT_TIME_REGADO;
extern volatile flagST_t UART_STATUS;
extern volatile flagST_t TRANSMIT_ACK;
extern volatile flagST_t EXPIRED_ACK;
extern volatile flagST_t RECEIVED_ACK;
extern volatile uint8_t timer_events;
extern volatile uint8_t timer_vector[];
extern volatile uint8_t timer_regado;
extern volatile flagST_t flag_alarm;
extern volatile uint8_t bufferTxEmpty;
extern volatile uint8_t bufferRxEmpty;
extern volatile uint8_t bufferTxFull;
extern volatile uint8_t bufferRxFull;
extern volatile uint8_t  umbral_H2O;
extern volatile uint8_t  umbral_temp;
extern volatile uint8_t  umbral_humedad;

#define 	PCONP	(* ( ( registro_t  * ) 0x400FC0C4UL ))

#define		PCLKSEL		( ( registro_t  * ) 0x400FC1A8UL )
//!< Registros PCLKSEL
#define		PCLKSEL0	PCLKSEL[0]
#define		PCLKSEL1	PCLKSEL[1]

#define     ISER                   ( ( registro_t  * )  0xE000E100UL )
#define     ISER0     ISER[0]

#define     ICPR                   ( ( registro_t  * )  0xE000E280UL )
#define     ICPR0     ICPR[0]

#define SALIDA 1
#define ENTRADA 0


/**
	\fn uint8_t acceptable_level(uint8_t level)
	\brief Funcion que indica si el nivel de H2O en el tanque es suficiente.

	\details En caso de haber poco nivel de agua, la funcion retorna 0 para activar una alarma que indique
	         que se debe llenar el tanque.

	\param [in] uint8_t level

	\return uint8_t

	\author Grupo II, curso R2053

	\version 1.0.0
*/
uint8_t acceptable_level(uint8_t level);


/**
	\fn uint8_t acceptable_moisture(uint8_t h)
	\brief Funcion que indica si el nivel de humedad en la maceta es estable o si ha poca humedad.

	\details En caso de haber poca humedad, la funcion retorna 0 para activar el riego automatico.

	\param [in] uint8_t level

	\return uint8_t

	\author Grupo II, curso R2053

	\version 1.0.0
*/
uint8_t acceptable_moisture(uint8_t h);

#endif
