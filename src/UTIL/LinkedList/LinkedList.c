/*************************************************************
 * 
 * Filename: LinkedList.c
 * Description: Implementation of a doubly linked list.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#include "LinkedList.h"

LL_node * LL_pop(LL_list *list) {
    LL_node *node = list->head;

    if (list->length > 0) {
        if (list->length == 1) {
            list->head = NULL; 
            list->tail = NULL;
        } else if (list->length > 1) {
            list->head = list->head->next;
            list->head->prev = NULL;

            node->next = NULL;
        }

        list->length--;
    }

    return node;
}

void LL_push(LL_list *list, LL_node *node) {
    if (list->length == 0) {
        list->head = node;
        list->tail = node;
    } else {
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }

    list->length++;
}

void LL_enqueue(LL_list *list, LL_node *node) {
    if (list->length == 0) {
        list->head = node;
        list->tail = node;
    } else {
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }

    list->length++;
}