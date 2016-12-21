/**
	\file EventsDrivers.c
	\brief Primitivas LCD 16X2
	\details
	\author Grupo II, curso R2053
	\version 1.0.0
*/
#include "infotronic.h"
#include "lcd.h"

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
