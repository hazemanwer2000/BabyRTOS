/*************************************************************
 * 
 * Filename: LCD_Types.h
 * Description: Types header file of the LCD driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __LCD_TYPES_H__
#define __LCD_TYPES_H__

#include "GPIO.h"


/*************************************************************
 * Description: LCD configuration type.
 *                  Note: 'D[0]' is D4, 'D[1]' is D5, and so on.
 * 
 *************************************************************/
typedef struct {
    GPIO_port_t port;

    GPIO_pinNumber_t pinNumber_D[4];
    
    GPIO_pinNumber_t pinNumber_RS;
    GPIO_pinNumber_t pinNumber_E;
} LCD_cfg_t;


/*************************************************************
 * Description: LCD service state type.
 * 
 *************************************************************/
typedef enum {
    LCD_serviceState_readyForHigh = 0,
    LCD_serviceState_sendingHigh = 1,
    LCD_serviceState_readyForLow = 2,
    LCD_serviceState_sendingLow = 3
} LCD_serviceState_t;


/*************************************************************
 * Description: LCD nibble-location type.
 * 
 *************************************************************/
typedef enum {
    LCD_nibble_low = 0,
    LCD_nibble_high
} LCD_nibbleLoc_t;


/*************************************************************
 * Description: LCD status type.
 * 
 *************************************************************/
typedef enum {
    LCD_status_ok = 0,
    LCD_status_busy,
    LCD_status_outOfDisplayLocation
} LCD_status_t;


#endif /* __LCD_TYPES_H__ */