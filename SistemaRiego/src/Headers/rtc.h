/*
 * rtc.h
 *
 *  Created on: 27 de oct. de 2016
 *      Author: Martin
 */

#ifndef HEADERS_RTC_H_
#define HEADERS_RTC_H_

#define RTC ((registro_t *) 0x40024000UL)

/*Interrupciones*/
#define RTCILR         RTC[0].dword

#define RTCCCR         RTC[2].dword

/*Registro de activacion de interrupciones por incremento de contador*/
#define RTCCIIR        RTC[3].dword

/*Registro de activacion de alarmas*/
#define RTCARM         RTC[4].dword

#define RTC_AUX        RTC[23].dword
#define RTC_AUXEN      RTC[22].dword
#define RTCCTIME0      RTC[5].dword
#define RTCCTIME1      RTC[6].dword
#define RTCCTIME2      RTC[7].dword

/*Registros con valores de fecha y hora*/
#define RTCSEC         RTC[8].dword //Segundos
#define RTCMIN         RTC[9].dword //Minutos
#define RTCHOUR        RTC[10].dword //Horas
#define RTCDOM         RTC[11].dword //Dia del mes de 1 a 31
#define RTCDOW         RTC[12].dword //Dia de la semana de 0 a 6
#define RTCDOY         RTC[13].dword //Dia del año, de 1 a 365 o 366 en años bisisestos
#define RTCMONTH       RTC[14].dword //Numero del mes de 1 a 12
#define RTCYEAR        RTC[15].dword //Año de 0 a 4095

/*Registro de calibracion*/
#define RTCCALIBRATION RTC[16].dword

/*Registros de backup GPREG*/
#define RTCGPREG0      RTC[17].dword
#define RTCGPREG1      RTC[18].dword
#define RTCGPREG2      RTC[19].dword
#define RTCGPREG3      RTC[20].dword
#define RTCGPREG4      RTC[21].dword

/*Registros de alarmas*/
#define RTCALSEC       RTC[24].dword
#define RTCALMIN       RTC[25].dword
#define RTCALHOUR      RTC[26].dword
#define RTCALDOM       RTC[27].dword
#define RTCALDOW       RTC[28].dword
#define RTCALDOY       RTC[29].dword
#define RTCALMON       RTC[30].dword
#define RTCALYEAR      RTC[31].dword

#endif /* HEADERS_RTC_H_ */
