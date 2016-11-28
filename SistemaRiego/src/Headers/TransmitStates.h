/*
 * TransmitStates.h
 *
 *  Created on: 21 de nov. de 2016
 *      Author: Martin
 */

#ifndef HEADERS_TRANSMITSTATES_H_
#define HEADERS_TRANSMITSTATES_H_

#define BUFF_TRAMA_SZ 16

enum transmitState{NO_TRANS,TRANS_TEMP,TRANS_HUM,TRANS_LVLH2O,TRANS_REG,TRANS_ACK,TRANS_CONFIRM};

void Transmit_Machine(void);
void no_transmit(void);
void transmitTemp(void);
void transmitHum(void);
void transmitLvlH2O(void);
void transmitRegando(void);
void transmitAck(void);
void confirmTransmission(void);



#endif /* HEADERS_TRANSMITSTATES_H_ */
