/**
  ******************************************************************************
  * @file					lcd20x4.c
	* @author 			Renardi Adryantoro P (2210161038) CE 2016 PENS [ERSOW]
  * @authorsource	Yohanes Erwin Setiawan
  * @date					12 Desember 2017
	* @note					Re-write form Peter Fleury AVR LCD library
  ******************************************************************************
  */

/** Includes s---------------------------------------------------------------- */
#include "lcd20x4.h"

/** Private function prototypes --------------------------------------------- */
static void lcd20x4_toggle_e(void);
static void lcd20x4_write(uint8_t data, uint8_t rs);
static uint8_t lcd20x4_read(uint8_t rs);
static uint8_t lcd20x4_wait_busy(void);
static void lcd20x4_new_line(uint8_t pos);

static uint8_t display_cursor_on_off_control;
GPIO_InitTypeDef GPIO_InitStruct;

/** Public functions -------------------------------------------------------- */
/**
  ******************************************************************************
  * @brief	Initialize the LCD 16x2 with 4-bit I/O mode.
  * @param	Display, cursor underline, and cursor blink settings. See
  * 				LCD display and cursor attributes define in lcd20x4.h file.
  * @retval	None
  ******************************************************************************
  */
void lcd20x4_init(uint8_t disp_attr)
{
	// Delay initialization
	DelayInit();
	
	// GPIO clock for control and data lines
	RCC_APB2PeriphClockCmd(lcd20x4_RCC_GPIO_CONTROL, ENABLE);
	RCC_APB2PeriphClockCmd(lcd20x4_RCC_GPIO_DATA, ENABLE);
	
	// Configure I/O for control lines as output
	GPIO_InitStruct.GPIO_Pin = lcd20x4_PIN_RS | lcd20x4_PIN_RW | 
		lcd20x4_PIN_EN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(lcd20x4_GPIO_CONTROL, &GPIO_InitStruct);
	
	// Configure I/O for data lines as output
	GPIO_InitStruct.GPIO_Pin = lcd20x4_PIN_D4 | lcd20x4_PIN_D5 | 
	lcd20x4_PIN_D6 | lcd20x4_PIN_D7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(lcd20x4_GPIO_DATA, &GPIO_InitStruct);

	// Delay power on 
	DelayUs(lcd20x4_DELAY_POWER_ON);
	
	// Initialize 8-bit mode first
	lcd20x4_GPIO_D5->BSRR = lcd20x4_PIN_D5;	// Function set
	lcd20x4_GPIO_D4->BSRR = lcd20x4_PIN_D4;	// 8-bit mode
	lcd20x4_toggle_e();
	// Delay, busy flag can't be checked here
	DelayUs(lcd20x4_DELAY_INIT);
	
	// Repeat last command
	lcd20x4_toggle_e();
	// Delay, busy flag can't be checked here
	DelayUs(lcd20x4_DELAY_INIT_REP);
	
	// Repeat last command for third time
	lcd20x4_toggle_e();
	// Delay, busy flag can't be checked here
	DelayUs(lcd20x4_DELAY_INIT_REP);
	
	// Initialize 4-bit mode
	lcd20x4_GPIO_D5->BSRR = lcd20x4_PIN_D5;	// Function set
	lcd20x4_GPIO_D4->BRR = lcd20x4_PIN_D4;	// 4-bit mode
	lcd20x4_toggle_e();
	DelayUs(lcd20x4_DELAY_INIT_4BIT);
	
	/* From now the LCD only accepts 4 bit I/O */
	
	// 4-bit interface, 2 lines, 5x7 dot format font
	lcd20x4_write_command(lcd20x4_FUNCTION_SET | lcd20x4_4BIT_INTERFACE | 
		lcd20x4_2LINE_MODE | lcd20x4_5X7DOT_FORMAT);
	// Display off
	lcd20x4_write_command(lcd20x4_DISPLAY_CURSOR_ON_OFF | lcd20x4_DISPLAY_OFF);
	// Clear screen
	lcd20x4_clrscr();
	// Entry mode
	lcd20x4_entry_inc();
	// Display cursor on off
	display_cursor_on_off_control = disp_attr;
	lcd20x4_write_command(lcd20x4_DISPLAY_CURSOR_ON_OFF | 
		display_cursor_on_off_control);
}

