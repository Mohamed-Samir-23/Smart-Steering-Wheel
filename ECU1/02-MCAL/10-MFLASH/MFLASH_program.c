/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: FLASH					*/
/*  Layer		: MCAL					*/
/*  Version		: 1.0					*/
/*  Date		: October 29, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/


/* Library Include */
#include "LSTD_types.h"

/* SWC Include */
#include "MFLASH_config.h"
#include "MFLASH_private.h"
#include "MFLASH_interface.h"


static STD_error_t MFLASH_stderrorUnlock
(
	void
)
{
	STD_error_t L_stderrorError=E_NOK;
	
	if((1&(FLASH_CR>>LOCK))==1)
	{
		FLASH_KEYR=FLASH_KEY1;
		FLASH_KEYR=FLASH_KEY2;	
		L_stderrorError=E_NOK;
	}
	else
	{
		L_stderrorError=E_OK;
	}
	
	return L_stderrorError;
}


static void MFLASH_stderrorlock
(
	void
)
{
	FLASH_CR|=(1<<LOCK);
}


void MFLASH_voidEraseAllSection
(
	void
)
{
	/*delay until no operation in Flash*/
	while((1&(FLASH_SR>>BSY))==1);
	
	/*Clear pending bit*/
	FLASH_SR|=(1<<EOP);
	
	/*unlock Flash*/
	while((MFLASH_stderrorUnlock())!=E_OK);
	
	/*Mass erase enable*/
	FLASH_CR|=(1<<MER);
	
	/*start erase*/
	FLASH_CR|=(1<<STRT);
	
	/*delay until no operation in Flash*/
	while((1&(FLASH_SR>>BSY))==1);
	
	/*Clear pending bit*/
	FLASH_SR|=(1<<EOP);
	
	/*Mass erase disable*/
	FLASH_CR&=~(1<<MER);
	
	/*lock Flash*/
	MFLASH_stderrorlock();
}


void MFLASH_voidErasePage
(
	u8 ARG_u8PageNumber
)
{
	
	/*delay until no operation in Flash*/
	while((1&(FLASH_SR>>BSY))==1);
	
	/*unlock Flash*/
	while((MFLASH_stderrorUnlock())!=E_OK);
	
	/*Clear pending bit*/
	FLASH_SR|=(1<<EOP);
	
	/*Page erase enable*/
	FLASH_CR|=(1<<PER);
	
	/*select page 1kb = 1024*/
	FLASH_AR = (u32)(ARG_u8PageNumber * 1024) + 0x08000000 ;
	
	/*start erase*/
	FLASH_CR|=(1<<STRT);
	
	/*delay until no operation in Flash*/
	while((1&(FLASH_SR>>BSY))==1);
	
	/*Clear pending bit*/
	FLASH_SR|=(1<<EOP);
	
	/*Page erase disable*/
	FLASH_CR&=~(1<<PER);
	
	/*lock Flash*/
	MFLASH_stderrorlock();
}



STD_error_t MFLASH_stderrorWrite32BitData
(
	u8 ARG_u8PageNumber,
	u32* ARG_Pu16Data
)
{
	
	STD_error_t L_stderrorError=E_NOK;
	
	if(ARG_Pu16Data != NULL_POINTER )
	{
		
		u32 L_u32Address =(u32)(ARG_u8PageNumber * 1024) + 0x08000000 ;
		
		/*Page erase*/
		MFLASH_voidErasePage(ARG_u8PageNumber);
	
		/*unlock Flash*/
		while((MFLASH_stderrorUnlock())!=E_OK);
	
		/*enable Flash programming*/
		FLASH_CR|=(1<<PG);
		
		/*set data to page*/
		*((volatile u16*)L_u32Address) =*ARG_Pu16Data ;

		/*delay until no operation in Flash*/
		while((1&(FLASH_SR>>BSY))==1);
		
		/*Clear pending bit*/
		FLASH_SR|=(1<<EOP);
		
		/*disable Flash programming*/
		FLASH_CR&=~(1<<PG);
		
		/*lock Flash*/
		MFLASH_stderrorlock();
		
		L_stderrorError=E_OK;
	}
	else
	{
		L_stderrorError=E_NULL_POINTER;
	}
	return L_stderrorError;
}



STD_error_t MFLASH_voidWriteSection
(
	u32 ARG_u32Address,
	u16* ARG_Pu16Data,
	u8 ARG_u8Length
)
{
	
	STD_error_t L_stderrorError=E_NOK;
	
	if(ARG_Pu16Data != NULL_POINTER )
	{
		u8 L_u8i=0;
		
		/*unlock Flash*/
		while((MFLASH_stderrorUnlock())!=E_OK);
	
	
		for (L_u8i = 0; L_u8i < ARG_u8Length; L_u8i++)
		{
			/*enable Flash programming*/
			FLASH_CR|=(1<<PG);
			
			*((volatile u16*)ARG_u32Address) = ARG_Pu16Data[L_u8i];
			ARG_u32Address+=2;
			
			/*delay until no operation in Flash*/
			while((1&(FLASH_SR>>BSY))==1);
			
			/*Clear pending bit*/
			FLASH_SR|=(1<<EOP);
		
			/*disable Flash programming*/
			FLASH_CR&=~(1<<PG);
		}
		
		/*lock Flash*/
		MFLASH_stderrorlock();
		
		L_stderrorError=E_OK;
	}
	else
	{
		L_stderrorError=E_NULL_POINTER;
	}
	return L_stderrorError;
}


STD_error_t MFLASH_voidReadPage
(
	u8 ARG_u8PageNumber,
	u16* ARG_Pu16Data
)
{
	STD_error_t L_stderrorError=E_NOK;

	if(ARG_Pu16Data != NULL_POINTER )
	{
		u32 L_u32Address =(u32)(ARG_u8PageNumber * 1024) + 0x08000000 ;

		*ARG_Pu16Data=	*((volatile u32*)L_u32Address);
		L_stderrorError=E_OK;
	}
	else
	{
		L_stderrorError=E_NULL_POINTER;
	}
	return L_stderrorError;
}
