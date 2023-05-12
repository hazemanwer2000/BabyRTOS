/*************************************************************
 * 
 * Filename: LCD_Cfg.h
 * Description: Configuration header file of the LCD driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __LCD_CFG_H__
#define __LCD_CFG_H__

#include "LCD_Types.h"


/*************************************************************
 * Description: Buffer capacity (used by background service).
 * 
 *************************************************************/
#define LCD_BUFFER_CAPACITY         64


/*************************************************************
 * Description: LCD configuration.
 * 
 *************************************************************/
extern LCD_cfg_t LCD_cfg;


#endif /* __LCD_CFG_H__ */