/**
  ******************************************************************************
  * @brief	Write a command to the LCD.
  * @param	The LCD instructions set.
  * @retval	None
  ******************************************************************************
  */
void lcd20x4_write_command(uint8_t cmd)
{
	lcd20x4_wait_busy();
	lcd20x4_write(cmd, 0);
}

/**
  ******************************************************************************
  * @brief	Write a data byte to the LCD.
  * @param	Data which want to written to the LCD.
  * @retval	None
  ******************************************************************************
  */
void lcd20x4_write_data(uint8_t data)
{
	lcd20x4_wait_busy();
	lcd20x4_write(data, 1);
}

/**
  ******************************************************************************
  * @brief	Clear the LCD display and return cursor to home position.
  * @param	None
  * @retval	None
  ******************************************************************************
  */
void lcd20x4_clrscr()
{
	lcd20x4_write_command(lcd20x4_CLEAR_DISPLAY);
}

/**
  ******************************************************************************
  * @brief	Return cursor to home position.
  * @param	None
  * @retval	None
  ******************************************************************************
  */
void lcd20x4_home()
{
	lcd20x4_write_command(lcd20x4_CURSOR_HOME);	
}

/**
  ******************************************************************************
  * @brief	Set LCD cursor to specific position.
  * @param	LCD column (x)
  * @param	LCD row (y)
  * @retval	None
  ******************************************************************************
  */
char addr;int wow;
void lcd20x4_gotoxy(uint8_t x, uint8_t y)
{		
#if lcd20x4_LINES == 1 
	lcd20x4_write_command(lcd20x4_SET_DDRAM_ADDRESS |
		(lcd20x4_START_LINE_1 + x));
#elif lcd20x4_LINES == 2
	
	if (y == 0)
		lcd20x4_write_command(lcd20x4_SET_DDRAM_ADDRESS | 
			(lcd20x4_START_LINE_1 + x));
	else if (y == 1)
		lcd20x4_write_command(lcd20x4_SET_DDRAM_ADDRESS | 
			(lcd20x4_START_LINE_2 + x));
		else if (y == 2)
		lcd20x4_write_command(lcd20x4_SET_DDRAM_ADDRESS | 
			(lcd20x4_START_LINE_1 +20 + x));
			else if (y == 3)
		lcd20x4_write_command(lcd20x4_SET_DDRAM_ADDRESS | 
			(lcd20x4_START_LINE_2+20 + x));
			wow=y;
#endif
}
	


/**
  ******************************************************************************
  * @brief	Get LCD cursor/ DDRAM address.
  * @param	None
  * @retval	LCD cursor/ DDRAM address.
  ******************************************************************************
  */
uint8_t lcd20x4_getxy()
{
	return lcd20x4_wait_busy();
}

/**
  ******************************************************************************
  * @brief	Set LCD entry mode: increment cursor.
  * @param	None
  * @retval	None
  ******************************************************************************
  */
void lcd20x4_entry_inc()
{
	lcd20x4_write_command(lcd20x4_CHARACTER_ENTRY_MODE | lcd20x4_INCREMENT |
		lcd20x4_DISPLAY_SHIFT_OFF);
}

/**
  ******************************************************************************
  * @brief	Set LCD entry mode: decrement cursor.
  * @param	None
  * @retval	None
  ******************************************************************************
  */
void lcd20x4_entry_dec()
{
	lcd20x4_write_command(lcd20x4_CHARACTER_ENTRY_MODE | lcd20x4_DECREMENT |
		lcd20x4_DISPLAY_SHIFT_OFF);
}

/**
  ******************************************************************************
  * @brief	Set LCD entry mode: increment cursor and shift character to left.
  * @param	None
  * @retval	None
  ******************************************************************************
  */
void lcd20x4_entry_inc_shift()
{
	lcd20x4_write_command(lcd20x4_CHARACTER_ENTRY_MODE | lcd20x4_INCREMENT |
		lcd20x4_DISPLAY_SHIFT_ON);
}

