/*************************************************************
 * 
 * Filename: Heap.c
 * Description: Implementation of a heap.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#include "Heap.h"
#include "Utils.h"

#define BT_PARENT(I)                ((((I) + 1) / 2) - 1)
#define BT_LCHILD(I)                ((((I) + 1) * 2) - 1)
#define BT_RCHILD(I)                (BT_LCHILD(I) + 1)

void Heap_init(Heap_t *heap, void **array, Heap_comparator_t cmp) {
    heap->length = 0;
    heap->array = array;
    heap->cmp = cmp;
}

void Heap_insert(Heap_t *heap, void *data) {
    uint32_t i_child = heap->length;
    uint32_t i_parent = BT_PARENT(i_child);
    void **array = heap->array;

    array[i_child] = data;
    
    if (heap->length > 0) {
        while (1) {
            if (heap->cmp(array[i_child], array[i_parent])) {
                swap(array + i_child, array + i_parent);
            } else {
                break;             /* Further shifting is un-necessary. */
            }
                
            if (i_parent == 0) {
                break;             /* Root node reached. */
            }

            i_child = i_parent;
            i_parent = BT_PARENT(i_child);
        }
    }

    heap->length++;
}

void * Heap_remove(Heap_t *heap) {
    uint32_t i_parent = 0;
    uint32_t i_lchild = BT_LCHILD(i_parent);
    uint32_t i_rchild = i_lchild + 1;
    uint8_t stop_flag = 0;
    void **array = heap->array;
    void *removed = array[i_parent];

    heap->length--;
    swap(array, array + heap->length);

    while (i_lchild < heap->length && i_rchild < heap->length) {
        if (heap->cmp(array[i_parent], array[i_lchild]) && heap->cmp(array[i_parent], array[i_rchild])) {
            stop_flag = 1;
            break;                      /* Further shifting is unnecessary. */
        }

        if (heap->cmp(array[i_lchild], array[i_rchild])) {
            swap(array + i_lchild, array + i_parent);
            i_parent = i_lchild;
        } else {
            swap(array + i_rchild, array + i_parent);
            i_parent = i_rchild;
        }

        i_lchild = BT_LCHILD(i_parent);
        i_rchild = i_lchild + 1;
    }

    if (stop_flag == 0 && i_lchild < heap->length) {           /* Case: Left-child only */
        if (heap->cmp(array[i_lchild], array[i_parent])) {
            swap(array + i_parent, array + i_lchild);
        }
    }

    return removed;
}
