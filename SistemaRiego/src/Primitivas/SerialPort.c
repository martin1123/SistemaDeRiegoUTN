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
    int aux;

    if(bufferRxEmpty)
    	return -1;

    aux = BufferRx[inxRxOut++];
    inxRxOut %= BUFF_SIZE;
    bufferRxFull = OFF;

    if (inxRxIn == inxRxOut)
    	bufferRxEmpty = ON;

    return aux;
}

int PushTx (unsigned char dato)
{
	if(bufferTxFull)
		return -1;

    BufferTx[inxTxIn++] = dato;
    inxTxIn %= BUFF_SIZE;
    bufferTxEmpty = OFF;

    if (inxTxIn == inxTxOut)
    	bufferTxFull = ON;

    if (TxStart == 0)
    {
        TxStart = 1;
        bufferTxEmpty = ON;
        U0THR= PopTx();
    }

    return 1;
}

int PushRx (unsigned char dato)
{
	  if(bufferRxFull)
		  return -1;

	  BufferRx[inxRxIn++] = dato;
	  inxRxIn %= BUFF_SIZE;
	  bufferRxEmpty = OFF;

	  if(inxRxIn == inxRxOut)
		  bufferRxFull = ON;

	  return 1;
}

int PopTx (void)
{
	  int aux = -1;

	  if(bufferTxEmpty)
		  return -1;

	  aux = BufferTx[inxTxOut++];
	  inxTxOut %= BUFF_SIZE;
	  bufferTxFull = OFF;

	  if (inxTxIn == inxTxOut)
	  {
		  bufferTxEmpty = ON;
	  }

	  return aux;
}
