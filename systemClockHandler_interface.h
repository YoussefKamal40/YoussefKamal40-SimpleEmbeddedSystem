/*
 * SwitchHandler_interface.h
 *
 *  Created on: Mar 30, 2020
 *      Author: LENOVO.SXM1
 */

#ifndef SWITCHHANDLER_INTERFACE_H_
#define SWITCHHANDLER_INTERFACE_H_



#pragma pack(4)
typedef struct {
	u32 mode;
	u32	active_state;
	void* port;
	u16 pin;
}switch_type;

#define	NOT_PRESSED_STATE ((u8)0)
#define	PRESSED_STATE ((u8)1)

#define MODE_INPUT_PULL_UP		GPIO_INPUT_PULL_UP_MODE
#define MODE_INPUT_PULL_DOWN	GPIO_INPUT_PULL_DOWN_MODE
#define MODE_INPUT_FLAOTING		GPIO_INPUT_FLOAT_MODE

#define ACTIVE_HIGH		1
#define ACTIVE_LOW		0

#define PIN0	GPIO_PIN_0
#define PIN1	GPIO_PIN_1
#define PIN2	GPIO_PIN_2
#define PIN3	GPIO_PIN_3
#define PIN4	GPIO_PIN_4
#define PIN5	GPIO_PIN_5
#define PIN6	GPIO_PIN_6
#define PIN7	GPIO_PIN_7
#define PIN8	GPIO_PIN_8
#define PIN9	GPIO_PIN_9
#define PIN10	GPIO_PIN_10
#define PIN11	GPIO_PIN_11
#define PIN12	GPIO_PIN_12
#define PIN13	GPIO_PIN_13
#define PIN14	GPIO_PIN_14
#define PIN15	GPIO_PIN_15

#define PORTA	 GPIO_A_PORT
#define PORTB    GPIO_B_PORT
#define PORTC    GPIO_C_PORT
#define PORTD    GPIO_D_PORT
#define PORTE    GPIO_E_PORT
#define PORTF    GPIO_F_PORT
#define PORTG    GPIO_G_PORT

void HSWITCH_debounce_runnable(void);
void HSWITCH_init(void);
u8 HSWITCH_getState(u8 switch_index);



#endif /* SWITCHHANDLER_INTERFACE_H_ */
