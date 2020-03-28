/*
 * LCD_interface.h
 *
 *  Created on: Mar 28, 2020
 *      Author: LENOVO.SXM1
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

typedef u8 Status_t ;
void LCD_init(void);
void LCD_runnable(void);
Status_t LCD_moveXY(u8 x, u8 y);
Status_t LCD_writeString(const u8 * word, u8 length);
Status_t lcd_applyCommand(u8 cmd);

#define ONE_LINE	0
#define	TWO_LINES	1

#define CUSER_OFF	0
#define CURSER_ON	1
#define BLINKIN_ON	1
#define BLINKIN_OFF 0

#define DISPLAY_OFF	0
#define DISPLAY_ON	1

#define INC_MODE_ON			1
#define INC_MODE_OFF		0

#define NO_DISPLAY_SHIFT	0
#define DISPLAY_SHIFT	1

//#define FOUR_BITS_DATA_LENTGH	0
#define EIGHT_BITS_DATA_LENTGH	1

#define SMALL_FONT	0
#define LARGE_FONT	1

#define SPEED_10M	((u32)0b01)
#define SPEED_2M	((u32)0b10)
#define	SPEED_50M	((u32)0b11)


#define PIN_0 	((u16)0x1)
#define PIN_1 	((u16)0x2)
#define PIN_2 	((u16)0x4)
#define PIN_3 	((u16)0x8)
#define PIN_4 	((u16)0x10)
#define PIN_5 	((u16)0x20)
#define PIN_6 	((u16)0x40)
#define PIN_7 	((u16)0x80)
#define PIN_8 	((u16)0x100)
#define PIN_9 	((u16)0x200)
#define PIN_10 ((u16)0x400)
#define PIN_11 ((u16)0x800)
#define PIN_12 ((u16)0x1000)
#define PIN_13 ((u16)0x2000)
#define PIN_14 ((u16)0x4000)
#define PIN_15 ((u16)0x8000)

#define PORT_A	((void*)0x40010800)
#define PORT_B	((void*)0x40010c00)
#define PORT_C	((void*)0x40011000)
#define PORT_D	((void*)0x40011400)
#define PORT_E	((void*)0x40011800)
#define PORT_F	((void*)0x40011c00)
#define PORT_G	((void*)0x40012000)


#define STATUS_OK		0
#define STATUS_BUSY		1

#endif /* LCD_INTERFACE_H_ */
