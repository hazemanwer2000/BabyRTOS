# BabyRTOS

A priority-based Real-Time Operating System (RTOS), based on the ARM Cortex-M4 processor.

Major features of the implementation includes,
* Up to 63 task priorities.
* Time-sharing (i.e, round-robin scheduling) between tasks of equal priority.
* Support for multiple OS resources, including *Mutex*, *Semaphore*, and *Queue*.
* Priority inheritance by mutex-locking tasks, by ceiling all waiting tasks.
