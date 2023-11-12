/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: HBDG					*/
/*  Layer		: MCAL					*/
/*  Version		: 1.0					*/
/*  Date		: October 24, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/

/* Library Include */
#include "LSTD_types.h"

/* SWC Include */
#include "HHBDG_config.h"
#include "HHBDG_private.h"
#include "HHBDG_interface.h"
#include "MGPIO_interface.h"
#include "MTIM2_interface.h"

void HHBDG_voidInit
(
	void
)
{
	/*intitalization pin motor 1 & 2*/
	MGPIO_stderrorPinModeSelect(HHBDG_PIN_MOTOR1_PWM,ALTFUN_PUSH_PULL_SPEED_50MHZ);
	MGPIO_stderrorPinModeSelect(HHBDG_PIN_MOTOR2_PWM,ALTFUN_PUSH_PULL_SPEED_50MHZ);
	/*
	MGPIO_stderrorPinModeSelect(HHBDG_PIN_MOTOR1_DIR1,OUTPUT_PUSH_PULL_SPEED_50MHZ);
	MGPIO_stderrorPinModeSelect(HHBDG_PIN_MOTOR1_DIR2,OUTPUT_PUSH_PULL_SPEED_50MHZ);
	
	MGPIO_stderrorPinModeSelect(HHBDG_PIN_MOTOR2_DIR1,OUTPUT_PUSH_PULL_SPEED_50MHZ);
	MGPIO_stderrorPinModeSelect(HHBDG_PIN_MOT0R2_DIR2,OUTPUT_PUSH_PULL_SPEED_50MHZ);
	*/
}


STD_error_t HHBDG_stderrorPWMGeneration
(
	u8 ARG_u8SysClk,
	u16 ARG_u16PreScaler,
	u16 ARG_u16PWMFREQ,
	u16 ARG_u16Motor1DutyCycleValue,
	u16 ARG_u16Motor2DutyCycleValue
)
{
	STD_error_t L_stderrorError=E_NOK;
	
	if((ARG_u16Motor1DutyCycleValue<=100)&&(ARG_u16Motor2DutyCycleValue<=100))
	{
		MTIM2_voidPWMGeneration
		(
			ARG_u8SysClk,
			ARG_u16PreScaler,
			ARG_u16PWMFREQ,
			ARG_u16Motor1DutyCycleValue,
			ARG_u16Motor2DutyCycleValue
		);
		L_stderrorError=E_OK;
	}
	else
	{
		L_stderrorError=E_NOK;
	}
	return L_stderrorError;
}


void HHBDG_voidRotateRight
(
	void
)
{
	MGPIO_stderrorSetPinValueBSSR(HHBDG_PIN_MOTOR1_DIR1,HIGH);
	MGPIO_stderrorSetPinValueBSSR(HHBDG_PIN_MOTOR1_DIR2,LOW);
	MGPIO_stderrorSetPinValueBSSR(HHBDG_PIN_MOTOR2_DIR1,HIGH);
	MGPIO_stderrorSetPinValueBSSR(HHBDG_PIN_MOT0R2_DIR2,LOW);
}


void HHBDG_voidRotateLeft
(
	void
)
{
	MGPIO_stderrorSetPinValueBSSR(HHBDG_PIN_MOTOR1_DIR1,LOW);
	MGPIO_stderrorSetPinValueBSSR(HHBDG_PIN_MOTOR1_DIR2,HIGH);
	MGPIO_stderrorSetPinValueBSSR(HHBDG_PIN_MOTOR2_DIR1,LOW);
	MGPIO_stderrorSetPinValueBSSR(HHBDG_PIN_MOT0R2_DIR2,HIGH);
}



void HHBDG_voidStopAll
(
	void
)
{
	MGPIO_stderrorSetPinValueBSSR(HHBDG_PIN_MOTOR1_DIR1,LOW);
	MGPIO_stderrorSetPinValueBSSR(HHBDG_PIN_MOTOR1_DIR2,LOW);
	MGPIO_stderrorSetPinValueBSSR(HHBDG_PIN_MOTOR2_DIR1,LOW);
	MGPIO_stderrorSetPinValueBSSR(HHBDG_PIN_MOT0R2_DIR2,LOW);
}

