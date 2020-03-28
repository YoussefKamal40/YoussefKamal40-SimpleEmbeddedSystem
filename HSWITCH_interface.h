/*
 * HSWITCH_interface.h
 *
 *  Created on: Mar 25, 2020
 *      Author: LENOVO.SXM1
 */

#ifndef HSWITCH_INTERFACE_H_
#define HSWITCH_INTERFACE_H_

typedef struct {
	u32 mode;
	u16 pin;
	void* port;
}switch_type;

#define	NOT_PRESSED_STATE ((u8)0)
#define	PRESSED_STATE ((u8)1)

#define MODE_PULL_UP_ACTIVE_LOW			((u32)0b10000)
#define MODE_PULL_DOWN_ACTOVE_HIGH		((u32)0b10001)
#define MODE_INPUT_FLAOTING_ACTIVE_LOW 	((u32)0b01000)
#define MODE_INPUT_FLAOTING_ACTIVE_HIGH	((u32)0b01001)

#define PIN0	((u16)0x1)
#define PIN1	((u16)0x2)
#define PIN2	((u16)0x4)
#define PIN3	((u16)0x8)
#define PIN4	((u16)0x10)
#define PIN5	((u16)0x20)
#define PIN6	((u16)0x40)
#define PIN7	((u16)0x80)
#define PIN8	((u16)0x100)
#define PIN9	((u16)0x200)
#define PIN10	((u16)0x400)
#define PIN11	((u16)0x800)
#define PIN12	((u16)0x1000)
#define PIN13	((u16)0x2000)
#define PIN14	((u16)0x4000)
#define PIN15	((u16)0x8000)

#define PORTA	 ((void*)0x40010800)
#define PORTB    ((void*)0x40010c00)
#define PORTC    ((void*)0x40011000)
#define PORTD    ((void*)0x40011400)
#define PORTE    ((void*)0x40011800)
#define PORTF    ((void*)0x40011c00)
#define PORTG    ((void*)0x40012000)

void HSWITCH_debounce_runnable(void);
void HSWITCH_init(void);
u8 HSWITCH_getState(u8 switch_index);

#endif /* HSWITCH_INTERFACE_H_ */
