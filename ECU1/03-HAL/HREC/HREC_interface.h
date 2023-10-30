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
	CLOCKWISE,
	ANTICLOCKWISE,
}direction;

direction state;

#define HREC_PULSE_PER_REV    600

void  HREC_voidInit(void);
void  HREC_voidEnableEncoder(void);
void  HREC_voidDisableEncoder(void);
void  HREC_u16currentPosition(u16 *ARG_u16Angle, u8 *ARG_u8Rev);

#endif
