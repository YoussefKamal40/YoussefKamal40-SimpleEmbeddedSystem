#include "STD_TYPES_H.h"
#include "ChipUSARTHandler_interface.h"
#include "USART_interface.h"
#include "ChipUSARTHandler_config.h"
#include "GPIO_Interface.h"
#include "RCC_interface.h"

extern ChipUSARTHandler_configType ChipUSARTHandler_config[NUMBER_OF_CHIPS];

u8 ChipUSARTHandler_Init(void)
{
	u8 i,error;
	GPIO_pinType tx,rx;

	error=CUH_OK;
	tx.mode=GPIO_AFOUT_PP_MODE;
	tx.speed=GPIO_50M_SPEED;
	rx.mode=GPIO_INPUT_PULL_UP_MODE;
	rx.speed=GPIO_50M_SPEED;
	for(i=0;i<NUMBER_OF_CHIPS;i++)
	{
		switch((u32)ChipUSARTHandler_config[i].channel)
		{
		case (u32)USART_ID_USART1:
			error|=RCC_u8_ControlPrephiral(RCC_u32_CONTROL_PERIP_USART1EN,RCC_u8_ENABLE);
			tx.port=GPIO_A_PORT;
			tx.pin=GPIO_PIN_9;
			rx.port=GPIO_A_PORT;
			rx.pin=GPIO_PIN_10;
			break;
		case (u32)USART_ID_USART2:
			error|=RCC_u8_ControlPrephiral(RCC_u32_CONTROL_PERIP_USART2EN,RCC_u8_ENABLE);
			tx.port=GPIO_A_PORT;
			tx.pin=GPIO_PIN_2;
			rx.port=GPIO_A_PORT;
			rx.pin=GPIO_PIN_3;
			break;
		case (u32)USART_ID_USART3:
			error|=RCC_u8_ControlPrephiral(RCC_u32_CONTROL_PERIP_USART3EN,RCC_u8_ENABLE);
			tx.port=GPIO_B_PORT;
			tx.pin=GPIO_PIN_10;
			rx.port=GPIO_B_PORT;
			rx.pin=GPIO_PIN_11;
			break;
		}
		GPIO_configPins(&tx);
		GPIO_configPins(&rx);
		if(ChipUSARTHandler_config[i].configMode)
		{
			USART_config((USARTConfig_Type*)(&ChipUSARTHandler_config[i]));
		}
		else
		{
			USART_init(ChipUSARTHandler_config[i].channel);
		}
	}
	if(error)
	{
		error=CUH_NOK;
	}
	return error;
}

u8 ChipUSARTHandler_sendBacket(u8 ID,const u8* buffer,u16 length,ChipUSARTHandler_notifyType notifyFunction)
{
	if(USART_send(ChipUSARTHandler_config[ID].channel,buffer,length,notifyFunction))
	{
		return CUH_NOK;
	}
	else
	{
		return CUH_OK;
	}
}

u8 ChipUSARTHandler_receiveBacket(u8 ID,u8* buffer,u16 length,ChipUSARTHandler_notifyType notifyFunction)
{
	if(USART_receive(ChipUSARTHandler_config[ID].channel,buffer,length,notifyFunction))
	{
		return CUH_NOK;
	}
	else
	{
		return CUH_OK;
	}
}
