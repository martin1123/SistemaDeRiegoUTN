/**
	\file Commands.h
	\brief Header de los comandos de comunicacion
	\details
	\author Grupo II, curso R2053
	\version 1.0.0
*/

#ifndef HEADERS_COMMANDS_H_
#define HEADERS_COMMANDS_H_

/*COMANDOS*/
#define COM_INFORMAR   0x49
#define COM_ACK        0x41
#define COM_REGAR      0x52
#define COM_CONFIG     0x43
#define COM_QUERY      0x51

/*SUB-COMANDOS*/
#define SUB_HUMEDAD    0x48
#define SUB_TEMP       0x54
#define SUB_LVLH2O     0x4E
#define SUB_ALARM      0x41
#define SUB_UMBRAL_H   0x4B
#define SUB_TIME_R     0x54
#define SUB_UMRAL_H2O  0x4C
#define SUB_UMRAL_TEMP 0x4A
#define SUB_HORA       0x48
#define SUB_FECHA      0x46
#define SUB_MACETA     0x41
#define SUB_REGAR      0x41
#define SUB_CONN_PC    0x58
#define SUB_DESCONN_PC 0x59

/*Posiciones en array de estructuras de los comandos y subcomandos*/
#define POS_COM_INFORM         0
#define POS_COM_CONF           1
#define POS_COM_ACK        	   2
#define POS_COM_REGAR          3
#define POS_COM_QUERY          4
/*Posiciones comandos de notificacion*/
#define POS_SUBCOM_HUMEDAD     0
#define POS_SUBCOM_TEMP        1
#define POS_SUBCOM_LVLH2O      2
#define POS_SUBCOM_ALARM       3
#define POS_SUBCOM_CONN_PC     4
#define POS_SUBCOM_DESCONN_PC  5
/*Posiciones Subcomando ACK*/
#define POS_SUBCOM_ACK         0
/*Posiciones sub comandos de configuracion. Los primeros 4 tambien conrresponden a los subcomandos de consulta(query)*/
#define POS_SUBCOM_UMBRAL_HUM  0
#define POS_SUBCOM_TIME_REG    1
#define POS_SUBCOM_UMBRAL_H2O  2
#define POS_SUBCOM_UMBRAL_TEMP 3
#define POS_SUBCOM_HORA        4
#define POS_SUBCOM_FECHA       5

//Tamaño del vector de las estruturas
#define SIZE_COMMANDS       5
#define SIZE_SUB_INFORMAR   6
#define SIZE_SUB_CONFIGURAR 6
#define SIZE_SUB_QUERY      4
#define SIZE_SUB_REGAR      1
#define SIZE_SUB_ACK        1

typedef struct{
	uint8_t subCommand;
	uint8_t sz; //Cantidad de bytes que ocupan los parametros del subcomando. Por ejemplo en temperatura va a ser un byte, mientras
	            //que para fecha y hora van a ser 2 bytes
}sub_command_t;

typedef struct{
	uint8_t command;
	sub_command_t *sub;
}command_t;

extern sub_command_t sub_informar[];
extern sub_command_t sub_configurar[];
extern sub_command_t sub_regar[];
extern sub_command_t sub_query[];
extern sub_command_t sub_ack[];
extern command_t commands[];


#endif /* HEADERS_COMMANDS_H_ */
