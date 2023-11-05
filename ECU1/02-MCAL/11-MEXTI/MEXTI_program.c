/************************************/
/*  Author:     MOHAMED ABOUBAKR    */
/*  SWC:        EXTERNAL INTERRUPT  */
/*  Layer:      MCAL                */
/*  Version:    1.0                 */
/*  Date:       NOVEMBER 05, 2023   */
/************************************/

/*library Includes*/
#include "LSTD_types.h"
#include "LBIT_math.h"

/*SWC Includes*/
#include "MEXTI_private.h"
#include "MEXTI_interface.h"

void (*MEXTI0_CallBack)  (void);
void (*MEXTI1_CallBack)  (void);
void (*MEXTI2_CallBack)  (void);
void (*MEXTI3_CallBack)  (void);
void (*MEXTI4_CallBack)  (void);
void (*MEXTI5_CallBack)  (void);
void (*MEXTI6_CallBack)  (void);
void (*MEXTI7_CallBack)  (void);
void (*MEXTI8_CallBack)  (void);
void (*MEXTI10_CallBack) (void);
void (*MEXTI11_CallBack) (void);
void (*MEXTI12_CallBack) (void);
void (*MEXTI13_CallBack) (void);
void (*MEXTI14_CallBack) (void);
void (*MEXTI15_CallBack) (void);


STD_error_t MEXTI_stderrorInit
(
	MEXTI_Interupt_Lines_t ARG_udtEXTILine,
	MEXTI_Interupt_Edge ARG_udtEXTIEdge
)
{
	
	STD_error_t L_stderrorError = E_NOK;
	
	switch(ARG_u8EdgeMode)
	{
		case INPUT_RISING_EDGE:
		{
			SET_BIT(EXTI->RTSR , ARG_udtEXTILine);
			break;
		}
		
		case INPUT_FALLING_EDGE:
		{
			SET_BIT(EXTI->FTSR , ARG_udtEXTILine);
			break;
		}
		
		case INPUT_ON_CHANGE:
		{
			SET_BIT(EXTI->RTSR , ARG_udtEXTILine);
			SET_BIT(EXTI->FTSR , ARG_u8LineSource);
			break;
		}
		
		default:
		L_stderrorError = E_OK;
		break;
	}
	return L_stderrorError;
}




void MEXTI_voidEnableInterrupt
(
	MEXTI_Interupt_Lines_t ARG_udtEXTILine,
)
{
	SET_BIT(EXTI->IMR, ARG_udtEXTILine);
}




void MEXTI_voidDisableInterrupt
(
	MEXTI_Interupt_Lines_t ARG_udtEXTILine,
)
{
	CLR_BIT(EXTI->IMR, ARG_udtEXTILine);
}



void MEXTI_voidSoftWareTrigger
(
	MEXTI_Interupt_Lines_t ARG_udtEXTILine,
)
{
	SET_BIT(EXTI->SWIER, ARG_udtEXTILine );
}




void (*EXTI0_CallBack) (void);



