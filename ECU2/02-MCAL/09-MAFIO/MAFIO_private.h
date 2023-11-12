/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: AFIO					*/
/*  Layer		: MCAL					*/
/*  Version		: 1.0					*/
/*  Date		: November 10, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/

#ifndef _MAFIO_PRIVATE_H_
#define _MAFIO_PRIVATE_H_



typedef struct{

	volatile u32 EVCR;
	volatile u32 MAPR;
	volatile u32 EXTICRx[4];
	volatile u32 MAPR2;

}MAFIO_t;


#define AFIO ((volatile MAFIO_t *) 0x40010000)



#endif
