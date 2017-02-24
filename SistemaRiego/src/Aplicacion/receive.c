/**
	\file receive.c
	\brief Funciones utilizadas para la recepcion de datos
	\details Las funciones de este fuente son utilizadas para la correcta recepcion de los
			 datos enviados desde un dispositivo conectado por puerto serie y de la ejecucion
			 de los comandos recibidos.
	\author Grupo II, curso R2053
	\version 1.0.0
*/
#include "infotronic.h"
#include "receive.h"

/**
	\fn uint8_t verificarComando(uint8_t * trama, uint8_t size_datos, uint8_t *cpos, uint8_t *scpos)
	\brief Funcion que verifica si el comando recibido es existente.

	\details Verifica si los comandos recibidos existen en el fuente Commands.c

	\param trama[in] trama de datos con el comando recibido
	\param size_datos[in] size de la trama
	\param *cpos[out] Posicion del comando recibido si es que se encontro
	\param *scpos[out] Posicion del subcomando recibido si es que se encontro

	\return uint8_t Devuelve 1 si encontro comando, sino 0.

	\author Grupo II, curso R2053

	\version 1.0.0
*/
uint8_t verificarComando(uint8_t * trama, uint8_t size_datos, uint8_t *cpos, uint8_t *scpos)
{
	uint8_t sz_sub;

	for(*cpos = 0; *cpos < SIZE_COMMANDS; (*cpos)++)
	{
		//Si encontro comando
		if(commands[*cpos].command == trama[0])
			break;
	}

	//Si no encontró el comando no se realiza ninguna accion por el momento
	if(*cpos == SIZE_COMMANDS)
		//Se debería informar error????
		return 0;

	switch(commands[*cpos].command)
	{
		case COM_INFORMAR:
			sz_sub = SIZE_SUB_INFORMAR;
			break;
		case COM_ACK:
			return 1;
			break;
		case COM_REGAR:
			sz_sub = SIZE_SUB_REGAR;
			break;
		case COM_CONFIG:
			sz_sub = SIZE_SUB_CONFIGURAR;
			break;
		case COM_QUERY:
			sz_sub = SIZE_SUB_QUERY;
			break;
		default:
			break; //Este caso es imposible que pase
	}

	for(*scpos = 0; *scpos < sz_sub; (*scpos)++)
	{
		//Si encontro comando
		if(commands[*cpos].sub[*scpos].subCommand == trama[1])
			break;
	}

	//Si no encontró el subcomando no se realiza ninguna accion por el momento
	if(*scpos == sz_sub)
		//Se debería informar error????
		return 0;

	return 1;

}

/**
	\fn void executeCommand(uint8_t comm_pos, uint8_t scomm_pos, uint8_t * trama)
	\brief Funcion que ejecuta los comandos recibidos

	\details Una vez recibidos los comandos y verificados, se proceden a ejecutar las acciones correspondientes
	         a cada uno en esta funcion.

	\param comm_pos[in] posicion del comando en array de comandos
	\param scomm_pos[in] posicion del subcomando en array correspondiente del subcomando
	\param trama[in] trama con el comando a ejecutar

	\return void

	\author Grupo II, curso R2053

	\version 1.0.0
*/
void executeCommand(uint8_t comm_pos, uint8_t scomm_pos, uint8_t * trama)
{
	switch(commands[comm_pos].command)
	{
		case COM_INFORMAR:
			enableUART(scomm_pos, trama);
			break;
		case COM_ACK:
			RECEIVED_ACK = ON;
			break;

		case COM_REGAR:
			flag_regar = ON;
			TRANSMIT_ACK = ON;
			break;

		case COM_CONFIG:
			config(scomm_pos, trama);
			TRANSMIT_ACK = ON;
			break;

		case COM_QUERY:
			query(scomm_pos);
	        break;

		default:
			break;
	}
}

/**
	\fn void enableUART(uint8_t scomm_pos, uint8_t * trama)
	\brief Funcion que activa o desactiva el envio de datos del LPC por UART segun el comando recibido.

	\details Una vez recibidos los comandos y verificados, se proceden a ejecutar las acciones correspondientes
	         a cada uno en esta funcion.

	\param scomm_pos[in] posicion del subcomando en array correspondiente del subcomando
	\param trama[in] trama con el comando a ejecutar

	\return void

	\author Grupo II, curso R2053

	\version 1.0.0
*/
void enableUART(uint8_t scomm_pos, uint8_t * trama){
	switch(commands[POS_COM_INFORM].sub[scomm_pos].subCommand){
		case SUB_CONN_PC:
			//Se activa comunicacion con UART
			UART_STATUS = ON;
			TRANSMIT_ACK = ON;
			break;
		case SUB_DESCONN_PC:
			//Se desactiva comunicacion con UART
			UART_STATUS = OFF;
			TRANSMIT_ACK = ON;
			break;
		default:
			break;
	}
}

/**
	\fn void config(uint8_t scomm_pos, uint8_t * trama)
	\brief Funcion para la ejecucion de los comandos de configuracion.

	\details

	\param scomm_pos[in] posicion del subcomando en array correspondiente del subcomando
	\param trama[in] trama con el comando a ejecutar

	\return void

	\author Grupo II, curso R2053

	\version 1.0.0
*/
void config(uint8_t scomm_pos, uint8_t * trama)
{
	switch(commands[POS_COM_CONF].sub[scomm_pos].subCommand)
	{
		case SUB_TIME_R:
			RTCGPREG4 = timer_regado = *trama;//Revisar
			break;

		case SUB_HORA:
			RTCHOUR = *trama;
			RTCMIN  = *(trama+1);
			RTCSEC  = *(trama+2);
			break;

		case SUB_FECHA:
			RTCYEAR  = (*trama * 100) + *(trama+1); //Se forma el año
			RTCMONTH = *(trama+2);
			RTCDOM   = *(trama+3);
			break;

		case SUB_UMBRAL_H:
			RTCGPREG3 = umbral_humedad = *trama;
			break;

		case SUB_UMRAL_H2O:
			RTCGPREG1 = umbral_H2O = *trama;
			break;

		case SUB_UMRAL_TEMP:
			RTCGPREG2 = umbral_temp = *trama; //Asume que siempre va a ser una temperatura positiva
			break;

		default:
			break;
	}
}

/**
	\fn void query(uint8_t scomm_pos)
	\brief Funcion para la ejecucion de los comandos de consulta de datos persistentes.

	\details Segun los datos que se consulten desde la PC, se realizan las acciones necesarias
	         para el envio de dichos datos.

	\param scomm_pos[in] posicion del subcomando a ejecutar de consulta

	\return void

	\author Grupo II, curso R2053

	\version 1.0.0
*/
void query(uint8_t scomm_pos)
{
	switch(commands[POS_COM_QUERY].sub->subCommand)
	{
		case SUB_TIME_R:
			//Transmite a la PC la configuracion del tiempo de regado
			TRANSMIT_TIME_REGADO = ON;
			break;

		case SUB_UMBRAL_H:
			//Transmite a la PC la configuracion del umbral de humedad
			TRANSMIT_UMBRAL_HUM = ON;
			break;

		case SUB_UMRAL_H2O:
			//Transmite a la PC la configuracion del umbral de agua minimo
			TRANSMIT_UMBRAL_H2O = ON;
			break;

		case SUB_UMRAL_TEMP:
			//Transmite a la PC la configuracion del umbral de temperatura maximo
			TRANSMIT_UMBRAL_TEMP = ON;
			break;

		default:
			break;//No se realiza ninguna accion
	}
}
