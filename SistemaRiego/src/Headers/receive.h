/*
 * receive.h
 *
 *  Created on: 1 de dic. de 2016
 *      Author: Martin
 */

#ifndef HEADERS_RECEIVE_H_
#define HEADERS_RECEIVE_H_

#include "types.h"

int recepcionOk(uint8_t * trama, uint8_t size_trama);
void recuperarDato(uint8_t * trama, uint8_t size_datos);

#endif /* HEADERS_RECEIVE_H_ */
