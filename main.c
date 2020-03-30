#include "STD_TYPES_H.h"
#include "RCC_interface.h"
#include "HSWITCH_interface.h"

void main(void)
{
	RCC_u8_ControlPrephiral(RCC_u32_GIOPA_PERIP,ENABLE);
	HSWITCH_init();
  while (1)
    {
       // Add your code here.
    }
}

