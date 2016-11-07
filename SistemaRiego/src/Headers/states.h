/*
 * states.h
 *
 *  Created on: 13 de oct. de 2016
 *      Author: Martin
 *
 *  Declaración de los estados en los que se puede encontrar el sistema
 */

#ifndef HEADERS_STATES_H_
#define HEADERS_STATES_H_

/*Estados de la bandera state_flag*/
typedef enum{INICIAR = 0, REPOSO, GET_HYT, GET_HYT_AMB, GET_H2O_LEVEL, REGAR, SIN_AGUA, INF_UART} STATES_T;


/*Estados del sistema*/
void inicializar(void);
void reposo(void);
void obtenerHyTMaceta(void);
void obtenerHyTAmb(void);
void obtenerNivH2O(void);
void regar(void);
void alertaAgua(void);
void informarUART(void);

#endif /* HEADERS_STATES_H_ */
