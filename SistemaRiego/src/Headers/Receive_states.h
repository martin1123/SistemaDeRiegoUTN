/**
	\file Receive_states.h
	\brief Header de maquina de recepcion de datos
	\details
	\author Grupo II, curso R2053
	\version 1.0.0
*/

#ifndef HEADERS_RECEIVE_STATES_H_
#define HEADERS_RECEIVE_STATES_H_

void Receive_Machine(void);
void Receive_Reposo(void);
void Receiving(void);

enum receiveState{R_REPOSO, R_RECEIVING};

#endif /* HEADERS_RECEIVE_STATES_H_ */
