#include "STD_Types.h"
#include "RCC_interface.h"
#include "systemClockHandler_config.h"
#include "systemClockHandler_interface.h"

#define HSI_VALUE 						SYS_HAN_CLOCK_8MHz
#define HSI_BY_2_VALUE 					SYS_HAN_CLOCK_4MHz
#define MAX_PLL_MULTIPLICATION_FACTOR 	16
#define MIN_PLL_MULTIPLICATION_FACTOR 	2
#define PLL_MULT_FACT_OFFSET 			2
#define NUMBER_OF_AHB_PRESCALERS		9
#define NUMBER_OF_APB1_PRESCALERS		5
#define NUMBER_OF_APB2_PRESCALERS		5
#define SYS_HAN_MAX_AHB_CLOCK			SYS_HAN_CLOCK_72MHz
#define SYS_HAN_MAX_APB1_CLOCK			SYS_HAN_CLOCK_36MHz
#define SYS_HAN_MAX_APB2_CLOCK			SYS_HAN_CLOCK_72MHz

static u32 sysClock;
static u32 AHBClock;
static u32 APB1Clock;
static u32 APB2Clock;

static const u32 PLLFactors[]={
		RCC_u32_2_PLL_MULT,
		RCC_u32_3_PLL_MULT,
		RCC_u32_4_PLL_MULT,
		RCC_u32_5_PLL_MULT,
		RCC_u32_6_PLL_MULT,
		RCC_u32_7_PLL_MULT,
		RCC_u32_8_PLL_MULT,
		RCC_u32_9_PLL_MULT,
		RCC_u32_10_PLL_MULT,
		RCC_u32_11_PLL_MULT,
		RCC_u32_12_PLL_MULT,
		RCC_u32_13_PLL_MULT,
		RCC_u32_14_PLL_MULT,
		RCC_u32_15_PLL_MULT,
		RCC_u32_16_PLL_MULT
};

static const u32 AHBprescalers[NUMBER_OF_AHB_PRESCALERS]=
{
		RCC_u32_0_AHB_PRESCALER,
		RCC_u32_2_AHB_PRESCALER,
		RCC_u32_4_AHB_PRESCALER,
		RCC_u32_8_AHB_PRESCALER,
		RCC_u32_16_AHB_PRESCALER,
		RCC_u32_64_AHB_PRESCALER,
		RCC_u32_128_AHB_PRESCALER,
		RCC_u32_256_AHB_PRESCALER,
		RCC_u32_512_AHB_PRESCALER
};

static const u32 APB1prescalers[NUMBER_OF_APB1_PRESCALERS]=
{
		RCC_u32_0_APB1_PRESCALER,
		RCC_u32_2_APB1_PRESCALER,
		RCC_u32_4_APB1_PRESCALER,
		RCC_u32_8_APB1_PRESCALER,
		RCC_u32_16_APB1_PRESCALER
};

static const u32 APB2prescalers[NUMBER_OF_APB2_PRESCALERS]=
{
		RCC_u32_0_APB2_PRESCALER,
		RCC_u32_2_APB2_PRESCALER,
		RCC_u32_4_APB2_PRESCALER,
		RCC_u32_8_APB2_PRESCALER,
		RCC_u32_16_APB2_PRESCALER
};

static u8 setPLLSystemSource(u32 PLLSourceControl,u32 PLLSourceSysSource,u32 controlDisableSource,u32 PLLSource,u32 multFactor);

