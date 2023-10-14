/*****************************************/
/*   Author      : Mahmoud Ahmed         */
/*   SWC         : UART						       */
/*   Layer       : MCAL                  */
/*   Version     : 1.0                   */
/*   Date        : October 13, 2023      */
/*   Last Edit   : N/A                   */
/*****************************************/

/******inclusion*******/
#include "LSTD_types.h"
#include "LBIT_math.h"

#include "MUART_private.h"
#include "MUART_interface.h"

/******CallBack*******/
FUNC_T MUART_CALLBACK[3] = {0};
/**********APIs************/
void MUART_voidInit( u8 Copy_u8UART_Number,u32 Copy_u32BaudRate,u8 Copy_u8ParityType, u8 Copy_u8StopBit,u8 Copy_u8WordSize)
{
	f64 mantessa , fraction;
	volatile USART_T* L_pMyUart = GetUsartPointer(Copy_u8UART_Number);
	if(NULL_POINTER != L_pMyUart)
	{
		L_pMyUart->CR1 |= (L_pMyUart->CR1 & PCE_CLEAR & PS_CLEAR & M_CLEAR ) | (( (~Copy_u8ParityType>>1)&1 )<<PCE_BIT) | ((Copy_u8ParityType & 1)<< PS_BIT) | TE_SET | RE_SET | (Copy_u8WordSize<<M_BIT);
		mantessa = ((f64)F_CPU / (Copy_u32BaudRate*16.0));
		fraction = ( mantessa - ((int)mantessa) ) *16;
		L_pMyUart->BRR = ( ((int)mantessa)<<4 | ((int)fraction) );
		L_pMyUart->CR2 |= (L_pMyUart->CR2 & ~(STOP_MASK) ) | (Copy_u8StopBit<<STOP_BITS);
		SET_BIT(L_pMyUart->CR1,UE_BIT);
	}
	
}

void MUART_voidTransimit( u8 Copy_u8UART_Number,  u16 Copy_u8Data)
{
	volatile USART_T* L_pMyUart = GetUsartPointer(Copy_u8UART_Number);
	if(NULL_POINTER != L_pMyUart)
	{
		L_pMyUart->DR = Copy_u8Data;
		while(!GET_BIT(L_pMyUart->SR,TXE_BIT));
	}
}

u8 MUART_u8RXNEFlag(u8 Copy_u8UART_Number)
{
	volatile USART_T* L_pMyUart = GetUsartPointer(Copy_u8UART_Number);
	if(NULL_POINTER != L_pMyUart)
	{
		return GET_BIT(L_pMyUart->SR,RXNE_BIT);
	}
	return 0;
}

u8 MUART_u8TCFlag(u8 Copy_u8UART_Number)
{
	volatile USART_T* L_pMyUart = GetUsartPointer(Copy_u8UART_Number);
	if(NULL_POINTER != L_pMyUart)
	{
		return GET_BIT(L_pMyUart->SR,TC_BIT);
	}
	return 0;
}
u16 MUART_u16GetData(u8 Copy_u8UART_Number)
{
	volatile USART_T* L_pMyUart = GetUsartPointer(Copy_u8UART_Number);
	if(NULL_POINTER != L_pMyUart)
	{
		return (u16) L_pMyUart->DR ;
	}
	return 0;
		
}

u16 MUART_u8ReceivePolling( u8 Copy_u8UART_Number)
{
	volatile USART_T* L_pMyUart = GetUsartPointer(Copy_u8UART_Number);
	if(NULL_POINTER != L_pMyUart)
	{
		while(!MUART_u8RXNEFlag(Copy_u8UART_Number));
		return (u16) L_pMyUart->DR ;
		
	}
	return 0;
}


void MUART_voidSetCallBack( u8 Copy_u8UART_Number,FUNC_T  Copy_pvUserFunc)
{
	if(NULL_POINTER !=  Copy_pvUserFunc)
	{
		MUART_CALLBACK[Copy_u8UART_Number-1] =  Copy_pvUserFunc;
	}
}

void MUART_voidInterruptEnable(u8 Copy_u8UART_Number, u8 Copy_u8InterruptType)
{
	volatile USART_T* L_pMyUart = GetUsartPointer(Copy_u8UART_Number);
	if(NULL_POINTER != L_pMyUart)
	{
			SET_BIT(L_pMyUart->CR1,PEIE_BIT);
			SET_BIT(L_pMyUart->CR1,Copy_u8InterruptType);
	}
	
}
void MUART_voidInterruptDisable(u8 Copy_u8UART_Number, u8 Copy_u8InterruptType)
{
	volatile USART_T* L_pMyUart = GetUsartPointer(Copy_u8UART_Number);
	if(NULL_POINTER != L_pMyUart)
	{
			CLEAR_BIT(L_pMyUart->CR1,Copy_u8InterruptType);
	}
}


volatile void * GetUsartPointer(u8 Copy_u8UART_Number)
{
	void * L_pReturn  = NULL_POINTER;
		switch(Copy_u8UART_Number)
		{
			case	MUART1:
				L_pReturn = (void *) USART1;
			break;
			
			case	MUART2:
				L_pReturn = (void *) USART2;
			break;
			
			case	MUART3:
				L_pReturn = (void *)USART3;
			break;
			
			default:
				//Error return Null
				L_pReturn =  NULL_POINTER;
			break;
			
		}
		return L_pReturn;
}
void USART1_IRQHandler(void)
{
	if(NULL_POINTER != MUART_CALLBACK[MUART1-1])
	{
		MUART_CALLBACK[MUART1-1]();
	}
}
void USART2_IRQHandler(void)
{
	if(NULL_POINTER != MUART_CALLBACK[MUART2-1])
	{
		MUART_CALLBACK[MUART2-1]();
	}
}
