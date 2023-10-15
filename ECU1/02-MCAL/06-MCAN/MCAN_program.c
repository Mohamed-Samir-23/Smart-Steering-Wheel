/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: CAN					*/
/*  Layer		: MCAL					*/
/*  Version		: 1.0					*/
/*  Date		: October 13, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/

/* Library Include */
#include "LSTD_types.h"
/* SWC Include */
#include "MCAN_config.h"
#include "MCAN_private.h"
#include "MCAN_interface.h"



volatile MCAN_State_t MCAN_udtState=NODE_SLEEP;


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
)
{
	STD_error_t L_stderrorError=E_NOK;
	if
	(
		(ARG_udt_TimeTriggeredMode<=1)&&
		(ARG_udtBusOffMode<=1)&&
		(ARG_udtWakeupMode<=1)&&
		(ARG_udtReceiveLockedMode<=1)&&
		(ARG_udtTransmitPriority<=1)&&
		(ARG_udtRetransmissionMode<=1)&&
		(ARG_udtCommunicationMode<=3)&&
		(ARG_u32Prescaler<=1024)&&
		(ARG_udtTime_Seg1<=16)&&
		(ARG_udtTime_Seg1!=0)&&
		(ARG_udtTime_Seg2<=8)&&
		(ARG_udtTime_Seg2!=0)&&
		(ARG_udtSyncJumpWidth<=4)&&
		(ARG_udtSyncJumpWidth!=0)
	)
	{
		/*Initialization request*/
		CAN_MCR |=(1<<INRQ);
		/*Initialization acknowledge*/
		while((1&(CAN_MSR>>INAK))==0);
		/*Sleep mode request exit*/
		CAN_MCR &=~(1<<SLEEP);
		/*Initialization acknowledge*/
		while((1&(CAN_MSR>>SLAK))!=0);
		/*Time triggered communication mode config*/
		CAN_MCR &=~(1<<TTCM);
		CAN_MCR |=(ARG_udt_TimeTriggeredMode<<TTCM);
		/*bus-off management config*/
		CAN_MCR &=~(1<<ABOM);
		CAN_MCR |=(ARG_udtBusOffMode<<ABOM);
		/*wakeup mode config*/
		CAN_MCR &=~(1<<AWUM);
		CAN_MCR |=(ARG_udtWakeupMode<<AWUM);
		/*retransmission mode config*/
		CAN_MCR &=~(1<<NART);
		CAN_MCR |=(ARG_udtRetransmissionMode<<NART);
		/*Receive FIFO locked mode*/
		CAN_MCR &=~(1<<RFLM);
		CAN_MCR |=(ARG_udtReceiveLockedMode<<RFLM);
		/*Transmit FIFO priority mode*/
		CAN_MCR &=~(1<<TXFP);
		CAN_MCR |=(ARG_udtTransmitPriority<<TXFP);
		/*Communication Mode*/
		CAN_BTR &=~(3<<LBKM);
		CAN_BTR |=(ARG_udtCommunicationMode<<LBKM);
		/*Communication Mode 
		 *SyncJumpWidth
		 *Time Seg1
		 *Time Seg2
		 *Prescaler
		*/
		CAN_BTR =0x00;
		CAN_BTR |=(	(ARG_udtCommunicationMode<<LBKM)|
					(ARG_udtSyncJumpWidth<<SJW)|
					(ARG_udtTime_Seg1<<TS1)|
					(ARG_udtTime_Seg2<<TS2)|
					((ARG_u32Prescaler-1)<<BRP));
	
		MCAN_udtState=NODE_INIT_READY;
		L_stderrorError=E_OK;
	}
	else
	{
		L_stderrorError=E_NOK;
	}
	return L_stderrorError;
}



STD_error_t MCAN_stderrorCanStart
(
	void
)
{
	STD_error_t L_stderrorError=E_NOK;
	
	u16 L_u16TimeoutCounter =0;
	
	if(MCAN_udtState==NODE_INIT_READY)
	{
		/*Request to be Normal Mode*/
		CAN_MCR &=~(1<<INRQ);
		/*Normal Mode acknowledge*/
		while(((1&(CAN_MSR>>INAK))!=0)&&(L_u16TimeoutCounter<MCAN_START_TIMEOUT))
		{
			L_u16TimeoutCounter++;
		}
		if(L_u16TimeoutCounter==MCAN_START_TIMEOUT)
		{
			
			L_stderrorError=E_TIME_OUT;
			
		}
		else
		{
			L_stderrorError=E_OK;
		}
	}
	else
	{
		L_stderrorError=E_NOK;
	}
	return L_stderrorError;
}