SYS_error SYS_HAN_setSystemClock(u32 clock)
{
	SYS_error error=SYS_HAN_OK;
	u32 possibleMultiplication;
	u32 possibleRemainder;
	if(clock>SYS_HAN_MAX_SYS_CLOCK)
	{
		error=SYS_HAN_NOK;
	}
	else
	{
		if(clock<=SYS_HAN_CLOCK_8MHz)
		{
			if(clock!=SYS_HAN_HSE_VALUE)
			{
				if(clock==HSI_VALUE)
				{
					error|=RCC_u8_ControlClock(RCC_u32_CLOCK_CONTROL_HSI,RCC_u8_ENABLE);
					error|=RCC_u8_SelectSystemClock(RCC_u32_HSI_SYS_SOURCE);
					error|=RCC_u8_ControlClock(RCC_u32_CLOCK_CONTROL_HSE,RCC_u8_DISABLE);
					error|=RCC_u8_ControlClock(RCC_u32_CLOCK_CONTROL_PLL,RCC_u8_DISABLE);
				}
				else
				{
					error=SYS_HAN_NOK;
				}
			}
			else
			{
				error|=RCC_u8_ControlClock(RCC_u32_CLOCK_CONTROL_HSE,RCC_u8_ENABLE);
				error|=RCC_u8_SelectSystemClock(RCC_u32_HSE_SYS_SOURCE);
				error|=RCC_u8_ControlClock(RCC_u32_CLOCK_CONTROL_HSI,RCC_u8_DISABLE);
				error|=RCC_u8_ControlClock(RCC_u32_CLOCK_CONTROL_PLL,RCC_u8_DISABLE);
			}
		}
		else
		{
			possibleRemainder=clock%SYS_HAN_HSE_VALUE;
			if(possibleRemainder)
			{
				possibleRemainder=clock%(SYS_HAN_HSE_VALUE/2);
				if(possibleRemainder)
				{
					error=SYS_HAN_NOK;
				}
				else
				{
					possibleMultiplication=(2*clock)/SYS_HAN_HSE_VALUE;
					if((possibleMultiplication<=MAX_PLL_MULTIPLICATION_FACTOR)&&(possibleMultiplication>=MIN_PLL_MULTIPLICATION_FACTOR))
					{
						/*select PLL with HSE/2 source*/
						error|=setPLLSystemSource(RCC_u32_CLOCK_CONTROL_HSE,RCC_u32_HSE_SYS_SOURCE,RCC_u32_CLOCK_CONTROL_HSI,RCC_u32_HSE_BY2_PLL_SOURCE,possibleMultiplication);
					}
					else
					{
						error=SYS_HAN_NOK;
					}
				}
			}
			else
			{
				possibleMultiplication=clock/SYS_HAN_HSE_VALUE;
				if((possibleMultiplication<=MAX_PLL_MULTIPLICATION_FACTOR)&&(possibleMultiplication>=MIN_PLL_MULTIPLICATION_FACTOR))
				{
					/*select PLL with HSE source*/
					error|=setPLLSystemSource(RCC_u32_CLOCK_CONTROL_HSE,RCC_u32_HSE_SYS_SOURCE,RCC_u32_CLOCK_CONTROL_HSI,RCC_u32_HSE_PLL_SOURCE,possibleMultiplication);
				}
				else
				{
					possibleRemainder=clock%(SYS_HAN_HSE_VALUE/2);
					if(possibleRemainder)
					{
						error=SYS_HAN_NOK;
					}
					else
					{
						possibleMultiplication=(2*clock)/SYS_HAN_HSE_VALUE;
						if((possibleMultiplication<=MAX_PLL_MULTIPLICATION_FACTOR)&&(possibleMultiplication>=MIN_PLL_MULTIPLICATION_FACTOR))
						{
							/*select PLL with HSE/2 source*/
							error|=setPLLSystemSource(RCC_u32_CLOCK_CONTROL_HSE,RCC_u32_HSE_SYS_SOURCE,RCC_u32_CLOCK_CONTROL_HSI,RCC_u32_HSE_BY2_PLL_SOURCE,possibleMultiplication);
						}
						else
						{
							possibleRemainder=clock%HSI_BY_2_VALUE;
							if(possibleRemainder)
							{
								error=SYS_HAN_NOK;
							}
							else
							{
								possibleMultiplication=clock/HSI_BY_2_VALUE;
								if((possibleMultiplication<=MAX_PLL_MULTIPLICATION_FACTOR)&&(possibleMultiplication>=MIN_PLL_MULTIPLICATION_FACTOR))
								{
									/*select PLL with HSI/2 source*/
									error|=setPLLSystemSource(RCC_u32_CLOCK_CONTROL_HSI,RCC_u32_HSI_SYS_SOURCE,RCC_u32_CLOCK_CONTROL_HSE,RCC_u32_HSI_BY2_PLL_SOURCE,possibleMultiplication);
								}
								else
								{
									error=SYS_HAN_NOK;
								}
							}
						}
					}
				}
			}
		}
	}
	if(!error)
	{
		sysClock=clock;
	}
	else
	{
		error=SYS_HAN_NOK;
	}
	return error;
}

