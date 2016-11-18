/*
 * sensors.c
 *
 *  Created on: 18 de nov. de 2016
 *      Author: mmaccio
 */
#include "infotronic.h"
#include "sensors.h"

short getTemp(short t)
{
	uint16_t result;
	if(result = sensorTemp())
	{
		return convertToTemp(result);
	}

	return t;
}

uint8_t getHumedad(uint8_t h)
{
	uint16_t result;
	if(result = sensorHum())
	{
		return convertToHum(result);
	}

	return h;
}

uint8_t getlvlH2O(uint8_t lvl)
{
	uint16_t result;
	if(result = sensorlvlH2O())
	{
		return convertToLvlH2O(result);
	}

	return lvl;
}
