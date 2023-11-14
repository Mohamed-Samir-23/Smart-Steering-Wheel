/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: RCC					*/
/*  Layer		: MCAL					*/
/*  Version		: 1.0					*/
/*  Date		: October 09, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/

/* Library Include */
#include "LSTD_types.h"

/* SWC Include */
#include "MRCC_config.h"
#include "MRCC_private.h"
#include "MRCC_interface.h"

static u8 MRCC_u8PllCk=0;

STD_error_t MRCC_stderrorInit 
(
	RCC_ClkSrc_t 		ARG_udtClkSrc ,
	RCC_AHBPreScaler_t 	ARG_udtAHBPreScaler,
	RCC_APBPreScaler_t 	ARG_udtAPB1PreScaler,
	RCC_APBPreScaler_t 	ARG_udtAPB2PreScaler
)
{
	STD_error_t L_stderrorError=E_NOK;
	
	if((ARG_udtClkSrc<=4)&&(((ARG_udtAHBPreScaler>=8)&&(ARG_udtAHBPreScaler<=15))||(ARG_udtAHBPreScaler==0))&&(((ARG_udtAPB1PreScaler>=3)&&(ARG_udtAPB1PreScaler<=7))||(ARG_udtAPB1PreScaler==0))&&(((ARG_udtAPB2PreScaler>=3)&&(ARG_udtAPB2PreScaler<=7))||(ARG_udtAPB2PreScaler==0)))
	{
		switch(ARG_udtClkSrc)
		{
			case HSE_Crystal:
			{
				MRCC_u8PllCk=0;
				/*SYSCLK equal to HSE*/
				RCC_CFGR=(RCC_CFGR&(~(3U<<SW)));
				RCC_CFGR|=(HSE_FLAG);
				/*Disable bypass*/
				RCC_CR	&=~(1U<<HSEBYP);
				/*Enable HSE*/
				RCC_CR|=(1U<<HSEON);
				while((((RCC_CR>>HSERDY)&1))==0);
				break;
			}
			case HSE_RC:
			{
				MRCC_u8PllCk=0;
				/*SYSCLK equal to HSE*/
				RCC_CFGR=(RCC_CFGR&(~(3U<<SW)));
				RCC_CFGR|=(HSE_FLAG);
				/*Enable bypass*/
				RCC_CR|=(1U<<HSEBYP);
				/*Enable HSE*/
				RCC_CR|=(1U<<HSEON);
				while((((RCC_CR>>HSERDY)&1))==0);
				break;
			}
			case HSI:
			{
				MRCC_u8PllCk=0;
				/*SYSCLK equal to HSI*/
				RCC_CFGR=(RCC_CFGR&(~(3U<<SW)));
				/*Enable HSI*/
				RCC_CR|=(1U<<HSION);
				while((((RCC_CR>>HSIRDY)&1))==0);
				
				
				break;
			}
			case PLL_HSE:
			{
				MRCC_u8PllCk=1;
				/*Disable PLL*/
				RCC_CR &=(~(1<<PLLRON));
				while((((RCC_CR>>PLLRDY)&1))==1);
				/*Enable HSE*/
				RCC_CR|=(1U<<HSEON);
				while((((RCC_CR>>HSERDY)&1))==0);
				/*PLL HSE SELECT*/
				RCC_CFGR|=(1U<<PLLSRC);
				/*PLL NO DIVIDED HSE */
				RCC_CFGR&=(~(1<<PLLXTPRE));
				break;
			}
			case PLL_HSE_DIVIDED_BY_2:
			{
				MRCC_u8PllCk=1;
				/*Disable PLL*/
				RCC_CR &=(~(1<<PLLRON));
				while((((RCC_CR>>PLLRDY)&1))==1);
				/*Enable HSE*/
				RCC_CR|=(1U<<HSEON);
				while((((RCC_CR>>HSERDY)&1))==0);
				/*PLL HSE SELECT*/
				RCC_CFGR|=(1U<<PLLSRC);
				/*PLL NO DIVIDED HSE */
				RCC_CFGR|=(1U<<PLLXTPRE);
				break;
			}
			case PLL_HSI_DIVIDED_BY_2:
			{
				MRCC_u8PllCk=1;
				/*Disable PLL*/
				RCC_CR &=(~(1<<PLLRON));
				while((((RCC_CR>>PLLRDY)&1))==1);
				/*Enable HSI*/
				RCC_CR|=(1U<<HSION);
				while((((RCC_CR>>HSIRDY)&1))==0);
				/*PLL HSI SELECT*/
				RCC_CFGR&=~(1U<<PLLSRC);
				break;
			}
			default : 
			{
				/*nothing*/
				break;
			}
		}
		
		/*AHB1*/
		RCC_CFGR=(RCC_CFGR&AHB_FLAG);
		RCC_CFGR|=(ARG_udtAHBPreScaler<<HPRE);
		/*APB1*/
		RCC_CFGR=(RCC_CFGR&APB1_FLAG);
		RCC_CFGR|=(ARG_udtAPB1PreScaler<<PPRE1);
		/*APB2*/
		RCC_CFGR=(RCC_CFGR&APB2_FLAG);
		RCC_CFGR|=(ARG_udtAPB2PreScaler<<PPRE2);
		
		L_stderrorError = E_OK;
	}
	else
	{
		L_stderrorError=E_NOK;
	}
	
	return L_stderrorError;
}



