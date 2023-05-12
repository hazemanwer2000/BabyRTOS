
extern unsigned int __vectors_start;

extern unsigned int __idata_start;
extern unsigned int __data_start;
extern unsigned int __data_end;

extern unsigned int __bss_start;
extern unsigned int __bss_end;

extern void main(void);

inline void __attribute__((always_inline))
_initialize_data(unsigned int* from, unsigned int* region_begin, unsigned int* region_end) {
    unsigned int *p = region_begin;
    while (p < region_end) *p++ = *from++;
}

inline void __attribute__((always_inline))
_initialize_bss(unsigned int* region_begin, unsigned int* region_end) {
    unsigned int *p = region_begin;
    while (p < region_end) *p++ = 0;
}

void __attribute__ ((section(".after_vectors"),noreturn))
_start(void) {

        /* Re-locate vector table */
    (*(volatile unsigned int *) 0xE000ED08) = (unsigned int) &__vectors_start;

    _initialize_data(&__idata_start, &__data_start, &__data_end);
    _initialize_bss(&__bss_start, &__bss_end);
    
    main();

    while(1);   
}