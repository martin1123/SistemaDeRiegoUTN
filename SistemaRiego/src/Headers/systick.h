/*
 * systick.h
 *
 *  Created on: 13 de oct. de 2016
 *      Author: Martin
 *
 *  Registro y declaracion de funciones del systick
 */

#ifndef HEADERS_SYSTICK_H_
#define HEADERS_SYSTICK_H_

typedef struct{
	volatile uint32_t STCTRL;
	volatile uint32_t STRELOAD;
	volatile uint32_t STCURR;
	volatile uint32_t STCALIB;
}SYSTICK_T;

/*Puntero a registro SYSTICK*/
#define SYSTICK_PUNT ((SYSTICK_T *) 0xE000E010)

void init_systick();

#endif /* HEADERS_SYSTICK_H_ */
