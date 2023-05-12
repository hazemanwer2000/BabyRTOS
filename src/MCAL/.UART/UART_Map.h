/*************************************************************
 * 
 * Filename: UART_Map.h
 * Description: Map file of the UART driver.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __UART_MAP_H__
#define __UART_MAP_H__

#include "Std_Types.h"


/*************************************************************
 * Description: Register layout of the module.
 *
 *************************************************************/
typedef struct {
	uint32_t SR;
	uint32_t DR;
	uint32_t BRR;
	uint32_t CR1;
	uint32_t CR2;
	uint32_t CR3;
	uint32_t GTPR;
} __attribute__((packed, aligned(4))) UART_t;


/*************************************************************
 * Description: Bit numbers in the SR register.
 *
 *************************************************************/
#define PE                              0
#define FE                              1
#define NF                              2
#define ORE                             3
#define IDLE                            4
#define RXNE                            5
#define TC                              6
#define TXE                             7
#define LBD                             8
#define CTS                             9


/*************************************************************
 * Description: Bit numbers in the BRR register.
 *
 *************************************************************/
#define DIV_Fraction0                   0
#define DIV_FractionN                   3
#define DIV_Mantissa0                   4
#define DIV_MantissaN                   15


/*************************************************************
 * Description: Bit numbers in the CR1 register.
 *
 *************************************************************/
#define SBK                             0
#define RWU                             1
#define RE                              2
#define TE                              3
#define IDLEIE                          4
#define RXNEIE                          5
#define TCIE                            6
#define TXEIE                           7
#define PEIE                            8
#define PS                              9
#define PCE                             10
#define WAKE                            11
#define M                               12
#define UE                              13
#define OVER8                           15


/*************************************************************
 * Description: Bit numbers in the CR2 register.
 *
 *************************************************************/
#define ADD0                            0
#define ADDN                            3
#define LBDL                            5
#define LBDIE                           6
#define LBCL                            8
#define CPHA                            9
#define CPOL                            10
#define CLKEN                           11
#define STOP0                           12
#define STOPN                           13
#define LINEN                           14


/*************************************************************
 * Description: Bit numbers in the CR3 register.
 *
 *************************************************************/
#define EIE                             0
#define IREN                            1
#define IRLP                            2
#define HDSEL                           3
#define NACK                            4
#define SCEN                            5
#define DMAR                            6
#define DMAT                            7 
#define RTSE                            8
#define CTSE                            9
#define CTSIE                           10
#define ONEBIT                          11


/*************************************************************
 * Description: Bit numbers in the GTPR register.
 *
 *************************************************************/
#define PSC0                            0
#define PSCN                            7
#define GT0                             8
#define GTN                             15


/*************************************************************
 * Description: Base addresses of modules.
 *
 *************************************************************/
#define UART1					((volatile UART_t *) 0x40011000)
#define UART2					((volatile UART_t *) 0x40004400)
#define UART6					((volatile UART_t *) 0x40011400)


#endif /* __UART_MAP_H__ */