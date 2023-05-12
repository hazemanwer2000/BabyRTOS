/*************************************************************
 * 
 * Filename: Std_Types.h
 * Description: Standard type-definitions file, relevant to the STM32F401CC MCU.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __STD_TYPES_H__
#define __STD_TYPES_H__

/*************************************************************
 * Description: Type-definitions of unsigned integral types.
 * 
 *************************************************************/
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;


/*************************************************************
 * Description: Type-definitions of signed integral types.
 * 
 *************************************************************/
typedef signed char int8_t;
typedef signed short int int16_t;
typedef signed int int32_t;
typedef signed long long int int64_t;


/*************************************************************
 * Description: Macro-definition of what it means to be false (boolean).
 * 
 *************************************************************/
#define FALSE 			0
#define TRUE 			1


/*************************************************************
 * Description: Macro-definition of what it means to be a NULL pointer.
 * 
 *************************************************************/
#define NULL            ((void *) 0)


#endif /* __STD_TYPES_H__ */
