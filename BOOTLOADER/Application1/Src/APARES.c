/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: APPLICATION			*/
/*  Layer		: APP					*/
/*  Version		: 1.0					*/
/*  Date		: October 30, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/

/* Library Include */
#include "LSTD_types.h"

/* SWC Include */
#include "MFLASH_interface.h"


u8 APARES_u8EndMSG=0;

u16 APARES_arru16Data[100] = {0};

u32 APARES_u8Address= 0x08000000;

u8 APARES_AsciToHex
(
	u8 ARG_u8Asci
)
{
	u8 L_u8Result;
	if ( (ARG_u8Asci >= 48) && (ARG_u8Asci <= 57) )
	{
		L_u8Result = ARG_u8Asci - 48;
	}
	else
	{
		L_u8Result = ARG_u8Asci - 55;
	}

	return L_u8Result;
}


STD_error_t APARES_voidData
(
	volatile u8* ARG_Pu8Data
)
{
	STD_error_t L_stderrorError=E_NOK;
	
	if(ARG_Pu8Data != NULL_POINTER )
	{
		u8 L_u8DigitLow,L_u8DigitHigh,L_u8CC,L_u8I;
		u8 L_u8DataDigit0,L_u8DataDigit1,L_u8DataDigit2,L_u8DataDigit3;
		u8 L_u8DataCounter = 0;

		/* Get Character Count */
		L_u8DigitHigh = APARES_AsciToHex (ARG_Pu8Data[1]);
		L_u8DigitLow  = APARES_AsciToHex (ARG_Pu8Data[2]);
		L_u8CC = (L_u8DigitHigh<<4) | L_u8DigitLow ;

		/* Get Address */
		L_u8DataDigit0 = APARES_AsciToHex (ARG_Pu8Data[3]);
		L_u8DataDigit1 = APARES_AsciToHex (ARG_Pu8Data[4]);
		L_u8DataDigit2 = APARES_AsciToHex (ARG_Pu8Data[5]);
		L_u8DataDigit3 = APARES_AsciToHex (ARG_Pu8Data[6]);

		/* Clear Low Part of Address */
		APARES_u8Address = APARES_u8Address & 0xFFFF0000;
		APARES_u8Address = APARES_u8Address | (L_u8DataDigit3) | (L_u8DataDigit2 << 4) | (L_u8DataDigit1 << 8) | (L_u8DataDigit0<<12);

		for (L_u8I=0;L_u8I<(L_u8CC/2); L_u8I++)
		{
			L_u8DataDigit0 = APARES_AsciToHex (ARG_Pu8Data[4*L_u8I+9 ]);
			L_u8DataDigit1 = APARES_AsciToHex (ARG_Pu8Data[4*L_u8I+10]);
			L_u8DataDigit2 = APARES_AsciToHex (ARG_Pu8Data[4*L_u8I+11]);
			L_u8DataDigit3 = APARES_AsciToHex (ARG_Pu8Data[4*L_u8I+12]);

			APARES_arru16Data[L_u8DataCounter] = (L_u8DataDigit3 << 8) | (L_u8DataDigit2 << 12) | (L_u8DataDigit1) | (L_u8DataDigit0<<4);
			L_u8DataCounter++;
		}

		L_stderrorError=MFLASH_voidWriteSection(APARES_u8Address,APARES_arru16Data,(L_u8CC/2));
	}
	else
	{
		L_stderrorError=E_NULL_POINTER;
	}
	return L_stderrorError;
}


void APARES_voidRecord
(
	volatile u8* ARG_Pu8Data
)
{
	switch (ARG_Pu8Data[8])
	{
		case '0':	APARES_voidData(ARG_Pu8Data); break;
		case '4':	break;
		case '1':	APARES_u8EndMSG=1; break;
		default :	break;
	}
}


u8 APARES_u8EndRecordFlag
(
	void
)
{
	u8 L_u8temp =APARES_u8EndMSG;

	if(L_u8temp==1)
	{
		APARES_u8EndMSG=0;
	}
	else
	{

	}
	return L_u8temp;
}


