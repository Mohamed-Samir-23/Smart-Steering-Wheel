/*****************************************/
/*   Author      : Mahmoud Ahmed         */
/*   SWC         : SPI                   */
/*   Layer       : MCAL                  */
/*   Version     : 1.0                   */
/*   Date        : September 26, 2023    */
/*   Last Edit   : N/A                   */
/*****************************************/

#include "LSTD_types.h"
#include "LBIT_math.h"

#include "MSPI_interface.h"
#include "MSPI_config.h"
#include "MSPI_private.h"

void (*MSPI1_CallBack) (void) = NULL_POINTER;

void MSPI_vInit ( void ){

#if   MSP1_STATUS == MSPI_ENABLE

	#if		MSPI1_CLOCK_MODE == MSPI_CPOL_0_CPHA_0

		CLEAR_BIT( MSPI1 -> CR1 , 0 ); CLEAR_BIT( MSPI1 -> CR1 , 1 );

	#elif	MSPI1_CLOCK_MODE == MSPI_CPOL_0_CPHA_1

		SET_BIT( MSPI1 -> CR1 , 0 ); CLEAR_BIT( MSPI1 -> CR1 , 1 );

	#elif	MSPI1_CLOCK_MODE == MSPI_CPOL_1_CPHA_0

		CLEAR_BIT( MSPI1 -> CR1 , 0 ); SET_BIT( MSPI1 -> CR1 , 1 );

	#elif	MSPI1_CLOCK_MODE == MSPI_CPOL_1_CPHA_1

		SET_BIT( MSPI1 -> CR1 , 0 ); SET_BIT( MSPI1 -> CR1 , 1 );

	#endif

	#if    MSPI1_MASTER_SLAVE == MSPI_MASTER

		SET_BIT( MSPI1 -> CR1 , 2 );

	#elif  MSPI1_MASTER_SLAVE == MSPI_SLAVE

		CLEAR_BIT( MSPI1 -> CR1 , 2 );

	#endif

	#if   MSPI1_DATA_ORDER == MSPI_MSB_FIRST

		CLEAR_BIT( MSPI1 -> CR1 , 7 );

	#elif MSPI1_DATA_ORDER == MSPI_LSB_FIRST

		SET_BIT( MSPI1 -> CR1 , 7 );

	#endif

	#if   MSPI1_SS_MANAGE  == HW_SLAVE_MANAGEMENT

		CLEAR_BIT( MSPI1 -> CR1 , 9 );

	#elif MSPI1_SS_MANAGEb == SW_SLAVE_MANAGEMENT

		SET_BIT( MSPI1 -> CR1 , 9 );

	#endif

	#if   MSPI1_DATA_SIZE == MSPI_8BIT_DATA

		CLEAR_BIT( MSPI1 -> CR1 , 11 );

	#elif MSPI1_DATA_SIZE == MSPI_DATA_16BITS

		SET_BIT( MSPI1 -> CR1 , 11 );

	#endif

	#if   MSPI1_INT_STATUS == MSPI_INT_DISABLE

		MSPI1 -> CR2 = 0 ;

	#elif MSPI1_INT_STATUS == MSPI_TXE_INT_ENABLE

		SET_BIT( MSPI1 -> CR2 , 7 );

	#elif MSPI1_INT_STATUS == MSPI_RXNE_INT_ENABLE

		SET_BIT( MSPI1 -> CR2 , 6 );

	#endif

	/*MSPI1 -> CR1 &= 0xFFC7 ;
	MSPI1 -> CR1 |= ( MSPI1_PRESCALLER << 3 ) ;

	SET_BIT( MSPI1 -> CR1 , 6 );*/

#elif MSP1_STATUS == MSPI_DISABLE
	CLEAR_BIT( MSPI1 -> CR1 , 6 );
#endif

}

u8 MSPI1_vSendData ( u8 Copy_u8Data ){

	MSPI1 -> DR = Copy_u8Data;

	while ( GET_BIT( MSPI1 -> SR , 7) == 1 );

	return ((u8) MSPI1 -> DR) ;

}

void MSPI1_vSetCallBack( void (*ptr) (void) ){
	if(NULL_POINTER != ptr)
	{
		MSPI1_CallBack = ptr;
	}

}

void SPI1_IRQHandler(void){

	if(NULL_POINTER != MSPI1_CallBack)
	{
		MSPI1_CallBack();
	}
	

}

