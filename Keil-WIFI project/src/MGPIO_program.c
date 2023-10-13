/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: GPIO					*/
/*  Layer		: MCAL					*/
/*  Version		: 1.0					*/
/*  Date		: October 09, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/

/* Library Include */
#include "LSTD_types.h"

/* SWC Include */
#include "MGPIO_config.h"
#include "MGPIO_private.h"
#include "MGPIO_interface.h"


STD_error_t MGPIO_stderrorPinModeSelect
(
	MGPIO_Port_Name_t ARG_udtGPIOPort, 
	MGPIO_Pin_Number_t ARG_udtGPIOPin,
	MGPIO_Pin_Mode_t ARG_udtGPIOMode
)
{
	
	STD_error_t L_stderrorError=E_NOK;
	
	if(ARG_udtGPIOPort <= 4 && ARG_udtGPIOPin <= 15 && ARG_udtGPIOMode <= 15)
	{
		
		switch(ARG_udtGPIOPort)
		{
			case GPIOA:
			{
				
				if(ARG_udtGPIOPin<=7)
				{
					GPIOA_CRL =(GPIOA_CRL&(~(15U<<(4*ARG_udtGPIOPin))));
					GPIOA_CRL|=(ARG_udtGPIOMode<<(4*ARG_udtGPIOPin));
				}
				else
				{
					GPIOA_CRH =(GPIOA_CRH&(~(15U<<(4*(ARG_udtGPIOPin%8)))));
					GPIOA_CRH|=(ARG_udtGPIOMode<<(4*(ARG_udtGPIOPin%8)));
				}
				L_stderrorError=E_OK;
				break;
			}
			case GPIOB:
			{
				if(ARG_udtGPIOPin<=7)
				{
					GPIOB_CRL =(GPIOA_CRL&(~(15U<<(4*ARG_udtGPIOPin))));
					GPIOB_CRL|=(ARG_udtGPIOMode<<(4*ARG_udtGPIOPin));
				}
				else
				{
					GPIOB_CRH =(GPIOA_CRH&(~(15U<<(4*(ARG_udtGPIOPin%8)))));
					GPIOB_CRH|=(ARG_udtGPIOMode<<(4*(ARG_udtGPIOPin%8)));
				}
				L_stderrorError=E_OK;
				break;
			}
			case GPIOC:
			{
				if(ARG_udtGPIOPin<=7)
				{
					GPIOC_CRL =(GPIOA_CRL&(~(15U<<(4*ARG_udtGPIOPin))));
					GPIOC_CRL|=(ARG_udtGPIOMode<<(4*ARG_udtGPIOPin));
				}
				else
				{
					GPIOC_CRH =(GPIOA_CRH&(~(15U<<(4*(ARG_udtGPIOPin%8)))));
					GPIOC_CRH|=(ARG_udtGPIOMode<<(4*(ARG_udtGPIOPin%8)));
				}
				L_stderrorError=E_OK;
				break;
			}
			case GPIOD:
			{
				if(ARG_udtGPIOPin<=7)
				{
					GPIOD_CRL =(GPIOA_CRL&(~(15U<<(4*ARG_udtGPIOPin))));
					GPIOD_CRL|=(ARG_udtGPIOMode<<(4*ARG_udtGPIOPin));
				}
				else
				{
					GPIOD_CRH =(GPIOA_CRH&(~(15U<<(4*(ARG_udtGPIOPin%8)))));
					GPIOD_CRH|=(ARG_udtGPIOMode<<(4*(ARG_udtGPIOPin%8)));
				}
				L_stderrorError=E_OK;
				break;
			}
			case GPIOE:
			{
				if(ARG_udtGPIOPin<=7)
				{
					GPIOE_CRL =(GPIOA_CRL&(~(15U<<(4*ARG_udtGPIOPin))));
					GPIOE_CRL|=(ARG_udtGPIOMode<<(4*ARG_udtGPIOPin));
				}
				else
				{
					GPIOE_CRH =(GPIOA_CRH&(~(15U<<(4*(ARG_udtGPIOPin%8)))));
					GPIOE_CRH|=(ARG_udtGPIOMode<<(4*(ARG_udtGPIOPin%8)));
				}
				L_stderrorError=E_OK;
				break;
			}
			default :
			{
				/*nothing*/
				break;
			}
		}
	}
	else
	{
		L_stderrorError=E_NOK;
	}
	
	return L_stderrorError;
	
}



