#include "../../LIB/STD_TYPES_H.h"
#include "../../MCAL/NVIC/NVIC.h"
#include "../../HAL/HSYSTEM/systemClockHandler_interface.h"
#include "USART_interface.h"
#include "USART_registers.h"
#include "USART_config.h"

#define USART1_INDEX	0
#define USART2_INDEX	1
#define USART3_INDEX	2
#define UART4_INDEX	3
#define UART5_INDEX	4

#define USART1_INT_NUM	((u8)37)
#define USART2_INT_NUM	((u8)38)
#define USART3_INT_NUM	((u8)39)
#define UART4_INT_NUM	((u8)52)
#define UART5_INT_NUM	((u8)53)

#define ENABLE 	1
#define DISABLE 0

#define IDLE 0
#define BUSY 1

#define NUMBER_OF_UARTS 5

typedef struct bufferType
{
	u8* ptr;
	u32 position;
	u32 size;
	u8	state;
	u8 reserved1;
	u16 reserved2;
}bufferType;

void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
void UART4_IRQHandler(void);
void UART5_IRQHandler(void);

static volatile handlerNotifyType sendNotify[NUMBER_OF_UARTS];
static volatile handlerNotifyType receiveNotify[NUMBER_OF_UARTS];

static volatile bufferType TxBuffer[NUMBER_OF_UARTS];
static volatile bufferType RxBuffer[NUMBER_OF_UARTS];

static const u8 USART_InterruptNumber[NUMBER_OF_UARTS]=
{
		USART1_INT_NUM,
		USART2_INT_NUM,
		USART3_INT_NUM,
		UART4_INT_NUM,
		UART5_INT_NUM
};

static u8 USART_indexGetter(void* ID);
static void USART_GeneralHandler(volatile USARTtype* const USART);

void USART_init(void* ID)
{
	volatile USARTtype* USART;
	f32 BRRValue;
	f32 BRRFraction;
	u32 BRRMantessa;
	u8 USARTIndex;

	USART=(USARTtype*)ID;
	USARTIndex=USART_indexGetter((void*)USART);

	/*Enable UART*/
	USART->CR1|=USART_CR1_UE;

	/*Disable interrupt*/
	USART->CR1&=~USART_CR1_TXEIE;
	USART->CR1&=~USART_CR1_RXNEIE;

	/*Set Word Length to 8 bit*/
	USART->CR1&=~USART_CR1_M;

	/*Stop bit configuration*/
	USART->CR2=(USART->CR2&USART_CR2_STOP_CLEARMASK)|(STOP_CONFIG);

	/*USART Parity configuer*/
#if PARITY_CONFIG == USART_PARITY_DISABLE
	USART->CR1&=~USART_CR1_PCE;
#elif PARITY_CONFIG == USART_PARITY_EVEN
	USART->CR1|=USART_CR1_PCE;
#elif PARITY_CONFIG == SART_PARITY_ODD
	USART->CR1|=USART_CR1_PCE|USART_CR1_PS;
#endif

	/*Set Baud Rate*/
	if(USART==USART_ID_USART1)
	{
		BRRValue=((f32)SYS_HAN_getAPB2Clock())/(((f32)16)*BAUDRATE_CONFIG);
	}
	else
	{
		BRRValue=((f32)SYS_HAN_getAPB1Clock())/(((f32)16)*BAUDRATE_CONFIG);
	}
	BRRMantessa=(u32)BRRValue;
	BRRFraction=(BRRValue-((f32)BRRMantessa))*((f32)16);
	if((BRRFraction-((u32)BRRFraction))>=((f32)0.5))
	{
		BRRFraction++;
	}
	USART->BRR=((u32)(BRRMantessa<<USART_BRR_DIV_Mantissa_OFFSET))+((u32)BRRFraction);

	/*Transmit and receive enable*/
	USART->CR1|=USART_CR1_TE|USART_CR1_RE;

	/*Enable NVIC*/
	NVIC_extIntSetPending(USART_InterruptNumber[USARTIndex],NVIC_CLEAR);
	NVIC_extIntControl(USART_InterruptNumber[USARTIndex],NVIC_ENABLE);

	RxBuffer[USARTIndex].state=IDLE;
	TxBuffer[USARTIndex].state=IDLE;
}

