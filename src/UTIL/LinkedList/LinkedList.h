/*************************************************************
 * 
 * Filename: LinkedList.h
 * Description: Header file of a doubly linked list.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include "Std_Types.h"

#define LL_dequeue              LL_pop

typedef struct LL_node {
    volatile void *data;
    volatile struct LL_node *next;
    volatile struct LL_node *prev;
} LL_node;

typedef struct {
    volatile LL_node *head;
    volatile LL_node *tail;
    volatile uint32_t length;
} LL_list;

volatile LL_node * LL_pop(volatile LL_list *list);
void LL_push(volatile LL_list *list, volatile LL_node *node);
void LL_enqueue(volatile LL_list *list, volatile LL_node *node);
void LL_remove(volatile LL_list *list, volatile LL_node *node);
void LL_priority_enqueue(volatile LL_list *list, volatile LL_node *node, uint8_t (*compare)(volatile void *, volatile void *));

#endif      /* __LINKED_LIST_H__ */