/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: TIM2					*/
/*  Layer		: MCAL					*/
/*  Version		: 1.0					*/
/*  Date		: October 24, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/


#ifndef  _MTIM2_INTERFACE_H_
#define  _MTIM2_INTERFACE_H_

void MTIM2_voidStartCount
(
	void
);

void MTIM2_voidStopCount
(
	void
);


void MTIM2_voidDisabledUpdataEvent
(
	void
);


void MTIM2_voidEnabledUpdataEvent
(
	void
);


void MTIM2_voidPWMGeneration
(
	u8 ARG_u8SysClk,
	u16 ARG_u16PreScaler,
	u16 ARG_u16PWMFREQ,
	u8 ARG_u8PWMDutyCycleChannelCC1,
	u8 ARG_u8PWMDutyCycleChannelCC2
);




#endif
