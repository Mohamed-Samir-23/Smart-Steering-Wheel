/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: EXTI					*/
/*  Layer		: MCAL					*/
/*  Version		: 1.0					*/
/*  Date		: November 10, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/


#ifndef _MEXTI_INTERFACE_H_
#define _MEXTI_INTERFACE_H_

typedef enum 
{
	
	EXTI_LINE0=0, 
	EXTI_LINE1,
	EXTI_LINE2,
	EXTI_LINE3,
	EXTI_LINE4,
	EXTI_LINE5,
	EXTI_LINE6,
	EXTI_LINE7,
	EXTI_LINE8,
	EXTI_LINE9,
	EXTI_LINE10,
	EXTI_LINE11,
	EXTI_LINE12,
	EXTI_LINE13,
	EXTI_LINE14,
	EXTI_LINE15,
	
}MEXTI_Line_t


typedef enum 
{
	EXTI_LINE0IRQn=6, 
	EXTI_LINE1IRQn=7,
	EXTI_LINE2IRQn=8,
	EXTI_LINE3IRQn=9,
	EXTI_LINE4IRQn=10,
	EXTI_LINE5IRQn=23,
	EXTI_LINE6IRQn=23,
	EXTI_LINE7IRQn=23,
	EXTI_LINE8IRQn=23,
	EXTI_LINE9IRQn=23,
	EXTI_LINE10IRQn=40,
	EXTI_LINE11IRQn=40,
	EXTI_LINE12IRQn=40,
	EXTI_LINE13IRQn=40,
	EXTI_LINE14IRQn=40,
	EXTI_LINE15IRQn=40,
	
}MEXTI_IRQn_t


typedef enum 
{
	
	RISING_EDGE  = 0,
	FALLING_EDGE = 1,
	ON_CHANGE = 2,

}MEXTI_ModeTrigger_t



STD_error_t MEXTI_stderrorTriggerMode
(
	MEXTI_Line_t ARG_udtEXTILine,
	MEXTI_ModeTrigger_t ARG_udtEXTIMode
);

void MEXTI_VoidEnableEXTI
( 
	MEXTI_Line_t ARG_udtEXTILine
);

void MEXTI_VoidDisableEXTI
( 
	MEXTI_Line_t ARG_udtEXTILine
);

void MEXTI_VoidSoftWareTrigger
( 
	MEXTI_Line_t ARG_udtEXTILine
);

void MEXTI_VoidSetCallBack
( 
	void (*ARG_pvoidfUserFunction) (MEXTI_Line_t ARG_udtEXTILine) 
);


#endif 
