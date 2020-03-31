#ifndef CHIPUSARTHANDLER_INTERFACE_H_
#define CHIPUSARTHANDLER_INTERFACE_H_

#define CUH_CONFIG_MODE_DEFAULT			0
#define CUH_CONFIG_MODE_NON_DEFAULT		1

#define CHU_CONNECTION_DEFAULT			0
#define	CHU_CONNECTION_REMAPED			1

#define CUH_BAUDRATE_2400	USART_BAUDRATE_2400
#define CUH_BAUDRATE_9600	USART_BAUDRATE_9600
#define CUH_BAUDRATE_19200  USART_BAUDRATE_19200
#define CUH_BAUDRATE_57600  USART_BAUDRATE_57600
#define CUH_BAUDRATE_115200 USART_BAUDRATE_115200

#define CUH_PARITY_EVEN		USART_PARITY_EVEN
#define CUH_PARITY_ODD		USART_PARITY_ODD
#define CUH_PARITY_DISABLE	USART_PARITY_DISABLE

#define CUH_CHANNEL_USART1 USART_ID_USART1
#define CUH_CHANNEL_USART2 USART_ID_USART2
#define CUH_CHANNEL_USART3 USART_ID_USART3

#define CUH_STOP_1_p_5 	USART_STOP_1_p_5
#define CUH_STOP_2 		USART_STOP_2
#define CUH_STOP_0_p_5 	USART_STOP_0_p_5
#define CUH_STOP_1 		USART_STOP_1

#define CUH_OK 	((u8)0)
#define CUH_NOK	((u8)1)

#pragma pack(4)
typedef struct ChipUSARTHandler_configType
{
	void* channel;
	u32 stopBit;
	f32 baudRate;
	u8 parity;
	u8 configMode;
	/*u8 connection;*/
}ChipUSARTHandler_configType;

typedef void (*ChipUSARTHandler_notifyType) (void);

u8 ChipUSARTHandler_Init(void);
u8 ChipUSARTHandler_sendBacket(u8 ID,const u8* buffer,u16 length,ChipUSARTHandler_notifyType notifyFunction);
u8 ChipUSARTHandler_receiveBacket(u8 ID,u8* buffer,u16 length,ChipUSARTHandler_notifyType notifyFunction);


#endif /* CHIPUSARTHANDLER_INTERFACE_H_ */
