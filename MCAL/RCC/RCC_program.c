#include "../../LIB/STD_TYPES_H.h"
#include "RCC_interface.h"

#define RCC_BASE_ADDRESS 0x40021000

#pragma pack(4)
typedef struct RCCType
{
	u32 CR;
	u32 CFGR;
	u32 CIR;
	u32 APB2RSTR;
	u32 APB1RSTR;
	u32 AHBENR;
	u32 APB2ENR;
	u32 APB1ENR;
	u32 BDCR;
	u32 CSR;
}RCCType;

#define RCC ((volatile RCCType*const)RCC_BASE_ADDRESS)

#define RCC_u32_CR_HSION_MASK	((u32)0x0000001)
#define RCC_u32_CR_HSIRDY_MASK	((u32)0x0000002)
#define RCC_u32_CR_HSEON_MASK	((u32)0x0010000)
#define RCC_u32_CR_HSERDY_MASK	((u32)0x0020000)
#define RCC_u32_CR_PLLON_MASK	((u32)0x1000000)
#define RCC_u32_CR_PLLRDY_MASK	((u32)0x2000000)

#define RCC_u32_CFGR_SW_MASK_0		((u32)0xfffffffc)
#define RCC_u32_CFGR_SW_MASK_1		((u32)0x00000003)
#define RCC_u32_CFGR_SWS_MASK		((u32)0x0000000c)
#define RCC_u32_CFGR_HPRE_MASK_1	((u32)0x000000f0)
#define RCC_u32_CFGR_HPRE_MASK_0	((u32)0xffffff0f)
#define RCC_u32_CFGR_PPRE1_MASK_1	((u32)0x00000700)
#define RCC_u32_CFGR_PPRE1_MASK_0	((u32)0xfffff8ff)
#define RCC_u32_CFGR_PPRE2_MASK_1	((u32)0x00003800)
#define RCC_u32_CFGR_PPRE2_MASK_0	((u32)0xffffc7ff)
#define RCC_u32_CFGR_PLLSCR_MASK	((u32)0x00010000)
#define RCC_u32_CFGR_PLLXTPRE_MASK	((u32)0x00020000)
#define RCC_u32_CFGR_PLLMUL_MASK_1	((u32)0x003c0000)
#define RCC_u32_CFGR_PLLMUL_MASK_0	((u32)0xffc3ffff)
#define RCC_u32_CFGR_PLLCFG_MASK_0	((u32)0xffc0ffff)
#define RCC_u32_CFGR_MCO_MASK_1		((u32)0x07000000)
#define RCC_u32_CFGR_MCO_MASK_0		((u32)0xf8ffffff)

#define RCC_u32_APB2RSTR_AFIO_MASK	((u32)0x00000001)
#define RCC_u32_APB2RSTR_IOPA_MASK	((u32)0x00000004)
#define RCC_u32_APB2RSTR_IOPB_MASK	((u32)0x00000008)
#define RCC_u32_APB2RSTR_IOPC_MASK	((u32)0x00000010)

#define RCC_u32_APB2ENR_AFIO_MASK	((u32)0x00000001)
#define RCC_u32_APB2ENR_IOPA_MASK	((u32)0x00000004)
#define RCC_u32_APB2ENR_IOPB_MASK	((u32)0x00000008)
#define RCC_u32_APB2ENR_IOPC_MASK	((u32)0x00000010)

#define RCC_u32_CHECK_MASK					((u32)0xf0000000)
#define RCC_u32_PERIP_CONTROL_CHECK_MASK	((u32)0xc0000000)

#define RCC_u32_CLOCK_CONTROL_CHECK	((u32)0x90000000)
#define RCC_u32_PLL_SOURCE_CHECK	((u32)0xa0000000)
#define RCC_u32_PLL_MULT_CHECK		((u32)0xe0000000)
#define RCC_u32_SYS_SOURCE_CHECK	((u32)0xb0000000)
#define RCC_u32_BUS_PRESCALER_CHECK	((u32)0xd0000000)

#define RCC_u32_AHB_PERIP_CHECK		((u32)0x40000000)
#define RCC_u32_APB1_PERIP_CHECK	((u32)0x80000000)
#define RCC_u32_APB2_PERIP_CHECK	((u32)0xc0000000)

#define RCC_u16_TIMEOUT_CUT_VALUE	((u16)0x0fff)

