/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: EXTI					*/
/*  Layer		: MCAL					*/
/*  Version		: 1.0					*/
/*  Date		: November 10, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/

/* Library Include */
#include "LSTD_types.h"
/* SWC Include */
#include "MRCC_interface.h"
#include "MGPIO_interface.h"
#include "MAFIO_interface.h"
#include "MSYSTICK_interface.h"
#include "MEXTI_interface.h"
#include "MNVIC_interface.h"
#include "HHBDG_interface.h"
#include "MCAN_interface.h"
#include <math.h>


u8 ECU2_u8counterdr0 ;

u8 ECU2_u8counterdr1;

s32 ECU2_s32Encodercounter =0;

void ECU2_voidUpdateTime(void);

void ECU2_ENCODER(MEXTI_Line_t ARG_udtEXTILine);

u32 ECU2_u32CountOverFlow=0;

void ECU2_voidMotorControlWithSoftStarters(u8 ARG_u8PWMValue , u8 ARG_u8DIR);

volatile s32 ECU2_u32CTPosition=0;

u64 ECU2_u32PVTime=0;

float ECU2_u32PVError=0;

float ECU2_u32CTError=0;

u32 ECU2_u32SetPoint=1000;

void ECU2_voidDelay(u32 ARG_u32Milliseconds);

u8 ECU2_u8Map(u16 x, u16 in_min, u16 in_max, u16 out_min, u16 out_max);

void ECU2_voidNewMsg(void);

u8 TxData[8];
u8 RxData[8];
MCAN_TX_FRAME_S ECU2_udtPIDMsgFram;
MCAN_RX_FRAME_S ECU2_udtPIDResiveMsgFram;

u8 ECU2_u8PIDState=0 ;