/**
  ******************************************************************************
  * @brief	Set LCD entry mode: decrement cursor and shift character to right.
  * @param	None
  * @retval	None
  ******************************************************************************
  */
void lcd20x4_entry_dec_shift()
{
	lcd20x4_write_command(lcd20x4_CHARACTER_ENTRY_MODE | lcd20x4_DECREMENT |
		lcd20x4_DISPLAY_SHIFT_ON);
}

/**
  ******************************************************************************
  * @brief	Turn on display (can see character(s) on display).
  * @param	None
  * @retval	None
  ******************************************************************************
  */
void lcd20x4_display_on()
{
	display_cursor_on_off_control |= lcd20x4_DISPLAY_ON;
	lcd20x4_write_command(lcd20x4_DISPLAY_CURSOR_ON_OFF | 
		display_cursor_on_off_control);	
}

/**
  ******************************************************************************
  * @brief	Turn off display (blank/ can't see character(s) on display).
  * @param	None
  * @retval	None
  ******************************************************************************
  */
void lcd20x4_display_off()
{
	display_cursor_on_off_control &= ~lcd20x4_DISPLAY_ON;
	lcd20x4_write_command(lcd20x4_DISPLAY_CURSOR_ON_OFF | 
		display_cursor_on_off_control);	
}

/**
  ******************************************************************************
  * @brief	Turn on underline cursor.
  * @param	None
  * @retval	None
  ******************************************************************************
  */
void lcd20x4_cursor_on()
{
	display_cursor_on_off_control |= lcd20x4_CURSOR_UNDERLINE_ON; 	
	lcd20x4_write_command(lcd20x4_DISPLAY_CURSOR_ON_OFF | 
		display_cursor_on_off_control);
}

/**
  ******************************************************************************
  * @brief	Turn off underline cursor.
  * @param	None
  * @retval	None
  ******************************************************************************
  */
void lcd20x4_cursor_off()
{
	display_cursor_on_off_control &= ~lcd20x4_CURSOR_UNDERLINE_ON;
	lcd20x4_write_command(lcd20x4_DISPLAY_CURSOR_ON_OFF | 
		display_cursor_on_off_control);
}

/**
  ******************************************************************************
  * @brief	Turn on blinking cursor.
  * @param	None
  * @retval	None
  ******************************************************************************
  */
void lcd20x4_blink_on()
{
	display_cursor_on_off_control |= lcd20x4_CURSOR_BLINK_ON;
	lcd20x4_write_command(lcd20x4_DISPLAY_CURSOR_ON_OFF | 
		display_cursor_on_off_control);
}

/**
  ******************************************************************************
  * @brief	Turn off blinking cursor.
  * @param	None
  * @retval	None
  ******************************************************************************
  */
void lcd20x4_blink_off()
{
	display_cursor_on_off_control &= ~lcd20x4_CURSOR_BLINK_ON;
	lcd20x4_write_command(lcd20x4_DISPLAY_CURSOR_ON_OFF | 
		display_cursor_on_off_control);
}

/**
  ******************************************************************************
  * @brief	Shift the LCD display to the left.
  * @param	None
  * @retval	None
  ******************************************************************************
  */
void lcd20x4_display_shift_left()
{
	lcd20x4_write_command(lcd20x4_DISPLAY_CURSOR_SHIFT | 
		lcd20x4_DISPLAY_SHIFT | lcd20x4_LEFT_SHIFT);
}

/**
  ******************************************************************************
  * @brief	Shift the LCD display to the right.
  * @param	None
  * @retval	None
  ******************************************************************************
  */
void lcd20x4_display_shift_right()
{
	lcd20x4_write_command(lcd20x4_DISPLAY_CURSOR_SHIFT |
		lcd20x4_DISPLAY_SHIFT | lcd20x4_RIGHT_SHIFT);
}

/**
  ******************************************************************************
  * @brief	Shift the LCD cursor to the left (DDRAM address incremented).
  * @param	None
  * @retval	None
  ******************************************************************************
  */
void lcd20x4_cursor_shift_left()
{
	lcd20x4_write_command(lcd20x4_DISPLAY_CURSOR_SHIFT |
		lcd20x4_DISPLAY_CURSOR_SHIFT | lcd20x4_LEFT_SHIFT);
}

