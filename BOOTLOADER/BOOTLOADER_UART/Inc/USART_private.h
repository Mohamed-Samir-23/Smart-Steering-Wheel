/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: APPLICATION			*/
/*  Layer		: APP					*/
/*  Version		: 1.0					*/
/*  Date		: October 30, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/

#ifndef _USART_PRIVATE_H_
#define _USART_PRIVATE_H_

typedef struct{
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR[3];
	volatile u32 GTPR;
}USART_Register;


#define USART1 	((USART_Register *) 0x40013800)

#endif
