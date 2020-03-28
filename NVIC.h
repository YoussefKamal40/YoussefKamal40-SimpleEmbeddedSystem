#ifndef NVIC_H_
#define NVIC_H_

#define NVIC_ENABLE ((u8)1)
#define NVIC_DISABLE ((u8)0)

#define NVIC_SET ((u8)1)
#define NVIC_CLEAR ((u8)0)

#define NVIC_ACTIVE ((u8)1)
#define NVIC_NACTIVE ((u8)0)

#define NVIC_PENDED ((u8)1)
#define NVIC_NPENDED ((u8)0)

#define NVIC_OK ((u8)1)
#define NVIC_NOK ((u8)1)

typedef u8 NVIC_error;

NVIC_error NVIC_extIntControl(u8 intNumber,u8 enableDisable);
NVIC_error NVIC_extIntSetPending(u8 intNumber,u8 setClear);
NVIC_error NVIC_extIntSetPriorityLevel(u8 intNumber,u8 priority);
NVIC_error NVIC_setPriorityGrouping(u8 grouping);
NVIC_error NVIC_extIntGetAvtiveStatus(u8 intNumber,u8* status);
void NVIC_allExtIntControl(u8 enableDisable);
void NVIC_allExceptionsControl(u8 enableDisable);
void NVIC_extIntMask(u8 mask);
void NVIC_usageFaultHandlerControl(u8 enableDisable);
void NVIC_busFaultHandlerControl(u8 enableDisable);
void NVIC_memoryFaultHandlerControl(u8 enableDisable);
u8 NVIC_SVCallGetPending(void);
u8 NVIC_memoryFaultGetPending(void);
u8 NVIC_usageFaultGetPending(void);
u8 NVIC_busFaultGetPending(void);
void NVIC_SVCallSetPending(u8 setClear);
void NVIC_memoryFaultSetPending(u8 setClear);
void NVIC_usageFaultSetPending(u8 setClear);
void NVIC_busFaultSetPending(u8 setClear);
u8 NVIC_SYSTICKGetActiveStatus(void);
u8 NVIC_pendSVGetActiveStatus(void);
u8 NVIC_debugMonitorGetActiveStatus(void);
u8 NVIC_SVCallGetActiveStatus(void);
u8 NVIC_usageFaultGetActiveStatus(void);
u8 NVIC_busFaultGetActiveStatus(void);
u8 NVIC_memoryFaultGetActiveStatus(void);
u8 NVIC_NMIGetPending(void);
void NVIC_NMISetPending(u8 setClear);
u8 NVIC_systemCallGetPending(void);
void NVIC_systemCallSetPending(u8 setClear);
void NVIC_clearPendSVPendingStatus(void);
void NVIC_SYSTICKSetPending(u8 setClear);
u8 NVIC_SYSTICKGetPending(void);
u8 NVIC_allExtIntGetPended(void);
u8 NVIC_getIfLastException(void);
u16 NVIC_getPendedISR(void);
u16 NVIC_getRunningISR(void);

#endif /* NVIC_H_ */
