/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: HBDG					*/
/*  Layer		: MCAL					*/
/*  Version		: 1.0					*/
/*  Date		: October 24, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/

#ifndef _HHBDG_INERFACE_H_
#define _HHBDG_INERFACE_H_

/*speed*/
#define PWM_MAX_SPEED  	    50
#define PWM_MEDIUM_SPEED    25
#define PWM_MIN_SPEED   	0


void HHBDG_voidInit
(
	void
);


STD_error_t HHBDG_stderrorPWMGeneration
(
	u8 ARG_u8SysClk,
	u16 ARG_u16PreScaler,
	u16 ARG_u16PWMFREQ,
	u16 ARG_u16Motor1DutyCycleValue,
	u16 ARG_u16Motor2DutyCycleValue
);


void HHBDG_voidRotateRight
(
	void
);


void HHBDG_voidRotateLeft
(
	void
);


void HHBDG_voidStopAll
(
	void
);

#endif
