/**
	\file TransmitStates.c
	\brief Maquina de estados de transmision por puerto serie.
	\details Máquina de estados que comienza en el estado reposo. Si no se detecta algun dispositivo
	         conectado al kit, se permancera indefinidamente en este estado.
	         Cuando se detecta un dato a transmitir, se pasa al estado transmit_data, en el cual
	         se realizara el armado de la trama a transmitir, y se transmitira la misma. Una vez hecha
	         la transmision se pasará al estado confirmTransmission, en donde se va a esperar una confirmacion
	         por parte del equipo conectado al kit. En caso de no recibirse la confirmacion en un lapso de tiempo
	         determinado, se volverá a enviar el mensaje hasta 2 veces mas. Si no se llega a recibir un ACK, se
	         vuelve al estado de reposo.
	         Si se recibe el ACK por parte del equipo conectado al kit, se volvera al estado  de reposo a la espera
	         de la transmision de datos.
	\author Grupo II, curso R2053
	\version 1.0.0
*/
#include "TransmitStates.h"
#include "infotronic.h"

void (*TMV[])() = {no_transmit,transmit_data,transmitAck,confirmTransmission};
enum transmitState t_state = STATE_NO_TRANS;
enum transmitData dataToTrans = NO_DATA;

/**
	\fn void Transmit_Machine(void)
	\brief Punto de entrada a la maquina de estado de transmision

	\details Segun el flag t_state, se indica la funcion a llamar del estado que se debe ejecutar.

	\param trama[in] void

	\return void

	\author Grupo II, curso R2053

	\version 1.0.0
*/
void Transmit_Machine(void)
{
	TMV[t_state]();
}

/**
	\fn void no_transmit(void)
	\brief Estado de reposo de la maquina de transmision.

	\details Esta funcion indica que no se estan transmitiendo datos. Mientras la funcion isEnabledUART() no retorne u valor
	         distinto de 0, no se transmitira ningun dato, ya que esto significa que no hay conectado ningun dispositivo
	         que entienda el protocolo de comunicacion.
	         En caso de retornar un valor distinto de 0, se habilitara la transmision de datos. Periodicamente se transmitiran
	         la temperatura, humedad, y nivel de agua detectados por los sensores analogicos, aunque tambien se puede
	         transmitir otro tipo de informacion.
	         En caso de tener que transmitirse un dato, se pasara al estado de tranmision.

	\param trama[in] void

	\return void

	\author Grupo II, curso R2053

	\version 1.0.0
*/
void no_transmit(void)
{
	/*Si no hay dispositivos conectados a la UART no transmite*/
	if(isEnabledUART())
	{
		if(TRANSMIT_TEMP)
		{
			TRANSMIT_TEMP = OFF;
			dataToTrans = TRANS_TEMP;
		}
		else if(TRANSMIT_H)
		{
			TRANSMIT_H = OFF;
			dataToTrans = TRANS_HUM;
		}
		else if(TRANSMIT_H2O)
		{
			TRANSMIT_H2O = OFF;
			dataToTrans = TRANS_LVLH2O;
		}
		else if(TRANSMIT_ACK)
		{
			/*En este caso particular, se pasa a un estado especial para la transmisión de Ack*/
			TRANSMIT_ACK = OFF;
			t_state = STATE_TRANS_ACK;
		}
		else if(TRANSMIT_UMBRAL_H2O)
		{
			/*Se transmite configuracion del umbral de H2O*/
			TRANSMIT_UMBRAL_H2O = OFF;
			dataToTrans = TRANS_UMBRAL_H2O;
		}
		else if(TRANSMIT_UMBRAL_HUM)
		{
			/*Se transmite configuracion del umbral de Humedad*/
			TRANSMIT_UMBRAL_HUM = OFF;
			dataToTrans = TRANS_UMBRAL_HUM;
		}
		else if(TRANSMIT_UMBRAL_TEMP)
		{
			/*Se transmite configuracion del umbral de Temperatura*/
			TRANSMIT_UMBRAL_TEMP = OFF;
			dataToTrans = TRANS_UMBRAL_TEMP;
		}
		else if(TRANSMIT_TIME_REGADO)
		{
			/*Se transmite configuracion del tiempo de regado*/
			TRANSMIT_TIME_REGADO = OFF;
			dataToTrans = TRANS_TIME_REG;
		}
		/*Si hay datos a transmitir pasa al estado de transmisión de datos*/
		if(dataToTrans != NO_DATA)
			t_state = STATE_TRANS_DATA;
	}
}

