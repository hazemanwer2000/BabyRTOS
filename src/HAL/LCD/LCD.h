/*************************************************************
 * 
 * Filename: LCD.h
 * Description: Header (interface) file of the LCD driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __LCD_H__
#define __LCD_H__

#include "LCD_Cfg.h"
#include "LCD_Types.h"


/*************************************************************
 * Description: Commands.
 * 
 *************************************************************/
#define LCD_command_clearDisplay                0x1
#define LCD_command_cursorOn                    0b1111
#define LCD_command_cursorOff                   0b1100


/*************************************************************
 * Description: Initialize LCD.
 * Parameters:
 *      [X]
 * Return:
 *      None.
 *************************************************************/
void LCD_init(void);


/*************************************************************
 * Description: LCD service.
 *                  Note: Should run every 2 ms or more.
 * Parameters:
 *      [X]
 * Return:
 *      None.
 *************************************************************/
void LCD_service(void);


/*************************************************************
 * Description: Write character.
 * Parameters:
 *      [1] Character.
 * Return:
 *      None.
 *************************************************************/
LCD_status_t LCD_writeChar(uint8_t c);


/*************************************************************
 * Description: Write command.
 * Parameters:
 *      [1] Command.
 * Return:
 *      None.
 *************************************************************/
LCD_status_t LCD_writeCommand(uint8_t cmd);


/*************************************************************
 * Description: Write command.
 * Parameters:
 *      [1] Command.
 * Return:
 *      None.
 *************************************************************/
LCD_status_t LCD_goto(uint8_t x, uint8_t y);


/*************************************************************
 * Description: Write command.
 * Parameters:
 *      [1] Command.
 * Return:
 *      None.
 *************************************************************/
LCD_status_t LCD_writeString(const char * const ptr, uint8_t length);


#endif /* __LCD_H__ */