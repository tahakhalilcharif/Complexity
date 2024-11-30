#include "maxHeap.H"

MaxHeap* createMaxHeap(int capacity) {
    MaxHeap* heap = (MaxHeap*) malloc(sizeof(MaxHeap));
    heap->data = (int*) malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void insertMaxHeap(MaxHeap* heap, int value) {
    if (heap->size == heap->capacity) {
        printf("Heap is full\n");
        return;
    }
    
    int i = heap->size++;
    heap->data[i] = value;

    while (i != 0 && heap->data[i] > heap->data[(i - 1) / 2]) {
        int temp = heap->data[i];
        heap->data[i] = heap->data[(i - 1) / 2];
        heap->data[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

int extractMax(MaxHeap* heap) {
    if (heap->size <= 0) {
        return -1; 
    } else if (heap->size == 1) {
        return heap->data[--heap->size];
    }

    int root = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    maxHeapify(heap, 0);

    return root;
}

void maxHeapify(MaxHeap* heap, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->data[left] > heap->data[largest])
        largest = left;
    if (right < heap->size && heap->data[right] > heap->data[largest])
        largest = right;

    if (largest != index) {
        int temp = heap->data[index];
        heap->data[index] = heap->data[largest];
        heap->data[largest] = temp;
        maxHeapify(heap, largest);
    }
}

void buildMaxHeap_NlogN(MaxHeap* heap, int* array, int n) {
    heap->size = 0;
    for (int i = 0; i < n; i++) {
        insertMaxHeap(heap, array[i]);
    }
}

void buildMaxHeap_N(MaxHeap* heap, int* array, int n) {
    for (int i = 0; i < n; i++) {
        heap->data[i] = array[i];
    }
    heap->size = n;

    for (int i = (n / 2) - 1; i >= 0; i--) {
        maxHeapify(heap, i);
    }
}

void freeMaxHeap(MaxHeap* heap) {
    free(heap->data);
    free(heap);
}

void displayMaxHeap(MaxHeap* heap) {
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

int searchMaxHeap(MaxHeap* heap, int value) {
    for (int i = 0; i < heap->size; i++) {
        if (heap->data[i] == value) {
            return i;
        }
    }
    return -1;
}
