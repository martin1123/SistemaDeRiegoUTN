/*
 * UART1.c
 *
 *  Created on: 21 de oct. de 2016
 *      Author: Martin
 */
#include "infotronic.h"


int PopRx (void)
{

    int aux = -1;

    if (inxRxIn != inxRxOut)
      {
        aux = BufferRx[inxRxOut];
        inxRxOut ++;
        inxRxOut %= BUFF_SIZE;
      }
 return aux;
}

void PushTx (unsigned char dato)
{
    BufferTx[inxTxIn] = dato;
    inxTxIn ++;
    inxTxIn %= BUFF_SIZE;

    if (TxStart == 0)
       {
        TxStart = 1;
        U1THR= BufferTx[inxTxOut];
       }
}
