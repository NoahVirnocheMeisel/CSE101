#include "Queue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
// Implemeting Queue

/*

It returns a pointer to the instantiated Queue
*/
Queue *initializeQueue(int n, char **array) {
  Queue *Q = calloc(1, sizeof(Queue));
  Q->size = n;
  Q->array = array;
  return Q;
}
//------------------------------------------------------------------------

/*
TODO: implement Queue destructor - this function frees memory allocated to
Queue-make sure to delete strings and the array
*/
void destructQueue(Queue **q) {
  if (q != NULL && *q != NULL) {
    for (int i = 0; i < (*q)->size; i++) {
      free(((*q)->array)[i]);
    }
    free((*q)->array);
    free(*q);
    *q = NULL;
    q = NULL;
  }
}
//------------------------------------------------------------------------

/* TODO: implement the 'enqueue' functionality
This function takes in a queue pointer and a username and adds the username to
queue
*/
// I hate this
void enqueue(Queue *q, char *name) {
  (q->size)++;
  char **new = calloc(q->size, sizeof(char*));
  if (q->size-1 > 0) {
    for (int i = 0; i < q->size - 1; i++) {
      new[i] = q->array[i];
    }
  }
  new[(q->size)-1] = name;
  if(q->array != NULL) {
  free(q->array);
  }
  q->array = new;
}

//------------------------------------------------------------------------

/* TODO: implement the 'dequeue' functionality
This function takes in a queue pointer and removes element from head of the
queue Print "Empty Queue" if there's not element to remove
*/
void dequeue(Queue *q) {
  if (q->size == 0) {
    printf("Empty Queue\n");
  } else {
    (q->size)--;
    char **new = calloc(q->size, sizeof(char*));
    if (q->size > 0) {
    for (int i = 0; i < q->size; i++) {
      new[i] = q->array[i + 1];
    }
    }
    free(q->array);
    q->array = new;
  }

  }


//------------------------------------------------------------------------

/* TODO: implement the printQueue
This function takes in a queue pointer and prints the contents of the queue in
order (head to tail)
*/

char *front(Queue *q) { return q->array[0]; }


void printQueue(Queue *q) {
  for (int i = 0; i < q->size; i++) {
    printf("%s\n", (q->array)[i]);
  }
  printf("\n");
  }


//------------------------------------------------------------------------

/* TODO: implement the count
This function takes in a queue pointer and returns the 'count' field of the
queue
*/
int count(Queue *q) { return q->size; }
