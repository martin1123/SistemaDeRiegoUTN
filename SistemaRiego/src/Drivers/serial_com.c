/**
	\file serial_com.c
	\brief Driver de comunicacion por puerto serie
	\details
	\author Grupo II, curso R2053
	\version 1.0.0
*/
#include "infotronic.h"

void InitUART0(void)
{

    PCONP |= 0x01<<4;	     //1.- Registro PCONP (0x400FC0C4) – bit 4 en 1 prende la UART1
    PCLKSEL0 &= ~(0x03<<8);  //2.- Registro PCLKSEL0 - bits 8 y 9 en 0 seleccionan que el clk de la UART1 sea CCLK/4

    U1LCR1 = 0x00000083;    //3.- Registro U1LCR - Tx de 8 bits, 1 bit de stop, sin paridad, sin break cond, DLAB = 1
    U1DLM = 0x0A; 	       //4.- Registros U1DLL (0x40010000) y U1DLM (0x40010004) – 9600 baudios:
    U1DLL = 0x2C;   	   //0x00D9 p/115200;

//5.- Registros PINSEL0 (0x4002C000) y PINSEL1 (0x4002C004) - habilitan las funciones especiales de los pines:
    setPinSel(0,15,1); 	//TX0D   P0.2  PINSEL0: 4/5
    setPinSel(0,16,1);	//RX0D   P0.3  PINSEL0: 6/7
    U1LCR1 = 0x03;		 //6.- Registro U1LCR, pongo DLAB en 0

    U1IER = IER_RBR | IER_THRE ;		// Habilito interrupciones
    ISER0 |= (1<<6);
}

void UART1_IRQHandler (void)
{
 uint8_t aux , dato;
 int dato_tx;

    do
      {
        aux = U1IIR; // una vez que lo lei se resetea

        switch (aux & 0x06)
           {
             case 0x02:
            	 //Transmisión
            	 dato_tx = PopTx ();

            	 if (dato_tx >= 0)
                	 U1THR = dato_tx;
                 else
                     TxStart = 0; // aviso que puedo volver a transmitir

                 break;

             case 0x04:
            	 //Recepción
            	 dato = U1RBR;
                 PushRx (dato);
                 break;

             case 0x06:
            	 //errores
                 break;
           }
    } while ((aux & 0x01) == 0); // me fijo si hay otra interrupcion pendiente -> b0 = 0

}
