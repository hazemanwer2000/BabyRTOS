/*************************************************************
 * 
 * Filename: GPIO.h
 * Description: Header (interface) file of the GPIO driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __GPIO_H__
#define __GPIO_H__

#include "GPIO_Map.h"


/*************************************************************
 * Description: Base addresses of modules.
 *
 *************************************************************/
#define GPIOA					((volatile GPIO_t *) 0x40020000)
#define GPIOB					((volatile GPIO_t *) 0x40020400)
#define GPIOC					((volatile GPIO_t *) 0x40020800)
#define GPIOD					((volatile GPIO_t *) 0x40020C00)
#define GPIOE					((volatile GPIO_t *) 0x40021000)
#define GPIOH					((volatile GPIO_t *) 0x40021C00)


/*************************************************************
 * Description: Pin number options.
 *
 *************************************************************/
#define GPIO_pinNumber_0				0
#define GPIO_pinNumber_1				1
#define GPIO_pinNumber_2				2
#define GPIO_pinNumber_3				3

#define GPIO_pinNumber_4				4
#define GPIO_pinNumber_5				5
#define GPIO_pinNumber_6				6
#define GPIO_pinNumber_7				7

#define GPIO_pinNumber_8				8
#define GPIO_pinNumber_9				9
#define GPIO_pinNumber_10				10
#define GPIO_pinNumber_11				11

#define GPIO_pinNumber_12				12
#define GPIO_pinNumber_13				13
#define GPIO_pinNumber_14				14
#define GPIO_pinNumber_15				15


/*************************************************************
 * Description: Pin speed options.
 *
 *************************************************************/
#define GPIO_speed_Low				0
#define GPIO_speed_Medium			1
#define GPIO_speed_High				2
#define GPIO_speed_VeryHigh			3


/*************************************************************
 * Description: Pin mode options.
 *
 *************************************************************/
#define GPIO_mode_Input_Float						0b##0##00##00
#define GPIO_mode_Input_PullUp						0b##0##01##00
#define GPIO_mode_Input_PullDown					0b##0##10##00

#define GPIO_mode_Output_PushPull_Float				0b##0##00##01
#define GPIO_mode_Output_PushPull_PullUp			0b##0##01##01
#define GPIO_mode_Output_PushPull_PullDown			0b##0##10##01

#define GPIO_mode_Output_OpenDrain_Float			0b##1##00##01
#define GPIO_mode_Output_OpenDrain_PullUp			0b##1##01##01
#define GPIO_mode_Output_OpenDrain_PullDown			0b##1##10##01

#define GPIO_mode_AF_PushPull_Float					0b##0##00##10
#define GPIO_mode_AF_PushPull_PullUp				0b##0##01##10
#define GPIO_mode_AF_PushPull_PullDown				0b##0##10##10

#define GPIO_mode_AF_OpenDrain_Float				0b##1##00##10
#define GPIO_mode_AF_OpenDrain_PullUp				0b##1##01##10
#define GPIO_mode_AF_OpenDrain_PullDown				0b##1##10##10

#define GPIO_mode_Analog							0b##0##00##11


/*************************************************************
 * Description: Alternate function options.
 *
 *************************************************************/
#define GPIO_AF_0									0
#define GPIO_AF_1									1
#define GPIO_AF_2									2
#define GPIO_AF_3									3

#define GPIO_AF_4									4
#define GPIO_AF_5									5
#define GPIO_AF_6									6
#define GPIO_AF_7									7

#define GPIO_AF_8									8
#define GPIO_AF_9									9
#define GPIO_AF_10									10
#define GPIO_AF_11									11

#define GPIO_AF_12									12
#define GPIO_AF_13									13
#define GPIO_AF_14									14
#define GPIO_AF_15									15


/*************************************************************
 * Description: Pin mask options.
 *
 *************************************************************/
#define GPIO_pinMask_0								1
#define GPIO_pinMask_1								2
#define GPIO_pinMask_2								4
#define GPIO_pinMask_3								8

#define GPIO_pinMask_4								16
#define GPIO_pinMask_5								32
#define GPIO_pinMask_6								64
#define GPIO_pinMask_7								128

#define GPIO_pinMask_8								256
#define GPIO_pinMask_9								512
#define GPIO_pinMask_10								1024
#define GPIO_pinMask_11								2048

