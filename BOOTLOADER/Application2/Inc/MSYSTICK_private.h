/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: SYSTICK				*/
/*  Layer		: MCAL					*/
/*  Version		: 1.0					*/
/*  Date		: October 10, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/

#ifndef _MSYSTICK_PRIVATE_H_
#define _MSYSTICK_PRIVATE_H_


#define STK_BASE  0xE000E010 


#define STK_CTRL			*((uv32 *)(0x00 + STK_BASE))
#define STK_LOAD			*((uv32 *)(0x04 + STK_BASE))
#define STK_VAL				*((uv32 *)(0x08 + STK_BASE))
#define STK_CALIB     	    *((uv32 *)(0x0C + STK_BASE))

#define STK_CTRL_Flag 		7


#endif
