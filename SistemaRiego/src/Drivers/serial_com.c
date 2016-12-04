
#include "infotronic.h"


void UART1_IRQHandler (void)
{
 uint8_t aux, dato_tx, dato;

    do
      {
        aux = U1IIR; // una vez que lo lei se resetea

        switch (aux & 0x06)
           {
             case 0x02:
            	 //Transmisión
            	 dato_tx = PopTx ();

            	 if (dato_tx > 0)
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
