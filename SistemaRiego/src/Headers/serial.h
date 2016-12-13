/**
	\file serial.h
	\brief Header de funciones de puerto serie
	\details
	\author Grupo II, curso R2053
	\version 1.0.0
*/
#ifndef HEADERS_SERIAL_H_
#define HEADERS_SERIAL_H_

int PopRx (void);
int PopTx (void);
void PushTx (unsigned char dato);
void PushRx (unsigned char dato);


//Tamaño de buffer de las colas de transmision y recepcion
#define BUFF_SIZE 16

//Buffer de recepcion UART
extern volatile uint8_t BufferRx[BUFF_SIZE];

//Indices de cola circular del Buffer de recepcion
extern volatile uint8_t inxRxIn;
extern volatile uint8_t inxRxOut;

//Buffer de transmision UART
extern volatile uint8_t BufferTx[BUFF_SIZE];

//Indices de cola circular del Buffer de transmision
extern volatile uint8_t inxTxIn;
extern volatile uint8_t inxTxOut;
extern volatile uint8_t TxStart;

#define B_START 0x42
#define B_STOP  0x53



#endif /* HEADERS_SERIAL_H_ */
