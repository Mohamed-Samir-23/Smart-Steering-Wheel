/************************************/
/*	Author: 	Mohamed Osama		*/
/*	SWC: 		TIMERS				*/
/*	Layer: 		MCAL				*/
/*	Version: 	1.0					*/
/*	Date: 		OCTOBER 17, 2023	*/
/*	Last Edit:	N/ARP				*/
/************************************/

#ifndef _MTIM_PRIVATE_H_
#define _MTIM_PRIVATE_H_

typedef struct
{
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SMCR;
	volatile u32 DIER;
	volatile u32 SR;
	volatile u32 EGR;
	volatile u32 CCMR1;
	volatile u32 CCMR2;
	volatile u32 CCER;
	volatile u32 CNT;
	volatile u32 PSC;
	volatile u32 ARP;
	volatile u32 RCR; 
	volatile u32 CCR1;
	volatile u32 CCR2;
	volatile u32 CCR3;
	volatile u32 CCR4;
	volatile u32 BDTR; 
	volatile u32 DCR;
	volatile u32 DMAR;
	volatile u32 OR;
}TIM_t;

#define TIM1	((volatile TIM_t*)(0x40012C00))
#define TIM2	((volatile TIM_t*)(0x40000000))
#define TIM3	((volatile TIM_t*)(0x40000400))
#define TIM4	((volatile TIM_t*)(0x40000800))
#define TIM5	((volatile TIM_t*)(0x40000C00))
#define TIM6	((volatile TIM_t*)(0x40001000))
#define TIM7	((volatile TIM_t*)(0x40001400))
#define TIM8	((volatile TIM_t*)(0x40013400))
#define TIM9	((volatile TIM_t*)(0x40014C00))
#define TIM10	((volatile TIM_t*)(0x40015000))
#define TIM11	((volatile TIM_t*)(0x40015400))
#define TIM12	((volatile TIM_t*)(0x40001800))
#define TIM13	((volatile TIM_t*)(0x40001C00))
#define TIM14	((volatile TIM_t*)(0x40002000))


#endif
