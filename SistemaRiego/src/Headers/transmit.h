/*
 * transmit.h
 *
 *  Created on: 21 de nov. de 2016
 *      Author: Martin
 */

#ifndef HEADERS_TRANSMIT_H_
#define HEADERS_TRANSMIT_H_

enum transmitState{NO_TRANS,TRANS_TEMP,TRANS_HUM,TRANS_LVLH2O,TRANS_ACK};

void Transmit_Machine(void);
void no_transmit(void);
void transmitTemp(void);
void transmitHum(void);
void transmitLvlH2O(void);
void transmitRegando(void);
void transmitAck(void);

#endif /* HEADERS_TRANSMIT_H_ */
