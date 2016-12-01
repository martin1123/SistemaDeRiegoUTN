/*
 * Receive.h
 *
 *  Created on: 21 de nov. de 2016
 *      Author: Martin
 */

#ifndef HEADERS_RECEIVE_STATES_H_
#define HEADERS_RECEIVE_STATES_H_

void Receive_Machine(void);
void Receive_Reposo(void);
void Receiving(void);

enum receiveState{R_REPOSO, R_RECEIVING};

#endif /* HEADERS_RECEIVE_STATES_H_ */