/**
  ******************************************************************************
  * @brief	Shift the LCD cursor to the right (DDRAM address decremented).
  * @param	None
  * @retval	None
  ******************************************************************************
  */
void lcd20x4_cursor_shift_right()
{
	lcd20x4_write_command(lcd20x4_DISPLAY_CURSOR_SHIFT |
		lcd20x4_DISPLAY_CURSOR_SHIFT | lcd20x4_RIGHT_SHIFT);
}

/**
  ******************************************************************************
  * @brief	Put a character on the LCD display.
  * @param	Character that want to be displayed.
  * @retval	None
	* @EDITED Renardi Adryantoro P (2210161038) CE PENS 2017
  ******************************************************************************
  */
char detect;
void lcd20x4_putc(const char c)
{
	uint8_t pos = lcd20x4_getxy();

	if (c == '\n')
	{	detect=c;
		lcd20x4_new_line(pos);
	}
	else
	{
#if lcd20x4_LINES == 1
		if (pos == (lcd20x4_START_LINE_1 + 20))
			lcd20x4_write(lcd20x4_SET_DDRAM_ADDRESS |
				lcd20x4_START_LINE_1, 0);
#elif lcd20x4_LINES == 2
		if (pos == (lcd20x4_START_LINE_1 + 20)){
			
			if(wow==2){lcd20x4_write(lcd20x4_SET_DDRAM_ADDRESS |
				lcd20x4_START_LINE_1+20, 0);}
			else if(detect=='\n'){lcd20x4_write(lcd20x4_SET_DDRAM_ADDRESS |
				lcd20x4_START_LINE_1+20, 0);}
			else lcd20x4_write(lcd20x4_SET_DDRAM_ADDRESS |
				lcd20x4_START_LINE_2, 0);}	
		
		else if (pos == (lcd20x4_START_LINE_2 + 20)){
			if(wow==3){
			lcd20x4_write(lcd20x4_SET_DDRAM_ADDRESS |
				0x54, 0);}
			else if(detect=='\n')lcd20x4_write(lcd20x4_SET_DDRAM_ADDRESS |
				lcd20x4_START_LINE_2+20, 0);
				
			else lcd20x4_write(lcd20x4_SET_DDRAM_ADDRESS |
				lcd20x4_START_LINE_1+20, 0);
		}
		
		else if (pos ==(0x40)&&wow==2){
			if(detect=='\n')lcd20x4_write(lcd20x4_SET_DDRAM_ADDRESS |
				0x40, 0);
			else
			lcd20x4_write(lcd20x4_SET_DDRAM_ADDRESS |
				0x54, 0);}
		
#endif		
		
			lcd20x4_write_data(c);
	}
}

/**
  ******************************************************************************
  * @brief	Put string on the LCD display.
  * @param	String that want to be displayed.
  * @retval	None
  ******************************************************************************
  */
void lcd20x4_puts(const char* s)
{
	while (*s) {
		lcd20x4_putc(*s++);
	}
}

/**
  ******************************************************************************
  * @brief	Create a custom character on CGRAM location.
  * @param	CGRAM location (0-7).
  * @param	Custom character pattern (8 bytes).
  * @retval	None
  ******************************************************************************
  */
void lcd20x4_create_custom_char(uint8_t location, uint8_t* data_bytes)
{
	int i;
	
	// We only have 8 locations 0-7 for custom chars
	location &= 0x07; 
	
	// Set CGRAM address
	lcd20x4_write_command(lcd20x4_SET_CGRAM_ADDRESS | (location << 3));
	
	// Write 8 bytes custom char pattern
	for (i = 0; i < 8; i++) 
	{
		lcd20x4_write_data(data_bytes[i]);
	}
}

/**
  ******************************************************************************
  * @brief	Put a custom character on specific LCD display location.
  * @param	LCD column
  * @param	LCD row
  * @param	Custom character location on CGRAM (0-7).
  * @retval	None
  ******************************************************************************
  */
void lcd20x4_put_custom_char(uint8_t x, uint8_t y, uint8_t location)
{
	lcd20x4_gotoxy(x, y);
	lcd20x4_write_data(location);
}

