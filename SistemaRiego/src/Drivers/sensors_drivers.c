/**
	\file sensors_drivers.c
	\brief Drivers de los sensores de temperatura, nivel, y humedad.
	\details Estos drivers se encargan de obtener por una entrada ADC,
	         la informacion de los sensores del sistema.
	\author Grupo II, curso R2053
	\version 1.0.0
*/

#include "infotronic.h"
#include "sensors.h"

void InitSensores()
{
	//Configuracion de los sensores
	//1.- Activo la alimentacion del dispositivo desde el registro PCONP:
	PCONP |= 1<<12;
	//2.- Selecciono el clock del ADC como 25MHz:
	PCLKSEL0 &= ~(0x03<<24);
	//3.- Y el divisor como 1, para muestrear a 200kHz:
	AD0CR &= 0x00000100;
	//4.- Configuro los pines del ADC0
	//ADC0.1: Inicializo NTC
	setPinSel(PORT_H2O,PIN_H2O,3);
	set_dir(PORT_H2O,PIN_H2O,0);
	//5.- NO ACTIVO LAS INTERRUPCIONES:
	AD0INTEN &= 0xFFFFFE00;
	//6.- Selecciono que voy a tomar muestras del canal AD0.5:
	AD0CR |= 0x00000020;
	//7.- Activo el ADC (PDN = 1):
	AD0CR |= 1<<21;
	//8.- Selecciono que el ADC muestree solo, con BURST = 1 y START = 000:
	AD0CR &= ~(0x0F<<24);
	AD0CR |= 1<<16;
	/*
	conf_gpio(PORT_NTC,PIN_NTC,IN);
	conf_gpio(PORT_H2O,PIN_H2O,IN);
	conf_gpio(PORT_HUM,PIN_HUM,IN);
	setPinMode(PORT_NTC,PIN_NTC,PULL_UP);
	setPinMode(PORT_H2O,PIN_H2O,PULL_UP);
	setPinMode(PORT_HUM,PIN_HUM,PULL_UP);
	*/
}

uint16_t sensorTemp()
{
	if ( ADC_DONE (AD0DR1) ) //Verifico temp
	    return ADC1_VAL;

	return NO_VALUE;
}

uint16_t sensorHum()
{
	if ( ADC_DONE (AD0DR2) ) //Verifico Humedad
	    return ADC2_VAL;

	return NO_VALUE;
}

int sensorlvlH2O()
{
	static int resultado = 0;
	int registro = AD0DR5;
	if ( ADC_DONE (AD0DR5) ){ //Verifico nivel H2O
		resultado = ( registro >> 4 ) & 0x0000FFFF;
	    return resultado;
	}
	return resultado;
}
