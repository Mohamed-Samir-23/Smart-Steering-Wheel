/************************************/
/*	Auothor: 	mBravo18			*/
/*	SWC: 		ROTARY ENCODER		*/
/*	Layer: 		HAL					*/
/*	Version: 	1.0					*/
/*	Date: 		OCTOBER 16, 2023	*/
/*	Last Edit:	N/A					*/

#ifndef _HREC_INTERFACE_H_
#define _HREC_INTERFACE_H_

typedef enum
{
	clockwise,
	anticlockwise
}direction;

direction state;

void	HREC_voidInit(void);

u16	HREC_u16Postition(void);

direction HREC_directionState(void);

#endif
