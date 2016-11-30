/*
 * transmision.h
 *
 *  Created on: 28 de nov. de 2016
 *      Author: Martin
 */

#ifndef HEADERS_TRANSMISION_H_
#define HEADERS_TRANSMISION_H_

uint8_t isEnabledUART();
uint8_t armarTrama(uint8_t *trama, enum transmitData s);
uint8_t calc_checksum(uint8_t * dato, uint8_t size);
uint8_t acceptable_level(uint8_t level);
void transmitir (uint8_t *p);

#endif /* HEADERS_TRANSMISION_H_ */
