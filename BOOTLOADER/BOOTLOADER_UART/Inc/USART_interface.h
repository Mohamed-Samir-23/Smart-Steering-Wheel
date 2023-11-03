/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: APPLICATION			*/
/*  Layer		: APP					*/
/*  Version		: 1.0					*/
/*  Date		: October 30, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/

#ifndef _USART_INTERFACE_H_
#define _USART_INTERFACE_H_

void MUSART1_voidInit
(
	void
);

void MUSART1_voidTransmit
(
	char arr[]
);

u8 MUSART1_u8Receive
(
	volatile u8* Copy_u8Data
);

STD_error_t MUSART1_SetCallBack
(
	void (*ARG_pvoidFunction)(volatile u8* ARG_Pu8Data)
);

void MUART_voidInterruptEnable
(
	void
);

void MUART_voidInterruptDisable
(
	void
);


#endif






