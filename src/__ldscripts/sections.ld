
__stack = ORIGIN(RAM) + LENGTH(RAM);
ENTRY(_start)

SECTIONS
{
    .isr_vector : ALIGN(4)
    {
        FILL(0xFF)
        __vectors_start = . ;
        
        KEEP(*(.isr_vector))
        *(.after_vectors .after_vectors.*)
    } >FLASH
    
    .text : ALIGN(4)
    {
        *(.text .text.*)
        *(.rodata .rodata.* .constdata .constdata.*)
    } >FLASH

    __idata_start = LOADADDR(.data);

    .data : ALIGN(4)
    {
    	FILL(0xFF)
        __data_start = . ;

		*(.data_begin .data_begin.*)
		*(.data .data.*)
		*(.data_end .data_end.*)

	    . = ALIGN(4);
        __data_end = . ;

    } >RAM AT>FLASH

    .bss (NOLOAD) : ALIGN(4)
    {
        FILL(0xFF)
        __bss_start = . ;

        *(.bss_begin .bss_begin.*)
        *(.bss .bss.*)
        *(COMMON)
        *(.bss_end .bss_end.*)
	    
        . = ALIGN(4);
        __bss_end = . ;
    } >RAM
}
