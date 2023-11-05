/************************************/
/*  Author:     MOHAMED ABOUBAKR    */
/*  SWC:        EXTERNAL INTERRUPT  */
/*  Layer:      MCAL                */
/*  Version:    1.0                 */
/*  Date:       NOVEMBER 05, 2023   */
/************************************/

#ifndef _MEXTI_PRIVATE_H_
#define _MEXTI_PRIVATE_H_

typedef struct
{
	volatile u32 IMR;		//Interrupt mask register
	volatile u32 EMR;		//Event mask register
	volatile u32 RTSR;		//Rising trigger selection register
	volatile u32 FTSR;		//Falling trigger selection register
	volatile u32 SWIER;		//Software interrupt event register
	volatile u32 PR;		//Pending register
}EXTI_t;

#define EXTI	((volatile EXTI_t*)0x40010400)

#endif