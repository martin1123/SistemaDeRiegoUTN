/*
 * SensorsStates.c
 *
 *  Created on: 17 de nov. de 2016
 *      Author: Martin
 */
#include "infotronic.h"
#include "SensorsStates.h"

enum sensorState{REPOSO, GET_TEMP, GET_H, GET_H2O};

//Sensors Machine Vector
void (*SMV[])(void) = {reposo_state, getTemp_state, getHum_state, getH2O_state};

enum sensorState StateFlag = REPOSO;

void Sensors_Machine(void)
{
	SMV[StateFlag];
}

void reposo_state(void){

}

void getTemp_state(void){

}

void getHum_state(void){

}

void getH2O_state(void){

}
