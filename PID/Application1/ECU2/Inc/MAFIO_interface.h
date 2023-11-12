/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: AFIO					*/
/*  Layer		: MCAL					*/
/*  Version		: 1.0					*/
/*  Date		: November 10, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/

#ifndef _MAFIO_INTERFACE_H_
#define _MAFIO_INTERFACE_H_

typedef enum 
{
	MAFIO_GPIOA = 0,
	MAFIO_GPIOB = 1,
	MAFIO_GPIOC = 2,
	
}MAFIO_Port_Name_t;


typedef enum 
{
	
	AFIO_EXTI0=0, 
	AFIO_EXTI1,
	AFIO_EXTI2,
	AFIO_EXTI3,
	AFIO_EXTI4,
	AFIO_EXTI5,
	AFIO_EXTI6,
	AFIO_EXTI7,
	AFIO_EXTI8,
	AFIO_EXTI9,
	AFIO_EXTI10,
	AFIO_EXTI11,
	AFIO_EXTI12,
	AFIO_EXTI13,
	AFIO_EXTI14,
	AFIO_EXTI15,
	
}MAFIO_Line_t;


STD_error_t AFIO_VidSetEXTIConfiguration
( 
	MAFIO_Line_t ARG_udtAFIO_Line, 
	MAFIO_Port_Name_t ARG_udtPortMap 
);

#endif 
