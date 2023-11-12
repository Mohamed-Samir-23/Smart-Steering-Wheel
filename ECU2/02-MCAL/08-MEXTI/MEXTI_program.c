/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: EXTI					*/
/*  Layer		: MCAL					*/
/*  Version		: 1.0					*/
/*  Date		: November 10, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/

/* Library Include */
#include "LSTD_types.h"

/* SWC Include */
#include "MEXTI_private.h"
#include "MEXTI_config.h"
#include "MEXTI_interface.h"

void (*MEXTI_pvoidfCallBack)(void) =NULL_POINTER;


STD_error_t MEXTI_stderrorTriggerMode
(
	MEXTI_Line_t ARG_udtEXTILine,
	MEXTI_ModeTrigger_t ARG_udtEXTIMode
)
{
	STD_error_t L_stderrorError=E_NOK;
	
	if((ARG_udtEXTILine<=15)&&(ARG_udtEXTIMode<=2))
	{
		
		switch(ARG_udtEXTIMode)
		{
			case RISING_EDGE:
			{
				EXTI->RTSR |= (1<<ARG_udtEXTILine);;
				break;
			}
			case FALLING_EDGE:
			{
				EXTI->FTSR |= (1<<ARG_udtEXTILine);;
				break;
			}
			case ON_CHANGE:
			{
				EXTI->RTSR |=(1<<ARG_udtEXTILine);;
				EXTI->FTSR |=(1<<ARG_udtEXTILine);;
				break;
			}
			default:
			{
				/*Nothing*/
				break;
			}
		}
		
		L_stderrorError=E_OK;
	}
	else
	{
		L_stderrorError=E_NOK;
	}
	
	return L_stderrorError;
}

void MEXTI_VoidEnableEXTI
( 
	MEXTI_Line_t ARG_udtEXTILine
)
{
	EXTI->IMR |=(1<<ARG_udtEXTILine);
}

void MEXTI_VoidDisableEXTI
( 
	MEXTI_Line_t ARG_udtEXTILine
)
{

	EXTI->IMR &=~(1<<ARG_udtEXTILine);
}

void MEXTI_VoidSoftWareTrigger
( 
	MEXTI_Line_t ARG_udtEXTILine
)
{
	EXTI->SWIER |=(1<<ARG_udtEXTILine);	
}


void MEXTI_VoidSetCallBack
( 
	void (*ARG_pvoidfUserFunction) (MEXTI_Line_t ARG_udtEXTILine) 
)
{
	STD_error_t L_stderrorError=E_NOK;
	
	if(NULL_POINTER!=ARG_pvoidfUserFunction)
	{
		MEXTI_pvoidfCallBack = ARG_pvoidfUserFunction;
	}
	else
	{
		L_stderrorError=E_NULL_POINTER;
	}
	return L_stderrorError;
}


void EXTI0_IRQHandler(void)
{
	MEXTI_pvoidfCallBack(EXTI_LINE0);
	
	EXTI->PR |=(1<<EXTI_LINE0);
}

void EXTI1_IRQHandler(void)
{
	MEXTI_pvoidfCallBack(EXTI_LINE1);
	EXTI->PR |=(1<<EXTI_LINE1);
}