void USART_config(USARTConfig_Type* data)
{
	volatile USARTtype* USART;
	f32 BRRValue;
	f32 BRRFraction;
	u32 BRRMantessa;
	u8 USARTIndex;


	USART=(USARTtype*)data->ID;
	USARTIndex=USART_indexGetter((void*)USART);
	/*Enable UART*/
	USART->CR1|=USART_CR1_UE;

	/*Disable interrupt*/
	USART->CR1&=~USART_CR1_TXEIE;
	USART->CR1&=~USART_CR1_RXNEIE;

	/*Set Word Length to 8 bit*/
	USART->CR1&=~USART_CR1_M;

	/*Stop bit configuration*/
	USART->CR2=(USART->CR2&USART_CR2_STOP_CLEARMASK)|(data->stopBit);

	/*USART Parity configuer*/
	switch(data->parity)
	{
	case (u8)USART_PARITY_DISABLE:
			USART->CR1&=~USART_CR1_PCE;
	break;
	case (u8)USART_PARITY_EVEN:
			USART->CR1|=USART_CR1_PCE;
	break;
	case (u8)USART_PARITY_ODD:
			USART->CR1|=USART_CR1_PCE|USART_CR1_PS;
	}
	/*Set Baud Rate*/
	if(USART==USART_ID_USART1)
	{
		BRRValue=((f32)SYS_HAN_getAPB2Clock())/(((f32)16)*data->baudRate);
	}
	else
	{
		BRRValue=((f32)SYS_HAN_getAPB1Clock())/(((f32)16)*data->baudRate);
	}
	BRRMantessa=(u32)BRRValue;
	BRRFraction=(BRRValue-((f32)BRRMantessa))*((f32)16);
	if((BRRFraction-((u32)BRRFraction))>=((f32)0.5))
	{
		BRRFraction++;
	}
	USART->BRR=((u32)(BRRMantessa<<USART_BRR_DIV_Mantissa_OFFSET))+((u32)BRRFraction);

	/*Transmit and receive enable*/
	USART->CR1|=USART_CR1_TE|USART_CR1_RE;

	/*Enable NVIC*/
	NVIC_extIntSetPending(USART_InterruptNumber[USARTIndex],NVIC_CLEAR);
	NVIC_extIntControl(USART_InterruptNumber[USARTIndex],NVIC_ENABLE);
	RxBuffer[USARTIndex].state=IDLE;
	TxBuffer[USARTIndex].state=IDLE;
}

USART_ErrorType USART_send(void* ID,const u8* buffer,u16 length,handlerNotifyType notifyFunction)
{
	volatile USARTtype* USART;
	USART_ErrorType error=USART_ERROR_OK;
	u8 USART_index;

	if(ID)
	{
		USART=(USARTtype*)ID;
		USART_index=USART_indexGetter(ID);
		if(TxBuffer[USART_index].state==IDLE)
		{
			if(length>=1)
			{
				TxBuffer[USART_index].ptr=(u8*)buffer;
				TxBuffer[USART_index].size=length;
				TxBuffer[USART_index].state=BUSY;
				TxBuffer[USART_index].position=0;
				if(USART->SR&USART_SR_TXE)
				{
					USART->DR=*buffer;
					if(length==1)
					{
						if(notifyFunction)
						{
							notifyFunction();
						}
						TxBuffer[USART_index].state=IDLE;
						return error;
					}
					TxBuffer[USART_index].position++;
				}
				sendNotify[USART_index]=notifyFunction;

				/*Enable Interrupt*/
				USART->CR1|=USART_CR1_TXEIE;
			}
			else
			{
				error=USART_ERROR_NOK;
			}
		}
		else
		{
			error=USART_ERROR_NOK;
		}
	}
	else
	{
		error=USART_ERROR_NOK;
	}
	return error;
}

