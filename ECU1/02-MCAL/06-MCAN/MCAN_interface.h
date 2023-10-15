/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: CAN					*/
/*  Layer		: MCAL					*/
/*  Version		: 1.0					*/
/*  Date		: October 13, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/


#ifndef _MCAN_INTERFACE_H_
#define _MCAN_INTERFACE_H_


typedef enum 
{
	TIME_TRIGGERED_DISABLED=0,
	TIME_TRIGGERED_ENABLED=1,
}MCAN_Time_Triggered_Mode_t;

typedef enum 
{
	BUS_OFF_BY_SOFTWARE=0,
	BUS_OFF_BY_HARDWARE=1,

}MCAN_Bus_Off_Mode_t;


typedef enum 
{
	SLEEP_MODE_BY_SOFTWARE=0,
	SLEEP_MODE_BY_HARDWARE=1,

}MCAN_Wakeup_Mode_t;


typedef enum 
{
	RECEIVE_FIFO_OVERWRITE=0,
	RECEIVE_FIFO_DISCARDED=1,

}MCAN_Receive_FIFO_Locked_Mode_t;


typedef enum 
{
	PRIORITY_DRIVEN_BY_ID_MSG=0,
	PRIORITY_DRIVEN_BY_REQ=1,

}MCAN_Transmit_FIFO_Priority_t;



typedef enum 
{
	RETRANSMISSION_UNTIL_DONE=0,
	RETRANSMISSION_ONLY_ONCE=1,

}MCAN_Retransmission_Mode_t;


typedef enum 
{
	NORMAL_MODE=0,
	SILENT_MODE=2,
	LOOP_BACK_MODE=1,
	LOOP_BACK_SILENT_MODE=3,
	
}MCAN_Communication_Mode_t;


typedef enum 
{
	Ts1_1=0,
	Ts1_2,
	Ts1_3,
	Ts1_4,
	Ts1_5,
	Ts1_6,
	Ts1_7,
	Ts1_8,
	Ts1_9,
	Ts1_10,
	Ts1_11,
	Ts1_12,
	Ts1_13,
	Ts1_14,
	Ts1_15,
	Ts1_16,
	
}MCAN_Time_Seg1_t;


typedef enum 
{
	Ts2_1=0,
	Ts2_2,
	Ts2_3,
	Ts2_4,
	Ts2_5,
	Ts2_6,
	Ts2_7,
	Ts2_8,

}MCAN_Time_Seg2_t;


typedef enum 
{
	RJW_1=1,
	RJW_2,
	RJW_3,
	RJW_4,
	
}MCAN_Sync_Jump_Width_t;



typedef enum 
{
	NODE_SLEEP=0,
	NODE_INIT_READY=1,
	NODE_NORMAL_LISTENING=2,
	
}MCAN_State_t;


typedef enum 
{
	ID_STD=0,
	ID_Ext=4,
	
}MCAN_IDTYPE_t;

typedef enum 
{
	DATA_FRAME=0,
	REMOTE_FRAME=2,
	
}MCAN_RTR_t;

typedef enum 
{
	DLC0byte=0,
	DLC1byte,
	DLC2byte,
	DLC3byte,
	DLC4byte,
	DLC5byte,
	DLC6byte,
	DLC7byte,
	DLC8byte,
	
}MCAN_DLC_t;


typedef struct
{
	u32 u32Msg_Id;
	MCAN_IDTYPE_t udtID_Type;
	MCAN_RTR_t udtRTR_Type;
	MCAN_DLC_t udtDLC_Type;
	u8* pu8Payload;
	u8 u8TxMailbox;
	
}MCAN_TX_FRAME_S;


typedef enum 
{
	FILTER_DISABLED=0,
	FILTER_ENABLED=1,
}MCAN_Filter_Activation_State_t;

typedef enum 
{
	FILTER_BANK0=0,
	FILTER_BANK1,
	FILTER_BANK2,
	FILTER_BANK3,
	FILTER_BANK4,
	FILTER_BANK5,
	FILTER_BANK6,
	FILTER_BANK7,
	FILTER_BANK8,
	FILTER_BANK9,
	FILTER_BANK10,
	FILTER_BANK11,
	FILTER_BANK12,
	FILTER_BANK13,
	
}MCAN_Filter_Bank_t;


typedef enum 
{
	FILTER_FIFO0=0,
	FILTER_FIFO1,

}MCAN_Filter_FIFO_t;


typedef enum 
{
	FILTER_IDMASK=0,
	FILTER_IDLIST,

}MCAN_Filter_Mode_t;


typedef enum 
{
	FILTER_SCALE_16BIT=0,
	FILTER_SCALE_32BIT,

}MCAN_Filter_Scale_t;

typedef struct
{
	
	MCAN_Filter_Activation_State_t udtFILTER_ACTIVATION_STATE;
	MCAN_Filter_Bank_t udtSELECT_FILTER_BANK;
	MCAN_Filter_FIFO_t udtSET_FILTER_FIFO;
	u32 u32SET_FILTER_ID_HIGH;
	u32 u32SET_FILTER_ID_LOW;
	u32 u32SET_FILTER_MASK_HIGH;
	u32 u32SET_FILTER_MASK_LOW;
	MCAN_Filter_Mode_t udtSET_FILTER_MODE;
	MCAN_Filter_Scale_t udtSET_FILTER_SCALE;
	
}MCAN_Filter_Config_s;



typedef struct
{
	MCAN_Filter_FIFO_t udtSET_FILTER_FIFO;
	u32 u32Msg_Id;
	MCAN_IDTYPE_t udtID_Type;
	MCAN_RTR_t udtRTR_Type;
	MCAN_DLC_t udtDLC_Type;
	u32 u32FILTER_MATCH_INDEX;
	u8* pu8Payload;

}MCAN_RX_FRAME_S;



STD_error_t MCAN_stderrorInit
(
	MCAN_Time_Triggered_Mode_t ARG_udt_TimeTriggeredMode,
	MCAN_Bus_Off_Mode_t ARG_udtBusOffMode,
	MCAN_Wakeup_Mode_t ARG_udtWakeupMode,
	MCAN_Retransmission_Mode_t ARG_udtRetransmissionMode,
	MCAN_Receive_FIFO_Locked_Mode_t ARG_udtReceiveLockedMode,
	MCAN_Transmit_FIFO_Priority_t ARG_udtTransmitPriority,
	MCAN_Communication_Mode_t ARG_udtCommunicationMode,
	u32 ARG_u32Prescaler,
	MCAN_Time_Seg1_t ARG_udtTime_Seg1,
	MCAN_Time_Seg2_t ARG_udtTime_Seg2,
	MCAN_Sync_Jump_Width_t ARG_udtSyncJumpWidth
);


STD_error_t MCAN_stderrorCanStart
(
	void
);


STD_error_t MCAN_stderrorSend
(
	MCAN_TX_FRAME_S * ARG_pudtFrame
);


STD_error_t MCAN_stderrorIsSendMessagePending
(
	u8 ARG_u8MailBox,
	u8 * ARG_pu8State
);


STD_error_t MCAN_stderrorFilterInit
(
	MCAN_Filter_Config_s * ARG_pudtFilter
);


STD_error_t MCAN_stderrorReceive
(
	MCAN_RX_FRAME_S * ARG_pudtFrame
);



#endif
