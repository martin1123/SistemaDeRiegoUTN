/**
	\file lcd.h
	\brief Header LCD 16X2
	\details
	\author Grupo II, curso R2053
	\version 1.0.0
*/

#ifndef HEADERS_LCD_H_
#define HEADERS_LCD_H_

//GPIOS LCD:
#define		LCD_D4_PORT	0
#define		LCD_D4_PIN	5

#define		LCD_D5_PORT	0
#define		LCD_D5_PIN	10

#define		LCD_D6_PORT	2
#define		LCD_D6_PIN	4

#define		LCD_D7_PORT	2
#define		LCD_D7_PIN	5

#define		LCD_RS_PORT	2
#define		LCD_RS_PIN	6

#define		LCD_BF_PORT	1
#define		LCD_BF_PIN	28

#define		LCD_E_PORT	0
#define		LCD_E_PIN	4

#define		LCD_E_OFF				write_pin(LCD_E_PORT,LCD_E_PIN,0)
#define		LCD_E_ON				write_pin(LCD_E_PORT,LCD_E_PIN,1)
#define		LCD_RS_OFF				write_pin(LCD_RS_PORT,LCD_RS_PIN,0)
#define		LCD_RS_ON				write_pin(LCD_RS_PORT,LCD_RS_PIN,1)
#define		LCD_DATO(d4,d5,d6,d7)	write_pin(LCD_D4_PORT,LCD_D4_PIN,d4);write_pin(LCD_D5_PORT,LCD_D5_PIN,d5);write_pin(LCD_D6_PORT,LCD_D6_PIN,d6);write_pin(LCD_D7_PORT,LCD_D7_PIN,d7)

#define		LCD_CONTROL		1
#define		LCD_DATA		0

void InitLCD ( void );
void Dato_LCD ( unsigned char data , unsigned char control );
void Display_lcd( char *msg , char renglon , char posicion );

#endif /* HEADERS_LCD_H_ */