int main(void)
{
	MRCC_stderrorInit(HSI,AHB_PreScaler1,APB_PreScaler1,APB_PreScaler1);
	RCC_EnablePeripheralClk(APB2, GPIOA_PER);
	RCC_EnablePeripheralClk(APB2, AFIOEN_PER);
	RCC_EnablePeripheralClk(APB1, TIM2EN_PER);
	RCC_EnablePeripheralClk(APB1, PWREN_PER);
	RCC_EnablePeripheralClk(APB1, CAN1EN_PER);

	/*GPIO CONFIG*/
	MGPIO_stderrorPinModeSelect(GPIOA, PIN6, OUTPUT_PUSH_PULL_SPEED_10MHZ);
	MGPIO_stderrorSetPinValueBSSR(GPIOA, PIN6, LOW);

	/*enable Serial Debugger*/
	MGPIO_stderrorSerialWireJTAGConfiguration(JTAG_DISABLED_AND_SW_ENABLED);

	/*systick initialization */
	MSYSTICK_stderrorInit(AHB_DIV_8);

	/*H-bridge CONFIG*/
	HHBDG_voidInit();

	/*encoder CONFIG*/
	MGPIO_stderrorPinModeSelect(GPIOA, PIN2, INPUT_PULL_UP_DOWN);
	MGPIO_stderrorPinModeSelect(GPIOA, PIN3, INPUT_PULL_UP_DOWN);

	MGPIO_stderrorSetPinPull_Up_Down(GPIOA, PIN2,PULL_UP);
	MGPIO_stderrorSetPinPull_Up_Down(GPIOA, PIN3,PULL_UP);

	MNVIC_stderrorEnableIRQ(EXTI2);

	AFIO_VidSetEXTIConfiguration(AFIO_EXTI2,MAFIO_GPIOA);
	AFIO_VidSetEXTIConfiguration(AFIO_EXTI3,MAFIO_GPIOA);

	MEXTI_VoidSetCallBack(ECU2_ENCODER);

	MEXTI_stderrorTriggerMode(EXTI_LINE2,RISING_EDGE);
	MEXTI_stderrorTriggerMode(EXTI_LINE3,RISING_EDGE);

	MEXTI_VoidEnableEXTI(EXTI_LINE2);
	MEXTI_VoidEnableEXTI(EXTI_LINE3);

	/*CAN BUS CONFIG*/
	MGPIO_stderrorPinModeSelect(GPIOA, PIN11, INPUT_FLOAT);
	MGPIO_stderrorPinModeSelect(GPIOA, PIN12, ALTFUN_PUSH_PULL_SPEED_50MHZ);

	/*CAN CALCULATION*/
	MCAN_stderrorInit
	(
			TIME_TRIGGERED_DISABLED,
			BUS_OFF_BY_SOFTWARE,
			SLEEP_MODE_BY_SOFTWARE,
			RETRANSMISSION_UNTIL_DONE,
			RECEIVE_FIFO_OVERWRITE,
			PRIORITY_DRIVEN_BY_ID_MSG,
			LOOP_BACK_MODE,
			1,
			Ts1_6,
			Ts2_1,
			RJW_1
	);


	/*CAN TX FRAM*/
	ECU2_udtPIDMsgFram.udtDLC_Type=DLC8byte;
	ECU2_udtPIDMsgFram.udtID_Type=ID_STD;
	ECU2_udtPIDMsgFram.udtRTR_Type=DATA_FRAME;
	ECU2_udtPIDMsgFram.u32Msg_Id=0;
	ECU2_udtPIDMsgFram.pu8Payload=TxData;
	ECU2_udtPIDMsgFram.u8TxMailbox=10;

	/*CAN RX FRAM*/
	ECU2_udtPIDResiveMsgFram.udtSET_FILTER_FIFO=FILTER_FIFO0;
	ECU2_udtPIDResiveMsgFram.udtID_Type=ID_STD;
	ECU2_udtPIDResiveMsgFram.pu8Payload=RxData;


	/*filter one*/
	MCAN_Filter_Config_s ECU2_udtMsgsFilter;
	ECU2_udtMsgsFilter.udtFILTER_ACTIVATION_STATE=FILTER_ENABLED;
	ECU2_udtMsgsFilter.udtSELECT_FILTER_BANK=FILTER_BANK0;
	ECU2_udtMsgsFilter.udtSET_FILTER_FIFO=FILTER_FIFO0;
	ECU2_udtMsgsFilter.u32SET_FILTER_ID_HIGH=(0x30)<<5;
	ECU2_udtMsgsFilter.u32SET_FILTER_ID_LOW=(0x31)<<5;
	ECU2_udtMsgsFilter.u32SET_FILTER_MASK_HIGH=(0x32)<<5;
	ECU2_udtMsgsFilter.u32SET_FILTER_MASK_LOW=(0x33)<<5;
	ECU2_udtMsgsFilter.udtSET_FILTER_MODE=FILTER_IDLIST;
	ECU2_udtMsgsFilter.udtSET_FILTER_SCALE=FILTER_SCALE_16BIT;

	MCAN_stderrorFilterInit(&ECU2_udtMsgsFilter);

	MCAN_stderrorSetCallBackFIFO0(ECU2_voidNewMsg);

	/*Start can*/
	if(MCAN_stderrorCanStart()!=E_OK)
	{
		while(1)
		{
			/*ERROR INDECATION*/
			MGPIO_stderrorSetPinValueBSSR(GPIOA, PIN6, HIGH);
		}
	}

	MCAN_stderrorEnableInterrupt(FIFO0_MESSAGE_PENDING);



	while(1)
	{
		if(ECU2_u8PIDState==1)
		{
			/*PID*/
			float L_fKp=1.0;
			float L_fKd=0.0;
			float L_fKi=0.0;

			MSYSTICK_stderrorSetSingleInterval(16000000UL, ECU2_voidUpdateTime);
			/*calculate current time*/
			u64 CTTime=((ECU2_u32CountOverFlow*16000000UL)+(MSYSTICK_voidElepsedTime()));
			double L_DuDeltaT = ((float)(CTTime-ECU2_u32PVTime))/(1000000);
			ECU2_u32PVTime=CTTime;

			ECU2_u32CTPosition=0;

			/*take Encoder value*/
			MNVIC_stderrorDisableIRQ(EXTI_LINE2);
			ECU2_u32CTPosition=ECU2_s32Encodercounter;
			MEXTI_VoidEnableEXTI(EXTI_LINE2);


			/*Proportional*/
			s32 Error = ECU2_u32CTPosition-ECU2_u32SetPoint;

			/*Derivative*/
			float L_fDeltaError = (Error-ECU2_u32PVError)/L_DuDeltaT;

			/*Integral*/
			ECU2_u32CTError+=Error*L_DuDeltaT;

			/*PID Equation*/
			float System_Control_signal = (L_fKp*Error)+(L_fKd*L_fDeltaError)+(L_fKi*ECU2_u32CTError);

			ECU2_u32PVError=Error;

			float L_fPWM=System_Control_signal;

			L_fPWM=fabs(L_fPWM);

			if(L_fPWM>100)
			{
				L_fPWM=100;
			}

			u8 L_u8Direction_Motor=1;

			if(System_Control_signal<0)
			{
				L_u8Direction_Motor=0;
			}
			else
			{

			}

			if(fabs(ECU2_u32SetPoint-ECU2_s32Encodercounter)<=1)
			{
				/*stop motor control*/
				ECU2_voidMotorControlWithSoftStarters(0 ,L_u8Direction_Motor);
			}
			else
			{
				/*motor control*/
				ECU2_voidMotorControlWithSoftStarters(((u8)L_fPWM) ,L_u8Direction_Motor);
			}
		}
		else
		{
			/*stop motor control*/
			ECU2_voidMotorControlWithSoftStarters(0 ,0);
		}
	}


}


