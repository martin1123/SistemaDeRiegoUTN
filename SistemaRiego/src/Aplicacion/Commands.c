/**
	\file Commands.c
	\brief Comandos de comunicacion
	\details Definicion de los comandos utilizados para la comunicacion con la computadora
	         a través de puerto serie.
	\author Grupo II, curso R2053
	\version 1.0.0
*/

#include "infotronic.h"
#include "Commands.h"

sub_command_t sub_informar[] = {{SUB_HUMEDAD,1},{SUB_TEMP,1},{SUB_LVLH2O,1},{SUB_ALARM,1}};

sub_command_t sub_configurar[] = {{SUB_UMBRAL_H,1},{SUB_TIME_R,2},{SUB_UMRAL_H2O,1},{SUB_UMRAL_TEMP,1},{SUB_HORA,3},{SUB_FECHA,4}};

sub_command_t sub_regar[] = {{SUB_REGAR,1}};

sub_command_t sub_query[] = {{SUB_UMBRAL_H,1},{SUB_TIME_R,2},{SUB_UMRAL_H2O,1},{SUB_UMRAL_TEMP,1}};

sub_command_t sub_ack[] = {{0,0}}; //No tiene subcomandos

command_t commands[] = {{COM_INFORMAR,sub_informar},{COM_CONFIG,sub_configurar},{COM_ACK,sub_ack},{COM_REGAR,sub_regar},{COM_QUERY,sub_query}};
