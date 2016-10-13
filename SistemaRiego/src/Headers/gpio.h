/**
 *En este Header se encuentran todas las macros necesarias para la configuracion, lectura 
 *y escritura de los pines GPIO
 */

#ifndef __GPIO__
#define __GPIO__

typedef struct{
	volatile uint32_t fiodir;
	volatile uint32_t reserved[3];
	volatile uint32_t fiomask;
	volatile uint32_t fiopin;
	volatile uint32_t fioset;
	volatile uint32_t fioclr;
}GPIO_T;

/*Puntero a registro GPIO0*/
#define GPIO_BASE ((GPIO_T *) 0x2009C000UL)

#define set_dir(port,pin,dir) ((dir)?((GPIO_BASE + port)->fiodir |= (1 << pin)):((GPIO_BASE + port)->fiodir &= ~(1 << pin)))

#define write_pin(port,pin,val) ((val)?((GPIO_BASE + port)->fioset |= (1 << pin)):((GPIO_BASE + port)->fioclr |= (1 << pin)))

#define read_pin(port,pin) ((((GPIO_BASE + port)->fiopin) >> pin) & 0x01)

#define conf_gpio(port,pin,dir) {(*(DIR_PINSEL0 + (port * 2) + (pin / 16)) &= ~(0x3 <<((pin%16) * 2))); set_dir(port,pin,dir);}

#endif
