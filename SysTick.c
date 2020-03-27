/*
 * SysTick.c
 *
 *  Created on: Mar 25, 2020
 *      Author: Esraa
 */
#include "stdint.h"
#include "SysTick.h"
#include "SysTick_config.h"

#define STK_BASE_ADDRESS          (0xE000E010)

#define STK_CTRL_OFFSET           (0x00)
#define STK_LOAD_OFFSET           (0x04)
#define STK_VAL_OFFSET            (0x08)
#define STK_CALIB_OFFSET          (0x0C)

#define STK_CTRL                 *((volatile uint32_t*)(STK_BASE_ADDRESS + STK_CTRL_OFFSET  ))
#define STK_LOAD                 *((volatile uint32_t*)(STK_BASE_ADDRESS + STK_LOAD_OFFSET  ))
#define STK_VAL                  *((volatile uint32_t*)(STK_BASE_ADDRESS + STK_VAL_OFFSET   ))
#define STK_CALIB                *((volatile uint32_t*)(STK_BASE_ADDRESS + STK_CALIB_OFFSET ))

#define STK_CTRL_ENABLE_MASK      (0x00000001U)
#define STK_CTRL_TICKINT_MASK 	  (0x00000002U)
#define STK_CTRL_COUNTFLAG_MASK   (0x00010000U)
#define STK_CTRL_CLKSOURCE_MASK   (0x00000004U)
#define STK_CALIB_NOREF_MASK      (0x80000000U)
#define STK_CALIB_BIT_NUM         (31U)

#define STK_BIT_RESELUTION        ((uint32_t)24)
#define STK_PRESCALER             ((uint32_t)8)
#define STK_MAX_NUM_OF_TICKS      (16777216)

#define CONV_NUM_FROM_SEC_TO_NS   (1000000000U)
#define CONV_NUM_FROM_US_TO_NS    (1000U)

#define NULL                      ((void *)0)


static systickCbf_t APP_CBF;
static uint32_t overflowsNeededForDesiredT;
static uint32_t preload_value;
static uint32_t currentOverflowsNeeded;

void SysTick_init(void)
{
	/*SysTick exception request enable*/
	STK_CTRL |= STK_CTRL_TICKINT_MASK ;
	if ( (STK_CLOCK_SRC == EXTERNAL_REF_CLOCK) && (( STK_CALIB && STK_CALIB_NOREF_MASK ) >> STK_CALIB_BIT_NUM == 0 ))
	{
		STK_CTRL &= ~(STK_CTRL_CLKSOURCE_MASK);
	}
	else if (STK_CLOCK_SRC == FREE_RUNNIG_CLOCK)
	{
		STK_CTRL |= STK_CTRL_CLKSOURCE_MASK ;
	}
}

void SysTick_start(void)
{
	/*Clear Counter Flag or write anything in STK_VAL */
	STK_CTRL &= ~(STK_CTRL_COUNTFLAG_MASK);
	STK_CTRL |= STK_CTRL_ENABLE_MASK ;
}

void SysTick_stop(void)
{
	STK_CTRL &= ~(STK_CTRL_ENABLE_MASK);
}

void SysTick_setClockSrc(uint32_t clockSrc)
{
	if ( (clockSrc == EXTERNAL_REF_CLOCK) && (( STK_CALIB && STK_CALIB_NOREF_MASK ) >> STK_CALIB_BIT_NUM == 0 ))
	{
		STK_CTRL &= ~(STK_CTRL_CLKSOURCE_MASK);
	}
	else if (clockSrc == FREE_RUNNIG_CLOCK )
	{
		STK_CTRL |= STK_CTRL_CLKSOURCE_MASK ;
	}
}

void SysTick_setTime(uint32_t time_US , uint32_t AHB_clock)
{
	uint32_t timeOfOneCount_NS;
	uint32_t timeUS_NS;
	uint32_t timeOverFlow_NS;
	uint32_t remaining_time;
	timeUS_NS = (uint64_t) time_US * (uint64_t) (CONV_NUM_FROM_US_TO_NS);
	if ((STK_CLOCK_SRC == EXTERNAL_REF_CLOCK) && (( STK_CALIB && STK_CALIB_NOREF_MASK ) >> STK_CALIB_BIT_NUM == 0 ))
	{
		timeOfOneCount_NS = ((uint64_t)(CONV_NUM_FROM_SEC_TO_NS)/ ((uint64_t)(AHB_clock)/STK_PRESCALER)) ;
		timeOverFlow_NS = STK_MAX_NUM_OF_TICKS * (timeOfOneCount_NS);
		if(timeUS_NS <= timeOverFlow_NS )
		{
			STK_LOAD = timeUS_NS / timeOfOneCount_NS ;
			overflowsNeededForDesiredT = 0;
		}
		else if (timeUS_NS > timeOverFlow_NS)
		{
			overflowsNeededForDesiredT = timeUS_NS / timeOverFlow_NS ;
			remaining_time = timeUS_NS % timeOverFlow_NS ;
			preload_value = (remaining_time * (STK_MAX_NUM_OF_TICKS - 1))/ timeOverFlow_NS;
			STK_LOAD = preload_value;
			currentOverflowsNeeded = overflowsNeededForDesiredT;
		}
	}

	else if (STK_CLOCK_SRC == FREE_RUNNIG_CLOCK)
	{
		timeOfOneCount_NS = ((uint64_t)(CONV_NUM_FROM_SEC_TO_NS)/ ((uint64_t)(AHB_clock)) ) ;
		timeOverFlow_NS = (2^STK_BIT_RESELUTION) * timeOfOneCount_NS;
		if(timeUS_NS <= timeOverFlow_NS )
		{
			STK_LOAD = timeUS_NS / timeOfOneCount_NS ;
			overflowsNeededForDesiredT = 0;
		}
		else if (timeUS_NS > timeOverFlow_NS)
		{
			overflowsNeededForDesiredT = timeUS_NS / timeOverFlow_NS ;
			remaining_time = timeUS_NS % timeOverFlow_NS ;
			preload_value = (remaining_time * (STK_MAX_NUM_OF_TICKS - 1)) / timeOverFlow_NS;
			STK_LOAD = preload_value;
			currentOverflowsNeeded = overflowsNeededForDesiredT;
		}

	}
}

void SysTick_setCallBack(systickCbf_t cbf)
{
	if (cbf != NULL)
		APP_CBF = cbf;
}

void SysTick_Handler(void)
{
	if (0 == currentOverflowsNeeded)
	{
		currentOverflowsNeeded = overflowsNeededForDesiredT;
		if(currentOverflowsNeeded)
		{
			STK_LOAD = preload_value;
		}
		if (APP_CBF != NULL)
		    APP_CBF();
	}
	else
	{
		STK_LOAD = ((uint64_t)(STK_MAX_NUM_OF_TICKS)) - 1;
		currentOverflowsNeeded--;
	}

}
