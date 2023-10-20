/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: GPIO					*/
/*  Layer		: MCAL					*/
/*  Version		: 1.0					*/
/*  Date		: October 09, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/

#ifndef _MGPIO_PRIVATE_H_
#define _MGPIO_PRIVATE_H_


#define GPIOA_BASE  0x40010800 
#define GPIOB_BASE  0x40010C00
#define GPIOC_BASE  0x40011000
#define GPIOD_BASE  0x40011400
#define GPIOE_BASE  0x40011800


/* Registers of PORTA */ 
#define GPIOA_CRL			*((uv32 *)(0x00 + GPIOA_BASE))
#define GPIOA_CRH			*((uv32 *)(0x04 + GPIOA_BASE))
#define GPIOA_IDR			*((uv32 *)(0x08 + GPIOA_BASE))
#define GPIOA_ODR     	    *((uv32 *)(0x0C + GPIOA_BASE))
#define GPIOA_BSRR          *((uv32 *)(0x10 + GPIOA_BASE))
#define GPIOA_BRR           *((uv32 *)(0x14 + GPIOA_BASE))
#define GPIOA_LCKR          *((uv32 *)(0x18 + GPIOA_BASE))



/* Registers of PORTB */ 
#define GPIOB_CRL			*((uv32 *)(0x00 + GPIOA_BASE))
#define GPIOB_CRH			*((uv32 *)(0x04 + GPIOA_BASE))
#define GPIOB_IDR			*((uv32 *)(0x08 + GPIOA_BASE))
#define GPIOB_ODR     	    *((uv32 *)(0x0C + GPIOA_BASE))
#define GPIOB_BSRR          *((uv32 *)(0x10 + GPIOA_BASE))
#define GPIOB_BRR           *((uv32 *)(0x14 + GPIOA_BASE))
#define GPIOB_LCKR          *((uv32 *)(0x18 + GPIOA_BASE))


/* Registers of PORTC */ 
#define GPIOC_CRL			*((uv32 *)(0x00 + GPIOA_BASE))
#define GPIOC_CRH			*((uv32 *)(0x04 + GPIOA_BASE))
#define GPIOC_IDR			*((uv32 *)(0x08 + GPIOA_BASE))
#define GPIOC_ODR     	    *((uv32 *)(0x0C + GPIOA_BASE))
#define GPIOC_BSRR          *((uv32 *)(0x10 + GPIOA_BASE))
#define GPIOC_BRR           *((uv32 *)(0x14 + GPIOA_BASE))
#define GPIOC_LCKR          *((uv32 *)(0x18 + GPIOA_BASE))

/* Registers of PORTD */ 
#define GPIOD_CRL			*((uv32 *)(0x00 + GPIOA_BASE))
#define GPIOD_CRH			*((uv32 *)(0x04 + GPIOA_BASE))
#define GPIOD_IDR			*((uv32 *)(0x08 + GPIOA_BASE))
#define GPIOD_ODR     	    *((uv32 *)(0x0C + GPIOA_BASE))
#define GPIOD_BSRR          *((uv32 *)(0x10 + GPIOA_BASE))
#define GPIOD_BRR           *((uv32 *)(0x14 + GPIOA_BASE))
#define GPIOD_LCKR          *((uv32 *)(0x18 + GPIOA_BASE))

/* Registers of PORTE */ 
#define GPIOE_CRL			*((uv32 *)(0x00 + GPIOA_BASE))
#define GPIOE_CRH			*((uv32 *)(0x04 + GPIOA_BASE))
#define GPIOE_IDR			*((uv32 *)(0x08 + GPIOA_BASE))
#define GPIOE_ODR     	    *((uv32 *)(0x0C + GPIOA_BASE))
#define GPIOE_BSRR          *((uv32 *)(0x10 + GPIOA_BASE))
#define GPIOE_BRR           *((uv32 *)(0x14 + GPIOA_BASE))
#define GPIOE_LCKR          *((uv32 *)(0x18 + GPIOA_BASE))




#define BSRR_OFFSET			16U
#define LCKK				16U

#endif
