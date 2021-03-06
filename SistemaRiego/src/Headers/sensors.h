/**
	\file sensors.h
	\brief Registros de ADC y funciones declaracion de funciones de sensores
	\details
	\author Grupo II, curso R2053
	\version 1.0.0
*/

#ifndef HEADERS_SENSORS_H_
#define HEADERS_SENSORS_H_

#define NO_VALUE 0

//0x40034000UL: Registro de control del ADC:
#define		DIR_AD0CR	( ( uint32_t  * ) 0x40034000UL )
//0x40034004UL: Registro de estado del ADC:
#define		DIR_AD0GDR	( ( uint32_t  * ) 0x40034004UL )
//0x4003400CUL: Registro de interrupcion del ADC
#define		DIR_AD0INTEN ( ( uint32_t  * ) 0x4003400CUL )
//0x40034010UL: Registros de estado de los ADCx
#define		AD0DR		( ( uint32_t  * ) 0x40034010UL )

#define		AD0CR		DIR_AD0CR[0]
#define		AD0GDR		DIR_AD0GDR[0]
#define		AD0INTEN	DIR_AD0INTEN[0]

#define		AD0DR0		AD0DR[0]
#define		AD0DR1		AD0DR[1]
#define		AD0DR2		AD0DR[2]
#define		AD0DR3		AD0DR[3]
#define		AD0DR4		AD0DR[4]
#define		AD0DR5		AD0DR[5]
#define		AD0DR6		AD0DR[6]
#define		AD0DR7		AD0DR[7]


#define	ADC_VAL(reg)	((reg>>04)&0x0000FFFF)
#define	ADC_DONE(reg)	((reg>>31)&0x00000001)

#define	ADC1_VAL		ADC_VAL(AD0DR1)
#define	ADC2_VAL		ADC_VAL(AD0DR2)
#define	ADC3_VAL		ADC_VAL(AD0DR3)
#define	ADC4_VAL		ADC_VAL(AD0DR4)
#define	ADC5_VAL		ADC_VAL(AD0DR5)

//Puertos y pines de los sensores
#define PORT_NTC  0
#define PIN_NTC   24
#define PORT_H2O  1
#define PIN_H2O   31
#define PORT_HUM  0
#define PIN_HUM   25

void InitSensores();
int getTemp(int t);
uint8_t getHumedad(uint8_t h);
uint8_t getlvlH2O(uint8_t lvl);
int getSensorValue(int reg, int resultado);
int convertToTemp(int n);
uint8_t convertToLvlH2O(uint16_t n);
uint8_t convertToHum(int n);



#endif /* HEADERS_SENSORS_H_ */
