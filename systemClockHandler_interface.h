#ifndef SYSTEMCLOCKHANDLER_INTERFACE_H_
#define SYSTEMCLOCKHANDLER_INTERFACE_H_

#define SYS_HAN_CLOCK_72MHz 72000000
#define SYS_HAN_CLOCK_48MHz 48000000
#define SYS_HAN_CLOCK_36MHz 36000000
#define SYS_HAN_CLOCK_24MHz 24000000
#define SYS_HAN_CLOCK_16MHz 16000000
#define SYS_HAN_CLOCK_12MHz 12000000
#define SYS_HAN_CLOCK_8MHz  8000000
#define SYS_HAN_CLOCK_4MHz  4000000
#define SYS_HAN_CLOCK_NONE	0

#define SYS_HAN_OK ((SYS_error)0)
#define SYS_HAN_NOK ((SYS_error)1)

typedef u8 SYS_error;

SYS_error SYS_HAN_setSystemClock(u32 clock);
u32 SYS_HAN_getSystemClock(void);
SYS_error SYS_HAN_setAHBClock(u32 clock);
u32 SYS_HAN_getAHBClock(void);
SYS_error SYS_HAN_setAPB1Clock(u32 clock);
u32 SYS_HAN_getAPB1Clock(void);
SYS_error SYS_HAN_setAPB2Clock(u32 clock);
u32 SYS_HAN_getAPB2Clock(void);

#endif /* SYSTEMCLOCKHANDLER_INTERFACE_H_ */
