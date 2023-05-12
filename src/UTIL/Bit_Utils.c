/*************************************************************
 * 
 * Filename: Bit_Utils.c
 * Description: Functions, performing various bit manipulation operations.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/


/*************************************************************
 * Description: Count number of ones within a register of arbitrary size. 
 * 
 *************************************************************/
char countNumOfOnes(char reg) {
    int cnt = 0;
    while (reg != 0) {
        reg &= (reg - 1);
        cnt++;
    }
    return cnt;
}