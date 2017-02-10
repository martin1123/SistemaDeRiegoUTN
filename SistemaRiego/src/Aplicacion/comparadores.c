/**
	\file comparadores.c
	\brief Funciones verificadoras de humedad y nivel de agua estable
	\details Funciones que verifican a través de lógica difusa si el humedad de las macetas
	         es bajo o estable, asi como tambien el nivel de agua en el tanque.
	\author Grupo II, curso R2053
	\version 1.0.0
*/

#include "infotronic.h"

/*acceptable_moisture() determina si la humedad
 * es aceptable. EN caso de no serlo se procede a regar*/
uint8_t acceptable_moisture(uint8_t h)
{
	return h > umbral_humedad;
}

/*acceptable_level() determina si el nivel de agua
 * es aceptable. EN caso de no serlo se procede a activar alarma*/
uint8_t acceptable_level(uint8_t level)
{
	return level > umbral_H2O;
}