/**
	\fn void transmit_data(void)
	\brief Estado que indica que se estan transmitiendo datos.

	\details Esta funcion indica un estado generico que indica que se estan transmitiendo datos, sin importar
	         que tipo de comando o dato se este transmitiendo. En caso de ocurrir algun error, se pasa al estado de reposo
	          o no transmision, y en caso de transmitirse el dato correctamente, se pasa al estado de confirmaimacion de ACK,
	          donde se va a esperar una confirmacion por parte del dispositivo conectado por UARt para verificar la correcta recepcion
	          de los datos.

	\param trama[in] void

	\return void

	\author Grupo II, curso R2053

	\version 1.0.0
*/
void transmit_data(void)
{
	uint8_t trama[BUFF_TRAMA_SZ];
	uint8_t sz_trama;

	/*Se genera la trama segun el dato a transmitir*/
	if((sz_trama = armarTrama(trama, dataToTrans)) > 0)
	{
		transmitir(trama, sz_trama);
		t_state = STATE_TRANS_CONFIRM; //Se pasa al estado de espera de un ACK de parte del dispositivo conectado por UART
		TimerStart(TIMER_EV_UART_ACK,1);//Iniciar timer de espera para recibir ack, sino retransmite
	}
	else
		t_state = STATE_NO_TRANS;
}

/**
	\fn void transmitAck(void)
	\brief Estado que indica que se transmitira un ack en respuesta a la recepcion de un comando.

	\details Para este estado de transmision en particular, no se contempla que se reciba una confirmacion desde el otro dispositivo
             ya que en si, el envío de un ack, es una confirmación de que se recibio un mensaje

	\param trama[in] void

	\return void

	\author Grupo II, curso R2053

	\version 1.0.0
*/
void transmitAck(void)
{
	uint8_t sz;
	uint8_t trama[BUFF_TRAMA_SZ];

	sz = armarTrama(trama, TRANS_ACK);
	transmitir(trama, sz);
	t_state = STATE_NO_TRANS; //Se directamente al estado de reposo
}

/**
	\fn void confirmTransmission(void)
	\brief Estado que queda a la espera de que se reciba el ack por el dato transmitido

	\details Se permanece dentro de este estado hasta que se reciba un ack por parte del dispositivo conectado por UART
	         para confirmar la correcta recepcion de datos. En caso de recibir el ack, se pasa al estado de reposo o no transmision.
	         En caso de pasar un tiempo considerable sin respuesta, se vuelve al estado de transmision para reenviar el dato.
	         Esto sucede hasta 2 veces. Luego de los 2 reintentos de transmision sin respuesta alguna, se pasa al estado de reposo,
	         para no generar un bloqueo y liberar a la maquina de transmision para poder seguir transmitiendo otros datos.

	\param trama[in] void

	\return void

	\author Grupo II, curso R2053

	\version 1.0.0
*/
void confirmTransmission(void)
{
	static uint8_t reintentos = 2;

	//Se verifica si fue recibida la confirmación del dato enviado
	if(RECEIVED_ACK)
	{
		RECEIVED_ACK = OFF; //Desactiva flag
		EXPIRED_ACK = OFF; //Desactiva el flag en caso de que justo haya expirado el tiempo de espera del ack y se haya recibido el mismo
		TimerStop(TIMER_EV_UART_ACK);//desactiva timer de ack
		restartTimer();//Restartea los timers correspondientes del dato enviado
		reintentos = 2;
		t_state = STATE_NO_TRANS;
		dataToTrans = NO_DATA;
	}
	else if(EXPIRED_ACK)
	{
		EXPIRED_ACK = OFF;

		if(reintentos--)
		{
			TimerStart(TIMER_EV_UART_ACK, 1);//reiniciar timer de ack
			t_state = STATE_TRANS_DATA;
		}
		else
		{
			//Se acabaron los reintentos
			reintentos = 2;
			TimerStop(TIMER_EV_UART_ACK);//desactivar timer ack
			restartTimer();//Restartea los timers correspondientes del dato enviado
			t_state = STATE_NO_TRANS;
			dataToTrans = NO_DATA;
		}
	}
}

/**
	\fn void restartTimer(void)
	\brief Funcion que restartea los timers correspondientes de notificacion de temperatura, humedad, o nivel de agua
	       por UART.

	\details

	\param trama[in] void

	\return void

	\author Grupo II, curso R2053

	\version 1.0.0
*/
void restartTimer(void)
{
	switch(dataToTrans)
	{
		case TRANS_TEMP:
			TimerStart(TIMER_EV_UART_TEMP, 50);
			break;
		case TRANS_HUM:
			TimerStart(TIMER_EV_UART_HUM, 35);
			break;
		case TRANS_LVLH2O:
			TimerStart(TIMER_EV_UART_H2O, 25);
			break;
		default:
			break;
	}
}
