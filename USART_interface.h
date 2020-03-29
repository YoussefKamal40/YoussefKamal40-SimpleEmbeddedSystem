#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

#define USART_BAUDRATE_2400		((f32)2400)
#define USART_BAUDRATE_9600		((f32)9600)
#define USART_BAUDRATE_19200    ((f32)19200)
#define USART_BAUDRATE_57600    ((f32)57600)
#define USART_BAUDRATE_115200   ((f32)115200)

#define USART_PARITY_EVEN		2
#define USART_PARITY_ODD		1
#define USART_PARITY_DISABLE	0

#define USART_ID_USART1 ((void*)0x40013800)
#define USART_ID_USART2 ((void*)0x40004400)
#define USART_ID_USART3 ((void*)0x40004800)
#define USART_ID_UART4  ((void*)0x40004C00)
#define USART_ID_UART5  ((void*)0x40005000)

#define USART_STOP_1_p_5 	((u32)0x3000)
#define USART_STOP_2 		((u32)0x2000)
#define USART_STOP_0_p_5 	((u32)0x1000)
#define USART_STOP_1 		((u32)0x0000)

#define USART_ERROR_OK		((u8)0)
#define USART_ERROR_NOK		((u8)1)

typedef u8 USART_ErrorType;

typedef void (*handlerNotifyType)(void);

#pragma pack(4)
typedef struct USART_Type
{
	u32 stopBit;
	f32 baudRate;
	void* ID;
	u8 parity;
}USARTConfig_Type;

void USART_init(void* ID);
void USART_config(USARTConfig_Type* data);
USART_ErrorType USART_send(void* ID,const u8* buffer,u16 length,handlerNotifyType notifyFunction);
USART_ErrorType USART_receive(void* ID,u8* buffer,u16 length,handlerNotifyType notifyFunction);

#endif /* USART_INTERFACE_H_ */
