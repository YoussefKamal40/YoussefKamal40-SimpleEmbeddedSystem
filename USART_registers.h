#ifndef _USART_REGISTERS_H_
#define _USART_REGISTERS_H_

#define USART_SR_CTS ((u32)0x200)
#define USART_SR_LBD ((u32)0x100)
#define USART_SR_TXE ((u32)0x80)
#define USART_SR_TC ((u32)0x40)
#define USART_SR_RXNE ((u32)0x20)
#define USART_SR_IDLE ((u32)0x10)
#define USART_SR_ORE ((u32)0x8)
#define USART_SR_NE ((u32)0x4)
#define USART_SR_FE ((u32)0x2)
#define USART_SR_PE ((u32)0x1)

#define USART_DR_DR_SETMASK ((u32)0x1ff)
#define USART_DR_DR_CLEARMASK ((u32)0xfffffe00)
#define USART_DR_DR_OFFSET ((u8)0x0)

#define USART_BRR_DIV_Mantissa_SETMASK ((u32)0xfff0)
#define USART_BRR_DIV_Mantissa_CLEARMASK ((u32)0xffff000f)
#define USART_BRR_DIV_Mantissa_OFFSET ((u8)0x4)
#define USART_BRR_DIV_Fraction_SETMASK ((u32)0xf)
#define USART_BRR_DIV_Fraction_CLEARMASK ((u32)0xfffffff0)
#define USART_BRR_DIV_Fraction_OFFSET ((u8)0x0)

#define USART_CR1_UE ((u32)0x2000)
#define USART_CR1_M ((u32)0x1000)
#define USART_CR1_WAKE ((u32)0x800)
#define USART_CR1_PCE ((u32)0x400)
#define USART_CR1_PS ((u32)0x200)
#define USART_CR1_PEIE ((u32)0x100)
#define USART_CR1_TXEIE ((u32)0x80)
#define USART_CR1_TCIE ((u32)0x40)
#define USART_CR1_RXNEIE ((u32)0x20)
#define USART_CR1_IDLEIE ((u32)0x10)
#define USART_CR1_TE ((u32)0x8)
#define USART_CR1_RE ((u32)0x4)
#define USART_CR1_RWU ((u32)0x2)
#define USART_CR1_SBK ((u32)0x1)

#define USART_CR2_LINEN ((u32)0x4000)
#define USART_CR2_STOP_SETMASK ((u32)0x3000)
#define USART_CR2_STOP_CLEARMASK ((u32)0xffffcfff)
#define USART_CR2_STOP_OFFSET ((u8)0xc)
#define USART_CR2_CLKEN ((u32)0x800)
#define USART_CR2_CPOL ((u32)0x400)
#define USART_CR2_CPHA ((u32)0x200)
#define USART_CR2_LBCL ((u32)0x100)
#define USART_CR2_LBDIE ((u32)0x40)
#define USART_CR2_LBDL ((u32)0x20)
#define USART_CR2_ADD_SETMASK ((u32)0xf)
#define USART_CR2_ADD_CLEARMASK ((u32)0xfffffff0)
#define USART_CR2_ADD_OFFSET ((u8)0x0)

#define USART_CR3_CTSIE ((u32)0x400)
#define USART_CR3_CTSE ((u32)0x200)
#define USART_CR3_RTSE ((u32)0x100)
#define USART_CR3_DMAT ((u32)0x80)
#define USART_CR3_DMAR ((u32)0x40)
#define USART_CR3_SCEN ((u32)0x20)
#define USART_CR3_NACK ((u32)0x10)
#define USART_CR3_HDSEL ((u32)0x8)
#define USART_CR3_IRLP ((u32)0x4)
#define USART_CR3_IREN ((u32)0x2)
#define USART_CR3_EIE ((u32)0x1)

#define USART_GTPR_GT_SETMASK ((u32)0xff00)
#define USART_GTPR_GT_CLEARMASK ((u32)0xffff00ff)
#define USART_GTPR_GT_OFFSET ((u8)0x8)
#define USART_GTPR_PSC_SETMASK ((u32)0xff)
#define USART_GTPR_PSC_CLEARMASK ((u32)0xffffff00)
#define USART_GTPR_PSC_OFFSET ((u8)0x0)

typedef struct USARTtype
{
	u32 SR;
	u32 DR;
	u32 BRR;
	u32 CR1;
	u32 CR2;
	u32 CR3;
	u32 GTPR;
}USARTtype;

#endif
