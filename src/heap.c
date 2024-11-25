#include <stdio.h>
#include <stdlib.h>
#include "../include/heap.h"


MinHeap* createHeap(int capacity) {
    MinHeap* heap = (MinHeap*) malloc(sizeof(MinHeap));
    heap->data = (int*) malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void insertMinHeap(MinHeap* heap, int value) {
    if (heap->size == heap->capacity) {
        printf("Le tas est plein\n");
        return;
    }
    
    int i = heap->size++;
    heap->data[i] = value;

    while (i != 0 && heap->data[i] < heap->data[(i - 1) / 2]) {
        int temp = heap->data[i];
        heap->data[i] = heap->data[(i - 1) / 2];
        heap->data[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

int extractMin(MinHeap* heap) {
    if (heap->size <= 0) {
        return -1; 
    } else if (heap->size == 1) {
        return heap->data[--heap->size];
    }

    int root = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    minHeapify(heap, 0);

    return root;
}

void minHeapify(MinHeap* heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->data[left] < heap->data[smallest])
        smallest = left;
    if (right < heap->size && heap->data[right] < heap->data[smallest])
        smallest = right;

    if (smallest != index) {
        int temp = heap->data[index];
        heap->data[index] = heap->data[smallest];
        heap->data[smallest] = temp;
        minHeapify(heap, smallest);
    }
}

void buildMinHeap_NlogN(MinHeap* heap, int* array, int n) {
    heap->size = 0;
    for (int i = 0; i < n; i++) {
        insertMinHeap(heap, array[i]);
    }
}

void buildMinHeap_N(MinHeap* heap, int* array, int n) {
    for (int i = 0; i < n; i++) {
        heap->data[i] = array[i];
    }
    heap->size = n;

    for (int i = (n / 2) - 1; i >= 0; i--) {
        minHeapify(heap, i);
    }
}

void freeHeap(MinHeap* heap) {
    free(heap->data);
    free(heap);
}

void displayHeap(MinHeap* heap) {
    if (heap->size == 0) {
        printf("Heap is empty.\n");
        return;
    }

    printf("Heap elements: ");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}
