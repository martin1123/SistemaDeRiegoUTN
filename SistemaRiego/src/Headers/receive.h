/**
	\file receive.h
	\brief Header de funciones de recepcion de datos
	\details
	\author Grupo II, curso R2053
	\version 1.0.0
*/

#ifndef HEADERS_RECEIVE_H_
#define HEADERS_RECEIVE_H_

#include "types.h"

uint8_t verificarComando(uint8_t * trama, uint8_t size_datos, uint8_t *cpos, uint8_t *scpos);
void executeCommand(uint8_t comm_pos, uint8_t scomm_pos);
void config(uint8_t scomm_pos);

#endif /* HEADERS_RECEIVE_H_ */
