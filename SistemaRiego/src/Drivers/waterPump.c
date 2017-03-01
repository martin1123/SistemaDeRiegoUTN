/**
	\file systick.c
	\brief Driver de la bonba de agua
	\details
	\author Grupo II, curso R2053
	\version 1.0.0
*/

#include "infotronic.h"

/*Inicializacion del puerto y pin de la bomba de agua*/
void InitBomba()
{
	conf_gpio(PORT_BOMB,PIN_BOMB,OUT);
	write_pin(PORT_BOMB,PIN_BOMB,0);
}