USART_ErrorType USART_receive(void* ID,u8* buffer,u16 length,handlerNotifyType notifyFunction)
{
	volatile USARTtype* USART;
	USART_ErrorType error=USART_ERROR_OK;
	u8 USART_index;

	if(ID)
	{
		USART=(USARTtype*)ID;
		USART_index=USART_indexGetter(ID);
		if(RxBuffer[USART_index].state==IDLE)
		{
			if(length>=1)
			{
				RxBuffer[USART_index].ptr=buffer;
				RxBuffer[USART_index].size=length;
				RxBuffer[USART_index].state=BUSY;
				RxBuffer[USART_index].position=0;
				if(USART->SR&USART_SR_RXNE)
				{
					*buffer=(u8)USART->DR;
					if(length==1)
					{
						if(notifyFunction)
						{
							notifyFunction();
						}
						RxBuffer[USART_index].state=IDLE;
						return error;
					}
					RxBuffer[USART_index].position++;
				}
				receiveNotify[USART_index]=notifyFunction;
				/*Enable Interrupt*/
				USART->CR1|=USART_CR1_RXNEIE;
			}
			else
			{
				error=USART_ERROR_NOK;
			}
		}
		else
		{
			error=USART_ERROR_NOK;
		}
	}
	else
	{
		error=USART_ERROR_NOK;
	}
	return error;
}

static void USART_GeneralHandler(volatile USARTtype* const USART)
{
	u8 USARTIndex;

	USARTIndex=USART_indexGetter((void*)USART);

	if(RxBuffer[USARTIndex].state==BUSY)
	{
		if(USART->SR&USART_SR_RXNE)
		{
			if((RxBuffer[USARTIndex].size-RxBuffer[USARTIndex].position)==1)
			{
				/*Disable Interrupt*/
				USART->CR1&=~USART_CR1_RXNEIE;
				RxBuffer[USARTIndex].ptr[RxBuffer[USARTIndex].position]=(u8)USART->DR;
				RxBuffer[USARTIndex].state=IDLE;
				if(receiveNotify[USARTIndex])
				{
					receiveNotify[USARTIndex]();
				}
			}
			else
			{
				RxBuffer[USARTIndex].ptr[RxBuffer[USARTIndex].position]=(u8)USART->DR;
				RxBuffer[USARTIndex].position++;
			}
		}
	}
	if(TxBuffer[USARTIndex].state==BUSY)
	{
		if(USART->SR&USART_SR_TXE)
		{
			if((TxBuffer[USARTIndex].size-TxBuffer[USARTIndex].position)==1)
			{
				/*Disable Interrupt*/
				USART->CR1&=~USART_CR1_TXEIE;
				USART->DR=TxBuffer[USARTIndex].ptr[TxBuffer[USARTIndex].position];
				TxBuffer[USARTIndex].position++;
				/*Enable transmit complete interrupt*/
				USART->CR1|=USART_CR1_TCIE;
			}
			else if(TxBuffer[USARTIndex].size==TxBuffer[USARTIndex].position)
			{
				TxBuffer[USARTIndex].state=IDLE;
				if(sendNotify[USARTIndex])
				{
					sendNotify[USARTIndex]();
				}
				/*Disable transmit complete interrupt*/
				USART->CR1&=~USART_CR1_TCIE;
			}
			else
			{
				USART->DR=TxBuffer[USARTIndex].ptr[TxBuffer[USARTIndex].position];
				TxBuffer[USARTIndex].position++;
			}
		}
	}
}

static u8 USART_indexGetter(void* ID)
{
	switch((u32)ID)
	{
	case (u32)USART_ID_USART1:
			return USART1_INDEX;
	case (u32)USART_ID_USART2:
			return USART2_INDEX;
	case (u32)USART_ID_USART3:
			return USART3_INDEX;
	case (u32)USART_ID_UART4:
			return UART4_INDEX;
	case (u32)USART_ID_UART5:
			return UART5_INDEX;
	}
	return 0;
}

void USART1_IRQHandler(void)
{
	USART_GeneralHandler((USARTtype*)USART_ID_USART1);
}

void USART2_IRQHandler(void)
{
	USART_GeneralHandler((USARTtype*)USART_ID_USART2);
}

void USART3_IRQHandler(void)
{
	USART_GeneralHandler((USARTtype*)USART_ID_USART3);
}

void UART4_IRQHandler(void)
{
	USART_GeneralHandler((USARTtype*)USART_ID_UART4);
}

void UART5_IRQHandler(void)
{
	USART_GeneralHandler((USARTtype*)USART_ID_UART5);
}
