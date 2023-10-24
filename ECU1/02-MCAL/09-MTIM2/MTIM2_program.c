/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: TIM2					*/
/*  Layer		: MCAL					*/
/*  Version		: 1.0					*/
/*  Date		: October 24, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/

/* Library Include */
#include "LSTD_types.h"

/* SWC Include */
#include "MTIM2_config.h"
#include "MTIM2_private.h"
#include "MTIM2_interface.h"

void MTIM2_voidStartCount
(
	void
)
{
	TIMER2 -> TIM2_CR1 |=(1U<<CR1_CEN);
}


void MTIM2_voidStopCount
(
	void
)
{
	TIMER2 -> TIM2_CR1 &=(~(1U<<CR1_CEN));

}


void MTIM2_voidDisabledUpdataEvent
(
	void
)
{
	TIMER2 -> TIM2_CR1 |=(1U<<CR1_UDIS);
}


void MTIM2_voidEnabledUpdataEvent
(
	void
)
{
	TIMER2 -> TIM2_CR1 &=(~(1U<<CR1_UDIS));
}


void MTIM2_voidPWMGeneration
(
	u8 ARG_u8SysClk,
	u16 ARG_u16PreScaler,
	u16 ARG_u16PWMFREQ,
	u8 ARG_u8PWMDutyCycleChannelCC1,
	u8 ARG_u8PWMDutyCycleChannelCC2
)
{
	MTIM2_voidStopCount();
	
	MTIM2_voidDisabledUpdataEvent();

	/*set a PreScaler & auto-reload*/
	TIMER2 -> TIM2_PSC = ARG_u16PreScaler-1;
	TIMER2 -> TIM2_ARR = (u32)(((ARG_u8SysClk*1000000)/(ARG_u16PreScaler*ARG_u16PWMFREQ*1.0))-1);

	/*set a DutyCycle Channel*/
	TIMER2 -> TIM2_CCR1  = (u32)(((ARG_u8PWMDutyCycleChannelCC1*(TIMER2 -> TIM2_ARR + 1.0 ))/100)-1)*(ARG_u8PWMDutyCycleChannelCC1 != 0);
	TIMER2 -> TIM2_CCR2  = (u32)(((ARG_u8PWMDutyCycleChannelCC2*(TIMER2 -> TIM2_ARR + 1.0 ))/100)-1)*(ARG_u8PWMDutyCycleChannelCC1 != 0);

	/*Counter used as upcounter*/
	TIMER2 -> TIM2_CR1 &=~(1<<CR1_DIR);
	
	/* ENABLE Capture/Compare output  CH1 & CH2*/
	TIMER2 -> TIM2_CCER |= (1<<CCER_CC1E);
	TIMER2 -> TIM2_CCER |= (1<<CCER_CC2E);
	
	/* Auto-reload preload enable*/
	TIMER2 -> TIM2_CR1 |= (1<<CR1_ARPE);
	
	/*CLEAR CH1 & CH2*/
	TIMER2 -> TIM2_CCMR1 &= ~(15<<CCMR1_OC1PE);
	TIMER2 -> TIM2_CCMR1 &= ~(15<<CCMR1_OC2PE);
	
	/*CH1 & CH2 Active PWM Mode1 & Preload*/
	TIMER2 -> TIM2_CCMR1 |= (13<<CCMR1_OC1PE);
	TIMER2 -> TIM2_CCMR1 |= (13<<CCMR1_OC2PE);
	
	/*enable update generation*/
	TIMER2 -> TIM2_EGR |=(1<<EGR_UG);
	
	/*enable timer generation*/
	MTIM2_voidStartCount();
}
