/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: GPIO					*/
/*  Layer		: MCAL					*/
/*  Version		: 1.0					*/
/*  Date		: October 09, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/

#ifndef _MGPIO_INTERFACE_H_
#define _MGPIO_INTERFACE_H_

typedef enum 
{
	GPIOA = 0,
	GPIOB = 1,
	GPIOC = 2,
	GPIOD = 3,
	GPIOE = 4,
	
}MGPIO_Port_Name_t;

typedef enum
{
	PIN0  = 0,
	PIN1  = 1,
	PIN2  = 2,
	PIN3  = 3,
	PIN4  = 4,
	PIN5  = 5,
	PIN6  = 6,
	PIN7  = 7,
	PIN8  = 8,
	PIN9  = 9,
	PIN10 = 10,
	PIN11 = 11,
	PIN12 = 12,
	PIN13 = 13,
	PIN14 = 14,
	PIN15 = 15,
	
}MGPIO_Pin_Number_t;


typedef enum 
{
	ANALOG 							= 0,

	INPUT_FLOAT 					= 4,
	INPUT_PULL_UP_DOWN 				= 8,
	
	OUTPUT_PUSH_PULL_SPEED_10MHZ 	= 1,
	OUTPUT_OPEN_DRAIN_SPEED_10MHZ 	= 5,
	OUTPUT_PUSH_PULL_SPEED_2MHZ 	= 2,
	OUTPUT_OPEN_DRAIN_SPEED_2MHZ 	= 6,
	OUTPUT_PUSH_PULL_SPEED_50MHZ 	= 3,
	OUTPUT_OPEN_DRAIN_SPEED_50MHZ 	= 7,
	
	ALTFUN_PUSH_PULL_SPEED_10MHZ 	= 9,
	ALTFUN_OPEN_DRAIN_SPEED_10MHZ 	= 13,
	ALTFUN_PUSH_PULL_SPEED_2MHZ 	= 10,
	ALTFUN_OPEN_DRAIN_SPEED_2MHZ 	= 14,
	ALTFUN_PUSH_PULL_SPEED_50MHZ 	= 11,
	ALTFUN_OPEN_DRAIN_SPEED_50MHZ 	= 15,

}MGPIO_Pin_Mode_t;


typedef enum
{
	LOW 	= 0,
	HIGH 	= 1,
	
}MGPIO_Output_State_t;



typedef enum 
{
	PULL_DOWN 	= 0,
	PULL_UP 	= 1,

}MGPIO_Pull_t;


STD_error_t MGPIO_stderrorPinModeSelect
(
	MGPIO_Port_Name_t ARG_udtGPIOPort, 
	MGPIO_Pin_Number_t ARG_udtGPIOPin,
	MGPIO_Pin_Mode_t ARG_udtGPIOMode
);

STD_error_t MGPIO_stderrorGetPinValue
(
	MGPIO_Port_Name_t ARG_udtGPIOPort, 
	MGPIO_Pin_Number_t ARG_udtGPIOPin, 
	u8* ARG_pu8Value
);

STD_error_t MGPIO_stderrorSetPinValue
(
	MGPIO_Port_Name_t ARG_udtGPIOPort, 
	MGPIO_Pin_Number_t ARG_udtGPIOPin, 
	MGPIO_Output_State_t ARG_udtValue
);

STD_error_t MGPIO_stderrorSetPinValueBSSR
(
	MGPIO_Port_Name_t ARG_udtGPIOPort, 
	MGPIO_Pin_Number_t ARG_udtGPIOPin, 
	MGPIO_Output_State_t ARG_udtValue
);


STD_error_t MGPIO_stderrorSetPinPull_Up_Down
(
	MGPIO_Port_Name_t ARG_udtGPIOPort, 
	MGPIO_Pin_Number_t ARG_udtGPIOPin, 
	MGPIO_Pull_t ARG_udtPullType
);


#endif
