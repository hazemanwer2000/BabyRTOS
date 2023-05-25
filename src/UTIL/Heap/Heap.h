/*************************************************************
 * 
 * Filename: Heap.h
 * Description: Header file of a heap.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdint.h>
#include <stdio.h>

typedef uint8_t (*Heap_comparator_t)(void *, void *);          /* if '1', first argument is prioritized. */

typedef struct {
    void **array;
    uint32_t length;
    Heap_comparator_t cmp;
} Heap_t;

void Heap_init(Heap_t *heap, void **array, Heap_comparator_t cmp);

void Heap_insert(Heap_t *heap, void *data);

void * Heap_remove(Heap_t *heap);

#endif      /* __HEAP_H__ */