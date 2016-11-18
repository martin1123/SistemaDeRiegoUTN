/*
 * sensors_drivers.c
 *
 *  Created on: 18 de nov. de 2016
 *      Author: mmaccio
 */

#include "infotronic.h"
#include "sensors.h"

uint16_t sensorTemp()
{
	if ( ADC_DONE (AD0DR1) ) //Verifico temp
	    return ADC1_VAL;

	return NO_VALUE;
}

uint16_t sensorHum()
{
	if ( ADC_DONE (AD0DR2) ) //Verifico Humedad
	    return ADC2_VAL;

	return NO_VALUE;
}

uint16_t sensorlvlH2O()
{
	if ( ADC_DONE (AD0DR3) ) //Verifico nivel H2O
	    return ADC3_VAL;

	return NO_VALUE;
}
