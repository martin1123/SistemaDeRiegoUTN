/**
	\file serial_com.c
	\brief Driver de comunicacion por puerto serie
	\details
	\author Grupo II, curso R2053
	\version 1.0.0
*/
#include "infotronic.h"

void InitUART0 (void)
{

	//2.- Registro PCLKSEL0 (0x400FC1A8) - bits 6 y 7 en 0 seleccionan que el clk de la UART0 sea 25MHz:
	PCLKSEL0 &= ~(0x03<<6);
	//3.- Registro U1LCR (0x4001000C) - transmision de 8 bits, 1 bit de stop, sin paridad, sin break cond, DLAB = 1:
	U0LCR = 0x00000083;
	//4.- Registros U1DLL (0x40010000) y U1DLM (0x40010004) - 9600 baudios:
	U0DLM = 0;
	U0DLL = 0xA3;//0xD9;
	//5.- Registros PINSEL0 (0x4002C000) y PINSEL1 (0x4002C004) - habilitan las funciones especiales de los pines:
	//TX1D : PIN ??	-> 		P0[2]	-> PINSEL0: 04:05
	setPinSel(0,2,1);
	//RX1D : PIN ??	-> 		P0[3]	-> PINSEL1: 06:07
	setPinSel(0,3,1);
	//6.- Registro U1LCR, pongo DLAB en 0:
	U0LCR = 0x03;
	//7. Habilito las interrupciones (En la UART -IER- y en el NVIC -ISER)
	U0IER = 0x03;
	ISER0 |= (1<<5);
}

void UART0_IRQHandler (void)
{
 uint8_t aux , dato;
 int dato_tx;

    do
      {
        aux = U0IIR; // una vez que lo lei se resetea

        switch (aux & 0x06)
           {
             case 0x02:
            	 //Transmisión
            	 dato_tx = PopTx ();

            	 if (dato_tx >= 0)
                	 U0THR = dato_tx;
                 else
                     TxStart = 0; // aviso que puedo volver a transmitir

                 break;

             case 0x04:
            	 //Recepción
            	 dato = U0RBR;
                 PushRx (dato);
                 break;

             case 0x06:
            	 //errores
                 break;
           }
    } while ((aux & 0x01) == 0); // me fijo si hay otra interrupcion pendiente -> b0 = 0

}
