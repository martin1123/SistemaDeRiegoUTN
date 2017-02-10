/**
	\file rtc.c
	\brief Drivers RTC
	\details
	\author Grupo II, curso R2053
	\version 1.0.0
*/
#include "infotronic.h"

void init_rtc(void)
{

	RTCCCR = 0x01UL; //Se habilita clock
	RTCCIIR &= ~(0xFFUL); //No se generan interrupciones
	RTCARM |= 0xFFUL; //Inicialmente no se utiliza la alarma
	//ISER0  |= (1 << 17); //Se habilita interrupcion del RTC
	PCONP |= (1 << PCRTC); //Se alimenta periferico

	//Se verifica si hay valores a restaurar en los registros de backup
	if(RTCGPREG0 == BACKUP_FLAG){
		umbral_H2O = RTCGPREG1; // reestablece umbral del nivel de agua minimo
	    umbral_temp = RTCGPREG2; // reestablece umbral del nivel de humedad minimo
		umbral_humedad = RTCGPREG3; // reestablece umbral del nivel de temperatura maximo
		timer_regado = RTCGPREG4;// reestablece el tiempo de regado
	}else{
		//Si es la primera vez, se setea la bandera, y se guardan valores por defecto en los registros de backup
		RTCGPREG0 = BACKUP_FLAG;
		RTCGPREG1 = 15; //Setea umbral de agua minimo con 15%
		RTCGPREG2 = 45; //Setea umbral de humedad minimo con 45%
		RTCGPREG3 = 45; //Setea umbral de temperatura maximo con 45°C
		RTCGPREG4 = 5;  //Setea tiempo de regado con 5 segundos
	}
}

void config_date_RTC(uint8_t ss, uint8_t mm, uint8_t hh, uint8_t dd, uint8_t mo, uint16_t yy)
{
	RTCSEC   = ss;
	RTCMIN   = mm;
	RTCHOUR  = hh;
	RTCDOM   = dd;
	RTCMONTH = mo;
	RTCYEAR  = yy;
}

void RTC_IRQHandler(void)
{
}
