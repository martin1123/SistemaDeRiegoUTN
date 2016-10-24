#include "infotronic.h"

/*Flag que indica la posicion de la rutina a invocar en el vector de rutinas*/
STATES_T state_flag;

/*SSRV (States Services Routines Vector): Vector de punteros a funciones. Cada funcion es una rutina
 *encargada de atender una interrupcion*/
void (*SSRV[])(void) = {inicializar, informar, obtenerHyTMaceta, obtenerHyTAmb, obtenerNivH2O, regar, alertaAgua};

/*Variables globales*/

//Humedad tierra
volatile float humedad;

//Temperatura ambiente
volatile float temp;

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

int main (void)
{
	/*El sistema arranca con su inicializacion*/
	state_flag = INICIAR;

	/*Los estados van a ir cambiando a medida que las interrupciones cambien el valor de la bandera
	 *state_flag, para invocar a cada una de las rutinas definidas para el funcionamiento del sistema*/
	while(1)
	{
		SSRV[state_flag]();
	}

	return 0;
}
