#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

#pragma pack(4)
typedef struct GPIO_pinType
{
	u32 mode;
	u32 speed;
	void* port;
	u16 pin;
	u8 value;
}GPIO_pinType;

#define GPIO_PIN_0  ((u16)0x1)
#define GPIO_PIN_1  ((u16)0x2)
#define GPIO_PIN_2  ((u16)0x4)
#define GPIO_PIN_3  ((u16)0x8)
#define GPIO_PIN_4  ((u16)0x10)
#define GPIO_PIN_5  ((u16)0x20)
#define GPIO_PIN_6  ((u16)0x40)
#define GPIO_PIN_7  ((u16)0x80)
#define GPIO_PIN_8  ((u16)0x100)
#define GPIO_PIN_9  ((u16)0x200)
#define GPIO_PIN_10 ((u16)0x400)
#define GPIO_PIN_11 ((u16)0x800)
#define GPIO_PIN_12 ((u16)0x1000)
#define GPIO_PIN_13 ((u16)0x2000)
#define GPIO_PIN_14 ((u16)0x4000)
#define GPIO_PIN_15 ((u16)0x8000)

#define GPIO_A_PORT	((void*)0x40010800)
#define GPIO_B_PORT	((void*)0x40010c00)
#define GPIO_C_PORT	((void*)0x40011000)
#define GPIO_D_PORT	((void*)0x40011400)
#define GPIO_E_PORT	((void*)0x40011800)
#define GPIO_F_PORT	((void*)0x40011c00)
#define GPIO_G_PORT	((void*)0x40012000)

#define GPIO_GPOUT_PP_MODE			((u32)0b00110)
#define GPIO_GPOUT_OD_MODE			((u32)0b01110)
#define GPIO_AFOUT_PP_MODE			((u32)0b10110)
#define GPIO_AFOUT_OD_MODE			((u32)0b11110)
#define GPIO_INPUT_ANALOG_MODE		((u32)0b00000)
#define GPIO_INPUT_FLOAT_MODE		((u32)0b01000)
#define GPIO_INPUT_PULL_UP_MODE		((u32)0b10001)
#define GPIO_INPUT_PULL_DOWN_MODE	((u32)0b10000)

#define GPIO_10M_SPEED	((u32)0b1101)
#define GPIO_2M_SPEED	((u32)0b1110)
#define GPIO_50M_SPEED	((u32)0b1111)

#define GPIO_HIGH_VALUE ((u8)1)
#define GPIO_LOW_VALUE 	((u8)0)

void GPIO_configPins(GPIO_pinType* pins);
void GPIO_setPinValue(GPIO_pinType* pins);
void GPIO_getPinValue(GPIO_pinType* pin);



#endif /* GPIO_INTERFACE_H_ */
