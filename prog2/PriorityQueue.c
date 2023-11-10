#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include"Heap.h"
#include"PriorityQueue.h"
void swap(void *a, void*b);
// returns the oldest person in the PQ, without removing that person from the PQ.
Person* getMax(Heap* heap) {
    if (size(heap)>= 1) {
    return &(heap->arr[1]);
    }
    return NULL;
}
//Gets the root node(indexed 0 until I figure out if needs to be at 1 for grading or something idk)
//and then swaps the root with the last node in the tree. Then, the last node is freed and the heap->size is decreased.
//then we just heapify the entire tree(if I implement sink can just call sink on the root but haven't done that yet)
Person* extractMax(Heap* heap) {
    Person* return_val = calloc(1,sizeof(Person));
    *return_val = heap->arr[1];
    //printf("Before Swap %s\n",return_val->name);
    Person temp = heap->arr[1];
    heap->arr[1] = heap->arr[heap->size];
    heap->arr[heap->size] = temp; 
    //printf("After Swap %s\n",return_val->name);
    heap->size--;
    printf("SIZE: %d\n",size(heap));
    heapify(heap,1);
    return return_val;
}
//[0,1,2,3,4,5, ,]
// inserts the person into the PQ
void insert(Heap* heap, Person* person) {
    void freePersonPQMODE(Person *p);
    heap->size++;
    if (heap->capacity > heap->size) {
    heap->arr[heap->size] = *p;
    }
    
}

// Updates the age of the person at index, index, in the PQ, to new_priority
void increasePriority(Heap* heap, int index, int new_priority) {
if (heap->size < heap->capacity && heap != NULL && &(heap->arr[index]) != NULL) {
    heap->arr[index].age = new_priority;
    heapify(heap,1);
}
}

void freePersonPQMODE(Person *p) {;
    free((p->type));
    free((p->destinations));
    free(p);
    p = NULL;
}

// heap->size++;
//     //printf("Insertion:%d %d %s\n",heap->size,heap->capacity,person->name);
//     if (heap->size < heap->capacity && heap != NULL && person != NULL) {
//     heap->arr[heap->size] = *person;
//     heapify(heap,1);
//     //check if the size will be the capacity of the heap, and if so adjust the heap array to be double it's current size.
//     } else if (heap->size >= heap->capacity && heap != NULL && person != NULL ) {
//     heap->capacity = heap->capacity*2 + 1;
//     //this might not work as intended. I need to see how I am implementing the heap in the main program, and see if I should free it. 
//     Person* arr = calloc(heap->capacity,sizeof(Person));
//     for (int index = 1; index < heap->capacity/2; index++) {
//         arr[index] = heap->arr[index];
//     }
//     heap->arr = arr;
//     //after copying old array into a new array, insert our element.
//     heap->arr[heap->size] = *person;
    

//     //Why is heapify changing the name to NULL???
//     heapify(heap,1);
//     }