/** Private functions ------------------------------------------------------- */
/**
  ******************************************************************************
  * @brief	Give enable pulse to LCD EN pin.
  * @param	None
  * @retval	None
  ******************************************************************************
  */
static void lcd20x4_toggle_e()
{
	// EN pin = HIGH
	lcd20x4_GPIO_EN->BSRR = lcd20x4_PIN_EN;
	// Pulse length in us
	DelayUs(lcd20x4_DELAY_ENABLE_PULSE);
	// EN pin = LOW
	lcd20x4_GPIO_EN->BRR = lcd20x4_PIN_EN;
}

/**
  ******************************************************************************
  * @brief	Write instruction or data to LCD.
  * @param	Instruction/ data that want to sent to LCD.
  * @param	Instruction or data register select. If write instruction, then 
  *					RS = 0. Otherwise, RS = 1.
  * @retval	None
  ******************************************************************************
  */
static void lcd20x4_write(uint8_t data, uint8_t rs)
{
	// Write mode (RW = 0)
	lcd20x4_GPIO_RS->BRR = lcd20x4_PIN_RW;
	
	if (rs)
		// Write data (RS = 1)
		lcd20x4_GPIO_RS->BSRR = lcd20x4_PIN_RS;
	else		
		// Write instruction (RS = 0)
		lcd20x4_GPIO_RS->BRR = lcd20x4_PIN_RS;
	
	// Configure all data pins as output
	GPIO_InitStruct.GPIO_Pin = lcd20x4_PIN_D4 | lcd20x4_PIN_D5 | 
		lcd20x4_PIN_D6 | lcd20x4_PIN_D7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(lcd20x4_GPIO_DATA, &GPIO_InitStruct);
	
	// Output high nibble first
	lcd20x4_GPIO_D7->BRR = lcd20x4_PIN_D7;
	lcd20x4_GPIO_D6->BRR = lcd20x4_PIN_D6;
	lcd20x4_GPIO_D5->BRR = lcd20x4_PIN_D5;
	lcd20x4_GPIO_D4->BRR = lcd20x4_PIN_D4;
	if (data & 0x80) lcd20x4_GPIO_D7->BSRR = lcd20x4_PIN_D7;
	if (data & 0x40) lcd20x4_GPIO_D7->BSRR = lcd20x4_PIN_D6;
	if (data & 0x20) lcd20x4_GPIO_D7->BSRR = lcd20x4_PIN_D5;
	if (data & 0x10) lcd20x4_GPIO_D7->BSRR = lcd20x4_PIN_D4;
	lcd20x4_toggle_e();
	
	// Output low nibble
	lcd20x4_GPIO_D7->BRR = lcd20x4_PIN_D7;
	lcd20x4_GPIO_D6->BRR = lcd20x4_PIN_D6;
	lcd20x4_GPIO_D5->BRR = lcd20x4_PIN_D5;
	lcd20x4_GPIO_D4->BRR = lcd20x4_PIN_D4;
	if (data & 0x08) lcd20x4_GPIO_D7->BSRR = lcd20x4_PIN_D7;
	if (data & 0x04) lcd20x4_GPIO_D7->BSRR = lcd20x4_PIN_D6;
	if (data & 0x02) lcd20x4_GPIO_D7->BSRR = lcd20x4_PIN_D5;
	if (data & 0x01) lcd20x4_GPIO_D7->BSRR = lcd20x4_PIN_D4;
	lcd20x4_toggle_e();
	
	// All data pins high (inactive)
	lcd20x4_GPIO_D7->BSRR = lcd20x4_PIN_D7;
	lcd20x4_GPIO_D7->BSRR = lcd20x4_PIN_D6;
	lcd20x4_GPIO_D7->BSRR = lcd20x4_PIN_D5;
	lcd20x4_GPIO_D7->BSRR = lcd20x4_PIN_D4;
}

/**
  ******************************************************************************
  * @brief	Read DDRAM address + busy flag or data from LCD.
  * @param	DDRAM address + busy flag or data register select. 
  *					If read DDRAM address + busy flag, then RS = 0. Otherwise, RS = 1.
  * @retval	DDRAM address + busy flag or data value.
  ******************************************************************************
  */
