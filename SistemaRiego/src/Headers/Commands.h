/*
 * Commands.h
 *
 *  Created on: 22 de nov. de 2016
 *      Author: mmaccio
 */

#ifndef HEADERS_COMMANDS_H_
#define HEADERS_COMMANDS_H_

/*COMANDOS*/
#define COM_INFORMAR 0x49
#define COM_ACK      0x41
#define COM_REGAR    0x52
#define COM_CONFIG   0x43

/*SUB-COMANDOS*/
#define SUB_HUMEDAD  0x48
#define SUB_TEMP     0x54
#define SUB_LVLH2O   0x4E
#define SUB_ALARM    0x41
#define SUB_UMBRAL_H 0x4B
#define SUB_TIME_R   0x54
#define SUB_HORA     0x48
#define SUB_FECHA    0x46
#define SUB_MACETA   0x41

typedef struct{
	uint8_t subCommand;
	uint8_t sz;
}sub_command_t;

typedef struct{
	uint8_t command;
	sub_command_t *sub;
}command_t;

#endif /* HEADERS_COMMANDS_H_ */