u8 setPLLSystemSource(u32 PLLSourceControl,u32 PLLSourceSysSource,u32 controlDisableSource,u32 PLLSource,u32 multFactor)
{
	u8 error=SYS_HAN_OK;

	error|=RCC_u8_ControlClock(PLLSourceControl,RCC_u8_ENABLE);
	error|=RCC_u8_SelectSystemClock(PLLSourceSysSource);
	error|=RCC_u8_ControlClock(RCC_u32_CLOCK_CONTROL_PLL,RCC_u8_DISABLE);
	error|=RCC_u8_ControlClock(controlDisableSource,RCC_u8_DISABLE);
	error|=RCC_u8_SelectPLLConfig(PLLSource,PLLFactors[multFactor-PLL_MULT_FACT_OFFSET]);
	error|=RCC_u8_ControlClock(RCC_u32_CLOCK_CONTROL_PLL,RCC_u8_ENABLE);
	error|=RCC_u8_SelectSystemClock(RCC_u32_PLL_SYS_SOURCE);
	if(!error)
	{
		error=SYS_HAN_NOK;
	}

	return error;
}

u32 SYS_HAN_getSystemClock(void)
{
	return sysClock;
}

SYS_error SYS_HAN_setAHBClock(u32 clock)
{
	SYS_error error=SYS_HAN_OK;
	u32 prescaler;
	u8 prescalerIndex=0;

	if(clock<=sysClock&&clock<=SYS_HAN_MAX_AHB_CLOCK&&!(sysClock%clock)&&!clock)
	{
		prescaler=sysClock/clock;
		while(prescaler>1)
		{
			if(prescaler%2)
			{
				error=SYS_HAN_NOK;
				break;
			}
			prescaler/=2;
			prescalerIndex++;
		}
		if(prescaler<=NUMBER_OF_AHB_PRESCALERS&&(!error))
		{
			error|=RCC_u8_SelectBusPrescaler(RCC_u32_APB1_BUS,AHBprescalers[prescaler-1]);
		}
		else
		{
			error=SYS_HAN_NOK;
		}
	}
	else
	{
		error=SYS_HAN_NOK;
	}
	if(!error)
	{
		AHBClock=clock;
	}
	return error;
}

u32 SYS_HAN_getAHBClock(void)
{
	return AHBClock;
}

SYS_error SYS_HAN_setAPB1Clock(u32 clock)
{
	SYS_error error=SYS_HAN_OK;
	u32 prescaler;
	u8 prescalerIndex=0;

	if(clock<=sysClock&&clock<=SYS_HAN_MAX_APB1_CLOCK&&!(sysClock%clock)&&!clock)
	{
		prescaler=sysClock/clock;
		while(prescaler>1)
		{
			if(prescaler%2)
			{
				error=SYS_HAN_NOK;
				break;
			}
			prescaler/=2;
			prescalerIndex++;
		}
		if(prescaler<=NUMBER_OF_APB1_PRESCALERS&&(!error))
		{
			error|=RCC_u8_SelectBusPrescaler(RCC_u32_APB1_BUS,APB1prescalers[prescaler-1]);
		}
		else
		{
			error=SYS_HAN_NOK;
		}
	}
	else
	{
		error=SYS_HAN_NOK;
	}
	if(!error)
	{
		APB1Clock=clock;
	}
	return error;
}

u32 SYS_HAN_getAPB1Clock(void)
{
	return APB1Clock;
}

SYS_error SYS_HAN_setAPB2Clock(u32 clock)
{
	SYS_error error=SYS_HAN_OK;
	u32 prescaler;
	u8 prescalerIndex=0;

	if(clock<=sysClock&&clock<=SYS_HAN_MAX_APB2_CLOCK&&!(sysClock%clock)&&!clock)
	{
		prescaler=sysClock/clock;
		while(prescaler>1)
		{
			if(prescaler%2)
			{
				error=SYS_HAN_NOK;
				break;
			}
			prescaler/=2;
			prescalerIndex++;
		}
		if(prescaler<=NUMBER_OF_APB2_PRESCALERS&&(!error))
		{
			error|=RCC_u8_SelectBusPrescaler(RCC_u32_APB1_BUS,APB2prescalers[prescaler-1]);
		}
		else
		{
			error=SYS_HAN_NOK;
		}
	}
	else
	{
		error=SYS_HAN_NOK;
	}
	if(!error)
	{
		APB2Clock=clock;
	}
	return error;
}

u32 SYS_HAN_getAPB2Clock(void)
{
	return APB2Clock;
}
