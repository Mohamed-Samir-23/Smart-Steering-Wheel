/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: FLASH					*/
/*  Layer		: MCAL					*/
/*  Version		: 1.0					*/
/*  Date		: October 30, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/

#ifndef _MFLASH_INTERFACE_H_
#define _MFLASH_INTERFACE_H_


void MFLASH_voidEraseAllSection
(
	void
);


void MFLASH_voidEraseApp1Section
(
	void
);


void MFLASH_voidEraseApp2Section
(
	void
);


void MFLASH_voidEraseBootSection
(
	void
);


void MFLASH_voidErasePage
(
	u8 ARG_u8PageNumber
);


STD_error_t MFLASH_stderrorWrite32BitData
(
	u8 ARG_u8PageNumber,
	u32* ARG_Pu16Data
);


STD_error_t MFLASH_voidWriteSection
(
	u32 ARG_u32Address,
	u16* ARG_Pu16Data,
	u8 ARG_u8Length
);


STD_error_t MFLASH_voidReadPage
(
	u8 ARG_u8PageNumber,
	u16* ARG_Pu16Data
);


#endif
