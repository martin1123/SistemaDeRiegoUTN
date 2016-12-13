/*
 * pinconf.c
 *
 *  Created on: 8 de dic. de 2016
 *      Author: Martin
 */
#include "infotronic.h"
#include "pinConf.h"

void setPinSel(uint8_t port, uint8_t pin, uint8_t fun)
{
	uint32_t *pinsel = (DIR_PINSEL0 + port*2 + pin/16);
	pin %= 16;

	if(!fun)
	{
		//GPIO
		*pinsel &= ~(0x03<<pin*2);
	}
	else
	{
		//Inicializo en 0 los bits correspondientes al pin
		*pinsel &= ~(0x03<<pin*2);

		//Asigno fun a los bits correspondientes al pin
		*pinsel |= ~(fun<<pin*2);
	}
}

void setPinMode(uint8_t port, uint8_t pin, uint8_t fun)
{
	uint32_t *pinmode = (DIR_PINMODE0 + port*2 + pin/16);
	pin %= 16;

	if(!fun)
	{
		//PULLUP
		*pinmode &= ~(0x03<<pin*2);
	}
	else
	{
		//Inicializo en 0 los bits correspondientes al pin
		*pinmode &= ~(0x03<<pin*2);

		//Asigno fun a los bits correspondientes al pin
		*pinmode |= ~(fun<<pin*2);
	}
}
