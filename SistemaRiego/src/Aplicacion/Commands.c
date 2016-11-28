/*
 * Commands.c
 *
 *  Created on: 28 de nov. de 2016
 *      Author: Martin
 */
#include "infotronic.h"
#include "Commands.h"

sub_command_t sub_informar[] = {{SUB_HUMEDAD,1},{SUB_TEMP,1},{SUB_LVLH2O,1}};

command_t commands[] = {{COM_INFORMAR,sub_informar}};
