#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} MaxHeap;

MaxHeap* createMaxHeap(int capacity);
void insertMaxHeap(MaxHeap* heap, int value);
int extractMax(MaxHeap* heap);
void maxHeapify(MaxHeap* heap, int index);
void buildMaxHeap_NlogN(MaxHeap* heap, int* array, int n);
void buildMaxHeap_N(MaxHeap* heap, int* array, int n);
void freeMaxHeap(MaxHeap* heap);
void displayMaxHeap(MaxHeap* heap);
int searchMaxHeap(MaxHeap* heap, int value);

#endif
