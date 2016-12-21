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
	int result;
	if((result = getSensorValue(AD0DR1)))
	{
		return convertToTemp(result);
	}

	return t;
}

uint8_t getHumedad(uint8_t h)
{
	uint16_t result;
	if((result = getSensorValue(AD0DR2)))
	{
		return convertToHum(result);
	}

	return h;
}

uint8_t getlvlH2O(uint8_t lvl)
{
	int result;
	if((result = getSensorValue(AD0DR5)))
	{
		return convertToLvlH2O(result);
	}

	return lvl;
}

int convertToTemp(int n)
{
	  long Resistance;
	  double Temp;

	  // Assuming a 10k Thermistor.  Calculation is actually: Resistance = (1024/ADC)
	  Resistance=((10240000/n) - 10000);

	  /******************************************************************/
	  /* Utilizes the Steinhart-Hart Thermistor Equation:				*/
	  /*    Temperature in Kelvin = 1 / {A + B[ln(R)] + C[ln(R)]^3}		*/
	  /*    where A = 0.001129148, B = 0.000234125 and C = 8.76741E-08	*/
	  /******************************************************************/
	  Temp = log(Resistance);
	  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
	  Temp = Temp - 273.15;  // Convert Kelvin to Celsius

	  return (int)Temp;  // Return the Temperature
}

uint8_t convertToHum(uint16_t n)
{
	//Ver como convertir humedad. Si es lineal o exponencial
	return 1;
}

uint8_t convertToLvlH2O(uint16_t n)
{
	//Supone que es una conversión lineal. Un valor de 4095 es un 100%
	return (uint8_t)(n*100/4095);
}
