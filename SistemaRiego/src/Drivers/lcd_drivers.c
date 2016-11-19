/*
 * lcd_drivers.c
 *
 *  Created on: 18 de nov. de 2016
 *      Author: mmaccio
 */

#include "infotronic.h"
#include "lcd.h"

void InitLCD ( void )
{
	unsigned int i,j;

	//1.- Selecciono los bits del puerto como GPIOs y los direcciono:
	conf_gpio(LCD_D4_PORT,LCD_D4_PIN,SALIDA);

	conf_gpio(LCD_D5_PORT,LCD_D5_PIN,SALIDA);
	conf_gpio(LCD_D6_PORT,LCD_D6_PIN,SALIDA);
	conf_gpio(LCD_D7_PORT,LCD_D7_PIN,SALIDA);
	conf_gpio(LCD_RS_PORT,LCD_RS_PIN,SALIDA);
	conf_gpio(LCD_BF_PORT,LCD_BF_PIN,ENTRADA);
	conf_gpio(LCD_E_PORT,LCD_E_PIN,SALIDA);

	for( i = 0 ; i < 3 ; i++ )
	{
		LCD_E_OFF;
		for ( j = 0 ; j < 500000 ; j++ ); // 300000
		LCD_DATO(1,1,0,0);

		LCD_RS_OFF;
		LCD_E_ON;

		for( j = 0 ; j < 10000 ; j++ );//4500

		LCD_E_OFF;
	}

	LCD_E_OFF;

	for ( j = 0 ; j < 500000 ; j++ ); // 300000

	LCD_DATO(0,1,0,0);

	LCD_RS_OFF;
	LCD_E_ON;

	for( j = 0 ; j < 10000 ; j++ );//4500

	LCD_E_OFF;

	// A partir de aca pasa a 4 bits
	Dato_LCD( 0x28 , LCD_CONTROL );
	Dato_LCD( 0x08 , LCD_CONTROL);	// display OFF
	Dato_LCD( 0x01 , LCD_CONTROL);	// clear display
	for( j = 0 ; j < 10000 ; j++ );	//delay por la instruccion clear display
	Dato_LCD( 0x06 , LCD_CONTROL);	// programo el LCD para mis necesidades
	Dato_LCD( 0x0C , LCD_CONTROL);	// display ON,sin cursor y blinking OFF del cursor

}

void Dato_LCD ( unsigned char data , unsigned char control )
{
	int q , i = 1;
	int data_d4,data_d5,data_d6,data_d7;

	do
	{
		data_d4 = ( data >> ( 0 + i * 4 ) ) & 0x01 ;
		data_d5 = ( data >> ( 1 + i * 4 ) ) & 0x01 ;
		data_d6 = ( data >> ( 2 + i * 4 ) ) & 0x01 ;
		data_d7 = ( data >> ( 3 + i * 4 ) ) & 0x01 ;

		LCD_DATO(data_d4,data_d5,data_d6,data_d7);

		if( control == LCD_CONTROL )
			LCD_RS_OFF;
		else
			LCD_RS_ON;

		LCD_E_ON;
		for( q = 0 ; q < 400 ; q++ );
		LCD_E_OFF;
		for( q = 0 ; q < 14000 ; q++ );
	}
	while ( i-- );
}
