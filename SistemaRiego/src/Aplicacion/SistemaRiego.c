#include "infotronic.h"

/*Flag que indica la posicion de la rutina a invocar en el vector de rutinas*/
STATES_T state_flag;

/*SMV (States Machine Vector): Vector de punteros a funciones de cada estado.
 *encargada de atender una interrupcion*/
//void (*SMV[])(void) = {inicializar, reposo, obtenerHumedad, obtenerTempAmb, obtenerNivH2O, regar, alertaAgua};

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

volatile uint8_t TxStart;

/*FLAGS de sensores*/
volatile flagST_t flag_H2OBajo = OFF;
volatile flagST_t flag_regar = OFF;
volatile flagST_t flag_config = OFF;
volatile flagST_t flag_timerDisplay = OFF;
volatile flagST_t timer_h2o = OFF;
volatile flagST_t timer_Riego = OFF;
volatile flagST_t f_UARTRx_cHora = OFF;
volatile flagST_t f_UARTRx_regar = OFF;
volatile flagST_t f_UARTRx_cAlarma = OFF;
volatile flagST_t f_UARTRx_config = OFF;
volatile flagST_t UART_STATUS = OFF;
volatile flagST_t TRANSMIT_H = OFF;
volatile flagST_t TRANSMIT_TEMP = OFF;
volatile flagST_t TRANSMIT_H2O = OFF;

/*TIMERS*/

#define TIMERS_CANT 8
uint8_t timer_events;
uint8_t timer_vector[TIMERS_CANT];

void ActualizarDatos ( void );
void TimerEvent();

int main (void)
{
	/*El sistema arranca con su inicializacion*/
	//state_flag = INICIAR;
	inicializar();
	/*Los estados van a ir cambiando a medida que las interrupciones cambien el valor de la bandera
	 *state_flag, para invocar a cada una de las rutinas definidas para el funcionamiento del sistema*/
	while(1)
	{
		//SMV[state_flag]();
		//Se actualizan los datos de Humedad, Temperatura, y nivel de agua.
		ActualizarDatos();
		/*Funcion que analiza timers vencidos*/
		TimerEvent();
		/*Maquina que maneja la recepción de datos por UART*/
		//Receive_Machine();
		/*Maquina que se encarga de la transmisiónd e datos por UART*/
		//Transmit_Machine();
		/*Máquina que se encarga de disparar eventos como regado o alarma por bajo nivel de h2o*/
		//Event_Machine();
		/*Maquina que maneja el muestreo de información en el display 16X2*/
		Display_machine();
		/*Máquina que se encarga del manejo de la configuracion manual de fecha y hora por parte del usuario*/
		//Date_config_Machine();
	}

	return 0;
}

/**/
void ActualizarDatos ( void )
{
	temp = getTemp(temp);
	humedad = getHumedad(humedad);
	lvlH2O = getlvlH2O(lvlH2O);
}

void TimerEvent(){

}

void Display_lcd( char *msg , char renglon , char posicion )
{
	unsigned char i ;

	if( renglon )
        posicion = posicion + 0xc0 ;
	else
		posicion = posicion + 0x80 ;

	Dato_LCD( posicion , LCD_CONTROL );
	for( i = 0 ; msg[ i ] != '\0' ; i++ )
		Dato_LCD( msg[ i ] , LCD_DATA );

}
