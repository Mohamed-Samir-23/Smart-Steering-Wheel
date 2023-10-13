/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: RCC					*/
/*  Layer		: MCAL					*/
/*  Version		: 1.0					*/
/*  Date		: October 09, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/


#ifndef _MRCC_PRIVATE_H_
#define _MRCC_PRIVATE_H_

#define RCC_OFFSET			(0x40021000)

#define RCC_CR				*((uv32*)(0x00+RCC_OFFSET))
#define PLLRDY				25U
#define PLLRON				24U
#define HSEBYP				18U
#define HSERDY				17U
#define HSEON				16U
#define HSIRDY				1U
#define HSION				0U

#define RCC_CFGR			*((uv32*)(0x04+RCC_OFFSET))
#define PLLMUL				18U
#define PLLXTPRE			17U
#define PLLSRC				16U
#define PPRE2				11U
#define PPRE1				8U
#define HPRE				4U
#define SWS					2U
#define SW					0U

#define RCC_CIR				*((uv32*)(0x08+RCC_OFFSET))
#define RCC_APB2RSTR		*((uv32*)(0x0C+RCC_OFFSET))
#define RCC_APB1RSTR		*((uv32*)(0x10+RCC_OFFSET))
#define RCC_AHBENR			*((uv32*)(0x14+RCC_OFFSET))
#define RCC_APB2ENR			*((uv32*)(0x18+RCC_OFFSET))
#define RCC_APB1ENR			*((uv32*)(0x1C+RCC_OFFSET))
#define RCC_BDCR			*((uv32*)(0x20+RCC_OFFSET))
#define RCC_CSR				*((uv32*)(0x24+RCC_OFFSET))






#define AHB_FLAG			0xFFFFFF0F
#define APB1_FLAG			0xFFFFF8FF
#define APB2_FLAG			0xFFFFC7FF
#define PLL_FLAG			0xF0FC0000

#define HSE_FLAG			0X01
#define PLL_SYS_FLAG		0X02


#endif
