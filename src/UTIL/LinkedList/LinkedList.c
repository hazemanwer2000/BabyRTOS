/*************************************************************
 * 
 * Filename: LinkedList.c
 * Description: Implementation of a doubly linked list.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#include "LinkedList.h"

volatile LL_node * LL_pop(volatile LL_list *list) {
    volatile LL_node *node = list->head;

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

void LL_push(volatile LL_list *list, volatile LL_node *node) {
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

void LL_enqueue(volatile LL_list *list, volatile LL_node *node) {
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

void LL_remove(volatile LL_list *list, volatile LL_node *node) {
    volatile LL_node *tmp = list->head;

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

void LL_priority_enqueue(volatile LL_list *list, volatile LL_node *node, uint8_t (*compare)(volatile void *, volatile void *)) {
    volatile LL_node *traverse = list->tail;
    
    while (traverse != NULL) {
        if (compare(node->data, traverse->data)) {
            traverse = traverse->prev;
        } else {
            break;
        }
    }

    if (traverse == NULL) {
        LL_push(list, node);
    } else if (traverse == list->tail) {
        LL_enqueue(list, node);
    } else {
        node->next = traverse->next;
        node->prev = traverse;
        traverse->next = node;
        node->next->prev = node;
    }
}