static u8 MCAN_u8EmptyMailboxNumber
(
	void
)
{
	u8 L_u8freemailbox=0;
	
	if((1&(CAN_TSR>>TME0))!=0)
	{
		L_u8freemailbox++;
	}
	else
	{
		
	}
	
	if((1&(CAN_TSR>>TME1))!=0)
	{
		L_u8freemailbox++;
	}
	else
	{
		
	}
	
	if((1&(CAN_TSR>>TME2))!=0)
	{
		L_u8freemailbox++;
	}
	else
	{
		
	}
	
	return L_u8freemailbox;
}

static u8 MCAN_u8ReadyMailBox
(
	void
)
{
	return (3&(CAN_TSR>>MAILBOX_CODE));
}


STD_error_t MCAN_stderrorSend
(
	MCAN_TX_FRAME_S * ARG_pudtFrame
)
{
	STD_error_t L_stderrorError=E_NOK;
	
	if(ARG_pudtFrame != NULL_POINTER)
	{
		u8 L_u8FreeTxMailboxesNumber=0;
		u8 L_u8TransmitMailbox=0;
		
		if(MCAN_udtState==NODE_INIT_READY||MCAN_udtState==NODE_NORMAL_LISTENING)
		{
			
			L_u8FreeTxMailboxesNumber=MCAN_u8EmptyMailboxNumber();
			
			if(L_u8FreeTxMailboxesNumber>0)
			{
				
				
				if
				(
					((ARG_pudtFrame->udtID_Type==0)||(ARG_pudtFrame->udtID_Type==4))&&
					((ARG_pudtFrame->udtRTR_Type==0)||(ARG_pudtFrame->udtRTR_Type==2))&&
					(ARG_pudtFrame->udtDLC_Type<=8)
				)
				{
					L_u8TransmitMailbox=MCAN_u8ReadyMailBox();
					ARG_pudtFrame->u8TxMailbox=(u8)1<<L_u8TransmitMailbox;
					
					/*Fram Config MSG ID ,RTR and IDE */
					if(ARG_pudtFrame->udtID_Type==ID_STD)
					{
						CAN_MailBox[L_u8TransmitMailbox].TIR=(ARG_pudtFrame->u32Msg_Id<<21)|(ARG_pudtFrame->udtRTR_Type);
					}
					else
					{
						CAN_MailBox[L_u8TransmitMailbox].TIR=(ARG_pudtFrame->u32Msg_Id<<3)|(ARG_pudtFrame->udtRTR_Type)|(ARG_pudtFrame->udtID_Type);
					}
					
					/*Fram Config DLC*/
					CAN_MailBox[L_u8TransmitMailbox].TDTR=ARG_pudtFrame->udtDLC_Type;
					/*write data in mailbox reg*/
					CAN_MailBox[L_u8TransmitMailbox].TDHR=	(ARG_pudtFrame->pu8Payload[7]<<24)|
															(ARG_pudtFrame->pu8Payload[6]<<16)|
															(ARG_pudtFrame->pu8Payload[5]<<8) |
															(ARG_pudtFrame->pu8Payload[4]<<0) ;
															
					CAN_MailBox[L_u8TransmitMailbox].TDLR=	(ARG_pudtFrame->pu8Payload[3]<<24)|
															(ARG_pudtFrame->pu8Payload[2]<<16)|
															(ARG_pudtFrame->pu8Payload[1]<<8) |
															(ARG_pudtFrame->pu8Payload[0]<<0) ;
					/*Request Transmission*/
					CAN_MailBox[L_u8TransmitMailbox].TIR|=TXRQ;
					
					L_stderrorError=E_OK;
				}
				else
				{
					L_stderrorError=E_NOK;
				}
				
			}
			else
			{
				L_stderrorError=E_NOK;
			}
			
		}
		else
		{
			L_stderrorError=E_NOK;
		}
	}
	else
	{
		L_stderrorError=E_NULL_POINTER;
	}
	return L_stderrorError;
}


STD_error_t MCAN_stderrorIsSendMessagePending
(
	u8 ARG_u8MailBox,
	u8 * ARG_pu8State
)
{
	
	STD_error_t L_stderrorError=E_NOK;
	
	if(ARG_pu8State != NULL_POINTER)
	{
		
		if(MCAN_udtState==NODE_INIT_READY||MCAN_udtState==NODE_NORMAL_LISTENING)
		{
			*ARG_pu8State=0;
			
			if ((CAN_TSR & (ARG_u8MailBox << 26)) != (ARG_u8MailBox << 26))
			{
				*ARG_pu8State=1;
			}
			else
			{
				
			}
			L_stderrorError=E_OK;
		}
		else
		{
			L_stderrorError=E_NOK;
		}
	}
	else
	{
		L_stderrorError=E_NULL_POINTER;
	}

	return L_stderrorError;
}


