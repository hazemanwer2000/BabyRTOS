/*************************************************************
 * 
 * Filename: Bit_Utils.h
 * Description: Macros and function prototypes, performing various bit manipulation operations.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __BIT_UTILS_H__
#define __BIT_UTILS_H__


/*************************************************************
 * Description: Get mask of all bits (sized as the maximum integral type on a machine).
 * 
 *************************************************************/
#define MSK_BIT(BIT_NO)             (1 << (BIT_NO))


/*************************************************************
 * Description: Get mask, of the most significant bit within a register, of arbitrary size.
 * 
 *************************************************************/
#define MSK_MS_BIT(REG)             (1 << sizeof(REG) * 8 - 1)


/*************************************************************
 * Description: Get mask, from bit 'I' to bit 'J', all inclusive.
 * 
 *************************************************************/
#define MSK_I2J(I, J)               (((1 << ((J) + 1)) - 1) ^ ((1 << (I)) - 1))


/*************************************************************
 * Description: Get mask of all bits (sized as the maximum integral type on a machine).
 * 
 *************************************************************/
#define MSK_ALL                     (-1ll)


/*************************************************************
 * Description: Get mask of alternating bits, 'lsb' being '1' (sized as the 
 *                  maximum integral type on a machine).
 * 
 *************************************************************/
#define MSK_ALT                     (6148914691236517205ull)


/*************************************************************
 * Description: Set, clear, get, and toggle bits within a register (returns, does not assign).
 * 
 *************************************************************/
#define SET_BIT(REG, BIT_NO)        ((REG) | 1 << (BIT_NO))
#define CLR_BIT(REG, BIT_NO)        ((REG) & ~(1 << (BIT_NO)))
#define GET_BIT(REG, BIT_NO)        (((REG) >> (BIT_NO)) & 1)
#define TGL_BIT(REG, BIT_NO)        ((REG) ^ (1 << (BIT_NO)))


/*************************************************************
 * Description: Rotate normally and circularly, a register of arbitrary size.
 *                  Note: To gurantee logical right shift, cast register as unsigned beforehand.
 * 
 *************************************************************/
#define RSHFT_REG(REG, NO)          ((REG) >> (NO))
#define LSHFT_REG(REG, NO)          ((REG) << (NO))
#define CRSHFT_REG(REG, NO)         (((REG) >> (NO)) | ((REG) << sizeof(REG) * 8 - (NO)))
#define CLSHFT_REG(REG, NO)         (((REG) << (NO)) | ((REG) >> sizeof(REG) * 8 - (NO)))


/*************************************************************
 * Description: Set right most zero of a register, of arbitrary size.
 * 
 *************************************************************/
#define SET_RIGHT_MOST_ZERO(REG)    (((REG) + 1) | (REG))


/*************************************************************
 * Description: Set trailing zeros of a register, of arbitrary size.
 * 
 *************************************************************/
#define SET_TRAILING_ZEROS(REG)     (((REG) - 1) | (REG))


/*************************************************************
 * Description: Set trailing zeros of a register, of arbitrary size.
 * 
 *************************************************************/
#define CLR_RIGHT_MOST_ONE(REG)     (((REG) - 1) & (REG))


/*************************************************************
 * Description: Clear trailing ones of a register, of arbitrary size.
 * 
 *************************************************************/
#define CLR_TRAILING_ONES(REG)      (((REG) + 1) & (REG))


/*************************************************************
 * Description: Extract a bit field from a register of arbitrary size.
 * 
 *************************************************************/
#define EXTRACT_FIELD(REG, I, J)                ((MSK_I2J((I), (J)) & (REG)) >> (I))


/*************************************************************
 * Description: Replace a bit field with another bit field in a register of arbitrary size.
 * 
 *************************************************************/
#define REPLACE_FIELD(REG, I, J, FIELD)         ( ((FIELD) << (I)) | ((REG) & ~MSK_I2J((I), (J))) )
#define REPLACE_BIT(REG, I, FIELD)              REPLACE_FIELD(REG, I, I, FIELD)


/*************************************************************
 * Description: Swap every two (even, odd) bits within a register of arbitrary size.
 * 
 *************************************************************/
#define BITWISE_SWAP(REG)           (MSK_ALT & ((REG) >> 1)) | ((MSK_ALT << 1) & ((REG) << 1))


/*************************************************************
 * Description: Concat two binary series of digits.
 * 
 *************************************************************/
#define BIN_CONCAT__(BY, BX)                        (0b##BY##BX)
#define BIN_CONCAT(BY, BX)                          BIN_CONCAT__(BY, BX)


/*************************************************************
 * Description: Make nibble from individual bits (may be macros).
 * 
 *************************************************************/
#define MAKE_NIBBLE__(B3, B2, B1, B0)                   (0b##B3##B2##B1##B0)
#define MAKE_NIBBLE(B3, B2, B1, B0)                     MAKE_NIBBLE__(B3, B2, B1, B0)


/*************************************************************
 * Description: Make byte from individual bits (may be macros).
 * 
 *************************************************************/
#define MAKE_BYTE(B7, B6, B5, B4, B3, B2, B1, B0)       \
            (MAKE_NIBBLE__(B7, B6, B5, B4) << 4 | MAKE_NIBBLE__(B3, B2, B1, B0))


/*************************************************************
 * Description: ALIGN macros.
 * 
 *************************************************************/
#define ALIGN_8(X)            (((X) >> 3) << 3)
#define ALIGN_4(X)            (((X) >> 2) << 2)


/*************************************************************
 * Description: Count number of ones within a register of arbitrary size. 
 * 
 *************************************************************/
char countNumOfOnes(char reg);


#endif /* __BIT_UTILS_H__ */
