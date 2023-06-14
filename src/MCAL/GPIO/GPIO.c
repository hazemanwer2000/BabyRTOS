/*************************************************************
 * 
 * Filename: GPIO.c
 * Description: Source file of the GPIO driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#include "GPIO_Map.h"
#include "GPIO_Priv.h"
#include "GPIO.h"
#include "Bit_Utils.h"


/*************************************************************
 * Description: Initialize pin.
 * Parameters:
 *      [1] Address to Pin Configuration structure.
 * Return:
 *      None.
 *************************************************************/
void GPIO_initializePin(GPIO_pinConfiguration_t *pinConfiguration) {
	uint8_t bitISPEED = pinConfiguration->pinNumber * SIZE_SPEED;
	uint8_t bitIMODE = pinConfiguration->pinNumber * SIZE_MODE;
	uint8_t bitIPUPD = pinConfiguration->pinNumber * SIZE_PUPD;
	uint8_t bitIOTYPE = pinConfiguration->pinNumber * SIZE_OTYPE;

	pinConfiguration->port->OSPEEDR = REPLACE_FIELD(pinConfiguration->port->OSPEEDR,
			bitISPEED, bitISPEED + (SIZE_SPEED - 1), pinConfiguration->pinSpeed);

	volatile uint32_t var =  REPLACE_FIELD(pinConfiguration->port->MODER,
			bitIMODE, bitIMODE + (SIZE_MODE - 1), (pinConfiguration->pinMode >> GPIO_OFFSET_MODE) & MSK_I2J(0, SIZE_MODE - 1));
	pinConfiguration->port->MODER = var;

	pinConfiguration->port->PUPDR = REPLACE_FIELD(pinConfiguration->port->PUPDR,
			bitIPUPD, bitIPUPD + (SIZE_PUPD - 1), (pinConfiguration->pinMode >> GPIO_OFFSET_PULL_TYPE) & MSK_I2J(0, SIZE_PUPD - 1));

	pinConfiguration->port->OTYPER = REPLACE_FIELD(pinConfiguration->port->OTYPER,
			bitIOTYPE, bitIOTYPE + (SIZE_OTYPE - 1), (pinConfiguration->pinMode >> GPIO_OFFSET_OUTPUT_TYPE) & MSK_I2J(0, SIZE_OTYPE - 1));
}


/*************************************************************
 * Description: Select Alternate Function.
 * Parameters:
 * 		[1] Port option.
 * 		[2] Pin number option.
 *      [3] Alternate Function option.
 * Return:
 *      None.
 *************************************************************/
void GPIO_selectAF(GPIO_port_t port, GPIO_pinNumber_t pinNumber, GPIO_AF_t AF) {
	uint8_t bitIAF = (pinNumber % 8) * SIZE_AF;
	volatile uint32_t *reg = (pinNumber < 8 ? &port->AFRL : &port->AFRH);

	*reg = REPLACE_FIELD(*reg, bitIAF, bitIAF + (SIZE_AF - 1), AF);
}


/*************************************************************
 * Description: Toggle (output) pin.
 * Parameters:
 * 		[1] Port option.
 *      [2] Pin mask option (may be OR'd).
 * Return:
 *      None.
 *************************************************************/
void GPIO_togglePin(GPIO_port_t port, GPIO_pinMask_t pinMask) {
	port->ODR ^= pinMask;
}


/*************************************************************
 * Description: Toggle (output) pin state.
 * Parameters:
 * 		[1] Port option.
 *      [2] Pin number option.
 * Return:
 *      None.
 *************************************************************/
void GPIO_togglePinState(GPIO_port_t port, GPIO_pinNumber_t pinNumber) {
	port->ODR ^= (1 << pinNumber);
}


/*************************************************************
 * Description: Set (output) pin.
 * Parameters:
 * 		[1] Port option.
 *      [2] Pin mask option (may be OR'd).
 * Return:
 *      None.
 *************************************************************/
void GPIO_setPin(GPIO_port_t port, GPIO_pinMask_t pinMask) {
	port->BSRR |= pinMask;
}


/*************************************************************
 * Description: Reset (output) pin.
 * Parameters:
 * 		[1] Port option.
 *      [2] Pin mask option (may be OR'd).
 * Return:
 *      None.
 *************************************************************/
void GPIO_resetPin(GPIO_port_t port, GPIO_pinMask_t pinMask) {
	port->BSRR |= pinMask << 16;
}


/*************************************************************
 * Description: Set pin state.
 * Parameters:
 * 		[1] Port option.
 *      [2] Pin number option.
 *      [3] Pin state option.
 * Return:
 *      None.
 *************************************************************/
void GPIO_setPinState(GPIO_port_t port, GPIO_pinNumber_t pinNumber, GPIO_pinState_t pinState) {
	port->ODR = REPLACE_BIT(port->ODR, pinNumber, pinState);
}


/*************************************************************
 * Description: Set port value.
 * Parameters:
 * 		[1] Port option.
 *      [2] Value.
 * Return:
 *      None.
 *************************************************************/
void GPIO_setPortValue(GPIO_port_t port, uint16_t value) {
	port->ODR = value;
}


/*************************************************************
 * Description: Read pin state.
 * Parameters:
 * 		[1] Port option.
 *      [2] Pin number option.
 * Return:
 *      Pin state option.
 *************************************************************/
GPIO_pinState_t GPIO_readPinState(GPIO_port_t port, GPIO_pinNumber_t pinNumber) {
	return GET_BIT(port->IDR, pinNumber);
}


/*************************************************************
 * Description: Read port value.
 * Parameters:
 * 		[1] Port option.
 * Return:
 *      Value.
 *************************************************************/
uint16_t GPIO_readPortValue(GPIO_port_t port) {
	return port->IDR;
}
