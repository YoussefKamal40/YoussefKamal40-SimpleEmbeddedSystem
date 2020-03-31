#include "STD_TYPES_H.h"
#include "RCC_interface.h"
#include "systemClockHandler_interface.h"
#include "ChipUSARTHandler_interface.h"

static void receiveNotify(void);
static void sendNotify(void);

static volatile u8 dataSent=0;
static volatile u8 dataReceived=0;

void main(void)
{
	u8 dataReceiveBuffer[20];
	u8 dataSendBuffer[20]="hamada";
	u8 i;
	volatile u8 error=0;

	error|=SYS_HAN_setSystemClock(SYS_HAN_CLOCK_72MHz);
	error|=SYS_HAN_setAHBClock(SYS_HAN_CLOCK_72MHz);
	error|=SYS_HAN_setAPB1Clock(SYS_HAN_CLOCK_36MHz);
	error|=SYS_HAN_setAPB2Clock(SYS_HAN_CLOCK_72MHz);
	error|=RCC_u8_ControlPrephiral(RCC_u32_CONTROL_PERIP_IOPAEN,RCC_u8_ENABLE);
	error|=RCC_u8_ControlPrephiral(RCC_u32_CONTROL_PERIP_IOPBEN,RCC_u8_ENABLE);
	ChipUSARTHandler_Init();
	error|=ChipUSARTHandler_sendBacket(1,dataSendBuffer,6,sendNotify);
	error|=ChipUSARTHandler_receiveBacket(1,dataReceiveBuffer,20,receiveNotify);
	while (1)
	{
		if(dataReceived)
		{
			dataReceived=0;
			while(!dataSent);
			for(i=0;i<20;i++)
			{
				dataSendBuffer[i]=dataReceiveBuffer[i];
			}
			dataSent=0;
			error|=ChipUSARTHandler_sendBacket(1,dataSendBuffer,20,sendNotify);
			error|=ChipUSARTHandler_receiveBacket(1,dataReceiveBuffer,20,receiveNotify);
		}
	}
}

static void receiveNotify(void)
{
	dataReceived=1;
}

static void sendNotify(void)
{
	dataSent=1;
}