#define GPIO_pinMask_12								4096
#define GPIO_pinMask_13								8192
#define GPIO_pinMask_14								16384
#define GPIO_pinMask_15								32768

#define GPIO_pinMask_All							65535


/*************************************************************
 * Description: Pin state options.
 *
 *************************************************************/
#define GPIO_pinState_High							1
#define GPIO_pinState_Low							0


/*************************************************************
 * Description: (Type) Port.
 *
 *************************************************************/
typedef volatile GPIO_t *GPIO_port_t;


/*************************************************************
 * Description: Various type-definitions.
 *
 *************************************************************/
typedef uint8_t GPIO_pinNumber_t;
typedef uint16_t GPIO_pinMask_t;
typedef uint8_t GPIO_pinSpeed_t;
typedef uint8_t GPIO_pinMode_t;
typedef uint8_t GPIO_pinState_t;
typedef uint8_t GPIO_AF_t;


/*************************************************************
 * Description: (Type) Configuration structure of a pin.
 *
 *************************************************************/
typedef struct {
	GPIO_port_t port;
	GPIO_pinNumber_t pinNumber;
	GPIO_pinSpeed_t pinSpeed;
	GPIO_pinMode_t pinMode;
} GPIO_pinConfiguration_t;


/*************************************************************
 * Description: Initialize pin.
 * Parameters:
 *      [1] Address to Pin Configuration structure.
 * Return:
 *      None.
 *************************************************************/
void GPIO_initializePin(GPIO_pinConfiguration_t *pinConfiguration);


/*************************************************************
 * Description: Select Alternate Function.
 * Parameters:
 * 		[1] Port option.
 * 		[2] Pin number option.
 *      [3] Alternate Function option.
 * Return:
 *      None.
 *************************************************************/
void GPIO_selectAF(GPIO_port_t port, GPIO_pinNumber_t pinNumber, GPIO_AF_t AF);


/*************************************************************
 * Description: Toggle (output) pin.
 * Parameters:
 * 		[1] Port option.
 *      [2] Pin mask option (may be OR'd).
 * Return:
 *      None.
 *************************************************************/
void GPIO_togglePin(GPIO_port_t port, GPIO_pinMask_t pinMask);


/*************************************************************
 * Description: Toggle (output) pin state.
 * Parameters:
 * 		[1] Port option.
 *      [2] Pin number option.
 * Return:
 *      None.
 *************************************************************/
void GPIO_togglePinState(GPIO_port_t port, GPIO_pinNumber_t pinNumber);


/*************************************************************
 * Description: Set (output) pin.
 * Parameters:
 * 		[1] Port option.
 *      [2] Pin mask option (may be OR'd).
 * Return:
 *      None.
 *************************************************************/
void GPIO_setPin(GPIO_port_t port, GPIO_pinMask_t pinMask);


/*************************************************************
 * Description: Reset (output) pin.
 * Parameters:
 * 		[1] Port option.
 *      [2] Pin mask option (may be OR'd).
 * Return:
 *      None.
 *************************************************************/
void GPIO_resetPin(GPIO_port_t port, GPIO_pinMask_t pinMask);


/*************************************************************
 * Description: Set pin state.
 * Parameters:
 * 		[1] Port option.
 *      [2] Pin number option.
 *      [3] Pin state option.
 * Return:
 *      None.
 *************************************************************/
void GPIO_setPinState(GPIO_port_t port, GPIO_pinNumber_t pinNumber, GPIO_pinState_t pinState);


/*************************************************************
 * Description: Set port value.
 * Parameters:
 * 		[1] Port option.
 *      [2] Value.
 * Return:
 *      None.
 *************************************************************/
void GPIO_setPortValue(GPIO_port_t port, uint16_t value);


/*************************************************************
 * Description: Read pin state.
 * Parameters:
 * 		[1] Port option.
 *      [2] Pin number option.
 * Return:
 *      Pin state option.
 *************************************************************/
GPIO_pinState_t GPIO_readPinState(GPIO_port_t port, GPIO_pinNumber_t pinNumber);


/*************************************************************
 * Description: Read port value.
 * Parameters:
 * 		[1] Port option.
 * Return:
 *      Value.
 *************************************************************/
uint16_t GPIO_readPortValue(GPIO_port_t port);


#endif /* __GPIO_H__ */
