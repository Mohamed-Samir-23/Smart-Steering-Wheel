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
#include "MGPIO_interface.h"
#include "MNVIC_interface.h"
#include "MTIM_private.h"

/* SWC Includes */
#include "HREC_interface.h"
#include "HREC_private.h"
#include "HREC_config.h"


u16 midPoint = HREC_WHEEL_TURN * HREC_PULSE_PER_REV;
volatile u16 encoderCount = 0;
u8 encoderDirection;


void HREC_voidInit(void)
{
	/* Enable RCC for GPIOA and TIM2 */
	RCC_EnablePeripheralClk( APB2, GPIOA_PER );
	RCC_EnablePeripheralClk( APB1, TIM2EN_PER );
	
	/* Change PIN 0 and 1 in port A to alt func, push pull at 50mhz */
	MGPIO_stderrorPinModeSelect(HREC_OUTPUT_A, ALTFUN_PUSH_PULL_SPEED_50MHZ );
	MGPIO_stderrorPinModeSelect(HREC_OUTPUT_B, ALTFUN_PUSH_PULL_SPEED_50MHZ );
	
	/* CC1S config as Capture TI1 */
	SET_BIT(TIM2 -> CCMR1, 0);
	CLEAR_BIT(TIM2 -> CCMR1, 1);
	
	/* CC2S config as Capture TI2 */
	SET_BIT(TIM2 -> CCMR1, 8);
	CLEAR_BIT(TIM2 -> CCMR1, 9);
	
	/* TI1FP1 noninverted,TI1FP1=TI1 */
	CLEAR_BIT(TIM2 -> CCER, 1); // capture rising edge TI1
	TIM2 -> CCMR1 &=  (~0b1111) << 4; //No filter, sampling is done for TI1
	
	
	/* TI2FP2 noninverted,TI2FP2=TI2 */
	CLEAR_BIT(TIM2 -> CCER, 5); // capture rising edge TI2
	TIM2 -> CCMR1 &=  (~0b1111) << 12; //No filter, sampling is done for TI2
   
   
	/* Configure TIM2 in encoder mode */
  TIM2 -> SMCR &= ~0b111; // Clear SMS bits for encoder mode
  TIM2 -> SMCR |= 0b011; // Set SMS bits to count on TI1 and TI2 edges
	
	TIM2 -> CNT = midPoint; //set Preload to midpoint value
	
	TIM2 -> ARR = 0xFFFF; //set autoreload to max value
	
  SET_BIT(TIM2->CCER, 0 ); // Enable capture (input)

	
	SET_BIT( TIM2->DIER, 1 ); // Enable interrupt for input capture
    
  MNVIC_vEnableIRQ( TIM2_IRQn ); // Enable TIM2 interrupt in NVIC

	/* Start TIM2 */
	SET_BIT(TIM2->CR1, 0)
}


void HREC_u16currentPosition( u16 *ARG_u16Angle, u8 *ARG_u8Rev )
{
	u16 L_u16absCount;

	if(encoderCount > midPoint)
	{
		*ARG_u8Rev = ( encoderCount / HREC_PULSE_PER_REV ) - HREC_WHEEL_TURN;
		L_u16absCount = encoderCount - midPoint;
	}
	else if(encoderCount < midPoint)
	{
		*ARG_u8Rev = HREC_WHEEL_TURN - ( encoderCount / HREC_PULSE_PER_REV );
		L_u16absCount = midPoint - encoderCount;
	}
	
	*ARG_u16Angle = ( L_u16absCount * 360 ) / HREC_PULSE_PER_REV;
}


void TIM2_IRQHandler()
{
  if ( GET_BIT (TIM2 -> SR, 1 ) )
  {
    // Input capture event occurred on channel 1
    // Read the encoder count from the corresponding register
    encoderCount = TIM2 -> CCR1;
		
    //Check if DIR bit is 0 upcounter or 1 downcounter
    encoderDirection = GET_BIT(TIM2 -> CR1, 4 );
    }
}
