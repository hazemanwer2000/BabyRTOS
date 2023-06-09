OS_REQ_status_t OS_wait(OS_task *task) {
    OS_REQ_wait_t req = {
        .base.id = OS_REQ_id_WAIT,
        .task = task
    };

        /* Load 'req' address into R0 */
        /*     then make 'SVC' call   */
    __asm("MOV R0, SP");
    __asm("SVC #0");

        /* Memory-Barrier Synchronization Instructions. */
        /*     to force the execution of SVC before any */
        /*     subsequent instruction. */
    __asm("DSB");
    __asm("ISB")

    return req.base.status;
}