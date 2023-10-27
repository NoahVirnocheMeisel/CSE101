#include "List.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: Insert Null Guards, Add Comments, Implement DeleteList Tests

// Creates a pointer to a listObject, allocating memory from the heap.
ListPtr createList(void (*dataPrinter)(void *data)) {
  ListPtr L = calloc(1, sizeof(ListObj));
  L->head = NULL;
  L->dataPrinter = dataPrinter;
  L->length = 0;
  return L;
}

// Takes in a pointer to a list pointer. If the listpointer isn't NULL, the
// function will go through each node in the list and free the memory it is
// taking, before freeing the list.
void destroyList(ListPtr *pL) {
  NodePtr ptr;
  NodePtr ptr2;
  ptr = (*pL)->head;
  while (ptr != NULL) {
    ptr2 = ptr->next;
    if (ptr->data != NULL) {
      free(ptr->data);
    }
    free(ptr);
    ptr = ptr2;
  }
  free(*pL);
  *pL = NULL;
  pL = NULL;
}
// returns the length of a list.
int lengthList(ListPtr L) { return L->length; }
// Goes through a list and prints each element, from head to tail.
void printList(ListPtr L) {
  if (L == NULL) {
    return;
  }
  NodePtr ptr;
  ptr = L->head;
  while (ptr != NULL) {
    L->dataPrinter(ptr->data);
    ptr = ptr->next;
  }
}
// Takes in an index of an element. This function goes through each element in
// the list and decrements a counter each element, until it reaches 0 and then
// returns the elements we are on.
void *getList(ListPtr L, int i) {
  int n = i;
  NodePtr N;
  if (L->head == NULL) {
    return NULL;
  } else {
    N = L->head;
    while ((N->next != NULL) && n > 0) {
      N = (N->next);
      n--;
    }
    return N->data;
    //
  }
  // Your implementation of getList()
}
// Functions similar to getList, except the element our counter stops on will
// get deleted. Has a specical condition for if  i = 0 so that it swaps the head
// correctley.
void *deleteList(ListPtr L, int i) {
  int n = i;
  NodePtr N;
  NodePtr M;
  if (L == NULL || L->head == NULL) {
    return NULL;
  }
  if (n == 0) {
    N = L->head;
    void *val = N->data;
    L->head = (L->head)->next;
    free(N->data);
    free(N);
    (L->length)--;
    return val;
  } else {
    N = L->head;
    while ((N->next != NULL) && n > 0) {
      M = N;
      N = (N->next);
      n--;
    }
    void *val = N->data;
    M->next = N->next;
    free(N);
    (L->length)--;
    return val;
    //
  }
  // Your implementation of deleteList()
}
// Creates a new Node for our list and then adds it to the tail of the linked
// list.
bool appendList(ListPtr L, void *data) {
  NodePtr N = calloc(1, sizeof(NodeObj));
  N->data = data;
  NodePtr P = NULL;
  if (L->head == NULL) {
    L->head = N;
    (L->length)++;
    return true;
  } else {
    P = L->head;
    while (P->next != NULL)
      P = (P->next);
    P->next = N;
    (L->length)++;
    return true;
  }
  return false;
}
