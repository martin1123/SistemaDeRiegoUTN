#include "infotronic.h"

void inicializar(void)
{
	PCONP = 0; //Se desactiva por default la alimentacion de perifericos
	InitPLL () ;
	init_systick (); //Inicializacion Systick
	init_rtc(0,0,0,0,0,0);//Inicializacion RTC
	InitSensores(); //Inicializacion de Puertos y pines de todos los sensores del sistema
	InitBomba(); //Inicializacion de Puertos y pines de la bomba
	InitUART0(); //Inicializacion para comunicacion UART0
	initTimers();

	state_flag = REPOSO; //Cambio a estado de reposo
}

void reposo(void)
{
	if(timer_humedad == ON)
	{
		/*Se verifica humedad*/
		timer_humedad = OFF;
		state_flag = GET_HUMEDAD;
	}else if(timer_temp == ON)
	{
		/*Se verifica temperatura ambiente*/
		timer_temp = OFF;
		state_flag = GET_TEMP_AMB;
	}else if(timer_h2o == ON)
	{
		/*Se verifica nivel de agua en tanque*/
		timer_h2o = OFF;
		state_flag = GET_H2O_LEVEL;
	}else if(timer_Riego == ON)
	{
		/*Alarma activa riego de plantas*/
		timer_Riego = OFF;
		state_flag = REGAR;
	}
	/*Falta agregar transiciones a mas estados*/
}

void obtenerHumedad(void)
{
	//Funcion primitiva que me devuelve humedad
	//humedad = get_Humedad();

	/*acceptable_moisture() mediante logica difusa determina si la humedad
	 * es aceptable. EN caso de no serlo se procede a regar*/
	/*NOTA A BORRAR: Para deerminar una humedad aceptable se va a tomar como base
	 * no solo el nivel de humedad, sino tmb el tiempo que haya pasado desde el ulitmo regado,
	 * ya que puede pasar que la humedad luego de un regado no se actualice a el valor correcto
	 * sino hasta esperar un tiempo razonable en el que el agua se distribuya en la tierra.*/
	if(acceptable_moisture(humedad))
	{
		/*Si la conexion a traves de UART está activa flag para transmision de humedad*/
		if(isEnabledUART())
		{
			state_flag = INF_UART; //Informo humedad
			TRANSMIT_H = ON;
		}
		else
			state_flag = REPOSO;
	}
	else
	{
		state_flag = REGAR;
	}
}

void obtenerTempAmb(void)
{
	//Funcion primitiva que me devuelve temperatura
	//temp = get_Temperatura();

	if(isEnabledUART())
	{
		state_flag = INF_UART; //Informo humedad
		TRANSMIT_TEMP = ON;
	}
	else
		state_flag = REPOSO;
}

void obtenerNivH2O(void)
{
	//Funcion primitiva que me devuelve nivel de agua en tanque
	//humedad = get_Humedad();

	/*acceptable_level() mediante logica difusa determina si el nivel de agua
	 * es aceptable. EN caso de no serlo se procede a activar alarma*/
	if(acceptable_level(lvlH2O))
	{
		/*Si la conexion a traves de UART está activa flag para transmision de humedad*/
		if(isEnabledUART())
		{
			state_flag = INF_UART; //Informo Nivel de agua
			TRANSMIT_H2O = ON;
		}
		else
			state_flag = REPOSO;
	}
	else
	{
		state_flag = SIN_AGUA;
	}
}

void regar(void)
{

}

void alertaAgua(void)
{

}

void informarUART(void)
{

}
