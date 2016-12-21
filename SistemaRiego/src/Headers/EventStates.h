/**
	\file EventStates.h
	\brief Header de la maquina de estado de eventos
	\details
	\author Grupo II, curso R2053
	\version 1.0.0
*/

#ifndef HEADERS_EVENTSTATES_H_
#define HEADERS_EVENTSTATES_H_
#include "types.h"

void Event_Machine(void);
void no_event(void);
void regando(void);
void sinAgua(void);
void activarRiego(uint8_t t);
void desactivarRiego(void);
void activarAlarmaH2O(void);
void desactivarAlarmaH2O(void);
void encenderRegado(void);
void apagarRegado(void);

enum eventStates{NO_EVENT,REGAR,ALARMA_H2O};

#endif /* HEADERS_EVENTSTATES_H_ */
