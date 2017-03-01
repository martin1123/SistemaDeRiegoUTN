/**
	\file comparadores.c
	\brief Funciones verificadoras de humedad y nivel de agua estable
	\details Funciones que verifican si la humedad de las macetas
	         es bajo o estable, asi como tambien el nivel de agua en el tanque.
	\author Grupo II, curso R2053
	\version 1.0.0
*/

#include "infotronic.h"

/**
	\fn uint8_t acceptable_moisture(uint8_t h)
	\brief Funcion que indica si el nivel de humedad en la maceta es estable o si ha poca humedad.

	\details En caso de haber poca humedad, la funcion retorna 0 para activar el riego automatico.

	\param [in] uint8_t level

	\return uint8_t

	\author Grupo II, curso R2053

	\version 1.0.0
*/
uint8_t acceptable_moisture(uint8_t h)
{
	return h > umbral_humedad;
}

/**
	\fn uint8_t acceptable_level(uint8_t level)
	\brief Funcion que indica si el nivel de H2O en el tanque es suficiente.

	\details En caso de haber poco nivel de agua, la funcion retorna 0 para activar una alarma que indique
	         que se debe llenar el tanque.

	\param [in] uint8_t level

	\return uint8_t

	\author Grupo II, curso R2053

	\version 1.0.0
*/
uint8_t acceptable_level(uint8_t level)
{
	return level > umbral_H2O;
}
