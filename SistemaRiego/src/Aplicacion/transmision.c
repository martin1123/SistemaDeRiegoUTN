/**
	\file transmision.c
	\brief Funciones necesarias para la transmisión de datos por UART.
	\details Se proveen funciones que sirven para que siguiendo el protocolo de comunicación establecido, se arme la trama
	         del comando o mensaje a transmitir, y luego se transmita el mismo.
	\author Grupo II, curso R2053
	\version 1.0.0
*/
#include "infotronic.h"
#include "transmision.h"


//Size de los byte de Start, tamaño, checksum, y stop
#define SZ_CONTROL 4
#define POS_INI_DATA 2

/**
	\fn uint8_t isEnabledUART()
	\brief Funcion que verifica si esta habilitado el envio de datos por UART

	\details Con esta funcion se verifica que mientras no haya ningun dispositivo conectado que entienda
	         el protocolo del sistema, no se va transimitir ningun tipo de datos.

	\param trama[in] void

	\return uint8_t Devuelve 1 si hay un dispositivo conectado por UART que entiende el protocolo, sino 0.

	\author Grupo II, curso R2053

	\version 1.0.0
*/
uint8_t isEnabledUART()
{
	return UART_STATUS;
}

/*Funcion que arma la trama a enviar. Retorna un puntero a la trama o en caso de error retorna NULL.
 * dato es el dato a enviar, y sz es el tamaño del dato*/

/**
	\fn uint8_t armarTrama(uint8_t *trama, enum transmitData s)
	\brief Funcion que verifica si esta habilitado el envio de datos por UART

	\details Funcion que arma la trama a enviar. Retorna un puntero a la trama o en caso de error retorna NULL.
             dato es el dato a enviar, y sz es el tamaño del dato

	\param [out] uint8_t* trama: Trama a enviar
	\param [in] enum transmitData s: Indica dato a transmitir

	\return uint8_t Devuelve el size de la trama si se pudo armar correctamente, sino 0.

	\author Grupo II, curso R2053

	\version 1.0.0
*/
uint8_t armarTrama(uint8_t *trama, enum transmitData s)
{
	uint8_t sz, pos_command, pos_subcommand;
	trama[0] = B_START;

	switch (s)
	{
		case TRANS_TEMP:
			//Para la temperatura, se transmite en un byte.
			//El bit mas significativo indica el signo, y el resto el valor de la temperatura
			pos_command = POS_COM_INFORM; //Comando
			pos_subcommand = POS_SUBCOM_TEMP; //Sub comando
			trama[4] = 0x00; //Inicializo byte en 0

			if(temp < 0)
			{
				trama[4] |= (1<<7);  //Si es negativo, seteo en 1 el bit mas significativos
				trama[4] |= (uint8_t)(temp*(-1)); //Paso a positivo el valor de la temperatura y guardo valor en los bits menos significativos
			}
			else
			{
				trama[4] |= (uint8_t)(temp);//guardo valor en los bits menos significativos
			}

			break;

		case TRANS_HUM:
			pos_command = POS_COM_INFORM;
			pos_subcommand = POS_SUBCOM_HUMEDAD;
			trama[4] = humedad;
			break;

		case TRANS_LVLH2O:
			pos_command = POS_COM_INFORM;
			pos_subcommand = POS_SUBCOM_LVLH2O;
			trama[4] = lvlH2O;
			break;

		case TRANS_UMBRAL_H2O:
			pos_command = POS_COM_CONF;
			pos_subcommand = POS_SUBCOM_UMBRAL_H2O;
			trama[4] = umbral_H2O;
			break;

		case TRANS_UMBRAL_HUM:
			pos_command = POS_COM_CONF;
			pos_subcommand = POS_SUBCOM_UMBRAL_HUM;
			trama[4] = umbral_humedad;
			break;

		case TRANS_UMBRAL_TEMP:
			pos_command = POS_COM_CONF;
			pos_subcommand = POS_SUBCOM_UMBRAL_TEMP;
			trama[4] = umbral_temp;
			break;

		case TRANS_TIME_REG:
			pos_command = POS_COM_CONF;
			pos_subcommand = POS_SUBCOM_TIME_REG;
			trama[4] = timer_regado;
			break;

		case TRANS_ACK:
			/*En este caso, solo se envia el comando y subcomando, sin ningun dato adicional
			 * ya que solo es una confirmacion de recepcion de un dato*/
			pos_command = POS_COM_ACK;
			pos_subcommand = POS_SUBCOM_ACK;
			break;

		default:
			break;
	}

	sz = commands[pos_command].sub[pos_subcommand].sz + 2; //Size del dato, size del comando, y size del subcomando
	trama[1] = sz;
	trama[2] = commands[pos_command].command;
	trama[3] = commands[pos_command].sub[pos_subcommand].subCommand;
	trama[2 + sz] = calc_checksum(trama+2, sz);//En trama[2] comienza el analisis de los datos. Comando, subcomando, y dato en si.
	trama[2 + sz + 1] = B_STOP;

	return 2 + sz + 2; //Retorna size de la trama
}

/**
	\fn uint8_t calc_checksum(uint8_t * dato, uint8_t size)
	\brief Funcion que calcula checksum de los datos a enviar

	\details Funcion que calcula el checksum del comando a enviar, o del comando recibido segun el protocolo especificado en
	         el manual del sistema de riego.

	\param [in] uint8_t* dato: Comando a partir del cual se calcula checksum
	\param [in] uint8_t size: size del comando del cual se va a calcular el checksum

	\return uint8_t Devuelve checksum calculado.

	\author Grupo II, curso R2053

	\version 1.0.0
*/
uint8_t calc_checksum(uint8_t * dato, uint8_t size)
{
	uint32_t sum;
	uint8_t i;

	for(i = 0, sum = 0; i < size; i++)
		sum += (i+1) * dato[i];

	return (uint8_t) (sum % 256);
}

/**
	\fn void transmitir (uint8_t *p, uint8_t sz)
	\brief Funcion que envia datos byte por byte a la cola de transmision

	\details

	\param [in] uint8_t* p: Trama a transmitir
	\param [in] uint8_t size: size de la trama a transmitir

	\return void

	\author Grupo II, curso R2053

	\version 1.0.0
*/
void transmitir (uint8_t *p, uint8_t sz)
{
    uint32_t i;

    for (i=0; i < sz; ++i)
         PushTx(p[i]);
}
