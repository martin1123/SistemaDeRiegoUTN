/**
	\file DisplayStates.h
	\brief Header del Display LCD
	\details
	\author Grupo II, curso R2053
	\version 1.0.0
*/

#ifndef HEADERS_DISPLAYSTATES_H_
#define HEADERS_DISPLAYSTATES_H_

//Refresca display cada 5 segundos
#define REFRESH_TIME 50
#define SPACES "                "

void Display_machine(void);
void showHyT(void);
void showH2O(void);
void showDateAndHour(void);
void showRiego(void);
void showH2OLow(void);
void showConfigDate(void);
void refreshLCD(void);

enum dispStates{Disp_HyT, Disp_H2O, Disp_Date_Hour, Disp_Riego, Disp_H2O_Low, Disp_Config_Date};


#endif /* HEADERS_DISPLAYSTATES_H_ */
