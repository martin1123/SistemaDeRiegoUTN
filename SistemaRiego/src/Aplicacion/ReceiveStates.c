/**
	\file ReceiveStates.c
	\brief Maquina de estados de recepcion por puerto serie.
	\details Máquina de estados que comienza en el estado reposo. Cuando se detecta un dato en el
	         buffer de entrada se verifica que sea un byte de start. En caso de no serlo se desecha el dato.
	         El estado Receiving, se encarga de que se reciban los datos correctamente, contemplando
	         cualquier error de comunicacion. Una vez recibidos los datos o detectado algun error se vuelve
	         al estado de reposo.
	\author Grupo II, curso R2053
	\version 1.0.0
*/
#include "Receive_states.h"
#include "receive.h"
#include "infotronic.h"

void (*RMV[])(void) = {Receive_Reposo, Receiving};
enum receiveState r_state = R_REPOSO;

/**
	\fn void Receive_Machine(void)
	\brief Punto de entrada a la maquina de estado de recepcion

	\details Segun el flag r_state, se indica la funcion a llamar del estado que se debe ejecutar.

	\param trama[in] void

	\return void

	\author Grupo II, curso R2053

	\version 1.0.0
*/
void Receive_Machine(void)
{
	RMV[r_state]();
}


/**
	\fn void Receive_Reposo(void)
	\brief Estado de reposo de la maquina de recepcion.

	\details Esta funcion indica que no se estan recibiendo datos. Si se recibe un byte que sea igual
	         al byte de start(leer protocolo de comunicacion), se pasa al estado de recepcion.

	\param trama[in] void

	\return void

	\author Grupo II, curso R2053

	\version 1.0.0
*/
void Receive_Reposo(void)
{
	int d;

	if((d = PopRx()) >= 0)
	{
		if(d == B_START)
		{
			r_state = R_RECEIVING;
		}

		//Si no hay un error de sincronizción

	}
}

/**
	\fn void Receiving(void)
	\brief Estado de recepcion de datos

	\details Esta funcion se encarga de recibir toda la trama que se este recibiendo, reconocer si la informacion recibida
	         corresponde a un comando valido, y en caso de serlo, ejecutar el comando. Luego de ejecutar el comando se pasa al
	         estado de recepcion.
	         En caso de error se termina la recepcion de datos y se vuelve al estado de reposo.

	\param trama[in] void

	\return void

	\author Grupo II, curso R2053

	\version 1.0.0
*/
void Receiving(void)
{
	static uint8_t i = 0;
	static uint8_t intentos = 10; //Intentos de recepcion. Si a los 10 no llega a recibir la traa completa corta todo.
	static uint8_t trama[BUFF_TRAMA_SZ];
	int dato,j, banderaError;
	uint8_t cpos, scpos;
	int sz;

	banderaError = 0; //Debido a un error detectado que se saltea lineas de codigo de un ciclo for, se tuvo que recurrir a un metodo poco convencional para resolver el bug.

	if(intentos-- == 0){
		//Se acabaron intentos. Se pasa a estado de reposo y se elimina la trama
		intentos = 10;
		i = 0;
		r_state = R_REPOSO;
		return;
	}

	//Si i es igual a 0 asigno el byte de start para tener la trama completa y verifico si se recibio el byte que indica size del comando, subcomando y datos
	if(!i)
	{
		for(j = 0; j < BUFF_TRAMA_SZ; j++)
				trama[j] = 0;

		trama[0] = B_START;
		dato = PopRx();


		if(dato>=0)
		{
			trama[++i] = (uint8_t)dato;
			sz = dato + 4; //Size de la trama a recibir
			i++;
		}
		else
			return;
	}


	//Va llenando la trama con los datos de recepción hasta que la cola quede vacía, o hasta que se encuentre byte de stop
	for(; i < sz && (dato = PopRx()) >= 0; i++)
	{
		banderaError = 1;
		trama[i] = (uint8_t) dato;
		//Verifico si llego byte de stop, y que además llegue en la posición esperada
		if(dato == B_STOP && i == (sz-1))
			break;
	}

	if(banderaError == 0){

		//Va llenando la trama con los datos de recepción hasta que la cola quede vacía, o hasta que se encuentre byte de stop
			for(; i < sz && (dato = PopRx()) >= 0; i++)
			{
				banderaError = 1;
				trama[i] = (uint8_t) dato;
				//Verifico si llego byte de stop, y que además llegue en la posición esperada
				if(dato == B_STOP && i == (sz-1))
					break;
			}

	}
	//Si se da este caso, es porque hubo una desincronización. No pueden venir mas de 255 bytes en total.
	if(i >= sz)
	{
		// Informar ERROR. No se transmite ACK. Se espera restransmision del dato.
		intentos = 10;
		i = 0;
		r_state = R_REPOSO;
		return;
	}

	//Caso en que se recibio la trama hasta el byte de STOP. Se procede a realiza el checksum.
	//Luego se informa el dato recibido.
	if(dato == B_STOP && i == (sz-1))
	{
		//La proxima transición es al estado de reposo
		r_state = R_REPOSO;

		//Verifica checksum de comando, subcomando, y datos. trama[1] almacena el size de estos datos. trama[sz-2] almacena el checksum enviado.
		if(calc_checksum(trama+2, trama[1]) == trama[sz-2])
		{
			//Verifica que comando se recibio. En caso de no recibir un comando válido no se realiza ninguna acción.
			if(verificarComando(trama+2, i-3, &cpos, &scpos))
				//Verificado el comando, se procede a ejecutarlo
				executeCommand(cpos,scpos,trama+4);

			i = 0;
			intentos = 10;
		}
		else
		{
			//INFORMAR ERROR
			i = 0;
			intentos = 10;
			r_state = R_REPOSO;
		}
	}
}
