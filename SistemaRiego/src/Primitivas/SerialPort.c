/**
	\file SerialPort.c
	\brief Primitivas del manejo de los buffers de transmision y recepcion
	\details
	\author Grupo II, curso R2053
	\version 1.0.0
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

void PushRx (unsigned char dato)
{
  BufferRx[inxRxIn] = dato;           //recibo
  inxRxIn++;
  inxRxIn %= BUFF_SIZE;
}

int PopTx (void)
{
  int aux = 0;

  if (inxTxIn != inxTxOut)
    {
      aux = BufferTx[inxTxOut];
      inxTxOut ++;
      inxTxOut %= BUFF_SIZE;
    }

  return aux;
}
