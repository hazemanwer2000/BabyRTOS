/*************************************************************
 * 
 * Filename: LCD_Priv.h
 * Description: Private header file of the LCD driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __LCD_PRIV_H__
#define __LCD_PRIV_H__


/*************************************************************
 * Description: Multiple bit-location definitions.
 * 
 *************************************************************/
#define LCD_BIT_LOC_RS              8
#define LCD_BIT_LOC_D_COUNT         4


/*************************************************************
 * Description: LCD command definitions.
 * 
 *************************************************************/
#define LCD_command_DDRAM           0b10000000
#define LCD_DDRAM_Address_Line2     0x40


/*************************************************************
 * Description: LCD dimensions.
 * 
 *************************************************************/
#define LCD_DIM_X                   16
#define LCD_DIM_Y                   2


/*************************************************************
 * Description: Set high nibble of current data in buffer, on data pins.
 * Parameters:
 *      [1] Is high nibble (or low).
 * Return:
 *      None.
 *************************************************************/
static void LCD_setNibble(LCD_nibbleLoc_t nibbleLoc);


/*************************************************************
 * Description: Set RS of current byte in buffer, on data pins.
 * Parameters:
 *      [X]
 * Return:
 *      None.
 *************************************************************/
static void LCD_setRS(void);


/*************************************************************
 * Description: Set RS of current byte in buffer, on data pins.
 * Parameters:
 *      [X]
 * Return:
 *      None.
 *************************************************************/
static void LCD_setE(GPIO_pinState_t pinState);


/*************************************************************
 * Description: Write.
 * Parameters:
 *      [1] Data.
 * Return:
 *      None.
 *************************************************************/
static LCD_status_t LCD_write(uint16_t data);


#endif /* __LCD_PRIV_H__ */