/**
	\file comparadores.c
	\brief Funciones verificadoras de humedad y nivel de agua estable
	\details Funciones que verifican a través de lógica difusa si el humedad de las macetas
	         es bajo o estable, asi como tambien el nivel de agua en el tanque.
	\author Grupo II, curso R2053
	\version 1.0.0
*/

#include "infotronic.h"

/*acceptable_moisture() mediante logica difusa determina si la humedad
	 * es aceptable. EN caso de no serlo se procede a regar*/
	/*NOTA A BORRAR: Para deerminar una humedad aceptable se va a tomar como base
	 * no solo el nivel de humedad, sino tmb el tiempo que haya pasado desde el ulitmo regado,
	 * ya que puede pasar que la humedad luego de un regado no se actualice a el valor correcto
	 * sino hasta esperar un tiempo razonable en el que el agua se distribuya en la tierra.*/
uint8_t acceptable_moisture(uint8_t h)
{
	return h > 49;
}

/*acceptable_level() mediante logica difusa determina si el nivel de agua
 * es aceptable. EN caso de no serlo se procede a activar alarma*/
uint8_t acceptable_level(uint8_t level)
{
	return lvlH2O > 10;
}