STD_error_t MGPIO_stderrorGetPinValue
(
	MGPIO_Port_Name_t ARG_udtGPIOPort, 
	MGPIO_Pin_Number_t ARG_udtGPIOPin, 
	u8* ARG_pu8Value
)
{
	STD_error_t L_stderrorError=E_NOK;
	
	if(ARG_pu8Value != NULL_POINTER )
	{
		
		if(ARG_udtGPIOPort <= 4 && ARG_udtGPIOPin <= 15 )
		{
		
			switch(ARG_udtGPIOPort)
			{
				case GPIOA:
				{
					*ARG_pu8Value =((GPIOA_IDR>>ARG_udtGPIOPin)&1U);
					L_stderrorError=E_OK;
					break;
				}
				case GPIOB:
				{
					*ARG_pu8Value =((GPIOB_IDR>>ARG_udtGPIOPin)&1U);
					L_stderrorError=E_OK;
					break;
				}
				case GPIOC:
				{
					*ARG_pu8Value =((GPIOC_IDR>>ARG_udtGPIOPin)&1U);
					L_stderrorError=E_OK;
					break;
				}
				case GPIOD:
				{
					*ARG_pu8Value =((GPIOD_IDR>>ARG_udtGPIOPin)&1U);
					L_stderrorError=E_OK;
					break;
				}
				case GPIOE:
				{
					*ARG_pu8Value =((GPIOE_IDR>>ARG_udtGPIOPin)&1U);
					L_stderrorError=E_OK;
					break;
				}
				default :
				{
					/*nothing*/
					break;
				}
				
			}
		}
		else
		{
			L_stderrorError=E_NOK;
		}
	}
	else
	{
		L_stderrorError=E_NULL_POINTER;
	}
	return L_stderrorError;
}



STD_error_t MGPIO_stderrorSetPinValue
(
	MGPIO_Port_Name_t ARG_udtGPIOPort, 
	MGPIO_Pin_Number_t ARG_udtGPIOPin, 
	MGPIO_Output_State_t ARG_udtValue
)
{
	STD_error_t L_stderrorError=E_NOK;
	
	if(ARG_udtGPIOPort <= 4 && ARG_udtGPIOPin <= 15 && ARG_udtValue <= 1)
	{
		switch(ARG_udtGPIOPort)
		{
			case GPIOA:
			{
				GPIOA_ODR =(GPIOA_ODR&(~(1<<(ARG_udtGPIOPin))));
				GPIOA_ODR|=(ARG_udtValue<<(ARG_udtGPIOPin));
				L_stderrorError=E_OK;
				break;
			}
			case GPIOB:
			{
				GPIOB_ODR =(GPIOB_ODR&(~(1<<(ARG_udtGPIOPin))));
				GPIOB_ODR|=(ARG_udtValue<<(ARG_udtGPIOPin));
				L_stderrorError=E_OK;
				break;
			}
			case GPIOC:
			{
				GPIOC_ODR =(GPIOC_ODR&(~(1<<(ARG_udtGPIOPin))));
				GPIOC_ODR|=(ARG_udtValue<<(ARG_udtGPIOPin));
				L_stderrorError=E_OK;
				break;
			}
			case GPIOD:
			{
				GPIOD_ODR =(GPIOD_ODR&(~(1<<(ARG_udtGPIOPin))));
				GPIOD_ODR|=(ARG_udtValue<<(ARG_udtGPIOPin));
				L_stderrorError=E_OK;
				break;
			}
			case GPIOE:
			{
				GPIOE_ODR =(GPIOE_ODR&(~(1<<(ARG_udtGPIOPin))));
				GPIOE_ODR|=(ARG_udtValue<<(ARG_udtGPIOPin));
				L_stderrorError=E_OK;
				break;
			}
			default :
			{
				/*nothing*/
				break;
			}
			
		}
	}
	else
	{
		L_stderrorError=E_NOK;
	}
	
	return L_stderrorError;
	
}


