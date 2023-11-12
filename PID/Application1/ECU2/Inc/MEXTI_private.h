/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: EXTI					*/
/*  Layer		: MCAL					*/
/*  Version		: 1.0					*/
/*  Date		: November 10, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/

#ifndef _MEXTI_PRIVATE_H_
#define _MEXTI_PRIVATE_H_


typedef struct{

	volatile u32 IMR;
	volatile u32 EMR;
	volatile u32 RTSR;
	volatile u32 FTSR;
	volatile u32 SWIER;
	volatile u32 PR;

}MEXTI_t;

#define EXTI ((volatile MEXTI_t *) 0x40010400)


#endif 
