/*****************************************/
/*   Author      : Mahmoud Ahmed         */
/*   SWC         : NVIC                  */
/*   Layer       : MCAL                  */
/*   Version     : 1.0                   */
/*   Date        : October 2   , 2023    */
/*   Last Edit   : N/A                   */
/*****************************************/
#include "LSTD_types.h"
#include "LBIT_math.h"

#include "MNVIC_interface.h"
#include "MNVIC_private.h"

static u8 PriorityConfig;

void MNVIC_vEnableIRQ(u8 IRQn)
{
	SET_BIT(MNVIC->ISER[IRQn/32] ,IRQn%32);
}

void MNVIC_vDisableIRQ(u8 IRQn)
{
	SET_BIT(MNVIC->ICER[IRQn/32] ,IRQn%32);
}
void MNVIC_vSetPendingIRQ(u8 IRQn)
{
	SET_BIT(MNVIC->ISPR[IRQn/32] ,IRQn%32);
}
void MNVIC_vClearPendingIRQ(u8 IRQn)
{
	SET_BIT(MNVIC->ICPR[IRQn/32] ,IRQn%32);
}
u8 MNVIC_u8GetPendingIRQ(u8 IRQn)
{
	return (GET_BIT(MNVIC->ISPR[IRQn/32],IRQn%32));
}

void MNVIC_vSetPriorityConfig (u8 Copy_u8PrioriyConfig)
{
	PriorityConfig = Copy_u8PrioriyConfig;
	MSCB->AIRCR = (MNVIC_VECTKEY<<16) |  (Copy_u8PrioriyConfig<<8);
}

void MNVIC_vSetPriorityIRQ(u8 IRQn,u8 Copy_u8GroupId, u8 Copy_u8SubGroupId)
{
	u8 L_u8Priority = 0;
	switch (PriorityConfig) {

		case MNVIC_PRIORITY_GROUPS_0_SUBGROUPS_16 :
			L_u8Priority = Copy_u8SubGroupId<<4;
			break;

		case MNVIC_PRIORITY_GROUPS_16_SUBGROUPS_0 :
			L_u8Priority = Copy_u8GroupId<<4;
			break;

		case MNVIC_PRIORITY_GROUPS_2_SUBGROUPS_8 :
			L_u8Priority = (Copy_u8GroupId<<7) | ((Copy_u8SubGroupId<<4) & 0x70);
			break;

		case MNVIC_PRIORITY_GROUPS_4_SUBGROUPS_4:
			L_u8Priority = 	(Copy_u8GroupId<<6)	| ((Copy_u8SubGroupId<<4) & 0x30);
			break;

		case MNVIC_PRIORITY_GROUPS_8_SUBGROUPS_2 :
			L_u8Priority = 	(Copy_u8GroupId<<5)	| ((Copy_u8SubGroupId<<4) & 0x10);
			break;

		default:
			//error
			return;

	
			
	}
	MNVIC->IPR[IRQn/4] |= (L_u8Priority   << (8*(IRQn%4) )  );
}


