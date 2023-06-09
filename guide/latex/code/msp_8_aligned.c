    /* Ensure MSP is double-word aligned. */
    
__asm("MRS R0, MSP");
__asm("AND R0, R0, #0xFFFFFFFC");
__asm("MSR MSP, R0");