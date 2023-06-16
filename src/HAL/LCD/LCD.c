/*************************************************************
 * 
 * Filename: LCD.c
 * Description: Source file of the LCD driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#include "LCD_Cfg.h"
#include "LCD_Priv.h"
#include "LCD_Types.h"
#include "LCD.h"
#include "Bit_Utils.h"
#include "Std_Types.h"
#include "GPIO.h"


/*************************************************************
 * Description: Ring buffer's related functions.
 * Parameters:
 *      [X]
 * Return:
 *      None.
 *************************************************************/
static uint16_t LCD_buffer[LCD_BUFFER_CAPACITY] = {
    0b000110011,
    0b000110010,
    0b000101000,
    
    0b000001100,
    0b000000110,

    LCD_command_clearDisplay,
    LCD_command_cursorOn,
};
static uint8_t LCD_bufferSize = 7;
static uint8_t LCD_bufferSendIndex = 0;
static uint8_t LCD_bufferRecvIndex = 7;
static LCD_serviceState_t LCD_serviceState = LCD_serviceState_readyForHigh;


/*************************************************************
 * Description: Initialize LCD.
 * Parameters:
 *      [X]
 * Return:
 *      None.
 *************************************************************/
void LCD_init(void) {
    uint8_t i = 0;
    GPIO_pinConfiguration_t pinCfg = {
        .port = LCD_cfg.port,
        .pinSpeed = GPIO_speed_VeryHigh,
        .pinMode = GPIO_mode_Output_PushPull_Float
    };

    for (i = 0; i < 4; i++) {
        pinCfg.pinNumber = LCD_cfg.pinNumber_D[i];
        GPIO_initializePin(&pinCfg);
    }

    pinCfg.pinNumber = LCD_cfg.pinNumber_E;
    GPIO_initializePin(&pinCfg);

    pinCfg.pinNumber = LCD_cfg.pinNumber_RS;
    GPIO_initializePin(&pinCfg);
}


/*************************************************************
 * Description: Set high nibble of current data in buffer, on data pins.
 * Parameters:
 *      [1] Is high nibble (or low).
 * Return:
 *      None.
 *************************************************************/
static void LCD_setNibble(LCD_nibbleLoc_t nibbleLoc) {
    uint8_t i = (nibbleLoc == LCD_nibble_high ? 4 : 0);
    uint8_t j = 0;

    for (j = 0; j < LCD_BIT_LOC_D_COUNT; j++, i++) {
        GPIO_setPinState(LCD_cfg.port, LCD_cfg.pinNumber_D[j], 
            GET_BIT(LCD_buffer[LCD_bufferSendIndex], i));
    }
}


/*************************************************************
 * Description: Set RS of current byte in buffer, on data pins.
 * Parameters:
 *      [X]
 * Return:
 *      None.
 *************************************************************/
static void LCD_setRS(void) {
    GPIO_setPinState(LCD_cfg.port, LCD_cfg.pinNumber_RS, 
        GET_BIT(LCD_buffer[LCD_bufferSendIndex], LCD_BIT_LOC_RS));
}


/*************************************************************
 * Description: Set RS of current byte in buffer, on data pins.
 * Parameters:
 *      [X]
 * Return:
 *      None.
 *************************************************************/
static void LCD_setE(GPIO_pinState_t pinState) {
    GPIO_setPinState(LCD_cfg.port, LCD_cfg.pinNumber_E, pinState);
}


/*************************************************************
 * Description: LCD service.
 *                  Note: Should run every 2 ms or more.
 * Parameters:
 *      [X]
 * Return:
 *      None.
 *************************************************************/
void LCD_service(void) {
    switch (LCD_serviceState) {
        case LCD_serviceState_readyForHigh:
            if (LCD_bufferSize != 0) {
                LCD_setRS();
                LCD_setNibble(LCD_nibble_high);
                LCD_setE(GPIO_pinState_High);
                LCD_serviceState = LCD_serviceState_sendingHigh;
            }
            break;
        case LCD_serviceState_sendingHigh:
            LCD_setE(GPIO_pinState_Low);
            LCD_serviceState = LCD_serviceState_readyForLow;
            break;
        case LCD_serviceState_readyForLow:
            LCD_setNibble(LCD_nibble_low);
            LCD_setE(GPIO_pinState_High);
            LCD_serviceState = LCD_serviceState_sendingLow;
            break;
        case LCD_serviceState_sendingLow:
            LCD_setE(GPIO_pinState_Low);

            LCD_bufferSize--;
            if (++LCD_bufferSendIndex == LCD_BUFFER_CAPACITY) {
                LCD_bufferSendIndex = 0;
            }
            
            LCD_serviceState = LCD_serviceState_readyForHigh;
            break;
    }
}


/*************************************************************
 * Description: Write.
 * Parameters:
 *      [1] Data.
 * Return:
 *      None.
 *************************************************************/
static LCD_status_t LCD_write(uint16_t data) {
    LCD_status_t status = LCD_status_ok;

    if (LCD_bufferSize < LCD_BUFFER_CAPACITY) {
        LCD_buffer[LCD_bufferRecvIndex] = data;
        
        if (++LCD_bufferRecvIndex == LCD_BUFFER_CAPACITY) {
            LCD_bufferRecvIndex = 0;
        }
        
        LCD_bufferSize++;
    } else {
        status = LCD_status_busy;
    }

    return status;
}


/*************************************************************
 * Description: Write character.
 * Parameters:
 *      [1] Character.
 * Return:
 *      None.
 *************************************************************/
LCD_status_t LCD_writeChar(uint8_t c) {
    return LCD_write((1 << LCD_BIT_LOC_RS) | c);
}


/*************************************************************
 * Description: Write command.
 * Parameters:
 *      [1] Command.
 * Return:
 *      None.
 *************************************************************/
LCD_status_t LCD_writeCommand(uint8_t cmd) {
    return LCD_write(cmd);
}


/*************************************************************
 * Description: Write command.
 * Parameters:
 *      [1] Command.
 * Return:
 *      None.
 *************************************************************/
LCD_status_t LCD_goto(uint8_t x, uint8_t y) {
    LCD_status_t status = LCD_status_ok;

    if (x < LCD_DIM_X && y < LCD_DIM_Y) {
        if (y == 1) {
            x += LCD_DDRAM_Address_Line2;
        }

        status = LCD_write(LCD_command_DDRAM | x);
    } else {
        status = LCD_status_outOfDisplayLocation;
    }

    return status;
}


/*************************************************************
 * Description: Write command.
 * Parameters:
 *      [1] Command.
 * Return:
 *      None.
 *************************************************************/
LCD_status_t LCD_writeString(const char * const ptr, uint8_t length) {
    LCD_status_t status = LCD_status_ok;
    uint8_t i = 0;

    if (length <= (LCD_BUFFER_CAPACITY - LCD_bufferSize)) {
        while (ptr[i] != '\0') {
            status = LCD_write((1 << LCD_BIT_LOC_RS) | ptr[i]);
            
            if (status != LCD_status_ok) {
                break;
            }

            i++;
        }
    } else {
        status = LCD_status_busy;
    }

    return status;
}
