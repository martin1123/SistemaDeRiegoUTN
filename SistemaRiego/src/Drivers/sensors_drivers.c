/**
	\file sensors_drivers.c
	\brief Drivers de los sensores de temperatura, nivel, y humedad.
	\details Estos drivers se encargan de obtener por una entrada ADC,
	         la informacion de los sensores del sistema.
	\author Grupo II, curso R2053
	\version 1.0.0
*/

#include "infotronic.h"
#include "sensors.h"

void InitSensores()
{
	//Configuracion de los sensores
	conf_gpio(PORT_NTC,PIN_NTC,IN);
	conf_gpio(PORT_H2O,PIN_H2O,IN);
	conf_gpio(PORT_HUM,PIN_HUM,IN);
	setPinMode(PORT_NTC,PIN_NTC,PULL_UP);
	setPinMode(PORT_H2O,PIN_H2O,PULL_UP);
	setPinMode(PORT_HUM,PIN_HUM,PULL_UP);
}

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
