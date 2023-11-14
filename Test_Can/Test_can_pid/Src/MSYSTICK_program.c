/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: SYSTICK				*/
/*  Layer		: MCAL					*/
/*  Version		: 1.1					*/
/*  Date		: October  10, 2023		*/
/*  Last Edit	: November 10, 2023		*/
/****************************************/

/* Library Include */
#include "LSTD_types.h"

/* SWC Include */
#include "MSYSTICK_private.h"
#include "MSYSTICK_config.h"
#include "MSYSTICK_interface.h"

static void (*MSYSTICK_pvoidfUserFunctionSysTick)(void) =NULL_POINTER;

static u8 MSYSTICK_u8SelectISR;

STD_error_t MSYSTICK_stderrorInit
(
	MSYSTICK_CLkSRC_t ARG_udtCLkSRC
)
{
	STD_error_t L_stderrorError=E_NOK;
	
	if(ARG_udtCLkSRC <=1)
	{
		/*Disable SysTick peripheral and SysTick interrupt*/
		STK_CTRL =(STK_CTRL&(~STK_CTRL_Flag));
		/*Select Clock Source*/
		STK_CTRL|=(ARG_udtCLkSRC<<2);
		L_stderrorError=E_OK;
		
	}
	else
	{
		L_stderrorError=E_NOK;
	}
	
	return L_stderrorError;
}




STD_error_t MSYSTICK_stderrorSetBusyWait
(
	u32 ARG_u32Ticks
)
{
	STD_error_t L_stderrorError=E_NOK;
	STK_LOAD =ARG_u32Ticks-1;
	STK_VAL=0;
	STK_CTRL |=1U;
	while(((STK_CTRL>>16)&1)!=1);
	STK_CTRL =0;
	return L_stderrorError;
}



STD_error_t MSYSTICK_stderrorSetSingleInterval
(
	u32 ARG_u32Ticks,
	void (*ARG_pvoidfUserFunction)(void)
)
{
	STD_error_t L_stderrorError=E_NOK;
	
	if(ARG_pvoidfUserFunction != NULL_POINTER)
	{
		MSYSTICK_voidStopTICK();
		STK_VAL=0;
		MSYSTICK_u8SelectISR=0;
		MSYSTICK_pvoidfUserFunctionSysTick=ARG_pvoidfUserFunction;
		STK_LOAD =ARG_u32Ticks;
		STK_CTRL |=3U;
		L_stderrorError=E_OK;
	}
	else
	{
		L_stderrorError=E_NULL_POINTER;
	}
	
	return L_stderrorError;
}


STD_error_t MSYSTICK_stderrorSetPeriodiceInterval
(
	u32 ARG_u32Ticks,
	void (*ARG_pvoidfUserFunction)(void)
)
{
	
	STD_error_t L_stderrorError=E_NOK;
	
	if(ARG_pvoidfUserFunction != NULL_POINTER)
	{
		MSYSTICK_u8SelectISR=1;
		MSYSTICK_pvoidfUserFunctionSysTick=ARG_pvoidfUserFunction;
		STK_LOAD =ARG_u32Ticks;
		STK_CTRL |=3U;
		L_stderrorError=E_OK;
	}
	else
	{
		L_stderrorError=E_NULL_POINTER;
	}
	
	return L_stderrorError;
}


void MSYSTICK_voidStopTICK
(
	void
)
{
	STK_CTRL &=~(3U);
}


u32 MSYSTICK_voidElepsedTime
(
	void
)
{
	return (STK_LOAD-STK_VAL);
}


u32 MSYSTICK_voidRemainingTime
(
	void
)
{
	return STK_VAL;
}


void MSYSTICK_EnableInterrupt
(
	void
)
{
	STK_CTRL |=(1<<1);
}


void MSYSTICK_DisableInterrupt
(
	void
)
{
	
	STK_CTRL &=(~(1<<1));
}


void MSYSTICK_Delay_Ms
( 
	u32 ARG_u32Time 
)
{
	MSYSTICK_DisableInterrupt();
	MSYSTICK_stderrorSetBusyWait(ARG_u32Time * 1000);
}

void MSYSTICK_Delay_us
( 
	u32 ARG_u32Time
)
{
	MSYSTICK_DisableInterrupt();
	MSYSTICK_stderrorSetBusyWait(ARG_u32Time);
}


void SysTick_Handler(void)
{
	
	if(MSYSTICK_u8SelectISR ==0)
	{
		
		MSYSTICK_pvoidfUserFunctionSysTick();
		STK_CTRL &=~(3U);
	}
	else if(MSYSTICK_u8SelectISR ==1)
	{
		MSYSTICK_pvoidfUserFunctionSysTick();
	}
	else
	{
		
	}
}
