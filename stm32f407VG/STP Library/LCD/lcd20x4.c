



#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "delay.h"
#include "lcd20x4.h"



/**	
 *------------------------------------------------------------------------
 * 
 *@EditedBY Renardi Adryantoro Priambudi (2210161038) ERSOW 2017 PENS INDONESIA
 *@Source   GITHUB,  Tilen Majerle, 2014
 *@LATEST  2018
 *------------------------------------------------------------------------
*/
GPIO_InitTypeDef GPIO_Initstruct;
typedef struct {
	uint8_t DisplayControl;
	uint8_t DisplayFunction;
	uint8_t DisplayMode;
	uint8_t Rows;
	uint8_t Cols;
	uint8_t currentX;
	uint8_t currentY;
} HD44780_Options_t;

/* Private functions */
static void lcd_initPins(void);
static void lcd_Cmd(uint8_t cmd);
static void lcd_Cmd4bit(uint8_t cmd);
static void lcd_Data(uint8_t data);
void lcd_gotoxy(uint8_t col, uint8_t row);

/* Private variable */
static HD44780_Options_t HD44780_Opts;


void lcd_init(uint8_t cols, uint8_t rows) {
	/* Initialize delay */
	DELAY_Init();
	
	/* Init pinout */
	lcd_initPins();
	
	/* At least 40ms */
	DELAY_Us(45000);
	
	/* Set LCD width and height */
	HD44780_Opts.Rows = rows;
	HD44780_Opts.Cols = cols;
	
	/* Set cursor pointer to beginning for LCD */
	HD44780_Opts.currentX = 0;
	HD44780_Opts.currentY = 0;
	
	HD44780_Opts.DisplayFunction = HD44780_4BITMODE | HD44780_5x8DOTS | HD44780_1LINE;
	if (rows > 1) {
		HD44780_Opts.DisplayFunction |= HD44780_2LINE;
	}
	
	/* Try to set 4bit mode */
	lcd_Cmd4bit(0x03);
	DELAY_Us(4500);
	
	/* Second try */
	lcd_Cmd4bit(0x03);
		DELAY_Us(4500);
	
	/* Third goo! */
	lcd_Cmd4bit(0x03);
		DELAY_Us(4500);	
	
	/* Set 4-bit interface */
	lcd_Cmd4bit(0x02);
		DELAY_Us(100);
	
	/* Set # lines, font size, etc. */
	lcd_Cmd(HD44780_FUNCTIONSET | HD44780_Opts.DisplayFunction);

	/* Turn the display on with no cursor or blinking default */
	HD44780_Opts.DisplayControl = HD44780_DISPLAYON;
	lcd_DisplayOn();

	/* Clear lcd */
	lcd_clear();

	/* Default font directions */
	HD44780_Opts.DisplayMode = HD44780_ENTRYLEFT | HD44780_ENTRYSHIFTDECREMENT;
	lcd_Cmd(HD44780_ENTRYMODESET | HD44780_Opts.DisplayMode);

	/* Delay */
		DELAY_Us(4500);
}

void lcd_clear(void) {
	lcd_Cmd(HD44780_CLEARDISPLAY);
	DELAY_Us(3000);
}

void lcd_putsxy(uint8_t x, uint8_t y, char* str) {
	lcd_gotoxy(x, y);
	while (*str) {
		if (HD44780_Opts.currentX >= HD44780_Opts.Cols) {
			HD44780_Opts.currentX = 0;
			HD44780_Opts.currentY++;
			lcd_gotoxy(HD44780_Opts.currentX, HD44780_Opts.currentY);
		}
		if (*str == '\n') {
			HD44780_Opts.currentY++;
			//lcd_gotoxy(HD44780_Opts.currentX, HD44780_Opts.currentY);
			lcd_gotoxy(0, HD44780_Opts.currentY);
		}// else if (*str == '\r') {
			//lcd_gotoxy(0, HD44780_Opts.currentY);} 
		else {
			lcd_Data(*str);
			HD44780_Opts.currentX++;
		}
		str++;
	}
}

void lcd_puts(char* str){
		while (*str) {
		if (HD44780_Opts.currentX >= HD44780_Opts.Cols) {
			HD44780_Opts.currentX = 0;
			HD44780_Opts.currentY++;
			lcd_gotoxy(HD44780_Opts.currentX, HD44780_Opts.currentY);
		}
		
			if (*str == '\n') {
			HD44780_Opts.currentY++;
			//lcd_gotoxy(HD44780_Opts.currentX, HD44780_Opts.currentY);
			lcd_gotoxy(0, HD44780_Opts.currentY);
		}// else if (*str == '\r') {
			//lcd_gotoxy(0, HD44780_Opts.currentY);} 
		else {
			lcd_Data(*str);
			HD44780_Opts.currentX++;
		}
		str++;
	}
}

void lcd_DisplayOn(void) {
	HD44780_Opts.DisplayControl |= HD44780_DISPLAYON;
	lcd_Cmd(HD44780_DISPLAYCONTROL | HD44780_Opts.DisplayControl);
}

void lcd_DisplayOff(void) {
	HD44780_Opts.DisplayControl &= ~HD44780_DISPLAYON;
	lcd_Cmd(HD44780_DISPLAYCONTROL | HD44780_Opts.DisplayControl);
}

