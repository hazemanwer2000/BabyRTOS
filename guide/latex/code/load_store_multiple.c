    /* Save registers (Store Multiple Instruction). */
__asm("STMIA R0, {R4-R11}");

    /* Switch stack pointer. */
// ...

    /* Restore registers (Load Multiple Instruction). */
__asm("LDMIA R0, {R4-R11}");