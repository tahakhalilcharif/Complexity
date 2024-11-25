#ifndef HEAP_H
#define HEAP_H

typedef struct {
    int *data;      
    int size;       
    int capacity;  
} MinHeap;

MinHeap* createHeap(int capacity);
void insertMinHeap(MinHeap* heap, int value);
int extractMin(MinHeap* heap);
void minHeapify(MinHeap* heap, int index);
void buildMinHeap_NlogN(MinHeap* heap, int* array, int n);
void buildMinHeap_N(MinHeap* heap, int* array, int n);
void freeHeap(MinHeap* heap);
void displayHeap(MinHeap* heap);

#endif
