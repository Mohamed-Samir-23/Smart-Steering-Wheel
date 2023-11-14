/* Library Include */
#include "LSTD_types.h"

/* SWC Include */
#include "MRCC_interface.h"
#include "MGPIO_interface.h"
#include "MNVIC_interface.h"
#include "MCAN_interface.h"
#include "MSYSTICK_interface.h"

#define ECU2	2

#define ECU3	3

#define Selector ECU3

u32 L_u32I=0;


u8 TxData[8] = {0 , 0 , 0 , 0, 0 , 0 , 0, 0};
u8 RxData[8];

u8 L_u8blink=0;


void led_blink(void);
void can_Receive(void);

void error_can(void);


#if Selector ==	ECU2

MCAN_TX_FRAME_S ECU2_udtTX_MsgFram;
MCAN_RX_FRAME_S ECU2_udtResivemasg;

#else

MCAN_TX_FRAME_S ECU3_udtTX_MsgFram;
MCAN_RX_FRAME_S ECU3_udtResivemasg;

#endif





void USB_LP_CAN_RX0_IRQHandler (void)
{
	MCAN_RX0_IRQHandler();
}

int main(void)
{
	/*RCC CONFIG*/
	MRCC_stderrorInit(HSE_Crystal,AHB_PreScaler1,APB_PreScaler1,APB_PreScaler1);
	RCC_EnablePeripheralClk(APB2, GPIOA_PER);
	RCC_EnablePeripheralClk(APB2, AFIOEN_PER);
	RCC_EnablePeripheralClk(APB1, PWREN_PER);
	RCC_EnablePeripheralClk(APB1, CAN1EN_PER);

	/*Debugger*/
	MGPIO_stderrorSerialWireJTAGConfiguration(JTAG_DISABLED_AND_SW_ENABLED);

	/*CAN CONFIG*/
	MGPIO_stderrorPinModeSelect(GPIOA, PIN11, INPUT_FLOAT);
	MGPIO_stderrorPinModeSelect(GPIOA, PIN12, ALTFUN_PUSH_PULL_SPEED_50MHZ);

	/*Gpio pin*/
	MGPIO_stderrorPinModeSelect(GPIOA, PIN3, OUTPUT_PUSH_PULL_SPEED_10MHZ);

	MCAN_stderrorInit
	(
			TIME_TRIGGERED_DISABLED,
			BUS_OFF_BY_SOFTWARE,
			SLEEP_MODE_BY_SOFTWARE,
			RETRANSMISSION_UNTIL_DONE,
			RECEIVE_FIFO_OVERWRITE,
			PRIORITY_DRIVEN_BY_ID_MSG,
			NORMAL_MODE,
			1,
			Ts1_13,
			Ts2_2,
			RJW_1
	);

	MSYSTICK_stderrorInit(AHB_DIV_8);

#if Selector ==	ECU2

	/*filter one ECU2*/
	MCAN_Filter_Config_s ECU2_udtMsgFilter;
	ECU2_udtMsgFilter.udtFILTER_ACTIVATION_STATE=FILTER_ENABLED;
	ECU2_udtMsgFilter.udtSELECT_FILTER_BANK=FILTER_BANK0;
	ECU2_udtMsgFilter.udtSET_FILTER_FIFO=FILTER_FIFO0;
	ECU2_udtMsgFilter.u32SET_FILTER_ID_HIGH=(0x30)<<5;
	ECU2_udtMsgFilter.u32SET_FILTER_ID_LOW=(0x31)<<5;
	ECU2_udtMsgFilter.u32SET_FILTER_MASK_HIGH=(0x32)<<5;
	ECU2_udtMsgFilter.u32SET_FILTER_MASK_LOW=(0x33)<<5;
	ECU2_udtMsgFilter.udtSET_FILTER_MODE=FILTER_IDLIST;
	ECU2_udtMsgFilter.udtSET_FILTER_SCALE=FILTER_SCALE_16BIT;

	MCAN_stderrorFilterInit(&ECU2_udtMsgFilter);



#else

	/*filter one ECU3*/
	MCAN_Filter_Config_s ECU3_udtMsgFilter;
	ECU3_udtMsgFilter.udtFILTER_ACTIVATION_STATE=FILTER_ENABLED;
	ECU3_udtMsgFilter.udtSELECT_FILTER_BANK=FILTER_BANK0;
	ECU3_udtMsgFilter.udtSET_FILTER_FIFO=FILTER_FIFO0;
	ECU3_udtMsgFilter.u32SET_FILTER_ID_HIGH=(0x40)<<5;
	ECU3_udtMsgFilter.u32SET_FILTER_ID_LOW=(0x41)<<5;
	ECU3_udtMsgFilter.u32SET_FILTER_MASK_HIGH=(0x42)<<5;
	ECU3_udtMsgFilter.u32SET_FILTER_MASK_LOW=(0x43)<<5;
	ECU3_udtMsgFilter.udtSET_FILTER_MODE=FILTER_IDLIST;
	ECU3_udtMsgFilter.udtSET_FILTER_SCALE=FILTER_SCALE_16BIT;

	MCAN_stderrorFilterInit(&ECU3_udtMsgFilter);
#endif



#if Selector ==	ECU2

	/*ESU 2 send */
	ECU2_udtTX_MsgFram.udtDLC_Type=DLC8byte;
	ECU2_udtTX_MsgFram.udtID_Type=ID_STD;
	ECU2_udtTX_MsgFram.udtRTR_Type=DATA_FRAME;
	ECU2_udtTX_MsgFram.u32Msg_Id=0x40;//0x3AB
	ECU2_udtTX_MsgFram.pu8Payload=TxData;
	ECU2_udtTX_MsgFram.u8TxMailbox=10;
	ECU2_udtResivemasg.udtSET_FILTER_FIFO=FILTER_FIFO0;
	ECU2_udtResivemasg.udtID_Type=ID_STD;
	ECU2_udtResivemasg.pu8Payload=RxData;


#else
	/*ESU 3 send */
	ECU3_udtTX_MsgFram.udtDLC_Type=DLC8byte;
	ECU3_udtTX_MsgFram.udtID_Type=ID_STD;
	ECU3_udtTX_MsgFram.udtRTR_Type=DATA_FRAME;
	ECU3_udtTX_MsgFram.u32Msg_Id=0x30;
	ECU3_udtTX_MsgFram.pu8Payload=TxData;
	ECU3_udtTX_MsgFram.u8TxMailbox=10;

	ECU3_udtResivemasg.udtSET_FILTER_FIFO=FILTER_FIFO0;
	ECU3_udtResivemasg.udtID_Type=ID_STD;
	ECU3_udtResivemasg.pu8Payload=RxData;

#endif


	MCAN_stderrorSetCallBackFIFO0(can_Receive);
	MCAN_stderrorSetCallBackFIFOError(error_can);

	/*can interrupt & NVIC enable*/
	MCAN_stderrorEnableInterrupt(FIFO0_MESSAGE_PENDING);
	MNVIC_stderrorEnableIRQ(USB_HP_CAN_RX0);



	/*start can*/
	if(MCAN_stderrorCanStart()!=E_OK)
	{
		while(1)
		{


		}
	}





	while(1)
	{
		#if Selector ==	ECU2

		MCAN_stderrorSend(&ECU2_udtTX_MsgFram);
		//MSYSTICK_Delay_Ms(1000000);

		#else

		MCAN_stderrorSend(&ECU3_udtTX_MsgFram);
		MSYSTICK_Delay_Ms(500);

		#endif


	}
}


