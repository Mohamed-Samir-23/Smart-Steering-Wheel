/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: AFIO					*/
/*  Layer		: MCAL					*/
/*  Version		: 1.0					*/
/*  Date		: November 10, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/


/* Library Include */
#include "LSTD_types.h"

/* SWC Include */
#include "MAFIO_private.h"
#include "MAFIO_config.h"
#include "MAFIO_interface.h"

STD_error_t AFIO_VidSetEXTIConfiguration
( 
	MAFIO_Line_t ARG_udtAFIO_Line, 
	MAFIO_Port_Name_t ARG_udtPortMap 
)
{
	STD_error_t L_stderrorError=E_NOK;
	
	if((ARG_udtAFIO_Line<=15)&&(ARG_udtPortMap<=2))
	{
		u8 L_u8RegIndex = 0;

		if( ARG_udtAFIO_Line <= 3 )
		{
			L_u8RegIndex = 0 ;
		}
		else if( ARG_udtAFIO_Line <= 7 )
		{
			L_u8RegIndex   = 1 ;
			ARG_udtAFIO_Line -= 4 ;
		}
		else if( ARG_udtAFIO_Line <= 11 )
		{
			L_u8RegIndex   = 2 ;
			ARG_udtAFIO_Line -= 8 ;
		}
		else if( ARG_udtAFIO_Line <= 15 )
		{
			L_u8RegIndex   = 3 ;
			ARG_udtAFIO_Line -= 12 ;
		}

		AFIO->EXTICRx[L_u8RegIndex] &= ~ ( ( 0b1111 )    << ( ARG_udtAFIO_Line * 4 ));
		AFIO->EXTICRx[L_u8RegIndex] |= ( ARG_udtPortMap ) << ( ARG_udtAFIO_Line * 4 );
		
		L_stderrorError=E_OK;
	}
	else
	{
		L_stderrorError=E_NOK;
	}
	
	return L_stderrorError;
}
