#include "STD_TYPES_H.h"
#include "GPIO_Interface.h"
#include "LEDHandler_interface.h"
#include "LEDHandler_config.h"

extern LEDHandlerConfigType ledsConfig[NUMBER_OF_LEDS];

void LED_init(void)
{
	u8 i;
	GPIO_pinType tempPin;
	for(i=0;i<NUMBER_OF_LEDS;i++)
	{
		tempPin=(*(GPIO_pinType*)(ledsConfig+i));
		GPIO_configPins(&tempPin);
		if(ledsConfig[i].initState==LEDH_STATE_ON)
		{
			tempPin.value=ledsConfig[i].activeState;
			GPIO_setPinValue(&tempPin);
		}
		else
		{
			if(ledsConfig[i].activeState==GPIO_HIGH_VALUE)
			{
				tempPin.value=GPIO_LOW_VALUE;
				GPIO_setPinValue(&tempPin);
			}
			else
			{
				tempPin.value=GPIO_HIGH_VALUE;
				GPIO_setPinValue(&tempPin);
			}
		}
	}
}

void LED_setState(u8 ledID,u8 state)
{
	/*Check if input is valid*/
	GPIO_pinType tempPin;
	if(ledID<NUMBER_OF_LEDS)
	{
		tempPin=(*(GPIO_pinType*)(ledsConfig+ledID));
		if(state==LEDH_STATE_ON)
		{
			tempPin.value=ledsConfig[ledID].activeState;
			GPIO_setPinValue(&tempPin);
		}
		else
		{
			if(ledsConfig[ledID].activeState==GPIO_HIGH_VALUE)
			{
				tempPin.value=GPIO_LOW_VALUE;
				GPIO_setPinValue(&tempPin);
			}
			else
			{
				tempPin.value=GPIO_HIGH_VALUE;
				GPIO_setPinValue(&tempPin);
			}
		}
	}
}
