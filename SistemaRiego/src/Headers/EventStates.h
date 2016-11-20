/*
 * EventStates.h
 *
 *  Created on: 18 de nov. de 2016
 *      Author: mmaccio
 */

#ifndef HEADERS_EVENTSTATES_H_
#define HEADERS_EVENTSTATES_H_

void Event_Machine(void);
void no_event(void);
void regando(void);
void sinAgua(void);
void activarRiego(void);
void desactivarRiego(void);
void activarAlarmaH2O(void);
void desactivarAlarmaH2O(void);
void encenderRegado(void);
void apagarRegado(void);

enum eventStates{NO_EVENT,REGAR,ALARMA_H2O};

#endif /* HEADERS_EVENTSTATES_H_ */
