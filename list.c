#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List * newList = (List *)malloc(sizeof(List));
    newList->head = NULL;
    newList->tail = NULL;
    newList->current = NULL;
    return newList;
}

void * firstList(List * list) {
    if (list->head != NULL){
        list->current = list->head;
        return list->current->data;
    }
    return NULL;
}

void * nextList(List * list) {
    if (list->current != NULL){
        list->current = list->current->next;
        if (list->current != NULL){
            return list->current->data;
        }
    }
    return NULL;
}

void * lastList(List * list) {
    if (list->tail != NULL){
        list->current = list->tail;
        return list->current->data;
    }
    return NULL;
}

void * prevList(List * list){
    if (list->current != NULL){
        list->current = list->current->prev;
        if (list->current != NULL){
            return list->current->data;
        }
    }
    return NULL;
}

void pushFront(List * list, void * data){
    Node * newNode = createNode(data);
    if (list->head == NULL){
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
    list->current = newNode;
}

void pushBack(List * list, void * data){
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data){
    Node * newNode = createNode(data);
    if (list->current == NULL){
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->next = list->current->next;
        newNode->prev = list->current;
        if (list->current->next != NULL){
            list->current->next->prev = newNode;
        } else {
            list->tail = newNode;
        }
        list->current->next = newNode;
    }
    list->current = newNode;
}

void * popFront(List * list){
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list){
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list){
    if (list->current != NULL){
        Node * nodeToDelete = list->current;
        void * data = nodeToDelete->data;
        if (nodeToDelete->prev != NULL){
            nodeToDelete->prev->next = nodeToDelete->next;
        }else{
            list->head = nodeToDelete->next;
        }
        if(nodeToDelete->next != NULL){
            nodeToDelete->next->prev = nodeToDelete->prev;
        }else{
            list->tail = nodeToDelete->prev;
        }
        free(nodeToDelete);
        list->current = NULL;
        return data;
    }
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}