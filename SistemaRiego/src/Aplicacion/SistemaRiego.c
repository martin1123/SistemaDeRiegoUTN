#include "infotronic.h"

/*Variables globales*/

//Humedad tierra
volatile uint8_t humedad;

//Temperatura ambiente
volatile short temp;

//Porcentaje de nivel de agua en tanque
volatile uint8_t lvlH2O;

//Buffer de recepcion UART
volatile uint8_t BufferRx[BUFF_SIZE];

//Indices de cola circular del Buffer de recepcion
volatile uint8_t inxRxIn;
volatile uint8_t inxRxOut;

//Buffer de transmision UART
volatile uint8_t BufferTx[BUFF_SIZE];

//Indices de cola circular del Buffer de transmision
volatile uint8_t inxTxIn;
volatile uint8_t inxTxOut;

//Flag que indica si se estan transmitiendo datos
volatile uint8_t TxStart;

/*FLAGS de sensores*/
volatile flagST_t flag_H2OBajo = OFF; //Configurado en ON. Configurar en OFF cuando se detecte nivel de agua estable
volatile flagST_t flag_regar = OFF; //Configurado en ON. Configurar en OFF cuando se termine de regar. Recordar activar por presionar boton d eriego o por PC mediante UART.
volatile flagST_t flag_config = OFF; //Configurar flag en ON y OFF
volatile flagST_t flag_timerDisplay = OFF; //Configurar coomo timer 1
volatile flagST_t timer_h2o = OFF; //Configurar. Ver que uso se le puede dar
volatile flagST_t timer_Riego = OFF; //Configurar co
volatile flagST_t f_UARTRx_cHora = OFF;
volatile flagST_t f_UARTRx_regar = OFF;
volatile flagST_t f_UARTRx_cAlarma = OFF;
volatile flagST_t f_UARTRx_config = OFF;
volatile flagST_t UART_STATUS = OFF;//Flag que indica si hay un dispositivo conectado mediante UART
volatile flagST_t TRANSMIT_H = OFF;
volatile flagST_t TRANSMIT_TEMP = OFF;
volatile flagST_t TRANSMIT_H2O = OFF;
volatile flagST_t TRANSMIT_ACK = OFF;
volatile flagST_t RECEIVED_ACK = OFF; //Flag que indica si se recibio un ACK
volatile flagST_t EXPIRED_ACK = OFF;

/*========================================*/
/*                 TIMERS                 */
/*========================================*/
/*
 * 1) Timer de refresco de Display
 * 2) Timer de envio de temperatura por UART
 * 3) Timer de envio de humedad por UART
 * 4) Timer de envio de nivel de agua por UART
 * 5) Timer de espera de confirmación de envío de mensajes por UART
 * 6) Timer de regado
 * 7) Timer de alarma cuando lvl h2o es bajo
 */
volatile uint8_t timer_events;
volatile uint8_t timer_vector[TIMERS_CANT];

void ActualizarDatos ( void );

int main (void)
{
	inicializar();

	while(1)
	{
		ActualizarDatos();//Se actualizan los datos de Humedad, Temperatura, y nivel de agua.*/
		TimerEvent();//Funcion que analiza timers vencidos
		Receive_Machine();//Maquina que maneja la recepción de datos por UART
		Transmit_Machine();//Maquina que se encarga de la transmisión de datos por UART
		Event_Machine();//Máquina que se encarga de disparar eventos como regado o alarma por bajo nivel de h2o*/
		Display_machine();//Maquina que maneja el muestreo de información en el display 16X2
		//Date_config_Machine();//Máquina que se encarga del manejo de la configuracion manual de fecha y hora por parte del usuario
	}

	return 0;
}

/**/
void ActualizarDatos ( void )
{
	temp = getTemp(temp);
	humedad = getHumedad(humedad);
	lvlH2O = getlvlH2O(lvlH2O);

	if(!acceptable_moisture(humedad))
		flag_regar = ON;

	if(!acceptable_level(lvlH2O))
		flag_H2OBajo = ON;
	else
		flag_H2OBajo = OFF;
}

