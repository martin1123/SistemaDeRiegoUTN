/*
 * transmision.h
 *
 *  Created on: 28 de nov. de 2016
 *      Author: Martin
 */

#ifndef HEADERS_TRANSMISION_H_
#define HEADERS_TRANSMISION_H_

uint8_t isEnabledUART();
uint8_t armarTrama(uint8_t *trama, uint8_t sz, enum transmitState);
uint8_t calc_checksum(uint8_t * dato, uint8_t size);
uint8_t acceptable_level(uint8_t level);
void transmitir (char *p);

#endif /* HEADERS_TRANSMISION_H_ */