STD_error_t MCAN_stderrorFilterInit
(
	MCAN_Filter_Config_s * ARG_pudtFilter
)
{
	
	STD_error_t L_stderrorError=E_NOK;
	
	if(ARG_pudtFilter != NULL_POINTER)
	{
		if(MCAN_udtState==NODE_INIT_READY||MCAN_udtState==NODE_NORMAL_LISTENING)
		{
			if
			(
				(ARG_pudtFilter->udtFILTER_ACTIVATION_STATE<=1)&&
				(ARG_pudtFilter->udtSELECT_FILTER_BANK<=13)&&
				(ARG_pudtFilter->udtSET_FILTER_FIFO<=1)&&
				(ARG_pudtFilter->udtSET_FILTER_MODE<=1)&&
				(ARG_pudtFilter->udtSET_FILTER_SCALE<=1)
			)
			{
				/*enter initialisation Filter Mode*/
				CAN_FMR|=(1<<FINIT);
				
				/*Deactivation Filter*/
				CAN_FA1R&=(~(1<<ARG_pudtFilter->udtSELECT_FILTER_BANK));
				
				/*set scale mode 16bit or 32bit*/
				CAN_FS1R&=(~(1<<ARG_pudtFilter->udtSELECT_FILTER_BANK));
				CAN_FS1R|=(ARG_pudtFilter->udtSET_FILTER_SCALE<<ARG_pudtFilter->udtSELECT_FILTER_BANK);
				
				/*set id and mask*/
				CAN_FILTER[ARG_pudtFilter->udtSELECT_FILTER_BANK].FR1=	((0xFFFFU & (u32)ARG_pudtFilter->u32SET_FILTER_MASK_LOW) << 16U) |
																		(0xFFFFU & (u32)ARG_pudtFilter->u32SET_FILTER_ID_LOW);
																		
				CAN_FILTER[ARG_pudtFilter->udtSELECT_FILTER_BANK].FR2=	((0xFFFFU & (u32)ARG_pudtFilter->u32SET_FILTER_MASK_HIGH) << 16U) |
																		(0xFFFFU & (u32)ARG_pudtFilter->u32SET_FILTER_MASK_LOW);
				
				
				/*set mask mode or list mode*/
				CAN_FM1R&=(~(1<<ARG_pudtFilter->udtSELECT_FILTER_BANK));
				CAN_FM1R|=(ARG_pudtFilter->udtSET_FILTER_MODE<<ARG_pudtFilter->udtSELECT_FILTER_BANK);
				
				/*set Filter FIFO*/
				CAN_FFA1R&=(~(1<<ARG_pudtFilter->udtSELECT_FILTER_BANK));
				CAN_FFA1R|=(ARG_pudtFilter->udtSET_FILTER_FIFO<<ARG_pudtFilter->udtSELECT_FILTER_BANK);
				
				/*set Activation State*/
				CAN_FA1R&=(~(1<<ARG_pudtFilter->udtSELECT_FILTER_BANK));
				CAN_FA1R|=(ARG_pudtFilter->udtFILTER_ACTIVATION_STATE<<ARG_pudtFilter->udtSELECT_FILTER_BANK);
				
				/*exit initialisation Filter Mode*/
				CAN_FMR&=(~(1<<FINIT));
				
				
				L_stderrorError=E_OK;
			}
			else
			{
				L_stderrorError=E_NOK;
			}
			
			
		}
		else
		{
			L_stderrorError=E_NOK;
		}
		
		
		
	}
	else
	{
		L_stderrorError=E_NULL_POINTER;
	}
	
	return L_stderrorError;
}


static u8 MCAN_u8FIFOMailboxNumber
(
	u8 ARG_u8FIFOINDEX
)	
{
	u8 L_u8FIFOMailboxNumber=0;
	
	if(MCAN_udtState==NODE_INIT_READY||MCAN_udtState==NODE_NORMAL_LISTENING)
	{
		
		if(ARG_u8FIFOINDEX == 0)
		{
			L_u8FIFOMailboxNumber = CAN_RF0R & 3U;
		}
		else if(ARG_u8FIFOINDEX == 1)
		{
			L_u8FIFOMailboxNumber = CAN_RF1R & 3U;
		}
		else
		{
	
		}
	}
	else
	{
		
		
	}
	
	return L_u8FIFOMailboxNumber;
}


