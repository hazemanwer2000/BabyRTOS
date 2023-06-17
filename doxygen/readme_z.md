
A pre-emptive priority-based Real-Time Operating System (RTOS), based on the ARM Cortex-M4 processor.

Major features of the implementation includes,
* Up to 63 task priorities.
* Time-sharing (i.e, round-robin scheduling) between tasks of equal priority.
* Support for multiple OS resources, including `OS_mutex`, `OS_semaphore`, and `OS_queue`.
* Priority inheritance by mutex-locking tasks, by ceiling all waiting tasks.

> Notes

* Under `/src` is a sample application, based on the STM32F401CC micro-controller.
* The implementation resides under,
  * `/src/OS/OS.c` and,
  * `/src/OS/OS.h`.
* Other implementation dependencies are,
  * `/src/MCAL/UTIL/Std_Types.h`, 
  * `/src/UTIL/LinkedList` and,
  * `/src/UTIL/Queue`.
* The implementation uses the *SysTick* ISR for tracking OS ticks. 
  * Its clock configuration is the responsibility of the Application.
  * The interrupt is automatically enabled by `OS_init`. 
  * The timer is automatically started by `OS_start`.
* Zero interrupt-priority is reserved, and should not be assigned to any other interrupt.
* Interrupt pre-emption in the system is automatically disabled by `OS_init`.
* All system resources (i.e, tasks, mutexes, semaphores, queues) must be zero-initialized (i.e, defined as global variables).

> Links

* [Codebase](https://github.com/hazemanwer2000/BabyRTOS)
* [Documentation](https://hazemanwer2000.github.io/BabyRTOS)
* [Implementation Guide](guide/RTOS_from_scratch.pdf)