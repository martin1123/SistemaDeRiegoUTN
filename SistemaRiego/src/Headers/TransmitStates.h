/*
 * TransmitStates.h
 *
 *  Created on: 21 de nov. de 2016
 *      Author: Martin
 */

#ifndef HEADERS_TRANSMITSTATES_H_
#define HEADERS_TRANSMITSTATES_H_

#define BUFF_TRAMA_SZ 16

enum transmitState{STATE_NO_TRANS,STATE_TRANS_DATA,STATE_TRANS_ACK,STATE_TRANS_CONFIRM}; //Respetar orden del vector TMV del fuente TransmitStates
enum transmitData{NO_DATA, TRANS_TEMP, TRANS_HUM, TRANS_LVLH2O, TRANS_REG,TRANS_ACK};

void Transmit_Machine(void);
void no_transmit(void);
void transmit_data(void);
void transmitAck(void);
void confirmTransmission(void);



#endif /* HEADERS_TRANSMITSTATES_H_ */
