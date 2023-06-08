# BabyRTOS

A priority-based Real-Time Operating System (RTOS), based on the ARM Cortex-M4 processor.

Major features of the implementation includes,
* Up to 63 task priorities.
* Time-sharing (i.e, round-robin scheduling) between tasks of equal priority.
* Support for multiple OS resources, including *Mutex*, *Semaphore*, and *Queue*.
* Priority inheritance by mutex-locking tasks, by ceiling all waiting tasks.

*Notes:*
* Under */src* is a sample application, based on the STM32F401CC micro-controller. 
* The implementation resides under,
  * [*/src/OS/OS.c*](/src/OS/OS.c) and,
  * [*/src/OS/OS.h*](/src/OS/OS.h).
* Other implementation dependencies are,
  * [*/src/MCAL/UTIL/Std_Types.h*](/src/MCAL/UTIL/Std_Types.h), 
  * [*/src/UTIL/LinkedList*](/src/UTIL/LinkedList) and,
  * [*/src/UTIL/Queue*](/src/UTIL/Queue).
