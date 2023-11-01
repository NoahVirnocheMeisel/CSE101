// Implementation of (Min) Heap
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include"Heap.h"
/* TODO: declare the Heap struct as in the header file
This Heap struc has the following fields:
- len: length of the array used for implementing the heap
- size: number of elements in the backbone array that are 'heapified' or ordered as heap
- array: (pointer to) array used for implementing the heap
- id: (pointer to) array of client id used for implementing the heap
*/
struct Heap {
    int len;
    int size;
    int *array;
    int*id;
}

Heap* initializeHeap(int len, int h_size, int* arr, int* id) {
    Heap *h = calloc(1,sizeof(Heap));
    h->len = len;
    h-size = h_size;
    h->array = arr;
    h->id = id;
    return h;
}

// free memory allocated to Heap pointer h
void destructHeap(Heap** h) {
    return NULL;
}


// Heap Functionalities ------------------------------

// Maintain Heap property given an index i for heap pointed to by h
void heapify(Heap* h, int i) {
    int left = left(i);
    int right = right(i);
    int smallest = 0;
    if (left <= h->size && h->array[left] < h->array[i]) {
        smallest = left;
    } else {
        smallest = i;
    }
    if (right <= h->size && h->array[right] < h->array[largest]) {
        smallest = right;
    }
    if (smallest != i) {
        swap(h->array,i,smallest);
        heapify(h,smallest);
    }
}
void Heapsort(int *A, int length) {
    array_to_heap(A,A,length,size);
}


// Build heap from array of ints A
Heap* array_to_Heap(int* A, int* id, int len, int size) {
    Heap *h = initializeHeap(A,id,len,size);
    for (int i = h->size/2; i > 0;i--) {
        heapify(h,i);
    }
    return h;
}

// Return int corresponding to size of Heap* h

int size(Heap* h) {
    return h->size;
}

int len(Heap* h) {
    return h->len;
}


// Helper functions for fetching parent, left or right child
int parent(int i) {return i/2;}
int left(int i) {return 2*i;}
int right(int i) {return 2*i + 1;}
// Helper for replacing A[i] and A[j] elements in an array
void swap(int* A, int i, int j) {
    int temp;
    temp = A[i];
    A[i] = A[j];
    A[j] = temp;    
}
void printHeap(Heap* h);


//----------------------------------------------------------------------