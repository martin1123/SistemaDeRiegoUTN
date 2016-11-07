/*
 * rtc.c
 *
 *  Created on: 29 de oct. de 2016
 *      Author: hisoka
 */
#include "infotronic.h"

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
