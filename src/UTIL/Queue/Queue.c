/*************************************************************
 * 
 * Filename: Queue.c
 * Description: Source file of a static queue implementation.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#include "Queue.h"

void Queue_init(Queue_t *q, void **content, uint32_t capacity) {
    q->capacity = capacity;
    q->length = q->start = q->end = 0;
    q->content = content;
}

Queue_status_t Queue_enqueue(Queue_t *q, void *args) {
    Queue_status_t status = Queue_status_Ok;

    if (q->length == q->capacity) {
        status = Queue_status_Full;
    } else {
        q->content[q->end++] = args;

        if (q->end == q->capacity) {
            q->end = 0;
        }

        q->length++;
    }

    return status;
}

Queue_status_t Queue_dequeue(Queue_t *q, void **ret) {  
    Queue_status_t status = Queue_status_Ok;

    if (q->length == 0) {
        status = Queue_status_Empty;
    } else {
        *ret = q->content[q->start++];

        if (q->start == q->capacity) {
            q->start = 0;
        }

        q->length--;
    }

    return status;
}