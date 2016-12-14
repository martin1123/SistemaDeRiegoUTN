/**
	\file DisplayStates.c
	\brief Maquina de estados del LCD 16X2.
	\details Maquina de estados que se encarga de mostrar la información en el
	         Display 16X2, sin afectar el funcionamiento del resto del sistema.
	         Muestra: Fecha y hora; Humedad y temperatura; Porcentaje de nivel de agua
	                  en tanque; Mensaje de regado; Mensaje de nivel de agua bajo;
	                  Pantallas para configuracion de fecha y hora, umbral de humedad, y tiempo de riego.
	\author Grupo II, curso R2053
	\version 1.0.0
*/
#include "infotronic.h"
#include "DisplayStates.h"
#include <stdio.h>

char msg_renglon[16];

/*Display Machine Vector*/
void (*DMV[])(void) = {showHyT,showH2O,showDateAndHour,showRiego,showH2OLow,showConfigDate};

/*States flag*/
//Se inicia en el estado que muestra humedad y temperatura
enum dispStates f_states = Disp_HyT;

void Display_machine(void)
{
	DMV[f_states]();
}

void showHyT(void)
{
	sprintf(msg_renglon, "Temp: %3d", temp);
	Display_lcd( msg_renglon , 0 , 0 );
	sprintf(msg_renglon, "Humedad: %3d\%", humedad);
	Display_lcd( msg_renglon , 1 , 0 );

	if(flag_H2OBajo)
	{
		//Se pasa al estado que muestra en pantalla Alerta de nivel de agua bajo
		refreshLCD();
		f_states = Disp_H2O_Low;
	}
	else if(flag_regar)
	{
		//Se pasa al estado que muestra en pantalla un mensaje que indica que se esta regando
		refreshLCD();
		f_states = Disp_Riego;
	}

	else if(flag_config)
	{
		//Se pasa al estado que muestra en pantalla La configuracion para la fecha y hora
		f_states = Disp_Config_Date;
		refreshLCD();
	}
	else if(flag_timerDisplay)
	{
		//Se pasa al estado que muestra en pantalla el nivel de agua y se cambia estado de flag
		f_states = Disp_H2O;
		flag_timerDisplay = OFF;
		TimerStart(TIMER_EV_DISPLAY, 50);
		refreshLCD();
	}


	return;
}

void showH2O(void)
{
	sprintf(msg_renglon, "Nivel H2O: %3d\%", lvlH2O);
	Display_lcd( msg_renglon , 0 , 0 );
	Display_lcd( " " , 1 , 0 );

	if(flag_H2OBajo)
	{
		refreshLCD();
		//Se pasa al estado que muestra en pantalla Alerta de nivel de agua bajo
		f_states = Disp_H2O_Low;
	}
	else if(flag_regar)
	{
		refreshLCD();
		//Se pasa al estado que muestra en pantalla un mensaje que indica que se esta regando
		f_states = Disp_Riego;
	}
	else if(flag_config)
	{
		//Se pasa al estado que muestra en pantalla La configuracion para la fecha y hora
		f_states = Disp_Config_Date;
		refreshLCD();
	}

	else if(flag_timerDisplay)
	{
		//Se pasa al estado que muestra en pantalla la fecha y hora y se cambia estado de flag
		f_states = Disp_Date_Hour;
		flag_timerDisplay = OFF;
		TimerStart(TIMER_EV_DISPLAY, 50);
		refreshLCD();
	}

	return;
}

void showDateAndHour(void)
{
	sprintf(msg_renglon, "Fecha:%02d/%02d/%4d", RTCDOM, RTCMONTH, RTCYEAR);
	Display_lcd( msg_renglon , 0 , 0 );
	sprintf(msg_renglon, "Hora: %02d:%02d:%02d", RTCHOUR, RTCMIN, RTCSEC);
	Display_lcd( msg_renglon , 1 , 0 );
	f_states = Disp_Date_Hour;

	if(flag_H2OBajo)
	{
		//Se pasa al estado que muestra en pantalla Alerta de nivel de agua bajo
		f_states = Disp_H2O_Low;
		refreshLCD();
	}
	else if(flag_regar)
	{
		//Se pasa al estado que muestra en pantalla un mensaje que indica que se esta regando
		f_states = Disp_Riego;
		refreshLCD();
	}
	else if(flag_config)
	{
		//Se pasa al estado que muestra en pantalla La configuracion para la fecha y hora
		f_states = Disp_Config_Date;
		refreshLCD();
	}
	else if(flag_timerDisplay)
	{
		//Se pasa al estado que muestra en pantalla la humedad y temperatura y se cambia estado de flag
		f_states = Disp_HyT;
		flag_timerDisplay = OFF;
		TimerStart(TIMER_EV_DISPLAY, 50);
		refreshLCD();
	}

	return;
}

void showConfigDate(void)
{
	refreshLCD();
	//COMPLETAR!!!!!
	f_states = Disp_Date_Hour;
}

void showH2OLow(void)
{
	Display_lcd( "Nivel H2O bajo" , 0 , 0 );
	Display_lcd( "Recargue Tanque" , 1 , 0 );

	if(flag_H2OBajo == OFF)
	{
		//Si se volvio a cargar el tanque, se muestra su nivel
		f_states = Disp_HyT;
		refreshLCD();
	}
	return;
}

void showRiego(void)
{
	Display_lcd( "Regando..." , 0 , 0 );
	Display_lcd( " " , 1 , 0 );

	if(flag_regar == OFF)
	{
		//Si se termino de regar, se muestra temperatura y humedad
		f_states = Disp_HyT;
		refreshLCD();
	}


	return;
}

void refreshLCD(void)
{
	Display_lcd( SPACES , 0 , 0 );
	Display_lcd( SPACES , 1 , 0 );
}
