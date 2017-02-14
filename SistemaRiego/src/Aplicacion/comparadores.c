/**
	\file comparadores.c
	\brief Funciones verificadoras de humedad y nivel de agua estable
	\details Funciones que verifican si la humedad de las macetas
	         es bajo o estable, asi como tambien el nivel de agua en el tanque.
	\author Grupo II, curso R2053
	\version 1.0.0
*/

#include "infotronic.h"


uint8_t acceptable_moisture(uint8_t h)
{
	return h > umbral_humedad;
}

uint8_t acceptable_level(uint8_t level)
{
	return level > umbral_H2O;
}
