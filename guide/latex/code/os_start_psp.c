    /* MRS and MSR are used to read from, and write to */
    /*     special registers, such as CONTROL.         */
    
__asm("MRS R0, CONTROL");
__asm("ORR R0, R0, #0x2");
__asm("MSR CONTROL, R0");