/*****************************************/
/*   Author      : Mahmoud Ahmed         */
/*   SWC         : NVIC                  */
/*   Layer       : MCAL                  */
/*   Version     : 1.0                   */
/*   Date        : October 2   , 2023    */
/*   Last Edit   : N/A                   */
/*****************************************/


#ifndef _MNVIC_INTERFACE_H_
#define _MNVIC_INTERFACE_H_

/*Interrupt Level*/
//GIE ---> NVIC ENABLE ---> PIE
#define MNVIC_PRIORITY_GROUPS_16_SUBGROUPS_0 	0b000
#define MNVIC_PRIORITY_GROUPS_8_SUBGROUPS_2 	0b100
#define MNVIC_PRIORITY_GROUPS_4_SUBGROUPS_4 	0b101
#define MNVIC_PRIORITY_GROUPS_2_SUBGROUPS_8 	0b110
#define MNVIC_PRIORITY_GROUPS_0_SUBGROUPS_16 	0b111
#define MNVIC_VECTKEY							0x5FA

#define MNVIC_GIE(void) __ASM volatile ("cpsie i");
#define MNVIC_GID(void) __ASM volatile ("cpsid i");


void MNVIC_vEnableIRQ(u8 IRQn);
void MNVIC_vDisableIRQ(u8 IRQn);

void MNVIC_vSetPendingIRQ(u8 IRQn);
void MNVIC_vClearPendingIRQ(u8 IRQn);
u8 	 MNVIC_GetPendingIRQ(u8 IRQn);

void MNVIC_vSetPriorityConfig (u8 Copy_u8PrioriyConfig);
void MNVIC_vSetPriorityIRQ(u8 IRQn,u8 Copy_u8GroupId, u8 Copy_u8SubGroupId);
//u32 MNVIC_u32GetPriority(u8 IRQn);



#endif
