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
