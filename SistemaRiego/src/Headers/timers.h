/*
 * timers.h
 *
 *  Created on: 9 de nov. de 2016
 *      Author: Martin
 */

#ifndef HEADERS_TIMERS_H_
#define HEADERS_TIMERS_H_

#define T0IR   (*((registro_t *) 0x40004000UL))
#define T1IR   (*((registro_t *) 0x40008000UL))
#define T2IR   (*((registro_t *) 0x40090000UL))
#define T3IR   (*((registro_t *) 0x40094000UL))

#define T0TCR  (*((registro_t *) 0x40004004UL))
#define T1TCR  (*((registro_t *) 0x40008004UL))
#define T2TCR  (*((registro_t *) 0x40090004UL))
#define T3TCR  (*((registro_t *) 0x40094004UL))

#define T0TC   (*((registro_t *) 0x40004008UL))
#define T1TC   (*((registro_t *) 0x40008008UL))
#define T2TC   (*((registro_t *) 0x40090008UL))
#define T3TC   (*((registro_t *) 0x40094008UL))

#define T0PR   (*((registro_t *) 0x4000400CUL))
#define T1PR   (*((registro_t *) 0x4000800CUL))
#define T2PR   (*((registro_t *) 0x4009000CUL))
#define T3PR   (*((registro_t *) 0x4009400CUL))

#define T0PC   (*((registro_t *) 0x40004010UL))
#define T1PC   (*((registro_t *) 0x40008010UL))
#define T2PC   (*((registro_t *) 0x40090010UL))
#define T3PC   (*((registro_t *) 0x40094010UL))

#define T0MCR  (*((registro_t *) 0x40004014UL))
#define T1MCR  (*((registro_t *) 0x40008014UL))
#define T2MCR  (*((registro_t *) 0x40090014UL))
#define T3MCR  (*((registro_t *) 0x40094014UL))

#define T0MR0  (*((registro_t *) 0x40004018UL))
#define T1MR0  (*((registro_t *) 0x40008018UL))
#define T2MR0  (*((registro_t *) 0x40090018UL))
#define T3MR0  (*((registro_t *) 0x40094018UL))

#define T0MR1  (*((registro_t *) 0x4000401CUL))
#define T1MR1  (*((registro_t *) 0x4000801CUL))
#define T2MR1  (*((registro_t *) 0x4009001CUL))
#define T3MR1  (*((registro_t *) 0x4009401CUL))

#define T0MR2  (*((registro_t *) 0x40004020UL))
#define T1MR2  (*((registro_t *) 0x40008020UL))
#define T2MR2  (*((registro_t *) 0x40090020UL))
#define T3MR2  (*((registro_t *) 0x40094020UL))

#define T0MR3  (*((registro_t *) 0x40004024UL))
#define T1MR3  (*((registro_t *) 0x40008024UL))
#define T2MR3  (*((registro_t *) 0x40090024UL))
#define T3MR3  (*((registro_t *) 0x40094024UL))

#define T0CCR  (*((registro_t *) 0x40004028UL))
#define T1CCR  (*((registro_t *) 0x40008028UL))
#define T2CCR  (*((registro_t *) 0x40090028UL))
#define T3CCR  (*((registro_t *) 0x40094028UL))

#define T0CR0  (*((registro_t *) 0x4000402CUL))
#define T1CR0  (*((registro_t *) 0x4000802CUL))
#define T2CR0  (*((registro_t *) 0x4009002CUL))
#define T3CR0  (*((registro_t *) 0x4009402CUL))

#define T0CR1  (*((registro_t *) 0x40004030UL))
#define T1CR1  (*((registro_t *) 0x40008030UL))
#define T2CR1  (*((registro_t *) 0x40090030UL))
#define T3CR1  (*((registro_t *) 0x40094030UL))

#define T0EMR  (*((registro_t *) 0x4000403CUL))
#define T1EMR  (*((registro_t *) 0x4000803CUL))
#define T2EMR  (*((registro_t *) 0x4009003CUL))
#define T3EMR  (*((registro_t *) 0x4009403CUL))

#define T0CTCR (*((registro_t *) 0x40004070UL))
#define T1CTCR (*((registro_t *) 0x40008070UL))
#define T2CTCR (*((registro_t *) 0x40090070UL))
#define T3CTCR (*((registro_t *) 0x40094070UL))

#endif /* HEADERS_TIMERS_H_ */
