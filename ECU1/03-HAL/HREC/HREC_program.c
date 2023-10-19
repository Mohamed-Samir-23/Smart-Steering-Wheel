/************************************/
/*	Auothor: 	mBravo18			*/
/*	SWC: 		ROTARY ENCODER		*/
/*	Layer: 		HAL					*/
/*	Version: 	1.0					*/
/*	Date: 		OCTOBER 16, 2023	*/
/*	End Edit:	N/A					*/
/************************************/

/* Library Includes */
#include "LSTD_types.h"
#include "LBIT_math.h"

/* MCAL Includes */
#include "MGPIO_interface.h"

/* SWC Includes */
#include "HREC_interface.h"
#include "HREC_private.h"
#include "HREC_config.h"

u16 PulsePerRev = 600;
u16 counter = PulsePerRev;
u16 angle;
u8 aStartState;
u8 aEndState;

void HREC_voidInit(void)
{
	MGPIO_stderrorPinModeSelect(HREC_OUTPUT_A, INPUT_PULL_UP_DOWN );
	MGPIO_stderrorPinModeSelect(HREC_OUTPUT_B, INPUT_PULL_UP_DOWN );
	
	MGPIO_stderrorSetPinPull_Up_Down(HREC_OUTPUT_A, PULL_DOWN);
	MGPIO_stderrorSetPinPull_Up_Down(HREC_OUTPUT_B, PULL_DOWN);
	
	MGPIO_stderrorGetPinValue(HREC_OUTPUT_A, &aEndState);
}

u16	HREC_u16Postition(void)
{
	MGPIO_stderrorGetPinValue(HREC_OUTPUT_A, &aStartState);
	if(aStartState != aLastState)
	{
		if(aStartState > aEndState)
		{
			 counter++;
		}
		else
		{
			counter--;
		}
	}
	
	if(counter > midPoint)
	{
		angle = counter - PulsePerRev;
	}
	else if(counter < midPoint)
	{
		angle = PulsePerRev - counter;
	}
	return (angle * 360)/PulsePerRev;
}


direction HREC_directionState(void)
{
	if(counter > PulsePerRev)
	{
		state = clockwise;
	}
	else
	{
		state = anticlockwise;
	}
	return state;
}
