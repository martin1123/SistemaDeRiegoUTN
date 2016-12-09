/*
 * pinConf.h
 *
 *  Created on: 13 de oct. de 2016
 *      Author: Martin
 */

#ifndef HEADERS_PINCONF_H_
#define HEADERS_PINCONF_H_

/*Puntero a registro PINSEL0*/
#define DIR_PINSEL0 ((uint32_t *) 0x4002C000UL)

#define DIR_PINMODE0 ((uint32_t *) 0x4002C040UL)

#define setDir(port,pin,dir) ((dir==0)?((GPIO_BASE+port)->fiodir &= ~(1<<pin)):((GPIO_BASE+port)->fiodir |= (1<<pin)))
#define setPin(port,pin,v) ((v==0)?((GPIO_BASE+port)->fiopin &= ~(1<<pin)):((GPIO_BASE+port)->fiopin |= (1<<pin)))
#define getPin(port,pin) (((GPIO_BASE+port)->fiopin)>>pin & 0x01)

void setPinSel(uint8_t port, uint8_t pin, uint8_t fun);
void setPinMode(uint8_t port, uint8_t pin, uint8_t fun);

#endif /* HEADERS_PINCONF_H_ */
