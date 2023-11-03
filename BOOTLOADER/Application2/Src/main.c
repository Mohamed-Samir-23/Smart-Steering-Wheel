/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: Application 2			*/
/*  Layer		: APP					*/
/*  Version		: 1.0					*/
/*  Date		: November 03, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/

/* Library Include */
#include "LSTD_types.h"

/* SWC Include */
#include "MRCC_interface.h"
#include "MGPIO_interface.h"
#include "MSYSTICK_interface.h"
#include "MNVIC_interface.h"
#include "MFLASH_interface.h"
#include "USART_interface.h"

u8 APARES_u8EndRecordFlag(void);

void APARES_voidRecord(volatile u8* Copy_u8BufData);

void APP2_voidFlash(volatile u8* ARG_Pu8Data);

volatile u8  APP2_u8BLWriteReq    = 1;

/*for test Functionality*/
/*#define SCB_VTOR  *((volatile u32*)0xE000ED08)*/


int main(void)
{
	/*For Set vector table*/
	/*SCB_VTOR=0x0800F000;*/

	MRCC_stderrorInit(HSI,AHB_PreScaler1,APB_PreScaler1,APB_PreScaler1);
	RCC_EnablePeripheralClk(APB2, USART1EN_PER);
	RCC_EnablePeripheralClk(APB2, GPIOA_PER);
	RCC_EnablePeripheralClk(APB2, AFIOEN_PER);
	RCC_EnablePeripheralClk(AHB1, FLITFEN_PER);

	MGPIO_stderrorSerialWireJTAGConfiguration(JTAG_DISABLED_AND_SW_ENABLED);

	MSYSTICK_stderrorInit(AHB_DIV_8);

	MGPIO_stderrorPinModeSelect(GPIOA, PIN1, OUTPUT_PUSH_PULL_SPEED_10MHZ);

	MGPIO_stderrorPinModeSelect(GPIOA, PIN9, ALTFUN_PUSH_PULL_SPEED_2MHZ);/*Tx*/
	MGPIO_stderrorPinModeSelect(GPIOA, PIN10, INPUT_FLOAT);/*Rx*/

	/*ENABLE SET UART CALLBACK*/
	MUSART1_SetCallBack(APP2_voidFlash);

	/*ENABLE UART NVIC*/
	MNVIC_stderrorEnableIRQ(USART1);

	/*ENABLE UART INIT*/
	MUSART1_voidInit();

	/*ENABLE UART ISR*/
	MUART_voidInterruptEnable();


	while(1)
	{
		/*check if update is Done to jump and reset*/
		if(APARES_u8EndRecordFlag()==1)
		{
			u32 L_u32count =5;

			u16 L_readBuffer=0;

			while(L_readBuffer==0)
			{
				MFLASH_voidErasePage(63);

				MFLASH_stderrorWrite32BitData(63, &L_u32count);

				MFLASH_voidReadPage(63, &L_readBuffer);
			}

			/*Reset Request*/
			NVIC_voidResetRequest();
		}
		else
		{
			/*DO NOTHING*/
		}

		/*NORMAL CODE*/
		MGPIO_stderrorSetPinValueBSSR(GPIOA, PIN1, HIGH);
		MSYSTICK_Delay_Ms(300);
		MGPIO_stderrorSetPinValueBSSR(GPIOA, PIN1, LOW);
		MSYSTICK_Delay_Ms(300);
	}
}


void APP2_voidFlash(volatile u8* ARG_Pu8Data)
{
	if(APP2_u8BLWriteReq ==1)
	{
		MFLASH_voidEraseApp2Section();

		APP2_u8BLWriteReq = 0;
	}
	else
	{
		/*DO NOTHING*/
	}

	/* Parse */
	APARES_voidRecord(ARG_Pu8Data);

	MUSART1_voidTransmit("ok");
}

