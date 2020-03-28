/*
 * LCD_config.h
 *
 *  Created on: Mar 28, 2020
 *      Author: LENOVO.SXM1
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

#define NUMBER_OF_LINES		        TWO_LINES
#define CURSER				        CURSER_ON
#define BLINKING			        BLINKIN_OFF
#define FONT				        SMALL_FONT
#define DATA_LENGTH			        EIGHT_BITS_DATA_LENTGH
#define DISPLAY				        DISPLAY_ON
#define PINS_SPEED			        SPEED_50M
#define INC_MODE			        INC_MODE_ON
#define DISPLAY_SHIFT_OPERATION	    NO_DISPLAY_SHIFT

#define LCD_RS_PORT		 GPIO_A_PORT
#define LCD_RS_PIN  	 PIN_8
#define LCD_RW_PORT		 GPIO_A_PORT
#define LCD_RW_PIN  	 PIN_9
#define LCD_E_PORT 	     GPIO_A_PORT
#define LCD_E_PIN  		 PIN_10

#define LCD_D0_PORT		 GPIO_A_PORT
#define LCD_D0_PIN       PIN_0
#define LCD_D1_PORT	     GPIO_A_PORT
#define LCD_D1_PIN		 PIN_1
#define LCD_D2_PORT      GPIO_A_PORT
#define LCD_D2_PIN       PIN_2
#define LCD_D3_PORT      GPIO_A_PORT
#define LCD_D3_PIN       PIN_3
#define LCD_D4_PORT      GPIO_A_PORT
#define LCD_D4_PIN       PIN_4
#define LCD_D5_PORT      GPIO_A_PORT
#define LCD_D5_PIN       PIN_5
#define LCD_D6_PORT      GPIO_A_PORT
#define LCD_D6_PIN       PIN_6
#define LCD_D7_PORT      GPIO_A_PORT
#define LCD_D7_PIN       PIN_7

#endif /* LCD_CONFIG_H_ */