STD_error_t MRCC_stderrorSetPllClockFreq
(
	RCC_PLLPreScaler_t 	ARG_udtPLLPreScaler,
	RCC_FLASH_LATENCY_t ARG_udtLatency
)
{
	STD_error_t L_stderrorError=E_NOK;
	
	if((MRCC_u8PllCk==1)&&(ARG_udtPLLPreScaler<=14)&&(ARG_udtLatency<=2))
	{

		/*Set PLLM, PLLN, PLLP, PLLQ*/
		RCC_CFGR=(RCC_CFGR&(~(15U<<PLLMUL)));
		RCC_CFGR|=(ARG_udtPLLPreScaler<<PLLMUL);
		/*Enable PLL*/
		RCC_CR|=(1U<<PLLRON);
		while((((RCC_CR>>PLLRDY)&1))==0);

		/*set Latency*/
		FLASH_ACR&=~(LATENCY_FLAG);
		FLASH_ACR|=ARG_udtLatency;

		/*SYSCLK equal to PLL*/
		RCC_CFGR=(RCC_CFGR&(~(3U<<SW)));
		RCC_CFGR|=PLL_SYS_FLAG;

		L_stderrorError = E_OK;
	}
	else
	{
		L_stderrorError=E_NOK;	
	}
	
	return L_stderrorError;
}


STD_error_t RCC_EnablePeripheralClk
(
	RCC_Bus_t 			ARG_udtBus,
	RCC_PeripheraName_t ARG_udtPeripheraName
)
{
	
	STD_error_t L_stderrorError=E_NOK;
	
	switch(ARG_udtBus)
	{
		case AHB1:
		{
			RCC_AHBENR|=(1U<<ARG_udtPeripheraName);
			L_stderrorError=E_OK;
			break;
		}
		case APB1:
		{
			RCC_APB1ENR|=(1U<<ARG_udtPeripheraName);
			L_stderrorError=E_OK;
			break;
		}
		case APB2:
		{
			RCC_APB2ENR|=(1U<<ARG_udtPeripheraName);
			L_stderrorError=E_OK;
			break;
		}
		
		default:
		{
			L_stderrorError=E_NOK;
			break;
		}
			
	}
	return L_stderrorError;
	
}


STD_error_t RCC_DisablePeripheralClk
(
	RCC_Bus_t 			ARG_udtBus,
	RCC_PeripheraName_t ARG_udtPeripheraName
)
{
	STD_error_t L_stderrorError=E_NOK;
	
	switch(ARG_udtBus)
	{
		case AHB1:
		{
			RCC_AHBENR	&=~(1U<<ARG_udtPeripheraName);
			L_stderrorError=E_OK;
			break;
		}
		case APB1:
		{
			RCC_APB1ENR	&=~(1U<<ARG_udtPeripheraName);
			L_stderrorError=E_OK;
			break;
		}
		case APB2:
		{
			RCC_APB2ENR	&=~(1U<<ARG_udtPeripheraName);
			L_stderrorError=E_OK;
			break;
		}
		
		default:
		{
			L_stderrorError=E_NOK;
			break;
		}
			
	}
	return L_stderrorError;
	
}