STD_error_t MCAN_stderrorReceive
(
	MCAN_RX_FRAME_S * ARG_pudtFrame
)
{
	
	STD_error_t L_stderrorError=E_NOK;
	
	if(ARG_pudtFrame !=NULL_POINTER)
	{
		if(MCAN_udtState==NODE_INIT_READY||MCAN_udtState==NODE_NORMAL_LISTENING)
		{
			if(MCAN_u8FIFOMailboxNumber(ARG_pudtFrame->udtSET_FILTER_FIFO)!=0)
			{
				/*GET IDE*/
				ARG_pudtFrame->udtID_Type=(1&((CAN_FIFO_MailBox[ARG_pudtFrame->udtSET_FILTER_FIFO].RIR)>>2));
				
				/*GET MSG ID*/
				if(ARG_pudtFrame->udtID_Type ==ID_STD)
				{
					ARG_pudtFrame->u32Msg_Id=((STIDMSG_FLAG)&((CAN_FIFO_MailBox[ARG_pudtFrame->udtSET_FILTER_FIFO].RIR)>>21));
				}
				else
				{
					ARG_pudtFrame->u32Msg_Id=((EXIDMSG_FLAG)&((CAN_FIFO_MailBox[ARG_pudtFrame->udtSET_FILTER_FIFO].RIR)>>3));
				}
				/*GET RTR*/
				ARG_pudtFrame->udtRTR_Type=((2)&((CAN_FIFO_MailBox[ARG_pudtFrame->udtSET_FILTER_FIFO].RIR)));
				
				/*GET DLC*/
				ARG_pudtFrame->udtDLC_Type=((15)&((CAN_FIFO_MailBox[ARG_pudtFrame->udtSET_FILTER_FIFO].RDTR)));
				
				/*Get filter match index*/
				ARG_pudtFrame->u32FILTER_MATCH_INDEX=((0xFF)&((CAN_FIFO_MailBox[ARG_pudtFrame->udtSET_FILTER_FIFO].RDTR)>>8));
				
				/*get data*/
				ARG_pudtFrame->pu8Payload[0] = (u8)((0xFFU) & (CAN_FIFO_MailBox[ARG_pudtFrame->udtSET_FILTER_FIFO].RDLR >> 0));
				ARG_pudtFrame->pu8Payload[1] = (u8)((0xFFU) & (CAN_FIFO_MailBox[ARG_pudtFrame->udtSET_FILTER_FIFO].RDLR >> 8));
				ARG_pudtFrame->pu8Payload[2] = (u8)((0xFFU) & (CAN_FIFO_MailBox[ARG_pudtFrame->udtSET_FILTER_FIFO].RDLR >> 16));
				ARG_pudtFrame->pu8Payload[3] = (u8)((0xFFU) & (CAN_FIFO_MailBox[ARG_pudtFrame->udtSET_FILTER_FIFO].RDLR >> 24));
				
				ARG_pudtFrame->pu8Payload[4] = (u8)((0xFFU) & (CAN_FIFO_MailBox[ARG_pudtFrame->udtSET_FILTER_FIFO].RDHR >> 0));
				ARG_pudtFrame->pu8Payload[5] = (u8)((0xFFU) & (CAN_FIFO_MailBox[ARG_pudtFrame->udtSET_FILTER_FIFO].RDHR >> 8));
				ARG_pudtFrame->pu8Payload[6] = (u8)((0xFFU) & (CAN_FIFO_MailBox[ARG_pudtFrame->udtSET_FILTER_FIFO].RDHR >> 16));
				ARG_pudtFrame->pu8Payload[7] = (u8)((0xFFU) & (CAN_FIFO_MailBox[ARG_pudtFrame->udtSET_FILTER_FIFO].RDHR >> 24));

				/*Release fifo*/
				if (ARG_pudtFrame->udtSET_FILTER_FIFO == FILTER_FIFO0) 
				{
				  CAN_RF0R|=(1<<RFOM0);
				}
				else 
				{
				  
				  CAN_RF1R|=(1<<RFOM0);
				}
				
				L_stderrorError=E_OK;
				
			}
			else
			{
				L_stderrorError=E_NOK;
			}
		}
		else
		{
			L_stderrorError=E_NOK;
		}
		
	}
	else
	{
		L_stderrorError=E_NULL_POINTER;
	}
	return L_stderrorError;

}
