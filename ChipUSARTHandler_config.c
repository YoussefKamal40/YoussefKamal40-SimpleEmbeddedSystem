#include "STD_TYPES_H.h"
#include "ChipUSARTHandler_interface.h"
#include "ChipUSARTHandler_config.h"
#include "USART_interface.h"

const ChipUSARTHandler_configType ChipUSARTHandler_config [NUMBER_OF_CHIPS]=
{
		{
				CUH_CHANNEL_USART1,
				0,
				0,
				0,
				CUH_CONFIG_MODE_DEFAULT
		},
		{
				CUH_CHANNEL_USART2,
				CUH_STOP_1,
				CUH_BAUDRATE_19200,
				CUH_PARITY_DISABLE,
				CUH_CONFIG_MODE_NON_DEFAULT
		}
};
