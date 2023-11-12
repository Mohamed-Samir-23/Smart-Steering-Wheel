/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: SYSTICK				*/
/*  Layer		: MCAL					*/
/*  Version		: 1.0					*/
/*  Date		: October 10, 2023		*/
/*  Last Edit	: November 10, 2023		*/
/****************************************/


#ifndef _MSYSTICK_INTERFACE_H_
#define _MSYSTICK_INTERFACE_H_


typedef enum 
{
	AHB_DIV_8 = 0,
	AHB,
	
}MSYSTICK_CLkSRC_t;


STD_error_t MSYSTICK_stderrorInit
(
	MSYSTICK_CLkSRC_t ARG_udtCLkSRC
);


STD_error_t MSYSTICK_stderrorSetBusyWait
(
	u32 ARG_u32Ticks
);

STD_error_t MSYSTICK_stderrorSetSingleInterval
(
	u32 ARG_u32Ticks,
	void (*ARG_pvoidfUserFunction)(void)
);

STD_error_t MSYSTICK_stderrorSetPeriodiceInterval
(
	u32 ARG_u32Ticks,
	void (*ARG_pvoidfUserFunction)(void)
);


void MSYSTICK_voidStopTICK
(
	void
);

u32 MSYSTICK_voidElepsedTime
(
	void
);

u32 MSYSTICK_voidRemainingTime
(
	void
);

void MSYSTICK_EnableInterrupt
(
	void
);

void MSYSTICK_DisableInterrupt
(
	void
);

void MSYSTICK_Delay_Ms
( 
	u32 ARG_u32Time 
);

void MSYSTICK_Delay_us
( 
	u32 ARG_u32Time
);


#endif
