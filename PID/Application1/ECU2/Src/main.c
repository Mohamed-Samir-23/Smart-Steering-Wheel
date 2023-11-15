/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: PID					*/
/*  Layer		: MCAL					*/
/*  Version		: 1.0					*/
/*  Date		: November 10, 2023		*/
/*  Last Edit	: November 14, 2023		*/
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
#include "main.h"
#include <math.h>
#include <stdlib.h>


u8 ECU2_u8counterdr0 ;

u8 ECU2_u8counterdr1;

s16 ECU2_s16Encodercounter =0;

u32 ECU2_u32CountOverFlow=0;

volatile s32 ECU2_u32CTPosition=0;

u64 ECU2_u32PVTime=0;

float ECU2_u32PVError=0;

float ECU2_u32CTError=0;

s16 ECU2_S16SetPoint=1000;

u8 TxData[8];

u8 RxData[8];

MCAN_TX_FRAME_S ECU2_udtPIDMsgFram;

MCAN_RX_FRAME_S ECU2_udtPIDResiveMsgFram;

u8 ECU2_u8PIDState=0 ;



void USB_LP_CAN_RX0_IRQHandler (void)
{
	MCAN_RX0_IRQHandler();
}


int main(void)
{
	MRCC_stderrorInit(HSE_Crystal,AHB_PreScaler1,APB_PreScaler1,APB_PreScaler1);
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

	s32 s32_LPVEncodercounter =0;

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
			NORMAL_MODE,
			1,
			Ts1_13,
			Ts2_2,
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
	ECU2_udtMsgsFilter.u32SET_FILTER_ID_HIGH=(ECU2_MSG_ID_PID_OFF)<<5;
	ECU2_udtMsgsFilter.u32SET_FILTER_ID_LOW=(ECU2_MSG_ID_GET_SET_POINT)<<5;
	ECU2_udtMsgsFilter.u32SET_FILTER_MASK_HIGH=(ECU2_MSG_ID_SEND_ENCODER_VALUE)<<5;
	ECU2_udtMsgsFilter.u32SET_FILTER_MASK_LOW=(ECU2_MSG_ID_FlASH)<<5;
	ECU2_udtMsgsFilter.udtSET_FILTER_MODE=FILTER_IDLIST;
	ECU2_udtMsgsFilter.udtSET_FILTER_SCALE=FILTER_SCALE_16BIT;

	MCAN_stderrorFilterInit(&ECU2_udtMsgsFilter);



	/*SetCallBack Function*/
	MCAN_stderrorSetCallBackFIFO0(ECU2_voidNewMsg);
	MCAN_stderrorSetCallBackFIFOError(ECU2_voidCanError);

	/*Can interrupt & NVIC enable*/
	MCAN_stderrorEnableInterrupt(FIFO0_MESSAGE_PENDING);
	MNVIC_stderrorEnableIRQ(USB_HP_CAN_RX0);

	/*Start can*/
	if(MCAN_stderrorCanStart()!=E_OK)
	{
		while(1)
		{
			/*ERROR INDECATION*/
			MGPIO_stderrorSetPinValueBSSR(GPIOA, PIN6, HIGH);
		}
	}


	while(1)
	{
		if(ECU2_u8PIDState==1)
		{
			/*PID*/
			float L_fKp=1.0;
			float L_fKd=0.0;
			float L_fKi=0.0;


			/*calculate current time*/
			u64 CTTime=((ECU2_u32CountOverFlow*16000000UL)+(MSYSTICK_voidElepsedTime()));
			double L_DuDeltaT = ((float)(CTTime-ECU2_u32PVTime))/(1000000);
			ECU2_u32PVTime=CTTime;
			MSYSTICK_stderrorSetSingleInterval(16000000UL, ECU2_voidUpdateTime);
			ECU2_u32CTPosition=0;

			/*take Encoder value*/
			ECU2_u32CTPosition=ECU2_s16Encodercounter;

			/*Proportional*/
			s32 Error = ECU2_u32CTPosition-ECU2_S16SetPoint;

			/*Derivative*/
			float L_fDeltaError;
			if(L_DuDeltaT ==0)
			{
				L_fDeltaError=0;
			}
			else
			{
				L_fDeltaError= (Error-ECU2_u32PVError)/L_DuDeltaT;
			}

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

			/*Tolerance*/
			u32 L_u32absError = abs (ECU2_S16SetPoint - ECU2_s16Encodercounter);

			if(L_u32absError<=2)
			{
				/*stop motor control*/
				ECU2_voidMotorControlWithSoftStarters(0 ,L_u8Direction_Motor);
			}
			else
			{
				/*motor control*/
				ECU2_voidMotorControlWithSoftStarters(((u8)L_fPWM) ,L_u8Direction_Motor);
			}

			if(s32_LPVEncodercounter ==ECU2_s16Encodercounter)
			{
				ECU2_voidMotorControlWithSoftStarters(0 ,L_u8Direction_Motor);
			}
			else
			{
				/*stop motor control*/
				s32_LPVEncodercounter = ECU2_s16Encodercounter;
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
			ECU2_s16Encodercounter++;/*right*/
		}
		else
		{
			ECU2_s16Encodercounter--;/*left*/
		}
	}
	else
	{
		/*Nothing*/

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
		ARG_u8PWMValue=ECU2_u8Map(ARG_u8PWMValue,0,100,15,30);

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
		case ECU2_MSG_ID_PID_OFF:
		{
			/*PID OFF*/
			ECU2_u8PIDState=0;
			break;
		}
		case ECU2_MSG_ID_GET_SET_POINT:
		{
			/*get Set Point*/
			ECU2_u8PIDState=1;
			ECU2_S16SetPoint =(u32)ECU2_s32StringToShort((const char *)RxData);
			break;
		}
		case ECU2_MSG_ID_SEND_ENCODER_VALUE:
		{
			/*Send Encoder value*/
			ECU2_udtPIDMsgFram.u32Msg_Id=0x40;
			ECU2_voidshortToString(ECU2_s16Encodercounter,(char *)TxData);
			MCAN_stderrorSend(&ECU2_udtPIDMsgFram);

			break;
		}
		case ECU2_MSG_ID_FlASH:
		{
			/*Flash*/
			break;
		}
	}
}


void ECU2_voidCanError(void)
{
	MGPIO_stderrorSetPinValueBSSR(GPIOA, PIN6, HIGH);
}



void ECU2_voidReverseString(char *ARG_pcharStr, s32 ARG_s32Length)
{
    s32 L_s32Start = 0;
    s32 L_s32End = ARG_s32Length - 1;
    while (L_s32Start < L_s32End)
    {
        /*Swap characters at start and end*/
        char L_charTemp = ARG_pcharStr[L_s32Start];
        ARG_pcharStr[L_s32Start] = ARG_pcharStr[L_s32End];
        ARG_pcharStr[L_s32End] = L_charTemp;

        /*Move towards the center*/
        L_s32Start++;
        L_s32End--;
    }
}


void ECU2_voidshortToString(s16 ARG_s16Number, char *ARG_pcharResult)
{
    s32 L_s32I = 0;
    s32 L_s32isNegative = 0;

    /*Handle negative numbers*/
    if (ARG_s16Number < 0)
    {
    	L_s32isNegative = 1;
        ARG_s16Number = -ARG_s16Number;
    }

    /*Handle special case when the number is 0*/
    if (ARG_s16Number == 0)
    {
    	ARG_pcharResult[L_s32I++] = '0';
    }

    /*Extract digits one by one*/
    while (ARG_s16Number != 0)
    {
        s32 L_digit = ARG_s16Number % 10;
        /* Convert digit to character*/
        ARG_pcharResult[L_s32I++] = '0' + L_digit;
        ARG_s16Number = ARG_s16Number / 10;
    }

    /*Add '-' for negative numbers*/
    if (L_s32isNegative)
    {
    	ARG_pcharResult[L_s32I++] = '-';
    }

    /*Null-terminate the string*/
    ARG_pcharResult[L_s32I] = '\0';

    /*Reverse the string to get the correct order*/
    ECU2_voidReverseString(ARG_pcharResult, L_s32I);
}



s32 ECU2_s32StringToShort(const char *ARG_pccharStr)
{
    s32 L_s32Result = 0;
    s32 L_s32isNegative = 0;
    s32 L_s32I = 0;

    /*Handle negative numbers*/
    if (ARG_pccharStr[0] == '-') {
    	L_s32isNegative = 1;
    	/*Start from the next character*/
    	L_s32I = 1;
    }

    /*Process each character in the string*/
    while (ARG_pccharStr[L_s32I] != '\0')
    {
        /*Convert character to digit*/
        s32 L_s32Digit = ARG_pccharStr[L_s32I] - '0';

        /*Update result based on the digit*/
        L_s32Result = L_s32Result * 10 + L_s32Digit;

        /*Move to the next character*/
        L_s32I++;
    }

    /*Apply the sign*/
    if (L_s32isNegative) {
    	L_s32Result = -L_s32Result;
    }

    return L_s32Result;
}







