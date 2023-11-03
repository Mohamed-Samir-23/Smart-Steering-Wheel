/*****************************************/
/*   Author      : Mohamed Samir         */
/*   SWC         : NVIC                  */
/*   Layer       : MCAL                  */
/*   Version     : 1.1                   */
/*   Date        : October 	02 , 2023	 */
/*   Last Edit   : November 03, 2023     */
/*****************************************/


#ifndef _MNVIC_PRIVATE_H_
#define _MNVIC_PRIVATE_H_

typedef struct
{
	u32 ISER[8];
	u32 RESERVED0[24];
	u32 ICER[8];
	u32 RESERVED1[24];
	u32 ISPR[8];
	u32 RESERVED2[24];
	u32 ICPR[8];
	u32 RESERVED3[24];
	u32 IABR[8];
	u32 RESERVED4[56];
	u32 IPR[60];
	u32 RESERVED5[580];
	u32 STIR;

}NVIC_t;

#define MNVIC ((volatile NVIC_t * ) 0xE000E100)

#ifndef	SCB_BASE_ADDRESS
#define SCB_BASE_ADDRESS	0xE000E008
typedef struct
{
	 u32 ACTLR[415];
	 u32 CPUID;
	 u32 ICSR;
	 u32 VTOR;
	 u32 AIRCR;
	 u32 SCR;
	 u32 CCR;
	 u32 SHPR1;
	 u32 SHPR2;
	 u32 SHPR3;
	 u32 SHCSR;
	 u32 CFSR;
	 u32 HFSR[2];
	 u32 MMAR;
	 u32 BFAR;
	 u32 AFSR;
	 
}SCB_t;
#define MSCB				((volatile SCB_t *)SCB_BASE_ADDRESS)
#define MSCB_VECTKEY		0x5FAUL

#endif


#define NO_CONFIG 8

#endif
