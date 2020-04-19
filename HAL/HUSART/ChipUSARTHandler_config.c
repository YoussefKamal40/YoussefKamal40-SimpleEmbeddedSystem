#include "../../LIB/STD_TYPES_H.h"
#include "ChipUSARTHandler_interface.h"
#include "ChipUSARTHandler_config.h"
#include "../../MCAL/USART/USART_interface.h"

const ChipUSARTHandler_configType ChipUSARTHandler_config [NUMBER_OF_CHIPS]=
{
		{
				CUH_CHANNEL_USART3,
				0,
				0,
				0,
				CUH_CONFIG_MODE_DEFAULT
		}
};
