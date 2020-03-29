/*
 * LCD_interface.h
 *
 *  Created on: Mar 28, 2020
 *      Author: sarah
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

#define SPEED_10M	GPIO_10M_SPEED
#define SPEED_2M	GPIO_2M_SPEED
#define	SPEED_50M	GPIO_50M_SPEED

/*commands*/

#define PIN_0 	GPIO_PIN_0
#define PIN_1 	GPIO_PIN_1
#define PIN_2 	GPIO_PIN_2
#define PIN_3 	GPIO_PIN_3
#define PIN_4 	GPIO_PIN_4
#define PIN_5 	GPIO_PIN_5
#define PIN_6 	GPIO_PIN_6
#define PIN_7 	GPIO_PIN_7
#define PIN_8 	GPIO_PIN_8
#define PIN_9 	GPIO_PIN_9
#define PIN_10  GPIO_PIN_10
#define PIN_11  GPIO_PIN_11
#define PIN_12  GPIO_PIN_12
#define PIN_13  GPIO_PIN_13
#define PIN_14  GPIO_PIN_14
#define PIN_15  GPIO_PIN_15

#define PORT_A	GPIO_A_PORT
#define PORT_B	GPIO_B_PORT
#define PORT_C	GPIO_C_PORT
#define PORT_D	GPIO_D_PORT
#define PORT_E	GPIO_E_PORT
#define PORT_F	GPIO_F_PORT
#define PORT_G	GPIO_G_PORT

#define STATUS_OK		0
#define STATUS_BUSY		1

#endif /* LCD_INTERFACE_H_ */
