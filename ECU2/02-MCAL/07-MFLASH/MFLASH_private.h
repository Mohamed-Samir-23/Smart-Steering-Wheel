/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: FLASH					*/
/*  Layer		: MCAL					*/
/*  Version		: 1.0					*/
/*  Date		: October 29, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/

#ifndef _MFLASH_PRIVATE_H_
#define _MFLASH_PRIVATE_H_



#define FLASH_BASE  0x40022000 


#define FLASH_ACR 		*((uv32 *)(0x00 + FLASH_BASE))
#define FLASH_KEYR 		*((uv32 *)(0x04 + FLASH_BASE))
#define FLASH_KEY1	0x45670123
#define FLASH_KEY2	0xCDEF89AB


#define FLASH_OPTKEYR 	*((uv32 *)(0x08 + FLASH_BASE))


#define FLASH_SR 		*((uv32 *)(0x0C + FLASH_BASE))
#define BSY          	0U                                                            
#define PGERR         	2U                               
#define WRPRTERR       	4U                               
#define EOP       		5U  




#define FLASH_CR 				*((uv32 *)(0x10 + FLASH_BASE))
#define PG          	0U                               
#define PER         	1U                               
#define MER         	2U                               
#define OPTPG       	4U                               
#define OPTER       	5U                               
#define STRT        	6U                               
#define LOCK        	7U                               
#define OPTWRE      	9U                               
#define ERRIE       	10U                              
#define EOPIE       	12U   


#define FLASH_AR 		*((uv32 *)(0x14 + FLASH_BASE))
#define FLASH_OBR 		*((uv32 *)(0x1C + FLASH_BASE))
#define FLASH_WRPR 		*((uv32 *)(0x20 + FLASH_BASE))


static STD_error_t MFLASH_stderrorUnlock
(
	void
);


static void MFLASH_stderrorlock
(
	void
);

#endif
