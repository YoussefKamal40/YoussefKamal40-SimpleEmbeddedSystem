#include "../../LIB/STD_TYPES_H.h"
#include "../../MCAL/GPIO/GPIO_Interface.h"
#include "LEDHandler_Interface.h"
#include "LEDHandler_config.h"

const LEDHandlerConfigType ledsConfig[NUMBER_OF_LEDS]=
{
		{LEDH_PP_MODE,LEDH_50M_SPEED,LEDH_C_PORT,LEDH_PIN_13,LEDH_STATE_OFF,LEDH_ACTIVE_STATE_LOW}
};
