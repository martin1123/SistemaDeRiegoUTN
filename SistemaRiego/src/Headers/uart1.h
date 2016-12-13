/**
	\file uart1.h
	\brief Registros UART1
	\details
	\author Grupo II, curso R2053
	\version 1.0.0
*/

#ifndef HEADERS_UART1_H_
#define HEADERS_UART1_H_

#define DIR_UART ((volatile uint32_t *) 0x40010000UL)
#define DIR_UART1 DIR_UART[0]

#define U1LCR1 (*( ( registro_t  * ) 0x4001000CUL))

#define SYSTEMCORECLOCK		100000000UL	// 100 MHZ
#define			U1RBR					(*( ( registro_t  * ) 0x40010000UL ))// Receiver Buffer Register. (DLAB = 0)		RO
#define			U1THR					(*( ( registro_t  * ) 0x40010000UL ))// Transmit Holding Register. (DLAB = 0)	WO
#define			U1DLL					(*( ( registro_t  * ) 0x40010000UL ))// Divisor Latch LSB. (DLAB = 1)			RW		0x01

#define			U1IER					(*( ( registro_t  * ) 0x40010004UL ))// Interrupt Enable Register. (DLAB = 0)	RW		NA
#define			U1DLM					(*( ( registro_t  * ) 0x40010004UL ))// Divisor Latch MSB. (DLAB = 1)			RW		NA

#define			U1IIR					(*( ( registro_t  * ) 0x40010008UL ))// Interrupt ID Register					RO		0x01
#define			U1FCR					(*( ( registro_t  * ) 0x40010008UL ))// FIFO Control Register					WO		0x00

#define			U1LCR					(*( ( registro_t  * ) 0x4001000cUL ))// Line Control Register					RW		0x00

#define			U1LSR					(*( ( registro_t  * ) 0x40010014UL ))// Line Status Register						RO		0x60

#define			U1SCR					(*( ( registro_t  * ) 0x4001001cUL ))// Scratch Pad Register						RW		0x00
#define			U1ACR					(*( ( registro_t  * ) 0x40010020UL ))// Auto-baud Control Register				RW		0x00
#define			U1ICR					(*( ( registro_t  * ) 0x40010024UL ))// IrDA Control Register					RW		0x00
#define			U1FDR					(*( ( registro_t  * ) 0x40010028UL ))// Fractional Divider Register				RW		0x10
#define			U1TER					(*( ( registro_t  * ) 0x40010030UL ))// Transmit Enable Register					RW		0x80

#define			UART1					( ( registro_t  * ) 0x40010000UL )

#endif /* HEADERS_UART1_H_ */