static uint8_t lcd20x4_read(uint8_t rs)
{
	uint8_t data = 0;
	
	// Read mode (RW = 1)
	lcd20x4_GPIO_RS->BSRR = lcd20x4_PIN_RW;
	
	if (rs)
		// Read data (RS = 1)
		lcd20x4_GPIO_RS->BSRR = lcd20x4_PIN_RS;
	else
		// Read busy flag and DDRAM address (RS = 0)
		lcd20x4_GPIO_RS->BRR = lcd20x4_PIN_RS;
		
	// Configure all data pins as input
	GPIO_InitStruct.GPIO_Pin = lcd20x4_PIN_D4 | lcd20x4_PIN_D5 | 
		lcd20x4_PIN_D6 | lcd20x4_PIN_D7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(lcd20x4_GPIO_DATA, &GPIO_InitStruct);
	
	// EN pin = HIGH
	lcd20x4_GPIO_EN->BSRR = lcd20x4_PIN_EN;
	// Pulse length in us
	DelayUs(lcd20x4_DELAY_ENABLE_PULSE);
	/* Read high nibble first */
	if (lcd20x4_GPIO_D4->IDR & lcd20x4_PIN_D4) data |= 0x10;	
	if (lcd20x4_GPIO_D5->IDR & lcd20x4_PIN_D5) data |= 0x20;
	if (lcd20x4_GPIO_D6->IDR & lcd20x4_PIN_D6) data |= 0x40;
	if (lcd20x4_GPIO_D7->IDR & lcd20x4_PIN_D7) data |= 0x80;
	// EN pin = LOW
	lcd20x4_GPIO_EN->BRR = lcd20x4_PIN_EN;
	
	// EN pin LOW delay
	DelayUs(lcd20x4_DELAY_ENABLE_PULSE);
	
	// EN pin = HIGH
	lcd20x4_GPIO_EN->BSRR = lcd20x4_PIN_EN;
	// Pulse length in us
	DelayUs(lcd20x4_DELAY_ENABLE_PULSE);
	/* Read low nibble */
	if (lcd20x4_GPIO_D4->IDR & lcd20x4_PIN_D4) data |= 0x01;
	if (lcd20x4_GPIO_D5->IDR & lcd20x4_PIN_D5) data |= 0x02;
	if (lcd20x4_GPIO_D6->IDR & lcd20x4_PIN_D6) data |= 0x04;
	if (lcd20x4_GPIO_D7->IDR & lcd20x4_PIN_D7) data |= 0x08;
	// EN pin = LOW
	lcd20x4_GPIO_EN->BRR = lcd20x4_PIN_EN;
	
	return data;
}

/**
  ******************************************************************************
  * @brief	Wait for LCD until finish it's job.
  * @param	None
  * @retval	DDRAM address + busy flag value.
  ******************************************************************************
  */
static uint8_t lcd20x4_wait_busy()
{
	// Wait until busy flag is cleared
	while (lcd20x4_read(0) & (lcd20x4_BUSY_FLAG));
	
	// Delay needed for address counter is updated after busy flag is cleared
	DelayUs(lcd20x4_DELAY_BUSY_FLAG);
	
	// Read and return address counter
	return lcd20x4_read(0);
}

/**
  ******************************************************************************
  * @brief	Give new line character 
  * @param	Current cursor/ DDRAM address position.
  * @retval	None
  ******************************************************************************
  */
static void lcd20x4_new_line(uint8_t pos)
{
	uint8_t address_counter;
#if lcd20x4_LINES == 1
	address_counter = 0;
#elif lcd20x4_LINES == 2
	
	if (pos >=0 && pos<20)
		address_counter = lcd20x4_START_LINE_2;
	
	else if(pos>=64 && pos<84)
	address_counter=lcd20x4_START_LINE_1+20;
	
	else if(pos>=0x14 && pos<0x28)
	address_counter=0x54;
	
	else if(pos>=0x54 && pos<=0x68)
	address_counter=lcd20x4_START_LINE_1;
	
#endif
	lcd20x4_write_command(lcd20x4_SET_DDRAM_ADDRESS | address_counter);
}

/********************************* END OF FILE ********************************/
/******************************************************************************/
