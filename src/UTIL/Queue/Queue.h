/*************************************************************
 * 
 * Filename: Queue.h
 * Description: Header file of a static queue implementation.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#include "stdint.h"
#include "stdio.h"

typedef struct {
    uint32_t length, capacity;
    uint32_t start, end;
    void **content;
} Queue_t;

typedef enum {
    Queue_status_Ok = 0,
    Queue_status_Full,
    Queue_status_Empty
} Queue_status_t;

void Queue_init(Queue_t *q, void **content, uint32_t capacity);

Queue_status_t Queue_enqueue(Queue_t *q, void *args);

Queue_status_t Queue_dequeue(Queue_t *q, void **ret);