/*
 * SysTick.h
 *
 *  Created on: Mar 25, 2020
 *      Author: Esraa
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

/* Systick ClockSrc :  EXTERNAL_REF_CLOCK
 *                     FREE_RUNNIG_CLOCK
 */

/* for st: FREE_RUNNIG_CLOCK  (processor clock AHB)
 *         EXTERNAL_REF_CLOCK (AHB/8)
 */

#define   EXTERNAL_REF_CLOCK            0
#define   FREE_RUNNIG_CLOCK	            1


typedef  void  (*systickCbf_t) (void);

extern void SysTick_init(void);
extern void SysTick_start(void);
extern void SysTick_stop(void);
extern void SysTick_setClockSrc(uint32_t clockSrc);
extern void SysTick_setTime(uint32_t desiredTime_US , uint32_t input_clock);
extern void SysTick_setCallBack(systickCbf_t cbf);



#endif /* SYSTICK_H_ */
