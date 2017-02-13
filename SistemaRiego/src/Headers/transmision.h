/**
	\file transmision.h
	\brief Declaracion de funciones para la transmision de datos
	\details
	\author Grupo II, curso R2053
	\version 1.0.0
*/

#ifndef HEADERS_TRANSMISION_H_
#define HEADERS_TRANSMISION_H_

uint8_t isEnabledUART();
uint8_t armarTrama(uint8_t *trama, enum transmitData s);
uint8_t calc_checksum(uint8_t * dato, uint8_t size);
void transmitir (uint8_t *p, uint8_t sz);

#endif /* HEADERS_TRANSMISION_H_ */
