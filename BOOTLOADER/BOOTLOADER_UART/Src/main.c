/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: BOOTLOADER			*/
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
#include "MFLASH_interface.h"
#include "USART_interface.h"

#define SCB_VTOR   *((volatile u32*)0xE000ED08)

u8 APARES_u8EndRecordFlag(void);

void APARES_voidRecord(volatile u8* Copy_u8BufData);

void APP_voidFlash(volatile u8* ARG_Pu8Data);

volatile u8   APP_u8RecBuffer[100]   ;
volatile u8   APP_u8RecCounter    = 0;
volatile u16  APP_u16TimerCounter = 0;
volatile u8   APP_u8BLWriteReq    = 1;
volatile u8   APP_u8bootgate      = 1;
typedef void (*APP_Function_t)(void);


APP_Function_t addr_to_call = 0;


void APP_BootSelector(void)
{
	u16 L_u16program=0;

	MFLASH_voidReadPage(31, &L_u16program);

	if((L_u16program==5)&&(APP_u8bootgate==1))
	{
		/*App2*/
		SCB_VTOR = 0x0800F000;
		addr_to_call = *(APP_Function_t*)(0x0800F004);
		addr_to_call();
	}
	else
	{
		/*APP*/

		SCB_VTOR = 0x08003400;
		addr_to_call = *(APP_Function_t*)(0x08003404);
		addr_to_call();
	}
}


int main(void)
{
	u8 L_u8RecStatus =0;

	MRCC_stderrorInit(HSI,AHB_PreScaler1,APB_PreScaler1,APB_PreScaler1);

	RCC_EnablePeripheralClk(APB2, USART1EN_PER);
	RCC_EnablePeripheralClk(APB2, GPIOA_PER);
	RCC_EnablePeripheralClk(AHB1, FLITFEN_PER);

	MGPIO_stderrorSerialWireJTAGConfiguration(JTAG_DISABLED_AND_SW_ENABLED);

	MSYSTICK_stderrorInit(AHB_DIV_8);

	MGPIO_stderrorPinModeSelect(GPIOA, PIN9, ALTFUN_PUSH_PULL_SPEED_2MHZ);/*Tx*/
	MGPIO_stderrorPinModeSelect(GPIOA, PIN10, INPUT_FLOAT);/*Rx*/

	MUSART1_voidInit();

	MSYSTICK_stderrorSetSingleInterval(5000000,APP_BootSelector);

	while(1)
	{
		L_u8RecStatus = MUSART1_u8Receive( &(APP_u8RecBuffer[APP_u8RecCounter]) );

		if (L_u8RecStatus == 1)
		{
			MSYSTICK_voidStopTICK();

			if(APP_u8RecBuffer[APP_u8RecCounter] == '\n')
			{
				if (APP_u8BLWriteReq == 1)
				{
					MFLASH_voidEraseApp1Section();
					APP_u8BLWriteReq = 0;
					APP_u8bootgate=0;
				}

				/* Parse */
				APARES_voidRecord(APP_u8RecBuffer);

				MUSART1_voidTransmit("ok");

				APP_u8RecCounter = 0;
			}
			else
			{
				APP_u8RecCounter ++ ;
			}
		}
		else
		{
			/*Nothing*/
		}

		if(APARES_u8EndRecordFlag()==1)
		{
			APP_BootSelector();
		}
		else
		{


		}

		MSYSTICK_stderrorSetSingleInterval(10000000,APP_BootSelector);
	}
}
