#include "../../LIB/STD_TYPES_H.h"
#include "NVIC.h"
#include "../../M3_interface.h"

NVIC_error NVIC_extIntControl(u8 intNumber,u8 enableDisable)
{
	NVIC_error error=NVIC_OK;
	if(intNumber<240)
	{
		if(enableDisable)
		{
			NVIC->ISER[intNumber/32]=((u32)(1<<(intNumber%32)));
		}
		else
		{
			NVIC->ICER[intNumber/32]=((u32)(1<<(intNumber%32)));
		}
	}
	else
	{
		error=NVIC_NOK;
	}
	return error;
}

NVIC_error NVIC_extIntSetPending(u8 intNumber,u8 setCelear)
{
	NVIC_error error=NVIC_OK;
	if(intNumber<240)
	{
		if(setCelear)
		{
			NVIC->ISPR[intNumber/32]=((u32)(1<<(intNumber%32)));
		}
		else
		{
			NVIC->ICPR[intNumber/32]=((u32)(1<<(intNumber%32)));
		}
	}
	else
	{
		error=NVIC_NOK;
	}
	return error;
}

NVIC_error NVIC_extIntSetPriorityLevel(u8 intNumber,u8 priority)
{
	NVIC_error error=NVIC_OK;
	if(intNumber<240)
	{
		NVIC->IP[intNumber]=priority;
	}
	else
	{
		error=NVIC_NOK;
	}
	return error;
}

NVIC_error NVIC_setPriorityGrouping(u8 grouping)
{
	NVIC_error error=NVIC_OK;
	if(grouping<8)
	{
		SCB->AIRCR=((u32)grouping<<SCB_AIRCR_PRIGROUP_Pos)|(SCB->AIRCR&(~SCB_AIRCR_PRIGROUP_Msk));
	}
	else
	{
		error=NVIC_NOK;
	}
	return error;
}

NVIC_error NVIC_extIntGetAvtiveStatus(u8 intNumber,u8* status)
{
	NVIC_error error=NVIC_OK;
	if(intNumber<240)
	{
		*status=(NVIC->IABR[intNumber/32]>>(intNumber%32))&1;
	}
	else
	{
		error=NVIC_NOK;
	}
	return error;
}

void NVIC_allExtIntControl(u8 enableDisable)
{
	if(enableDisable)
	{
		__set_PRIMASK(0);
	}
	else
	{
		__set_PRIMASK(1);
	}
}

void NVIC_allExceptionsControl(u8 enableDisable)
{
	if(enableDisable)
	{
		__set_FAULTMASK(0);
	}
	else
	{
		__set_FAULTMASK(1);
	}
}

void NVIC_extIntMask(u8 mask)
{
	__set_BASEPRI((u32)mask);
}

void NVIC_usageFaultHandlerControl(u8 enableDisable)
{
	if(enableDisable)
	{
		SCB->SHCSR|=SCB_SHCSR_USGFAULTENA_Msk;
	}
	else
	{
		SCB->SHCSR&=~SCB_SHCSR_USGFAULTENA_Msk;
	}
}

void NVIC_busFaultHandlerControl(u8 enableDisable)
{
	if(enableDisable)
	{
		SCB->SHCSR|=SCB_SHCSR_BUSFAULTENA_Msk;
	}
	else
	{
		SCB->SHCSR&=~SCB_SHCSR_BUSFAULTENA_Msk;
	}
}

void NVIC_memoryFaultHandlerControl(u8 enableDisable)
{
	if(enableDisable)
	{
		SCB->SHCSR|=SCB_SHCSR_MEMFAULTENA_Msk;
	}
	else
	{
		SCB->SHCSR&=~SCB_SHCSR_MEMFAULTENA_Msk;
	}
}

u8 NVIC_SVCallGetPending(void)
{
	return ((u8)(SCB->SHCSR>>SCB_SHCSR_SVCALLPENDED_Pos)&1);
}

u8 NVIC_memoryFaultGetPending(void)
{
	return ((u8)(SCB->SHCSR>>SCB_SHCSR_MEMFAULTPENDED_Pos)&1);
}

u8 NVIC_usageFaultGetPending(void)
{
	return ((u8)(SCB->SHCSR>>SCB_SHCSR_USGFAULTPENDED_Pos)&1);
}

u8 NVIC_busFaultGetPending(void)
{
	return ((u8)(SCB->SHCSR>>SCB_SHCSR_BUSFAULTPENDED_Pos)&1);
}

void NVIC_SVCallSetPending(u8 setClear)
{
	if(setClear)
	{
		SCB->SHCSR|=SCB_SHCSR_SVCALLPENDED_Msk;
	}
	else
	{
		SCB->SHCSR&=~SCB_SHCSR_SVCALLPENDED_Msk;
	}
}

