/*
 * SysIni.h
 *
 *  Created on: 7 de nov. de 2016
 *      Author: Martin
 */

#ifndef HEADERS_SYSINI_H_
#define HEADERS_SYSINI_H_

void init_systick();

void init_rtc(uint8_t ss, uint8_t mm, uint8_t hh, uint8_t dd, uint8_t mo, uint16_t yy);

void InitPLL ( );

void InitSensores();

void InitBomba();

void InitUART0();

void initTimers();

void initTimer0();

void initTimer1();

void initTimer2();

void initTimer3();

#endif /* HEADERS_SYSINI_H_ */
