#include "../../LIB/STD_TYPES_H.h"
#include "GPIO_Interface.h"

#define GPIO_u8_CONFIG_BITS_NUMBER ((u8)4)
#define GPIO_u32_CONFIG_BITS_MASK	((u32)0xf)

#pragma pack(4)
typedef struct GPIOType
{
	u32 CRL;
	u32 CRH;
	u32 IDR;
	u32 ODR;
	u32 BSR;
	u32 BRR;
	u32 LCKR;
}GPIOType;

void GPIO_configPins(GPIO_pinType* pins)
{
	volatile GPIOType* GPIO;
	u8 i;
	u8 shift;
	u32 mode;
	u32 temp;

	GPIO=((volatile GPIOType* )pins->port);
	if(pins->pin&((u16)0xff))
	{
		for(i=0;i<8;i++)
		{
			if(pins->pin&((u16)(1<<i)))
			{
				shift=(u8)(i*GPIO_u8_CONFIG_BITS_NUMBER);
				mode=(pins->mode>>1)&pins->speed;
				temp=GPIO->CRL;
				temp&=~(GPIO_u32_CONFIG_BITS_MASK<<shift);
				temp|=(u32)(mode<<shift);
				GPIO->CRL=temp;
				if(pins->mode&1)
				{
					GPIO->BSR=(u32)(1<<i);
				}
				else
				{
					GPIO->BRR=(u32)(1<<i);
				}
			}
		}
	}
	if(pins->pin&((u16)0xff00))
	{
		for(i=8;i<16;i++)
		{
			if(pins->pin&((u16)(1<<i)))
			{
				shift=(u8)((i-8)*GPIO_u8_CONFIG_BITS_NUMBER);
				mode=(pins->mode>>1)&pins->speed;
				temp=GPIO->CRH;
				temp&=~(GPIO_u32_CONFIG_BITS_MASK<<shift);
				temp|=(u32)(mode<<shift);
				GPIO->CRH=temp;
				if(pins->mode&1)
				{
					GPIO->BSR=(u32)(1<<i);
				}
				else
				{
					GPIO->BRR=(u32)(1<<i);
				}
			}
		}
	}
}

void GPIO_setPinValue(GPIO_pinType* pins)
{
	volatile GPIOType* GPIO;

	GPIO=((volatile GPIOType* )pins->port);
	if(pins->value)
	{
		GPIO->BSR=((u32)pins->pin);
	}
	else
	{
		GPIO->BRR=((u32)pins->pin);
	}
}

void GPIO_getPinValue(GPIO_pinType* pin)
{
	volatile GPIOType* GPIO;

	GPIO=((volatile GPIOType* )pin->port);
	if(GPIO->IDR&pin->pin)
	{
		pin->value=1;
	}
	else
	{
		pin->value=0;
	}
}
