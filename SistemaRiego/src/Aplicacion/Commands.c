/**
	\file Commands.c
	\brief Comandos de comunicacion
	\details Definicion de los comandos utilizados para la comunicacion con la computadora
	         a través de puerto serie.
	         La tupla que define cada comando es {COMANDO,array de subcomandos}.
	         La tupla que define cada subcomando es {SUBCOMANDO, Size Subcomando}.
	\author Grupo II, curso R2053
	\version 1.0.0
*/

#include "infotronic.h"
#include "Commands.h"

/*=======================================================*
 *         Sub Comandos del comando informar             *
 *====================================================== */
/* SUB_HUMEDAD:    Subcomando que notifica nivel de humedad. Este mensaje se envia desde el LPC a la PC.
 * SUB_TEMP:       Subcomando que notifica la temperatura del ambiente. Este mensaje se envia desde el LPC a la PC.
 * SUB_LVLH2O:     Subcomando que notifica nivel de H2O en tanque. Este mensaje se envia desde el LPC a la PC.
 * SUB_ALARM:      ---Ver---
 * SUB_CONN_PC:    Subcomando que notifica cuando la pc se conecta al LPC para habilitar la transmision de los datos anteriores por UART.
 * SUB_DESCONN_PC: Subcomando que notifica cuando la pc se desconecta al LPC para deshabilitar la transmision de los datos anteriores por UART.
 */

sub_command_t sub_informar[] = {{SUB_HUMEDAD,1},{SUB_TEMP,1},{SUB_LVLH2O,1},{SUB_ALARM,1},{SUB_CONN_PC,1},{SUB_DESCONN_PC,1}};

/*=======================================================*
 *        Sub Comandos del comando configurar            *
 *====================================================== */
/* SUB_UMBRAL_H:   subcomando que configura el umbral de humedad minima. Este mensaje se envia desde la PC al LPC.
 * SUB_TIME_R:     Subcomando que configura el tiempo de regado. Este mensaje se envia desde la PC al LPC.
 * SUB_UMRAL_H2O:  Subcomando que configura el umbral de H2O minima en tanque. Este mensaje se envia desde la PC al LPC.
 * SUB_UMRAL_TEMP: Subcomando que configura el umbral de temperatura maxima. Este mensaje se envia desde la PC al LPC.
 * SUB_HORA:       Subcomando que configura la hora del LPC. Este mensaje se envia desde la PC al LPC. Se utilizan 3 bytes, uno para la hora, otro para los minutos, y otro para los segundos.
 * SUB_FECHA:      Subcomando que configura la fecha del LPC. Este mensaje se envia desde la PC al LPC. Se utilizan 4 bytes. 2 para representar el año, 1 para el mes, y otro para el día.
 */
sub_command_t sub_configurar[] = {{SUB_UMBRAL_H,1},{SUB_TIME_R,1},{SUB_UMRAL_H2O,1},{SUB_UMRAL_TEMP,1},{SUB_HORA,3},{SUB_FECHA,4}};

/*=======================================================*
 *            Sub Comandos del comando regar             *
 *====================================================== */
/* SUB_REGAR:    Subcomando que ordena al LPC a activar el riego. Esta orden se envia desde la PC al LPC cuando se activa el riego de forma manual.
 */
sub_command_t sub_regar[] = {{SUB_REGAR,1}};

/*=======================================================*
 *            Sub Comandos del comando query             *
 *====================================================== */
/* SUB_UMBRAL_H:   subcomando que consulta el umbral de humedad minima. Este mensaje se envia desde la PC al LPC.
 * SUB_TIME_R:     Subcomando que consulta el tiempo de regado. Este mensaje se envia desde la PC al LPC.
 * SUB_UMRAL_H2O:  Subcomando que consulta el umbral de H2O minima en tanque. Este mensaje se envia desde la PC al LPC.
 * SUB_UMRAL_TEMP: Subcomando que consulta el umbral de temperatura maxima. Este mensaje se envia desde la PC al LPC.
 */
sub_command_t sub_query[] = {{SUB_UMBRAL_H,1},{SUB_TIME_R,2},{SUB_UMRAL_H2O,1},{SUB_UMRAL_TEMP,1}};

/*=======================================================*
 *              Sub Comandos del comando ack             *
 *====================================================== */
sub_command_t sub_ack[] = {{0,0}}; //No tiene subcomandos

/*=======================================================*
 *                      COMANDOS                         *
 *====================================================== */
/* COM_INFORMAR: Notificaciones.
 * COM_CONFIG:   Configuraciones.
 * COM_ACK:      Respuesta de un mensaje.
 * COM_REGAR:    Orden de Riego.
 * COM_QUERY:    Consultas.
 */
command_t commands[] = {{COM_INFORMAR,sub_informar},{COM_CONFIG,sub_configurar},{COM_ACK,sub_ack},{COM_REGAR,sub_regar},{COM_QUERY,sub_query}};
