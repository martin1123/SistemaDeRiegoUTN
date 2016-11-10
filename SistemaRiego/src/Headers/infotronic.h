#ifndef __INFOTRONIC__
#define __INFOTRONIC__

#include "types.h"
#include "gpio.h"
#include "systick.h"
#include "states.h"
#include "pinConf.h"
#include "uart1.h"
#include "serial.h"
#include "rtc.h"
#include "SysIni.h"
#include "timers.h"

//Humedad tierra
extern volatile float humedad;

//Temperatura ambiente
extern volatile float temp;

//Porcentaje de nivel de agua en tanque
extern volatile uint8_t lvlH2O;
extern STATES_T state_flag;
extern volatile flagST_t timer_temp;
extern volatile flagST_t timer_humedad;
extern volatile flagST_t timer_h2o;
extern volatile flagST_t timer_Riego;
extern volatile flagST_t f_UARTRx_cHora;
extern volatile flagST_t f_UARTRx_regar;
extern volatile flagST_t f_UARTRx_cAlarma;
extern volatile flagST_t f_UARTRx_config;
extern volatile flagST_t TRANSMIT_H;
extern volatile flagST_t TRANSMIT_TEMP;
extern volatile flagST_t TRANSMIT_H2O;
extern volatile flagST_t UART_STATUS;


#define 	PCONP	(* ( ( registro_t  * ) 0x400FC0C4UL ))

#define		PCLKSEL		( ( registro_t  * ) 0x400FC1A8UL )
//!< Registros PCLKSEL
#define		PCLKSEL0	PCLKSEL[0]
#define		PCLKSEL1	PCLKSEL[1]

#define     ISER0                   (*( ( registro_t  * )  0xE000E100UL ))

uint8_t isEnabledUART();
uint8_t acceptable_level(uint8_t level);

#endif
