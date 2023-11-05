/************************************/
/*  Author:     MOHAMED ABOUBAKR    */
/*  SWC:        EXTERNAL INTERRUPT  */
/*  Layer:      MCAL                */
/*  Version:    1.0                 */
/*  Date:       NOVEMBER 05, 2023   */
/************************************/

#ifndef _MEXTI_INTERFACE_H_
#define _MEXTI_INTERFACE_H_

typedef enum
{
	EXTI0_LINE   = 0,
	EXTI1_LINE   = 1,
	EXTI2_LINE   = 2,
	EXTI3_LINE   = 3,
	EXTI4_LINE   = 4,
	EXTI5_LINE   = 5,
	EXTI6_LINE   = 6,
	EXTI7_LINE   = 7,
	EXTI8_LINE   = 8,
	EXTI9_LINE   = 9,
	EXTI10_LINE  = 10,
	EXTI11_LINE  = 11,
	EXTI12_LINE  = 12,
	EXTI13_LINE  = 13,
	EXTI14_LINE  = 14,
	EXTI15_LINE  = 15,

}MEXTI_Interupt_Lines_t;

typedef enum
{
	EXTI0_IRQn  = 6,
	EXTI1_IRQn  = 7,
	EXTI2_IRQn  = 8,
	EXTI3_IRQn  = 9,
	EXTI4_IRQn  = 10,
	EXTI5_IRQn  = 23,
	EXTI6_IRQn  = 23,
	EXTI7_IRQn  = 23,
	EXTI8_IRQn  = 23,
	EXTI9_IRQn  = 23,
	EXTI10_IRQn = 40,
	EXTI11_IRQn = 40,
	EXTI12_IRQn = 40,
	EXTI13_IRQn = 40,
	EXTI14_IRQn = 40,
	EXTI15_IRQn = 40,

}MEXTI_Interupt_IRQn_t;

typedef enum
{
	INPUT_RISING_EDGE   = 0,
	INPUT_FALLING_EDGE  = 1,
	INPUT_ON_CHANGE     = 2,
	
}MEXTI_Interupt_Edge;




STD_error_t MEXTI_stderrorInit
(
	MEXTI_Interupt_Lines_t ARG_udtEXTILine,
	MEXTI_Interupt_Edge ARG_udtEXTIEdge
);

void MEXTI_voidEnableInterrupt
(
	MEXTI_Interupt_Lines_t ARG_udtEXTILine,
);

void MEXTI_voidDisableInterrupt
(
	MEXTI_Interupt_Lines_t ARG_udtEXTILine,
);

void MEXTI_voidSoftWareTrigger
(
	MEXTI_Interupt_Lines_t ARG_udtEXTILine,
);

STD_error_t MEXTI_stderrorSetCallback
(
	void (*ARG_pvoidfUserFunction) (void),
	MEXTI_Interupt_IRQn_t ARG_udtEXTIIRQn
);


#endif