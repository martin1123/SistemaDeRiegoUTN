#ifndef __INFOTRONIC__
#define __INFOTRONIC__

#include "types.h"
#include "gpio.h"
#include "systick.h"
#include "states.h"
#include "pinConf.h"
#include "uart1.h"
#include "serial.h"

//Humedad tierra
extern volatile float humedad;

//Temperatura ambiente
extern volatile float temp;

//Porcentaje de nivel de agua en tanque
extern volatile uint8_t lvlH2O;


#endif
