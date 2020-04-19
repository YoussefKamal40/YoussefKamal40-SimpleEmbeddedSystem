#ifndef LEDHANDLER_INTERFACE_H_
#define LEDHANDLER_INTERFACE_H_

#define LEDH_PP_MODE		GPIO_GPOUT_PP_MODE
#define LEDH_OD_MODE		GPIO_GPOUT_OD_MODE
#define LEDH_10M_SPEED	        GPIO_10M_SPEED
#define LEDH_2M_SPEED	        GPIO_2M_SPEED
#define LEDH_50M_SPEED	        GPIO_50M_SPEED

#define LEDH_PIN_0       GPIO_PIN_0
#define LEDH_PIN_1       GPIO_PIN_1
#define LEDH_PIN_2       GPIO_PIN_2
#define LEDH_PIN_3       GPIO_PIN_3
#define LEDH_PIN_4       GPIO_PIN_4
#define LEDH_PIN_5       GPIO_PIN_5
#define LEDH_PIN_6       GPIO_PIN_6
#define LEDH_PIN_7       GPIO_PIN_7
#define LEDH_PIN_8       GPIO_PIN_8
#define LEDH_PIN_9       GPIO_PIN_9
#define LEDH_PIN_10      GPIO_PIN_10
#define LEDH_PIN_11      GPIO_PIN_11
#define LEDH_PIN_12      GPIO_PIN_12
#define LEDH_PIN_13      GPIO_PIN_13
#define LEDH_PIN_14      GPIO_PIN_14
#define LEDH_PIN_15      GPIO_PIN_15

#define LEDH_A_PORT	((void*)0x40010800)
#define LEDH_B_PORT	((void*)0x40010c00)
#define LEDH_C_PORT	((void*)0x40011000)
#define LEDH_D_PORT	((void*)0x40011400)
#define LEDH_E_PORT	((void*)0x40011800)
#define LEDH_F_PORT	((void*)0x40011c00)
#define LEDH_G_PORT	((void*)0x40012000)

#define LEDH_ACTIVE_STATE_HIGH GPIO_HIGH_VALUE
#define LEDH_ACTIVE_STATE_LOW  GPIO_LOW_VALUE

#define LEDH_STATE_ON ((u8)1)
#define LEDH_STATE_OFF ((u8)0)

#pragma pack(4)
typedef struct LEDHandlerConfigType
{
	u32 mode;
	u32 speed;
	void* port;
	u16 pin;
	u8 initState;
	u8 activeState;
}LEDHandlerConfigType;

void LED_init(void);
void LED_setState(u8 ledID,u8 state);

#endif /* LEDHANDLER_INTERFACE_H_ */
