// Implementation of (Min) Heap
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include"Heap.h"

/*typedef struct person{
    int age;
    char* name;
    char* type;
    char* destinations;
} Person;

typedef struct Heap {
    Person* arr;
    int size;
    int capacity;
} Heap;*/

void swap(Person*a, Person*b);
void swim(Heap *h, int i);
Heap* initializeHeap(Person* arr, int capacity, int size) {
    Heap *h = calloc(1,sizeof(Heap));
    h->arr = calloc(capacity,sizeof(Person));
    //make our heap 1 indexed to help with our heap stuff so the numbers are nice and aren' ugly and bad
    if (arr != NULL) {
    for (int i = 0; (i < size) && i <= capacity; i++) {
        h->arr[i+1] = arr[i];
    }
    }
    h->size = size;
    h->capacity = capacity;
    heapify(h,0);
    return h;
}

// free memory allocated to Heap pointer h
void destructHeap(Heap** h) {
    void freePersonHEAPMODE(Person *p);
    if (h != NULL && (*h) != NULL) {
        for (int i = 1; i < (*h)->size; i++) {
           freePersonHEAPMODE(&(*h)->arr[i]);
        }
        free(*h);
        *h = NULL;

    }
}
void freePersonHEAPMODE(Person *p) {;
    free((p->type));
    free((p->destinations));
    free(p);
    p = NULL;
}
//add element to a heap, call swim on the element you are adding


//to remove head of heap, swap head of the heap with last element
//then remove the tail
//call sink on the head

// Heap Functionalities ------------------------------

// Maintain Heap property given an index i for heap pointed to by h
void heapify(Heap* h, int i) {
    for (int b = size(h);b > 0; b--) {
        swim(h,b);
    }  
}
//rip NRG and NA's chances at worlds
// void Heapsort(int *A, int length) {
//     array_to_heap(A,A,length,size);
// }
int size(Heap* h) {
    return h->size;
}
int len(Heap* h) {
    return h->capacity;
}
int parent(int i){
    return i/2;
}

int left(int i) {return 2*i;}

int right(int i) {return (2*i)+1;}

//sink or swim, this heap will be made :)
void swim(Heap *h, int i) {
     while (i > 1) {
        int parent = i/2;
        if ((h->arr[i]).age > (h->arr[parent]).age) {
            swap(&(h->arr[i]),&(h->arr[parent]));
            i = parent;
        } else{
            break;
        }
    }
}

// Helper functions for fetching parent, left or right child. Root Node is at index 1



void printHeap(Heap* h) {
    for(int i = 1; i < h->size;i++) {
        printf("%s(%s) ",((h->arr)[i]).name,((h->arr)[i]).type);
    }
}


void swap(Person*a, Person*b) {
    Person temp = *a;
    *a = *b;
    *b = temp;
}
//----------------------------------------------------------------------