STD_error_t MEXTI_stderrorSetCallback
(
	void (*ARG_pvoidfUserFunction) (void),
	MEXTI_Interupt_IRQn_t ARG_udtEXTIIRQn
)
{
	STD_error_t L_stderrorError = E_NOK;
	if(ARG_pvoidfUserFunction != NULL_POINTER)
	{
		switch(ARG_udtEXTIIRQn)
		{
			case EXTI0_IRQn:
			{
				MEXTI_pvoidfUserFunctionINT0 = ARG_pvoidfUserFunction;
				break;
			}
			case EXTI1_IRQn:
			{
				MEXTI_pvoidfUserFunctionINT1 = ARG_pvoidfUserFunction;
				break;
			}
			case EXTI2_IRQn:
			{
				MEXTI_pvoidfUserFunctionINT2 = ARG_pvoidfUserFunction;
				break;
			}
			case EXTI3_IRQn:
			{
				MEXTI_pvoidfUserFunctionINT3 = ARG_pvoidfUserFunction;
				break;
			}
			case EXTI4_IRQn:
			{
				MEXTI_pvoidfUserFunctionINT4 = ARG_pvoidfUserFunction;
				break;
			}
			case EXTI5_IRQn:
			{
				MEXTI_pvoidfUserFunctionINT5 = ARG_pvoidfUserFunction;
				break;
			}
			case EXTI6_IRQn:
			{
				MEXTI_pvoidfUserFunctionINT6 = ARG_pvoidfUserFunction;
				break;
			}
			case EXTI7_IRQn:
			{
				MEXTI_pvoidfUserFunctionINT7 = ARG_pvoidfUserFunction;
				break;
			}
			case EXTI8_IRQn:
			{
				MEXTI_pvoidfUserFunctionINT8 = ARG_pvoidfUserFunction;
				break;
			}
			case EXTI9_IRQn:
			{
				MEXTI_pvoidfUserFunctionINT9 = ARG_pvoidfUserFunction;
				break;
			}
			case EXTI10_IRQn:
			{
				MEXTI_pvoidfUserFunctionINT10 = ARG_pvoidfUserFunction;
				break;
			}
			case EXTI11_IRQn:
			{
				MEXTI_pvoidfUserFunctionINT11 = ARG_pvoidfUserFunction;
				break;
			}
			case EXTI12_IRQn:
			{
				MEXTI_pvoidfUserFunctionINT12 = ARG_pvoidfUserFunction;
				break;
			}
			case EXTI13_IRQn:
			{
				MEXTI_pvoidfUserFunctionINT13 = ARG_pvoidfUserFunction;
				break;
			}
			case EXTI14_IRQn:
			{
				MEXTI_pvoidfUserFunctionINT14 = ARG_pvoidfUserFunction;
				break;
			}
			case EXTI15_IRQn:
			{
				MEXTI_pvoidfUserFunctionINT15 = ARG_pvoidfUserFunction;
				break;
			}
			
			default:
			{
				/*nothing*/
				break;
			}
		}
	}
	else
	{
		L_stderrorError=E_NULL_POINTER;
	}
	
	return L_stderrorError;
}





void EXTI0_IRQHandler(void)
{
	MEXTI0_CallBack();
	SET_BIT( EXTI->PR , 0 );
}

void EXTI1_IRQHandler(void)
{
	MEXTI1_CallBack();
	SET_BIT( EXTI->PR , 1 );
}

void EXTI2_IRQHandler(void)
{
	MEXTI2_CallBack();
	SET_BIT( EXTI->PR , 2 );
}

void EXTI3_IRQHandler(void)
{
	MEXTI3_CallBack();
	SET_BIT( EXTI->PR , 3 );
}

void EXTI4_IRQHandler(void)
{
	MEXTI4_CallBack();
	SET_BIT( EXTI->PR , 4 );
}

void EXTI5_IRQHandler(void)
{
	MEXTI5_CallBack();
	SET_BIT( EXTI->PR , 5 );
}

void EXTI6_IRQHandler(void)
{
	MEXTI6_CallBack();
	SET_BIT( EXTI->PR , 6 );
}

void EXTI7_IRQHandler(void)
{
	MEXTI7_CallBack();
	SET_BIT( EXTI->PR , 7 );
}

void EXTI8_IRQHandler(void)
{
	MEXTI8_CallBack();
	SET_BIT( EXTI->PR , 8 );
}

void EXTI9_IRQHandler(void)
{
	MEXTI9_CallBack();
	SET_BIT( EXTI->PR , 9 );
}

void EXTI10_IRQHandler(void)
{
	MEXTI10_CallBack();
	SET_BIT( EXTI->PR , 10 );
}

void EXTI11_IRQHandler(void)
{
	MEXTI11_CallBack();
	SET_BIT( EXTI->PR , 11 );
}

void EXTI12_IRQHandler(void)
{
	MEXTI12_CallBack();
	SET_BIT( EXTI->PR , 12 );
}

void EXTI13_IRQHandler(void)
{
	MEXTI13_CallBack();
	SET_BIT( EXTI->PR , 13 );
}

void EXTI14_IRQHandler(void)
{
	MEXTI14_CallBack();
	SET_BIT( EXTI->PR , 14 );
}

void EXTI15_IRQHandler(void)
{
	MEXTI15_CallBack();
	SET_BIT( EXTI->PR , 15 );
}