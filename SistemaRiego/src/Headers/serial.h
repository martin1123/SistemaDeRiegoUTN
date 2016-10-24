/*
 * serial.h
 *
 *  Created on: 24 de oct. de 2016
 *      Author: mmaccio
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

#endif /* HEADERS_SERIAL_H_ */
