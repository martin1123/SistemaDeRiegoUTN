/*
 * Commands.h
 *
 *  Created on: 22 de nov. de 2016
 *      Author: mmaccio
 */

#ifndef HEADERS_COMMANDS_H_
#define HEADERS_COMMANDS_H_

typedef struct{
	uint8_t subCommand;
	uint8_t sz;
}sub_command_t;

typedef struct{
	uint8_t command;
	sub_command_t *sub;
}command_t;

#endif /* HEADERS_COMMANDS_H_ */
