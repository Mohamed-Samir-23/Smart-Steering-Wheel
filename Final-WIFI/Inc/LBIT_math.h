/************************************/
/*	Author	  :	Omar Morsy			*/
/*	SWC		  : Bit Math			*/
/*  Layer	  : LIB					*/
/*	Version	  :	1.0		  			*/
/*	Date	  :	August 2, 2023		*/
/*	Last Edit :	N/A					*/
/************************************/

#ifndef _LBIT_MATH_H_
#define _LBIT_MATH_H_

#define 	SET_BIT(reg, bit)		reg |= (1<<bit)
#define 	CLEAR_BIT(reg, bit)		reg &= ~(1<<bit)
#define		TOGGLE_BIT(reg, bit)	reg ^= (1<<bit)
#define 	GET_BIT(reg, bit)		((reg>>bit) & 1)

#endif
