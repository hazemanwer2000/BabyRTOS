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
    void *data;
    struct LL_node *next;
    struct LL_node *prev;
} LL_node;

typedef struct {
    LL_node *head;
    LL_node *tail;
    uint32_t length;
} LL_list;

LL_node * LL_pop(LL_list *list);
void LL_push(LL_list *list, LL_node *node);
void LL_enqueue(LL_list *list, LL_node *node);
void LL_remove(LL_list *list, LL_node *node);

#endif      /* __LINKED_LIST_H__ */