void lcd_BlinkOn(void) {
	HD44780_Opts.DisplayControl |= HD44780_BLINKON;
	lcd_Cmd(HD44780_DISPLAYCONTROL | HD44780_Opts.DisplayControl);
}

void lcd_BlinkOff(void) {
	HD44780_Opts.DisplayControl &= ~HD44780_BLINKON;
	lcd_Cmd(HD44780_DISPLAYCONTROL | HD44780_Opts.DisplayControl);
}

void lcd_CursorOn(void) {
	HD44780_Opts.DisplayControl |= HD44780_CURSORON;
	lcd_Cmd(HD44780_DISPLAYCONTROL | HD44780_Opts.DisplayControl);
}

void lcd_CursorOff(void) {
	HD44780_Opts.DisplayControl &= ~HD44780_CURSORON;
	lcd_Cmd(HD44780_DISPLAYCONTROL | HD44780_Opts.DisplayControl);
}

void lcd_ScrollLeft(void) {
	lcd_Cmd(HD44780_CURSORSHIFT | HD44780_DISPLAYMOVE | HD44780_MOVELEFT);
}

void lcd_ScrollRight(void) {
	lcd_Cmd(HD44780_CURSORSHIFT | HD44780_DISPLAYMOVE | HD44780_MOVERIGHT);
}

void lcd_CreateChar(uint8_t location, uint8_t *data) {
	uint8_t i;
	/* We have 8 locations available for custom characters */
	location &= 0x07;
	lcd_Cmd(HD44780_SETCGRAMADDR | (location << 3));
	
	for (i = 0; i < 8; i++) {
		lcd_Data(data[i]);
	}
}

void lcd_PutCustom(uint8_t x, uint8_t y, uint8_t location) {
	lcd_gotoxy(x, y);
	lcd_Data(location);
}

/* Private functions */
void lcd_Cmd(uint8_t cmd) {
	/* Command mode */
  GPIO_SetPinLow(RS_PORT,RS_PIN);
	
	/* High nibble */
	lcd_Cmd4bit(cmd >> 4);
	/* Low nibble */
	lcd_Cmd4bit(cmd & 0x0F);
}

void lcd_Data(uint8_t data) {
	/* Data mode */
	
	GPIO_SetPinHigh(RS_PORT,RS_PIN);
	
	/* High nibble */
	lcd_Cmd4bit(data >> 4);
	/* Low nibble */
	lcd_Cmd4bit(data & 0x0F);
}

void lcd_Cmd4bit(uint8_t cmd) {
	/* Set output port */
	GPIO_SetPinValue(HD44780_D7_PORT, HD44780_D7_PIN, (cmd & 0x08));
	GPIO_SetPinValue(HD44780_D6_PORT, HD44780_D6_PIN, (cmd & 0x04));
	GPIO_SetPinValue(HD44780_D5_PORT, HD44780_D5_PIN, (cmd & 0x02));
	GPIO_SetPinValue(HD44780_D4_PORT, HD44780_D4_PIN, (cmd & 0x01));
	HD44780_E_BLINK;
}

void lcd_gotoxy(uint8_t col, uint8_t row) {
	uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};
	
	/* Go to beginning */
	if (row >= HD44780_Opts.Rows) {
		row = 0;
	}
	
	/* Set current column and row */
	HD44780_Opts.currentX = col;
	HD44780_Opts.currentY = row;
	
	/* Set location address */
	lcd_Cmd(HD44780_SETDDRAMADDR | (col + row_offsets[row]));
}

void lcd_initPins(void) {
	/* Init all pins */

RCC_AHB1PeriphClockCmd(LCD_RCC_control ,ENABLE);
GPIO_Initstruct.GPIO_Mode=GPIO_Mode_OUT;
GPIO_Initstruct.GPIO_Speed=GPIO_Speed_2MHz;
GPIO_Initstruct.GPIO_OType=GPIO_OType_PP;
GPIO_Initstruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Initstruct.GPIO_Pin= RS_PIN| HD44780_E_PIN;
GPIO_Init(LCD_Control,&GPIO_Initstruct);

RCC_AHB1PeriphClockCmd(LCD_RCC_Data,ENABLE);
GPIO_Initstruct.GPIO_Mode=GPIO_Mode_OUT;
GPIO_Initstruct.GPIO_Speed=GPIO_Speed_2MHz;
GPIO_Initstruct.GPIO_OType=GPIO_OType_PP;
GPIO_Initstruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Initstruct.GPIO_Pin= HD44780_D4_PIN| HD44780_D5_PIN|HD44780_D6_PIN|HD44780_D7_PIN;
GPIO_Init(LCD_Data,&GPIO_Initstruct);


	/* Set pins low */
	GPIO_SetPinLow(RS_PORT,RS_PIN);
	GPIO_SetPinLow(HD44780_E_PORT, HD44780_E_PIN);
	GPIO_SetPinLow(HD44780_D4_PORT, HD44780_D4_PIN);
	GPIO_SetPinLow(HD44780_D5_PORT, HD44780_D5_PIN	);
	GPIO_SetPinLow(HD44780_D6_PORT, HD44780_D6_PIN);
	GPIO_SetPinLow(HD44780_D7_PORT, HD44780_D7_PIN);
}


