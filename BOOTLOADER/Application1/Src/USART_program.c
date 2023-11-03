/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: MCAL					*/
/*  Layer		: USART					*/
/*  Version		: 1.0					*/
/*  Date		: October 30, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/


/* Library Include */
#include "LSTD_types.h"

/* SWC Include */
#include "USART_interface.h"
#include "USART_private.h"
#include "USART_config.h"

static void (*MUSART1_pvoidfUserFunctionResive)(volatile u8* ARG_Pu8Data) =NULL_POINTER;

volatile u8 MUSART1_u8RecBuffer[100] ;

volatile u8 MUSART1_RecCounter=0;

void MUSART1_voidInit
(
	void
)
{
	/*	baud rate = 9600 */
	USART1 -> BRR = 0x341;
	/* Enabling Transmitter */
	USART1-> CR[0] |=(1<<3);
	/* Enabling Receiver */
	USART1-> CR[0] |=(1<<2);
	/* Enabling USART */
	USART1-> CR[0] |=(1<<13);
	/* Clearing status register */
	USART1 -> SR = 0;
}

void MUSART1_voidTransmit
(
	char arr[]
)
{
	u8 i = 0;
	while(arr[i] != '\0')
	{
		USART1 -> DR = arr[i];
		/*Transmission complete*/
		while((1&((USART1 -> SR)>>6)) == 0);
		i++;
	}
}

u8 MUSART1_u8Receive
(
	volatile u8* Copy_u8Data
)
{
	u8 Local_u8Result = 1;

	while((1&((USART1 -> SR)>>5)) != 1);

	*Copy_u8Data = USART1 -> DR;

	return (Local_u8Result);
}

STD_error_t MUSART1_SetCallBack
(
	void (*ARG_pvoidFunction)(volatile u8* ARG_Pu8Data)
)
{
	STD_error_t L_stderrorError=E_NOK;

	if(NULL_POINTER != ARG_pvoidFunction)
	{

		L_stderrorError=E_OK;
		MUSART1_pvoidfUserFunctionResive=ARG_pvoidFunction;
	}
	else
	{
		L_stderrorError=E_NULL_POINTER;
	}

	return L_stderrorError;
}


void USART1_IRQHandler(void)
{
	if(NULL_POINTER != MUSART1_pvoidfUserFunctionResive)
	{
		if ((1&((USART1 -> SR)>>5))== 1)
		{
			MUSART1_u8RecBuffer[MUSART1_RecCounter] = USART1 -> DR;

			if(MUSART1_u8RecBuffer[MUSART1_RecCounter]=='\n')
			{
				MUSART1_pvoidfUserFunctionResive(MUSART1_u8RecBuffer);
				MUSART1_RecCounter=0;
			}
			else
			{
				MUSART1_RecCounter++;
			}
			USART1 -> SR = 0;

		}
	}
}


void MUART_voidInterruptEnable
(
	void
)
{
	/*PE interrupt enable*/
	/*RXNE interrupt enable*/
	USART1-> CR[0] |=(1<<5)|(1<<8);
}


void MUART_voidInterruptDisable
(
	void
)
{
	/*PE interrupt disable*/
	USART1-> CR[0] &=~(1<<8);
	/*TXE interrupt disable*/
	USART1-> CR[0] &=~(1<<7);
	/*RXNE interrupt disable*/
	USART1-> CR[0] &=~(1<<5);
}