STD_error_t MGPIO_stderrorSetPinValueBSSR
(
	MGPIO_Port_Name_t ARG_udtGPIOPort, 
	MGPIO_Pin_Number_t ARG_udtGPIOPin, 
	MGPIO_Output_State_t ARG_udtValue
)
{
	
	STD_error_t L_stderrorError=E_NOK;
	
	if(ARG_udtGPIOPort <= 7 && ARG_udtGPIOPin <= 15 && ARG_udtValue <= 1)
	{
		
		if(ARG_udtValue==LOW)
		{
			
			switch(ARG_udtGPIOPort)
			{
				case GPIOA:
				{
					GPIOA_BSRR |=(1<<(ARG_udtGPIOPin+BSRR_OFFSET));
					L_stderrorError=E_OK;
					break;
				}
				case GPIOB:
				{
					GPIOB_BSRR |=(1<<(ARG_udtGPIOPin+BSRR_OFFSET));
					L_stderrorError=E_OK;
					break;
				}
				case GPIOC:
				{
					GPIOC_BSRR |=(1<<(ARG_udtGPIOPin+BSRR_OFFSET));
					L_stderrorError=E_OK;
					break;
				}
				case GPIOD:
				{
					GPIOD_BSRR |=(1<<(ARG_udtGPIOPin+BSRR_OFFSET));
					L_stderrorError=E_OK;
					break;
				}
				case GPIOE:
				{
					GPIOE_BSRR |=(1<<(ARG_udtGPIOPin+BSRR_OFFSET));
					L_stderrorError=E_OK;
					break;
				}
				default :
				{
					/*nothing*/
					break;
				}
				
			}
			
		}
		else
		{
			switch(ARG_udtGPIOPort)
			{
				case GPIOA:
				{
					GPIOA_BSRR |=(1<<(ARG_udtGPIOPin));
					L_stderrorError=E_OK;
					break;
				}
				case GPIOB:
				{
					GPIOB_BSRR |=(1<<(ARG_udtGPIOPin));
					L_stderrorError=E_OK;
					break;
				}
				case GPIOC:
				{
					GPIOC_BSRR |=(1<<(ARG_udtGPIOPin));
					L_stderrorError=E_OK;
					break;
				}
				case GPIOD:
				{
					GPIOD_BSRR |=(1<<(ARG_udtGPIOPin));
					L_stderrorError=E_OK;
					break;
				}
				case GPIOE:
				{
					GPIOE_BSRR |=(1<<(ARG_udtGPIOPin));
					L_stderrorError=E_OK;
					break;
				}
				default :
				{
					/*nothing*/
					break;
				}
				
			}	
		}
		
	}
	else
	{
		L_stderrorError=E_NOK;
	}
	return L_stderrorError;
}



STD_error_t MGPIO_stderrorSetPinPull_Up_Down
(
	MGPIO_Port_Name_t ARG_udtGPIOPort, 
	MGPIO_Pin_Number_t ARG_udtGPIOPin, 
	MGPIO_Pull_t ARG_udtPullType
)
{
	
	STD_error_t L_stderrorError=E_NOK;
	
	if(ARG_udtGPIOPort <= 4 && ARG_udtGPIOPin <= 15 && ARG_udtPullType <= 1)
	{
		switch(ARG_udtGPIOPort)
		{
			case GPIOA:
			{
				GPIOA_ODR =(GPIOA_ODR&(~(1<<(ARG_udtGPIOPin))));
				GPIOA_ODR|=(ARG_udtPullType<<(ARG_udtGPIOPin));
				L_stderrorError=E_OK;
				break;
			}
			case GPIOB:
			{
				GPIOB_ODR =(GPIOB_ODR&(~(1<<(ARG_udtGPIOPin))));
				GPIOB_ODR|=(ARG_udtPullType<<(ARG_udtGPIOPin));
				L_stderrorError=E_OK;
				break;
			}
			case GPIOC:
			{
				GPIOC_ODR =(GPIOC_ODR&(~(1<<(ARG_udtGPIOPin))));
				GPIOC_ODR|=(ARG_udtPullType<<(ARG_udtGPIOPin));
				L_stderrorError=E_OK;
				break;
			}
			case GPIOD:
			{
				GPIOD_ODR =(GPIOD_ODR&(~(1<<(ARG_udtGPIOPin))));
				GPIOD_ODR|=(ARG_udtPullType<<(ARG_udtGPIOPin));
				L_stderrorError=E_OK;
				break;
			}
			case GPIOE:
			{
				GPIOE_ODR =(GPIOE_ODR&(~(1<<(ARG_udtGPIOPin))));
				GPIOE_ODR|=(ARG_udtPullType<<(ARG_udtGPIOPin));
				L_stderrorError=E_OK;
				break;
			}
			default :
			{
				/*nothing*/
				break;
			}
		}
	}
	else
	{
		L_stderrorError=E_NOK;
	}
	
	return L_stderrorError;
	
}
