#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_

#define RCC_u8_OK			((u8)0)
#define RCC_u8_PARAM_NOK	((u8)1)
#define RCC_u8_HW_NOK		((u8)2)

#define RCC_u32_CLOCK_CONTROL_HSI	((u32)0x90000001)
#define RCC_u32_CLOCK_CONTROL_HSE	((u32)0x90010000)
#define RCC_u32_CLOCK_CONTROL_PLL	((u32)0x91000000)

#define RCC_u8_ENABLE		((u8)1)
#define RCC_u8_DISABLE		((u8)0)

#define RCC_u32_HSI_BY2_PLL_SOURCE	((u32)0xa0000000)
#define RCC_u32_HSE_BY2_PLL_SOURCE	((u32)0xa0030000)
#define RCC_u32_HSE_PLL_SOURCE		((u32)0xa0010000)

#define RCC_u32_2_PLL_MULT	((u32)0xe0000000)
#define RCC_u32_3_PLL_MULT	((u32)0xe0040000)
#define RCC_u32_4_PLL_MULT	((u32)0xe0080000)
#define RCC_u32_5_PLL_MULT	((u32)0xe00c0000)
#define RCC_u32_6_PLL_MULT	((u32)0xe0100000)
#define RCC_u32_7_PLL_MULT	((u32)0xe0140000)
#define RCC_u32_8_PLL_MULT	((u32)0xe0180000)
#define RCC_u32_9_PLL_MULT	((u32)0xe01c0000)
#define RCC_u32_10_PLL_MULT	((u32)0xe0200000)
#define RCC_u32_11_PLL_MULT	((u32)0xe0240000)
#define RCC_u32_12_PLL_MULT	((u32)0xe0280000)
#define RCC_u32_13_PLL_MULT	((u32)0xe02c0000)
#define RCC_u32_14_PLL_MULT	((u32)0xe0300000)
#define RCC_u32_15_PLL_MULT	((u32)0xe0340000)
#define RCC_u32_16_PLL_MULT	((u32)0xe0380000)

#define RCC_u32_HSI_SYS_SOURCE	((u32)0xb0000000)
#define RCC_u32_HSE_SYS_SOURCE	((u32)0xb0000001)
#define RCC_u32_PLL_SYS_SOURCE	((u32)0xb0000002)

#define RCC_u32_AHB_BUS		((u32)0xdfffff0f)
#define RCC_u32_APB1_BUS	((u32)0xdffff8ff)
#define RCC_u32_APB2_BUS	((u32)0xdfffc7ff)

#define RCC_u32_0_AHB_PRESCALER		((u32)0xd0000000)
#define RCC_u32_2_AHB_PRESCALER		((u32)0xd0000080)
#define RCC_u32_4_AHB_PRESCALER		((u32)0xd0000090)
#define RCC_u32_8_AHB_PRESCALER		((u32)0xd00000a0)
#define RCC_u32_16_AHB_PRESCALER	((u32)0xd00000b0)
#define RCC_u32_64_AHB_PRESCALER	((u32)0xd00000c0)
#define RCC_u32_128_AHB_PRESCALER	((u32)0xd00000d0)
#define RCC_u32_256_AHB_PRESCALER	((u32)0xd00000e0)
#define RCC_u32_512_AHB_PRESCALER	((u32)0xd00000f0)

#define RCC_u32_0_APB1_PRESCALER	((u32)0xd0000000)
#define RCC_u32_2_APB1_PRESCALER	((u32)0xd0000400)
#define RCC_u32_4_APB1_PRESCALER	((u32)0xd0000500)
#define RCC_u32_8_APB1_PRESCALER	((u32)0xd0000600)
#define RCC_u32_16_APB1_PRESCALER	((u32)0xd0000700)

#define RCC_u32_0_APB2_PRESCALER	((u32)0xd0000000)
#define RCC_u32_2_APB2_PRESCALER	((u32)0xd0002000)
#define RCC_u32_4_APB2_PRESCALER	((u32)0xd0002800)
#define RCC_u32_8_APB2_PRESCALER	((u32)0xd0003000)
#define RCC_u32_16_APB2_PRESCALER	((u32)0xd0003800)

#define RCC_u32_AFIO_PERIP	((u32)0xc0000001)
#define RCC_u32_GIOPA_PERIP	((u32)0xc0000004)
#define RCC_u32_GIOPB_PERIP	((u32)0xc0000008)
#define RCC_u32_GIOPC_PERIP	((u32)0xc0000010)

u8 RCC_u8_ControlClock(u32 clock,u8 enable);
u8 RCC_u8_SelectPLLConfig(u32 source,u32 mult);
u8 RCC_u8_SelectSystemClock(u32 source);
u8 RCC_u8_SelectBusPrescaler(u32 bus,u32 preScaler);
u8 RCC_u8_ControlPrephiral(u32 peripheral,u8 enable);

#endif /* RCC_INTERFACE_H_ */