void ECU2_ENCODER(MEXTI_Line_t ARG_udtEXTILine)
{

	if(ARG_udtEXTILine ==EXTI_LINE2)
	{

		u8 L_u8A=LOW;

		MGPIO_stderrorGetPinValue(GPIOA, PIN3,&L_u8A);

		if(L_u8A==LOW)
		{
			ECU2_s32Encodercounter++;//right
		}
		else
		{
			ECU2_s32Encodercounter--;//left
		}
	}
	else
	{


	}
}


void ECU2_voidUpdateTime(void)
{
	ECU2_u32CountOverFlow++;
}


void ECU2_voidMotorControlWithSoftStarters(u8 ARG_u8PWMValue , u8 ARG_u8DIR)
{
	if(ARG_u8PWMValue !=0)
	{
		ARG_u8PWMValue=ECU2_u8Map(ARG_u8PWMValue,0,100,15,40);

		if(ARG_u8DIR ==0)
		{
			ECU2_u8counterdr0 =0;

			for(ECU2_u8counterdr0 =15;ECU2_u8counterdr0<=ARG_u8PWMValue;ECU2_u8counterdr0+=1)
			{
				HHBDG_stderrorPWMGeneration(8,1,5000,ECU2_u8counterdr0,0);
				ECU2_voidDelay(10);
			}
		}
		else if(ARG_u8DIR ==1)
		{
			ECU2_u8counterdr1 =0;
			for(ECU2_u8counterdr1 =15;ECU2_u8counterdr1<=ARG_u8PWMValue;ECU2_u8counterdr1+=1)
			{
				HHBDG_stderrorPWMGeneration(8,1,5000,0,ECU2_u8counterdr1);
				ECU2_voidDelay(10);
			}
		}
	}
	else
	{
		HHBDG_stderrorPWMGeneration(8,1,5000,0,0);
	}
}


void ECU2_voidDelay(u32 ARG_u32Milliseconds)
{
    u32 L_u8counter;
    u32 L_u32loopCount = (ARG_u32Milliseconds * 8000)/10;

    for (L_u8counter = 0; L_u8counter < L_u32loopCount; ++L_u8counter)
    {
        asm("NOP");
    }
}


u8 ECU2_u8Map(u16 x, u16 in_min, u16 in_max, u16 out_min, u16 out_max)
{
  return (u8)((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

void ECU2_voidNewMsg(void)
{

	if(MCAN_stderrorReceive(&ECU2_udtPIDResiveMsgFram)!=E_OK)
	{
		while(1)
		{
			/*ERROR INDECATION*/
			MGPIO_stderrorSetPinValueBSSR(GPIOA, PIN6, HIGH);
		}
	}
	else
	{
		/*Nothing*/
	}


	switch(ECU2_udtPIDResiveMsgFram.u32Msg_Id)
	{
		case 0x30:
		{
			/*PID state*/
			ECU2_u8PIDState^=1;
			break;
		}
		case 0x31:
		{
			/*get Set Point*/
			if(ECU2_udtPIDResiveMsgFram.pu8Payload[2]=='-')
			{
				ECU2_u32SetPoint =(u32)(ECU2_udtPIDResiveMsgFram.pu8Payload[1]|(ECU2_udtPIDResiveMsgFram.pu8Payload[0]<<8))*-1;
			}
			else
			{
				ECU2_u32SetPoint =(u32)(ECU2_udtPIDResiveMsgFram.pu8Payload[1]|(ECU2_udtPIDResiveMsgFram.pu8Payload[0]<<8));
			}
			break;
		}
		case 0x32:
		{
			/*Send Encoder value*/
			ECU2_udtPIDMsgFram.u32Msg_Id=0x40;
			TxData[0]=(u8)((ECU2_s32Encodercounter>>8)&0xFF);
			TxData[1]=(u8)((ECU2_s32Encodercounter)&0xFF);
			if(ECU2_s32Encodercounter>0)
			{
				TxData[2]='+';
			}
			else
			{
				TxData[2]='-';
			}
			MCAN_stderrorSend(&ECU2_udtPIDMsgFram);
			break;
		}
		case 0x33:
		{
			/*Flash*/
			break;
		}
	}
}
