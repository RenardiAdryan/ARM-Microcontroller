/**
  ******************************************************************************
  * @file		lcd20x4.h
  * @author	Yohanes Erwin Setiawan
  * @date		6 February 2016
	* @note		Re-write form Peter Fleury AVR LCD library
  ******************************************************************************
  */
	
#ifndef __lcd20x4_H
#define __lcd20x4_H

#ifdef __cplusplus
extern "C" {
#endif

/** Includes ---------------------------------------------------------------- */
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "delay.h"	 

/** Port and pin definition for 4-bit mode ---------------------------------- */
// LCD control lines (must be on the same port) 
#define lcd20x4_RCC_GPIO_CONTROL	RCC_APB2Periph_GPIOB
#define lcd20x4_GPIO_CONTROL			GPIOB
#define lcd20x4_GPIO_RS						GPIOB
#define lcd20x4_GPIO_RW						GPIOB
#define lcd20x4_GPIO_EN						GPIOB
// LCD data lines (must be on the same port)
#define lcd20x4_RCC_GPIO_DATA			RCC_APB2Periph_GPIOA
#define lcd20x4_GPIO_DATA					GPIOA
#define lcd20x4_GPIO_D4						GPIOA
#define lcd20x4_GPIO_D5						GPIOA
#define lcd20x4_GPIO_D6						GPIOA
#define lcd20x4_GPIO_D7						GPIOA
// Pin definition
#define lcd20x4_PIN_RS	GPIO_Pin_12
#define lcd20x4_PIN_RW	GPIO_Pin_13
#define lcd20x4_PIN_EN	GPIO_Pin_14
#define lcd20x4_PIN_D4	GPIO_Pin_8		// 4-bit mode LSB
#define lcd20x4_PIN_D5	GPIO_Pin_9
#define lcd20x4_PIN_D6	GPIO_Pin_10
#define lcd20x4_PIN_D7	GPIO_Pin_11		// 4-bit mode MSB

/** Display size ------------------------------------------------------------ */
// Number of visible lines of the display (1 or 2)
#define lcd20x4_LINES					2
// Visible characters per line of the display
#define lcd20x4_DISP_LENGTH		16
// DDRAM address of first char of line 1
#define lcd20x4_START_LINE_1	0x00
// DDRAM address of first char of line 2
#define lcd20x4_START_LINE_2	0x40

/** Delay value ------------------------------------------------------------- */
// Delay power on
#define lcd20x4_DELAY_POWER_ON   		16000
// Delay after initialize 8-bit
#define lcd20x4_DELAY_INIT      		5000
// Delay after initialize 8-bit repeated
#define lcd20x4_DELAY_INIT_REP    	64
// Delay after set 4-bit mode
#define lcd20x4_DELAY_INIT_4BIT   	64
// Delay until address counter updated after busy flag is cleared
#define lcd20x4_DELAY_BUSY_FLAG    	4
// Enable pulse width high level
#define lcd20x4_DELAY_ENABLE_PULSE	2

/** Instructions bit location ----------------------------------------------- */
#define lcd20x4_CLEAR_DISPLAY					0x01
#define lcd20x4_CURSOR_HOME						0x02
#define lcd20x4_CHARACTER_ENTRY_MODE	0x04
#define lcd20x4_DISPLAY_CURSOR_ON_OFF	0x08
#define lcd20x4_DISPLAY_CURSOR_SHIFT 	0x10
#define lcd20x4_FUNCTION_SET					0x20
#define lcd20x4_SET_CGRAM_ADDRESS	 		0x40
#define lcd20x4_SET_DDRAM_ADDRESS	 		0x80
/* Character entry mode instructions */
#define lcd20x4_INCREMENT							0x02	// Initialization setting
#define lcd20x4_DECREMENT							0x00
#define lcd20x4_DISPLAY_SHIFT_ON			0x01
#define lcd20x4_DISPLAY_SHIFT_OFF			0x00	// Initialization setting
/* Display cursor on off instructions */
#define lcd20x4_DISPLAY_ON	 					0x04
#define lcd20x4_DISPLAY_OFF	 					0x00	// Initialization setting
#define lcd20x4_CURSOR_UNDERLINE_ON	 	0x02
#define lcd20x4_CURSOR_UNDERLINE_OFF	0x00	// Initialization setting
#define lcd20x4_CURSOR_BLINK_ON	 			0x01
#define lcd20x4_CURSOR_BLINK_OFF	 		0x00	// Initialization setting
/* Display cursor shift instructions */
#define lcd20x4_DISPLAY_SHIFT					0x08
#define lcd20x4_CURSOR_MOVE						0x00
#define lcd20x4_RIGHT_SHIFT						0x04
#define lcd20x4_LEFT_SHIFT						0x00
/* Function set instructions */
#define lcd20x4_8BIT_INTERFACE				0x10	// Initialization setting
#define lcd20x4_4BIT_INTERFACE				0x00
#define lcd20x4_2LINE_MODE						0x08
#define lcd20x4_1LINE_MODE						0x00	// Initialization setting
#define lcd20x4_5X10DOT_FORMAT				0x04
#define lcd20x4_5X7DOT_FORMAT					0x00	// Initialization setting
/* Busy flag bit location */
#define lcd20x4_BUSY_FLAG							0x80

/** LCD display and cursor attributes --------------------------------------- */
#define lcd20x4_DISPLAY_OFF_CURSOR_OFF_BLINK_OFF	(lcd20x4_DISPLAY_OFF | \
	lcd20x4_CURSOR_UNDERLINE_OFF | lcd20x4_CURSOR_BLINK_OFF)
