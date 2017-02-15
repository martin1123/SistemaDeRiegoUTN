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
	setPinSel(PORT_NTC,PIN_NTC,3);
	set_dir(PORT_NTC,PIN_NTC,0);
	setPinSel(PORT_HUM,PIN_HUM,3);
	set_dir(PORT_HUM,PIN_HUM,0);
	//5.- NO ACTIVO LAS INTERRUPCIONES:
	AD0INTEN &= 0xFFFFFE00;
	//6.- Selecciono que voy a tomar muestras del canal AD0.5, AD0.1 Y AD0.2 (00100110)
	AD0CR |= 0x00000026;
	//7.- Activo el ADC (PDN = 1):
	AD0CR |= 1<<21;
	//8.- Selecciono que el ADC muestree solo, con BURST = 1 y START = 000:
	AD0CR &= ~(0x0F<<24);
	AD0CR |= 1<<16;


}

int getSensorValue(int registro, int valor)
{

	if ( ADC_DONE (registro) ){ //Verifico nivel H2O
		valor = ( registro >> 4 ) & 0x0000FFFF;
	}

	return valor;
}
