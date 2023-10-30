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
#include "MTIM_private.h"
//#include "MNVIC_interface.h"

/* SWC Includes */
#include "HREC_interface.h"
#include "HREC_private.h"
#include "HREC_config.h"


u16 midPoint = HREC_WHEEL_TURN * HREC_PULSE_PER_REV;
//volatile u16 encoderCount = 0;
//u8 encoderDirection;


void HREC_voidInit(void)
{
	/* Enable RCC for GPIOA and TIM3 */
	RCC_EnablePeripheralClk( APB2, GPIOA_PER );
	RCC_EnablePeripheralClk( APB2, AFIOEN_PER );
	RCC_EnablePeripheralClk( APB1, TIM3EN_PER );
	
	/* Change PIN 0 and 1 in port A to alt func, push pull at 50mhz */
	MGPIO_stderrorPinModeSelect(HREC_OUTPUT_A, ALTFUN_PUSH_PULL_SPEED_50MHZ );
	MGPIO_stderrorPinModeSelect(HREC_OUTPUT_B, ALTFUN_PUSH_PULL_SPEED_50MHZ );

	MGPIO_stderrorSetPinPull_Up_Down(HREC_OUTPUT_A, PULL_UP);
	MGPIO_stderrorSetPinPull_Up_Down(HREC_OUTPUT_B, PULL_UP);

	/*Partial remap: PB0 (TIM3_CH3) and PB1 (TIM3_CH4)*/
	CLEAR_BIT(AFIO_MAPR, 10);
	SET_BIT(AFIO_MAPR, 11);
	
	/* CC1S config as Capture TI1 */
	SET_BIT(TIM3 -> CCMR1, 0);
	CLEAR_BIT(TIM3 -> CCMR1, 1);
	
	/* CC2S config as Capture TI2 */
	SET_BIT(TIM3 -> CCMR1, 8);
	CLEAR_BIT(TIM3 -> CCMR1, 9);
	
	/* TI1FP1 noninverted,TI1FP1=TI1 */
	CLEAR_BIT(TIM3 -> CCER, 1); // capture rising edge TI1
	TIM3 -> CCMR1 &=  (~0b1111) << 4; //No filter, sampling is done for TI1
	
	
	/* TI2FP2 noninverted,TI2FP2=TI2 */
	CLEAR_BIT(TIM3 -> CCER, 5); // capture rising edge TI2
	TIM3 -> CCMR1 &=  (~0b1111) << 12; //No filter, sampling is done for TI2
   
   
	/* Configure TIM3 in encoder mode */
	TIM3 -> SMCR &= ~0b111; // Clear SMS bits for encoder mode
	TIM3 -> SMCR |= 0b011; // Set SMS bits to count on TI1 and TI2 edges
	
	TIM3 -> CNT = midPoint; //set Preload to midpoint value
	
	TIM3 -> ARR = 0xFFFF; //set autoreload to max value
	
	SET_BIT(TIM3->CCER, 0 ); // Enable capture (input)

	/*
	SET_BIT( TIM3->DIER, 1 ); // Enable interrupt for input capture
    
	MNVIC_vEnableIRQ( TIM3_IRQn ); // Enable TIM3 interrupt in NVIC
	*/
}

void HREC_voidEnableEncoder(void)
{
	SET_BIT(TIM3->CR1, 0);
}

void HREC_voidDisableEncoder(void)
{
	CLEAR_BIT(TIM3->CR1, 0);
}

void HREC_u16currentPosition( u8 *ARG_u8Rev, direction *ARG_directionState, u16 *ARG_u16Angle )
{
	u16 L_u16absCount;
	u16 L_u16EncoderCount = TIM3 -> CCR1;

	if(L_u16EncoderCount > midPoint)
	{
		*ARG_u8Rev = ( L_u16encoderCount / HREC_PULSE_PER_REV ) - HREC_WHEEL_TURN;
		*ARG_directionState = CLOCKWISE;
		L_u16absCount = L_u16encoderCount - midPoint;
	}
	else if(L_u16EncoderCount < midPoint)
	{
		*ARG_u8Rev = HREC_WHEEL_TURN - ( L_u16encoderCount / HREC_PULSE_PER_REV );
		*ARG_directionState = ANTICLOCKWISE;
		L_u16absCount = midPoint - L_u16encoderCount;
	}
	else{/* Do Nothing */}

	*ARG_u16Angle = ( L_u16absCount * 360 ) / HREC_PULSE_PER_REV;
}

/*
void TIM3_IRQHandler()
{
	if ( GET_BIT (TIM3 -> SR, 1 ) )
	{
		// Input capture event occurred on channel 1
		// Read the encoder count from the corresponding register
		encoderCount = TIM3 -> CCR1;
		
		//Check if DIR bit is 0 upcounter or 1 downcounter
		encoderDirection = GET_BIT(TIM3 -> CR1, 4 );
	}
}
*/
