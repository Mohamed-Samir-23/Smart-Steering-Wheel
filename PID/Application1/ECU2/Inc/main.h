/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: EXTI					*/
/*  Layer		: MCAL					*/
/*  Version		: 1.0					*/
/*  Date		: November 14, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/



/*encoder prototype*/
void ECU2_voidUpdateTime(void);
void ECU2_ENCODER(MEXTI_Line_t ARG_udtEXTILine);

/*Motor prototype*/
void ECU2_voidMotorControlWithSoftStarters(u8 ARG_u8PWMValue , u8 ARG_u8DIR);
void ECU2_voidDelay(u32 ARG_u32Milliseconds);
u8 ECU2_u8Map(u16 x, u16 in_min, u16 in_max, u16 out_min, u16 out_max);

/*CAN prototype*/
void ECU2_voidNewMsg(void);
void ECU2_voidCanError(void);
s32 ECU2_s32StringToShort(const char *ARG_pccharStr);
void ECU2_voidReverseString(char *ARG_pcharStr, s32 ARG_s32Length);
void ECU2_voidshortToString(s16 ARG_s16Number, char *ARG_pcharResult);


#define ECU2_MSG_ID_PID_OFF					0x30

#define ECU2_MSG_ID_GET_SET_POINT			0x31

#define ECU2_MSG_ID_SEND_ENCODER_VALUE		0x32

#define ECU2_MSG_ID_FlASH					0x33
