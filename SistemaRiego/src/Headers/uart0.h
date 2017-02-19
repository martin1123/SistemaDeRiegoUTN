/**
	\file uart0.h
	\brief Registros UART0
	\details
	\author Grupo II, curso R2053
	\version 1.0.0
*/

#ifndef HEADERS_UART0_H_
#define HEADERS_UART0_H_

#define DIR_UART ((volatile uint32_t *) 0x40010000UL)
#define DIR_UART1 DIR_UART[0]

#define U0LCR0 (*( ( registro_t  * ) 0x4000C00CUL))

#define SYSTEMCORECLOCK		100000000UL	// 100 MHZ
#define			U0RBR					(*( ( registro_t  * ) 0x4000C000UL ))// Receiver Buffer Register. (DLAB = 0)		RO
#define			U0THR					(*( ( registro_t  * ) 0x4000C000UL ))// Transmit Holding Register. (DLAB = 0)	WO
#define			U0DLL					(*( ( registro_t  * ) 0x4000C000UL ))// Divisor Latch LSB. (DLAB = 1)			RW		0x01

#define			U0IER					(*( ( registro_t  * ) 0x4000C004UL ))// Interrupt Enable Register. (DLAB = 0)	RW		NA
#define			U0DLM					(*( ( registro_t  * ) 0x4000C004UL ))// Divisor Latch MSB. (DLAB = 1)			RW		NA

#define			U0IIR					(*( ( registro_t  * ) 0x4000C008UL ))// Interrupt ID Register					RO		0x01
#define			U0FCR					(*( ( registro_t  * ) 0x4000C008UL ))// FIFO Control Register					WO		0x00

#define			U0LCR					(*( ( registro_t  * ) 0x4000C00CUL ))// Line Control Register					RW		0x00

#define			U0LSR					(*( ( registro_t  * ) 0x4000C014UL ))// Line Status Register						RO		0x60

#define			U0SCR					(*( ( registro_t  * ) 0x4000C01CUL ))// Scratch Pad Register						RW		0x00
#define			U0ACR					(*( ( registro_t  * ) 0x4000C020UL ))// Auto-baud Control Register				RW		0x00
#define			U0ICR					(*( ( registro_t  * ) 0x4000C024UL ))// IrDA Control Register					RW		0x00
#define			U0FDR					(*( ( registro_t  * ) 0x4000C028UL ))// Fractional Divider Register				RW		0x10
#define			U0TER					(*( ( registro_t  * ) 0x4000C030UL ))// Transmit Enable Register					RW		0x80

#define			UART0					( ( registro_t  * ) 0x40000000UL )

#define IER_RBR 0x01
#define IER_THRE 0x02

void InitUART0(void);

#endif /* HEADERS_UART0_H_ */
