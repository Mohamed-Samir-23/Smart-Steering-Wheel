/*************************************/
/*  Auothor : MOHAMED ABOUBAKR       */
/*  SWC     : ROTARY ENCODER         */
/*  Layer   : HAL                    */
/*  Version : 1.0                    */
/*  Date    : OCTOBER 20, 2023       */
/*************************************/

#ifndef _HREC_INTERFACE_H_
#define _HREC_INTERFACE_H_

typedef enum
{
	POSITIVE,
	NEGATIVE,
}polarity;

typedef enum
{
	CLOCKWISE,
	ANTICLOCKWISE,
}direction;

#define HREC_PULSE_PER_REV    600

void	HREC_voidInit( void );
void	HREC_voidEnableEncoder( void );
void	HREC_voidDisableEncoder( void );
void HREC_voidCurrentPosition(  u16 *ARG_u16Angle , direction *ARG_directionState, polarity *ARG_polarityCond);

;

#endif
