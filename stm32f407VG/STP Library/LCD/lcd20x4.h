

#ifndef LCD20X4_H
#define LCD20X4_H


#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"


/**	
 *------------------------------------------------------------------------
 * 
 *@EditedBY Renardi Adryantoro Priambudi (2210161038) ERSOW 2017 PENS INDONESIA
 *@Source   GITHUB,  Tilen Majerle, 2014
 *@LATEST  2018
 *------------------------------------------------------------------------
*/
//CODE BELOW is definition for PIN
//IF you want to change the pin you can dirctly change 
//=================START pin can be change ===============

#define LCD_RCC_control   RCC_AHB1Periph_GPIOD//<<=== Boleh di ganti hanya GPIO nya,JIka diperlukan maka AHB boleh di ganti
#define LCD_RCC_Data      RCC_AHB1Periph_GPIOD//<<=== Boleh di ganti hanya GPIO nya,JIka diperlukan maka AHB boleh di ganti

#define LCD_Control       GPIOD   //<<===  Allow to change
#define LCD_Data          GPIOD   //<<===  Allow to change         


/* 4 bit mode */
/* Control pins, can be overwritten */
/* RS - Register select pin */

#define RS_PORT				LCD_Control
#define RS_PIN				GPIO_Pin_5 //<<===  Allow to change

/* E - Enable pin */

#define HD44780_E_PORT				LCD_Control
#define HD44780_E_PIN				  GPIO_Pin_6 //<<===   Allow to change

/* Data pins */
/* D4 - Data 4 pin */


#define HD44780_D4_PORT				  LCD_Data
#define HD44780_D4_PIN		     	GPIO_Pin_3 //<<===   Allow to change

/* D5 - Data 5 pin */

#define HD44780_D5_PORT				 LCD_Data
#define HD44780_D5_PIN				 GPIO_Pin_4 //<<===   Allow to change

/* D6 - Data 6 pin */

#define HD44780_D6_PORT				  LCD_Data
#define HD44780_D6_PIN				  GPIO_Pin_1 //<<===   Allow to change

/* D7 - Data 7 pin */

#define HD44780_D7_PORT				   LCD_Data
#define HD44780_D7_PIN				   GPIO_Pin_0 //<<===   Allow to change

//====================END of PIN can be change=================


/* Pin definitions */
#define HD44780_RS_LOW              HD44780_RS_PORT->BSRRH = HD44780_RS_PIN;
#define HD44780_RS_HIGH             HD44780_RS_PORT->BSRRL = HD44780_RS_PIN;
#define HD44780_E_LOW               HD44780_E_PORT->BSRRH = HD44780_E_PIN;
#define HD44780_E_HIGH              HD44780_E_PORT->BSRRL = HD44780_E_PIN;

#define HD44780_E_BLINK             HD44780_E_HIGH; DELAY_Us(20); HD44780_E_LOW;DELAY_Us(20)
#define HD44780_Delay(x)            DELAY_Ms(x)


#define GPIO_SetPinLow(GPIOx, GPIO_Pin)			((GPIOx)->BSRRH = (GPIO_Pin))
#define GPIO_SetPinHigh(GPIOx, GPIO_Pin)			((GPIOx)->BSRRL = (GPIO_Pin))
#define GPIO_SetPinValue(GPIOx, GPIO_Pin, val)	((val) ? GPIO_SetPinHigh(GPIOx, GPIO_Pin) : GPIO_SetPinLow(GPIOx, GPIO_Pin))



//=================ADDRES OF LCD====================
/* Commands*/
#define HD44780_CLEARDISPLAY        0x01
#define HD44780_RETURNHOME          0x02
#define HD44780_ENTRYMODESET        0x04
#define HD44780_DISPLAYCONTROL      0x08
#define HD44780_CURSORSHIFT         0x10
#define HD44780_FUNCTIONSET         0x20
#define HD44780_SETCGRAMADDR        0x40
#define HD44780_SETDDRAMADDR        0x80

/* Flags for display entry mode */
#define HD44780_ENTRYRIGHT          0x00
#define HD44780_ENTRYLEFT           0x02
#define HD44780_ENTRYSHIFTINCREMENT 0x01
#define HD44780_ENTRYSHIFTDECREMENT 0x00

/* Flags for display on/off control */
#define HD44780_DISPLAYON           0x04
#define HD44780_CURSORON            0x02
#define HD44780_BLINKON             0x01

/* Flags for display/cursor shift */
#define HD44780_DISPLAYMOVE         0x08
#define HD44780_CURSORMOVE          0x00
#define HD44780_MOVERIGHT           0x04
#define HD44780_MOVELEFT            0x00

/* Flags for function set */
#define HD44780_8BITMODE            0x10
#define HD44780_4BITMODE            0x00
#define HD44780_2LINE               0x08
#define HD44780_1LINE               0x00
#define HD44780_5x10DOTS            0x04
#define HD44780_5x8DOTS             0x00


/**
 * @}
 */

/**
 * @defgroup lcd_Functions
 * @brief    Library Functions
 * @{
 */

/**
 * @brief  Initializes HD44780 LCD
 * @brief  cols: width of lcd
 * @param  rows: height of lcd
 * @retval None
 */
void lcd_init(uint8_t cols, uint8_t rows);

/**
 * @brief  Turn display on
 * @param  None
 * @retval None
 */
void lcd_DisplayOn(void);

/**
 * @brief  Turn display off
 * @param  None
 * @retval None
 */
void lcd_DisplayOff(void);

/**
 * @brief  Clears entire LCD
 * @param  None
 * @retva
 
 l None
 */
void lcd_clear(void);

/**
 * @brief  Puts string on lcd
 * @param  x location
 * @param  y location
 * @param  *str: pointer to string to display
 * @retval None
 */
void lcd_putsxy(uint8_t x, uint8_t y, char* str);

/**
 * @brief  Enables cursor blink
 * @param  None
 * @retval None
 */
void lcd_BlinkOn(void);

/**
 * @brief  Disables cursor blink
 * @param  None
 * @retval None
 */
void lcd_BlinkOff(void);

/**
 * @brief  Shows cursor
 * @param  None
 * @retval None
 */
void lcd_CursorOn(void);

/**
 * @brief  Hides cursor
 * @param  None
 * @retval None
 */
void lcd_CursorOff(void);

/**
 * @brief  Scrolls display to the left
 * @param  None
 * @retval None
 */
void lcd_ScrollLeft(void);

/**
 * @brief  Scrolls display to the right
 * @param  None
 * @retval None
 */
void lcd_ScrollRight(void);

/**
 * @brief  Creates custom character
 * @param  location: Location where to save character on LCD. LCD supports up to 8 custom characters, so locations are 0 - 7
 * @param *data: Pointer to 8-bytes of data for one character
 * @retval None
 */
void lcd_CreateChar(uint8_t location, uint8_t* data);

/**
 * @brief  Puts custom created character on LCD
 * @param  location: Location on LCD where character is stored, 0 - 7
 * @retval None
 */
void lcd_PutCustom(uint8_t x, uint8_t y, uint8_t location);


void lcd_puts(char* str);

void lcd_gotoxy(uint8_t col, uint8_t row) ;
#endif
