/*************************************/
/*  Auothor : MOHAMED ABOUBAKR       */
/*  SWC     : ROTARY ENCODER         */
/*  Layer   : HAL                    */
/*  Version : 1.0                    */
/*  Date    : OCTOBER 20, 2023       */
/*************************************/

/* Library Includes */
#include "LSTD_types.h"
#include "LBIT_math.h"

/* MCAL Includes */
#include "MRCC_interface.h"
#include "MTIM_private.h"

/* SWC Includes */
#include "HREC_interface.h"
#include "HREC_config.h"


volatile u16 L_u16encoderCount = 0;


void HREC_voidInit(void)
{
	MRCC_stderrorInit(PLL_HSE, AHB_PreScaler1,APB_PreScaler2,APB_PreScaler1);

	MRCC_stderrorSetPllClockFreq(PLL_PreScaler9, Wait_States_2);

	/* Enable RCC for GPIOA and TIM4 */
	RCC_EnablePeripheralClk( APB2, GPIOA_PER );
	RCC_EnablePeripheralClk( APB2, AFIOEN_PER );
	RCC_EnablePeripheralClk( APB1, TIM4EN_PER );
	
	
	/* CC1S config as Capture TI1 */
	SET_BIT(TIM4 -> CCMR1, 0);
	CLEAR_BIT(TIM4 -> CCMR1, 1);
	
	/* CC2S config as Capture TI2 */
	SET_BIT(TIM4 -> CCMR1, 8);
	CLEAR_BIT(TIM4 -> CCMR1, 9);
	
	/* TI1FP1 noninverted,TI1FP1=TI1 */
	CLEAR_BIT(TIM4 -> CCER, 1);
	
	
	/* TI2FP2 noninverted,TI2FP2=TI2 */
	CLEAR_BIT(TIM4 -> CCER, 5);
   
	/* Configure TIM4 in encoder mode */
	TIM4 -> SMCR &= ~0b111; // Clear SMS bits for encoder mode
	TIM4 -> SMCR |= 0b011; // Set SMS bits to count on TI1 and TI2 edges
	
	
	TIM4 -> ARR = 600; //set autoreload to max value

	TIM4 -> PSC = 0x0000; //prescalar value
	
}

void HREC_voidEnableEncoder(void)
{
	SET_BIT(TIM4->CR1, 0);
}

void HREC_voidDisableEncoder(void)
{
	CLEAR_BIT(TIM4->CR1, 0);
}

void HREC_voidCurrentPosition(  u16 *ARG_u16Angle , direction *ARG_directionState, polarity *ARG_polarityCond)
{
	u16 L_u16absCount;
	L_u16encoderCount = TIM4 -> CNT;

	if(L_u16encoderCount > 0)
	{
		*ARG_polarityCond = POSITIVE;
		L_u16absCount = L_u16encoderCount ;
	}
	else if(L_u16encoderCount < 0)
	{
		//*ARG_u8Rev = HREC_WHEEL_TURN - ( L_u16encoderCount / HREC_PULSE_PER_REV );
		*ARG_polarityCond = NEGATIVE;
		L_u16absCount = HREC_PULSE_PER_REV - L_u16encoderCount;
	}
	else{/* Do Nothing */}

	if( GET_BIT(TIM3 -> CR1, 4 ) )
	{
		*ARG_directionState = ANTICLOCKWISE;
	}
	else
	{
		*ARG_directionState = CLOCKWISE;
	}

	*ARG_u16Angle = ( L_u16absCount * 360 ) / HREC_PULSE_PER_REV;
}
