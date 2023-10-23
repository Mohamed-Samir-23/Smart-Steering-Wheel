/*****************************************/
/*   Author      : Mohamed Samir         */
/*   SWC         : NVIC                  */
/*   Layer       : MCAL                  */
/*   Version     : 1.1                   */
/*   Date        : October 2 , 2023	     */
/*   Last Edit   : October 23, 2023      */
/*****************************************/

/* Library Include */
#include "LSTD_types.h"

/* SWC Include */
#include "MNVIC_private.h"
#include "MNVIC_interface.h"


static u8 MNVIC_u8PriorityConfig = NO_CONFIG;

STD_error_t MNVIC_stderrorEnableIRQ
(
	IRQ_t ARG_udtIRQn
)
{
	STD_error_t L_stderrorError=E_NOK;
	
	if(ARG_udtIRQn<=59)
	{
		MNVIC->ISER[ARG_udtIRQn/32]= (1<<(ARG_udtIRQn%32));
		L_stderrorError=E_OK;
	}
	else
	{
		L_stderrorError=E_NOK;
	}
	return L_stderrorError;
}


STD_error_t MNVIC_stderrorDisableIRQ
(
	IRQ_t ARG_udtIRQn
)
{
	STD_error_t L_stderrorError=E_NOK;
	if(ARG_udtIRQn<=59)
	{
		MNVIC->ICER[ARG_udtIRQn/32] = (1<<(ARG_udtIRQn%32));
		L_stderrorError=E_OK;
	}
	else
	{
		L_stderrorError=E_NOK;
	}
	return L_stderrorError;
}



STD_error_t MNVIC_stderrorSetPendingIRQ
(
	IRQ_t ARG_udtIRQn
)
{
	STD_error_t L_stderrorError=E_NOK;
	
	if(ARG_udtIRQn<=59)
	{
		MNVIC->ISPR[ARG_udtIRQn/32] = (1<<(ARG_udtIRQn%32));
		L_stderrorError=E_OK;
	}
	else
	{
		L_stderrorError=E_NOK;
	}
	return L_stderrorError;
}



STD_error_t MNVIC_stderrorClearPendingIRQ
(
	IRQ_t ARG_udtIRQn
)
{
	STD_error_t L_stderrorError=E_NOK;
	
	if(ARG_udtIRQn<=59)
	{
		MNVIC->ICPR[ARG_udtIRQn/32] = (1<<(ARG_udtIRQn%32));
		L_stderrorError=E_OK;
	}
	else
	{
		L_stderrorError=E_NOK;
	}
	return L_stderrorError;
}



STD_error_t MNVIC_stderrorGetPendingIRQ
(
	IRQ_t ARG_udtIRQn,
	u8* ARG_u8PendingState
)
{
	
	STD_error_t L_stderrorError=E_NOK;
	
	if(ARG_u8PendingState != NULL_POINTER )
	{
		if(ARG_udtIRQn<=59)
		{
			*ARG_u8PendingState= (1&(MNVIC->ISPR[ARG_udtIRQn/32]>>(ARG_udtIRQn%32)));
			
			L_stderrorError=E_OK;
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


STD_error_t MNVIC_stderrorSetPriorityConfig 
(
	SCB_PriorityGroup_t ARG_udtPrioriyConfig
)
{
	STD_error_t L_stderrorError=E_NOK;
	
	if((ARG_udtPrioriyConfig>=3)&&(ARG_udtPrioriyConfig>=7))
	{
		MNVIC_u8PriorityConfig = ARG_udtPrioriyConfig;
		
		MSCB->AIRCR = (MNVIC_VECTKEY<<16) |  (ARG_udtPrioriyConfig<<8);
	}
	else
	{
		L_stderrorError=E_NOK;
	}
	return L_stderrorError;
}



STD_error_t MNVIC_stderrorSetPriorityIRQ
(
	IRQ_t ARG_udtIRQn,
	u8 ARG_u8GroupId,
	u8 ARG_u8SubGroupId
)
{
	STD_error_t L_stderrorError=E_NOK;
	
	if(ARG_udtIRQn<=59)
	{
		u8 L_u8Priority = 0;
	
		switch (MNVIC_u8PriorityConfig)
		{
			case PRIGROUP_0GRU_16SUB:
			{
				L_u8Priority = ARG_u8SubGroupId<<4U;
				L_stderrorError=E_OK;
				break;
			}
			case PRIGROUP_16GRU_0SUB:
			{
				L_u8Priority = ARG_u8GroupId<<4U;
				L_stderrorError=E_OK;
				break;
			}
			case PRIGROUP_2GRU_8SUB:
			{
				L_u8Priority = (ARG_u8GroupId<<7U) | ((ARG_u8SubGroupId<<4U) & 0x70);
				L_stderrorError=E_OK;
				break;
			}
			case PRIGROUP_4GRU_4SUB:
			{
				L_u8Priority = 	(ARG_u8GroupId<<6U)	| ((ARG_u8SubGroupId<<4) & 0x30);
				L_stderrorError=E_OK;
				break;
			}
			case PRIGROUP_8GRU_2SUB:
			{
				L_u8Priority = 	(ARG_u8GroupId<<5U)	| ((ARG_u8SubGroupId<<4U) & 0x10);
				L_stderrorError=E_OK;
				break;
			}
			default:
			{
				L_stderrorError=E_NOK;
				break;
			}
		}
		
		if(L_stderrorError==E_NOK)
		{
			MNVIC->IPR[ARG_udtIRQn/4] |= (L_u8Priority   << (8*(ARG_udtIRQn%4) )  );
		}
		else
		{
			
			
		}
	}
	else
	{
		L_stderrorError=E_NOK;
	}
		
	return L_stderrorError;	
}