void led_blink(void)
{
	if(L_u32I ==100)
	{
		if(L_u8blink==0)
		{
			MGPIO_stderrorSetPinValueBSSR(GPIOA, PIN3, HIGH);
			L_u8blink=1;
		}
		else
		{
			MGPIO_stderrorSetPinValueBSSR(GPIOA, PIN3, LOW);
			L_u8blink=0;
		}
		L_u32I=0;
	}
	else
	{
		L_u32I++;
	}
}


void can_Receive(void)
{

#if Selector ==	ECU2

	MCAN_stderrorReceive(&ECU2_udtResivemasg);

	switch(ECU2_udtResivemasg.u32Msg_Id)
	{
		case 0x30:
		{
			led_blink();
			break;
		}
		case 0x31:
		{
			/*get Set Point*/
			break;
		}
		case 0x32:
		{
			/*Send Encoder value*/
			break;
		}
		case 0x33:
		{
			/*Flash*/
			break;
		}

	}

#else

	MCAN_stderrorReceive(&ECU3_udtResivemasg);

	switch(ECU3_udtResivemasg.u32Msg_Id)
	{
		case 0x40:
		{
			led_blink();
			break;
		}
		case 0x41:
		{
			/*get Set Point*/
			break;
		}
		case 0x42:
		{
			/*Send Encoder value*/
			break;
		}
		case 0x43:
		{
			/*Flash*/
			break;
		}
	}

#endif

}

void error_can(void)
{

}