#define lcd20x4_DISPLAY_ON_CURSOR_OFF_BLINK_OFF		(lcd20x4_DISPLAY_ON | \
	lcd20x4_CURSOR_UNDERLINE_OFF | lcd20x4_CURSOR_BLINK_OFF)					
#define lcd20x4_DISPLAY_ON_CURSOR_OFF_BLINK_ON		(lcd20x4_DISPLAY_ON | \
	lcd20x4_CURSOR_UNDERLINE_OFF | lcd20x4_CURSOR_BLINK_ON)
#define lcd20x4_DISPLAY_ON_CURSOR_ON_BLINK_OFF		(lcd20x4_DISPLAY_ON | \
	lcd20x4_CURSOR_UNDERLINE_ON | lcd20x4_CURSOR_BLINK_OFF)
#define lcd20x4_DISPLAY_ON_CURSOR_ON_BLINK_ON		(lcd20x4_DISPLAY_ON | \
	lcd20x4_CURSOR_UNDERLINE_ON | lcd20x4_CURSOR_BLINK_ON)

/** Public function prototypes ---------------------------------------------- */
void lcd20x4_init(uint8_t disp_attr);
void lcd20x4_write_command(uint8_t cmd);
void lcd20x4_write_data(uint8_t data);
void lcd20x4_clrscr(void);
void lcd20x4_home(void);
void lcd20x4_gotoxy(uint8_t x, uint8_t y);
uint8_t lcd20x4_getxy(void);
void lcd20x4_entry_inc(void);
void lcd20x4_entry_dec(void);
void lcd20x4_entry_inc_shift(void);
void lcd20x4_entry_dec_shift(void);
void lcd20x4_display_on(void);
void lcd20x4_display_off(void);
void lcd20x4_cursor_on(void);
void lcd20x4_cursor_off(void);
void lcd20x4_blink_on(void);
void lcd20x4_blink_off(void);
void lcd20x4_display_shift_left(void);
void lcd20x4_display_shift_right(void);
void lcd20x4_cursor_shift_left(void);
void lcd20x4_cursor_shift_right(void);
void lcd20x4_putc(const char c);
void lcd20x4_puts(const char* s);
void lcd20x4_create_custom_char(uint8_t location, uint8_t* data_bytes);
void lcd20x4_put_custom_char(uint8_t x, uint8_t y, uint8_t location);

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
