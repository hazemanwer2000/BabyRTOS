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

void LL_remove(LL_list *list, LL_node *node) {
    LL_node *tmp = list->head;

    while (tmp != NULL) {
        if (tmp == node) {
            if (list->length == 1) {
                list->head = NULL;
                list->tail = NULL;
            } else if (list->head == node) {
                list->head = node->next;
                list->head->prev = NULL;
                node->next = NULL;
            } else if (list->tail == node) {
                list->tail = node->prev;
                list->tail->next = NULL;
                node->prev = NULL;
            } else {
                node->next->prev = node->prev;
                node->prev->next = node->next;
                node->next = NULL;
                node->prev = NULL;
            }

            list->length--;
            break;
        } else {
            tmp = tmp->next;
        }
    }
}