#define RCC_u8_SW_SWS_BIT_DIFFRENCE	((u8)2)

u8 RCC_u8_ControlClock(u32 clock,u8 enable)
{
	u8 error=RCC_u8_OK;
	u16 timeout=0;
	if((clock&RCC_u32_CHECK_MASK)==RCC_u32_CLOCK_CONTROL_CHECK)
	{
		if(enable)
		{
			RCC->CR|=clock;
			clock=clock<<1;
			while((!(RCC->CR&clock))&&(timeout<RCC_u16_TIMEOUT_CUT_VALUE))
			{
				timeout++;
			}
			if(!(RCC->CR&clock))
			{
				error=RCC_u8_HW_NOK;
			}
		}
		else
		{
			RCC->CR&=~clock;
			clock=clock<<1;
			while((RCC->CR&clock)&&(timeout<RCC_u16_TIMEOUT_CUT_VALUE))
			{
				timeout++;
			}
			if(RCC->CR&clock)
			{
				error=RCC_u8_HW_NOK;
			}
		}
	}
	else
	{
		error=RCC_u8_PARAM_NOK;
	}
	return error;
}
u8 RCC_u8_SelectPLLConfig(u32 source,u32 mult)
{
	u8 error=RCC_u8_OK;
	u32 temp;
	if(((source&RCC_u32_CHECK_MASK)==RCC_u32_PLL_SOURCE_CHECK)&&((mult&RCC_u32_CHECK_MASK)==RCC_u32_PLL_MULT_CHECK))
	{
		temp=RCC->CFGR;
		temp&=RCC_u32_CFGR_PLLCFG_MASK_0;
		temp|=(source|mult);
		RCC->CFGR=temp;
	}
	else
	{
		error=RCC_u8_PARAM_NOK;
	}
	return error;
}

u8 RCC_u8_SelectSystemClock(u32 source)
{
	u8 error=RCC_u8_OK;
	u32 temp;
	u16 timeout=0;
	if((source&RCC_u32_CHECK_MASK)==RCC_u32_SYS_SOURCE_CHECK)
	{
		temp=RCC->CFGR;
		temp&=RCC_u32_CFGR_SW_MASK_0;
		temp|=source;
		RCC->CFGR=temp;
		source&=RCC_u32_CFGR_SW_MASK_1;
		while(((((u32)(RCC->CFGR>>RCC_u8_SW_SWS_BIT_DIFFRENCE))&RCC_u32_CFGR_SW_MASK_1)!=source)&&(timeout<RCC_u16_TIMEOUT_CUT_VALUE))
		{
			timeout++;
		}
		if(((((u32)(RCC->CFGR>>RCC_u8_SW_SWS_BIT_DIFFRENCE))&RCC_u32_CFGR_SW_MASK_1)!=source))
		{
			error=RCC_u8_HW_NOK;
		}
	}
	else
	{
		error=RCC_u8_PARAM_NOK;
	}
	return error;
}

u8 RCC_u8_SelectBusPrescaler(u32 bus,u32 preScaler)
{
	u8 error=RCC_u8_OK;
	u32 temp;
	if((bus&preScaler)==RCC_u32_BUS_PRESCALER_CHECK)
	{
		temp=RCC->CFGR;
		temp&=bus;
		temp|=preScaler;
		RCC->CFGR=temp;
	}
	else
	{
		error=RCC_u8_PARAM_NOK;
	}
	return error;
}
u8 RCC_u8_ControlPrephiral(u32 peripheral,u8 EnableDisable)
{
	u8 error=RCC_u8_OK;
	switch(peripheral&RCC_u32_PERIP_CONTROL_CHECK_MASK)
	{
	case RCC_u32_AHB_PERIP_CHECK:
		if(EnableDisable)
		{
			RCC->AHBENR|=peripheral;
		}
		else
		{
			RCC->AHBENR&=~peripheral;
		}
		break;
	case RCC_u32_APB1_PERIP_CHECK:
		if(EnableDisable)
		{
			RCC->APB1ENR|=peripheral;
		}
		else
		{
			RCC->APB1ENR&=~peripheral;
		}
		break;
	case RCC_u32_APB2_PERIP_CHECK:
		if(EnableDisable)
		{
			RCC->APB2ENR|=peripheral;
		}
		else
		{
			RCC->APB2ENR&=~peripheral;
		}
		break;
	default:
		error=RCC_u8_PARAM_NOK;
	}
	return error;
}
