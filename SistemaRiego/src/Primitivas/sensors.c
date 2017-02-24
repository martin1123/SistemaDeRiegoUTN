/**
	\file sensors.c
	\brief Primitivas de los sensores de humedad, temperatura, y nivel.
	\details
	\author Grupo II, curso R2053
	\version 1.0.0
*/
#include "infotronic.h"
#include "sensors.h"
#include <math.h>

int getTemp(int t)
{
	static int result = 0;
	if((result = getSensorValue(AD0DR1,result)))
	{
		return convertToTemp(result);
	}

	return t;
}

uint8_t getHumedad(uint8_t h)
{
	static int result = 0;
	if((result = getSensorValue(AD0DR2,result)))
	{
		return convertToHum(result);
	}

	return h;
}

uint8_t getlvlH2O(uint8_t lvl)
{
	static int result = 0;
	if((result = getSensorValue(AD0DR5, result)))
	{
		return convertToLvlH2O(result);
	}

	return lvl;
}

int convertToTemp(int n)
{
	float Rtherm, Temp;

    Rtherm = 10000 / (4096 / n - 1.0);

    Temp = (1.0 / (log(Rtherm/10000)/4050)+(1.0/298.15)) - 273.15;

    return (int)Temp;  // Return the Temperature

}

uint8_t convertToHum(int n)
{
	//0 es un 100% de humedad y 4095 es un 0% de humedad
	n = 4095 - n;

	return (uint8_t)(n*100/4095);
}

uint8_t convertToLvlH2O(uint16_t n)
{
	//Supone que es una conversión lineal. Un valor de 4095 es un 100%
	return (uint8_t)(n*100/4095)*2;
}
