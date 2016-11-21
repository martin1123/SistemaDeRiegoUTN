/*
 * TransmitStates.c
 *
 *  Created on: 17 de nov. de 2016
 *      Author: Martin
 */
#include "infotronic.h"
#include "transmit.h"

void (*TMV[])() = {no_transmit,transmitTemp,transmitHum,transmitLvlH2O,transmitRegando, transmitAck};
enum transmitState t_state = NO_TRANS;

void Transmit_Machine(void)
{
	TMV[t_state]();
}

void no_transmit(void)
{
	/*Si no hay dispositivos conectados a la UART no transmite*/
	if(isEnabledUART())
	{
		if(TRANSMIT_TEMP)
		{
			TRANSMIT_TEMP = OFF;
			t_state = TRANS_TEMP;
		}
		else if(TRANSMIT_H)
		{
			TRANSMIT_H = OFF;
			t_state = TRANS_HUM;
		}
		else if(TRANSMIT_H2O)
		{
			TRANSMIT_H2O = OFF;
			t_state = TRANS_LVLH2O;
		}
		else if(TRANSMIT_ACK)
		{
			TRANSMIT_ACK = OFF;
			t_state = TRANS_ACK;
		}
	}
}

void transmitTemp(void)
{

}

void transmitHum(void)
{

}

void transmitLvlH2O(void)
{

}

void transmitRegando(void)
{

}

void transmitAck(void)
{

}
