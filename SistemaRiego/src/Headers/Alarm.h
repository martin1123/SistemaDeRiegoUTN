/*
 * Alarm.h
 *
 *  Created on: 17/12/2016
 *      Author: Martin
 */

#ifndef HEADERS_ALARM_H_
#define HEADERS_ALARM_H_

#define BUZZ_PORT  0
#define BUZZ_PIN  28
#define BUZZ_ON    0
#define BUZZ_OFF   1

void Alarm_Machine(void);
void alarmOff(void);
void alarmBeep(void);

enum alarmStates{ALARM_OFF,ALARM_BEEP};

#endif /* HEADERS_ALARM_H_ */