void NVIC_memoryFaultSetPending(u8 setClear)
{
	if(setClear)
	{
		SCB->SHCSR|=SCB_SHCSR_MEMFAULTPENDED_Msk;
	}
	else
	{
		SCB->SHCSR&=~SCB_SHCSR_MEMFAULTPENDED_Msk;
	}
}

void NVIC_usageFaultSetPending(u8 setClear)
{
	if(setClear)
	{
		SCB->SHCSR|=SCB_SHCSR_USGFAULTPENDED_Msk;
	}
	else
	{
		SCB->SHCSR&=~SCB_SHCSR_USGFAULTPENDED_Msk;
	}
}

void NVIC_busFaultSetPending(u8 setClear)
{
	if(setClear)
	{
		SCB->SHCSR|=SCB_SHCSR_BUSFAULTPENDED_Msk;
	}
	else
	{
		SCB->SHCSR&=~SCB_SHCSR_BUSFAULTPENDED_Msk;
	}
}

u8 NVIC_SYSTICKGetActiveStatus(void)
{
	return ((u8)(SCB->SHCSR>>SCB_SHCSR_SYSTICKACT_Pos)&1);
}

u8 NVIC_pendSVGetActiveStatus(void)
{
	return ((u8)(SCB->SHCSR>>SCB_SHCSR_PENDSVACT_Pos)&1);
}

u8 NVIC_debugMonitorGetActiveStatus(void)
{
	return ((u8)(SCB->SHCSR>>SCB_SHCSR_MONITORACT_Pos)&1);
}

u8 NVIC_SVCallGetActiveStatus(void)
{
	return ((u8)(SCB->SHCSR>>SCB_SHCSR_SVCALLACT_Pos)&1);
}

u8 NVIC_usageFaultGetActiveStatus(void)
{
	return ((u8)(SCB->SHCSR>>SCB_SHCSR_USGFAULTACT_Pos)&1);
}

u8 NVIC_busFaultGetActiveStatus(void)
{
	return ((u8)(SCB->SHCSR>>SCB_SHCSR_BUSFAULTACT_Pos)&1);
}

u8 NVIC_memoryFaultGetActiveStatus(void)
{
	return ((u8)(SCB->SHCSR>>SCB_SHCSR_MEMFAULTACT_Pos)&1);
}

u8 NVIC_NMIGetPending(void)
{
	return ((u8)(SCB->ICSR>>SCB_ICSR_NMIPENDSET_Pos)&1);
}

void NVIC_NMISetPending(u8 setClear)
{
	if(setClear)
	{
		SCB->ICSR|=SCB_ICSR_NMIPENDSET_Msk;
	}
	else
	{
		SCB->ICSR&=~SCB_ICSR_NMIPENDSET_Msk;
	}
}

u8 NVIC_systemCallGetPending(void)
{
	return ((u8)(SCB->ICSR>>SCB_ICSR_PENDSVSET_Pos)&1);
}

void NVIC_systemCallSetPending(u8 setClear)
{
	if(setClear)
	{
		SCB->ICSR|=SCB_ICSR_PENDSVSET_Msk;
	}
	else
	{
		SCB->ICSR&=~SCB_ICSR_PENDSVSET_Msk;
	}
}

void NVIC_clearPendSVPendingStatus(void)
{
	SCB->ICSR|=SCB_ICSR_PENDSVCLR_Msk;
}

void NVIC_SYSTICKSetPending(u8 setClear)
{
	if(setClear)
	{
		SCB->ICSR|=SCB_ICSR_PENDSTSET_Msk;
	}
	else
	{
		SCB->ICSR|=SCB_ICSR_PENDSTCLR_Msk;
	}
}

u8 NVIC_SYSTICKGetPending(void)
{
	return ((u8)(SCB->ICSR>>SCB_ICSR_PENDSTSET_Pos)&1);
}

u8 NVIC_allExtIntGetPended(void)
{
	return ((u8)(SCB->ICSR>>SCB_ICSR_ISRPENDING_Pos)&1);
}

u8 NVIC_getIfLastException(void)
{
	return ((u8)(SCB->ICSR>>SCB_ICSR_RETTOBASE_Pos)&1);
}

u16 NVIC_getPendedISR(void)
{
	return ((u16)((SCB->ICSR&SCB_ICSR_VECTPENDING_Msk)>>SCB_ICSR_VECTPENDING_Pos));
}

u16 NVIC_getRunningISR(void)
{
	return ((u16)((SCB->ICSR&SCB_ICSR_VECTACTIVE_Msk)>>SCB_ICSR_VECTACTIVE_Pos));
}
