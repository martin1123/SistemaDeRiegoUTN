/**
	\file rtc.h
	\brief Declaracion dec funciones y registros del RTC
	\details
	\author Grupo II, curso R2053
	\version 1.0.0
*/

#ifndef HEADERS_RTC_H_
#define HEADERS_RTC_H_

#define RTC ((registro_t *) 0x40024000UL)

/*Interrupciones*/
#define RTCILR         RTC[0]

#define RTCCCR         RTC[2]

/*Registro de activacion de interrupciones por incremento de contador*/
#define RTCCIIR        RTC[3]

/*Registro de activacion de alarmas*/
#define RTCARM         RTC[4]

#define RTC_AUX        RTC[23]
#define RTC_AUXEN      RTC[22]
#define RTCCTIME0      RTC[5]
#define RTCCTIME1      RTC[6]
#define RTCCTIME2      RTC[7

/*Registros con valores de fecha y hora*/
#define RTCSEC         RTC[8] //Segundos
#define RTCMIN         RTC[9] //Minutos
#define RTCHOUR        RTC[10] //Horas
#define RTCDOM         RTC[11] //Dia del mes de 1 a 31
#define RTCDOW         RTC[12] //Dia de la semana de 0 a 6
#define RTCDOY         RTC[13] //Dia del año, de 1 a 365 o 366 en años bisisestos
#define RTCMONTH       RTC[14] //Numero del mes de 1 a 12
#define RTCYEAR        RTC[15] //Año de 0 a 4095

/*Registro de calibracion*/
#define RTCCALIBRATION RTC[16]

#define BACKUP_FLAG    0x56    //Valor que define si hay valores a restaurar en los registros de backup cuando se inicia el programa

/*Registros de backup GPREG*/
#define RTCGPREG0      RTC[17] //Bandera. Si su valor es 0x56 ('V'), significa que hay registros guardados como backup
#define RTCGPREG1      RTC[18] //Umbral minimo de agua
#define RTCGPREG2      RTC[19] //Umbral de humedad
#define RTCGPREG3      RTC[20] //Umbral temperatura
#define RTCGPREG4      RTC[21] //Tiempo de riego

/*Registros de alarmas*/
#define RTCALSEC       RTC[24]
#define RTCALMIN       RTC[25]
#define RTCALHOUR      RTC[26]
#define RTCALDOM       RTC[27]
#define RTCALDOW       RTC[28]
#define RTCALDOY       RTC[29]
#define RTCALMON       RTC[30]
#define RTCALYEAR      RTC[31]

#define PCRTC 9

void init_rtc(void);

void config_date_RTC(uint8_t ss, uint8_t mm, uint8_t hh, uint8_t dd, uint8_t mo, uint16_t yy);

#endif /* HEADERS_RTC_H_ */
