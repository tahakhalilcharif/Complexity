#include <stdio.h>
#include <assert.h>
#include "../include/heap.h"


void test_createHeap() {
    MinHeap* heap = createHeap(10);
    assert(heap != NULL);
    assert(heap->size == 0);
    assert(heap->capacity == 10);
    freeHeap(heap);
    printf("test_createHeap passed\n");
}

void test_insertMinHeap() {
    MinHeap* heap = createHeap(10);
    insertMinHeap(heap, 3);
    insertMinHeap(heap, 1);
    insertMinHeap(heap, 6);
    insertMinHeap(heap, 5);
    insertMinHeap(heap, 2);
    insertMinHeap(heap, 4);

    assert(heap->data[0] == 1);
    freeHeap(heap);
    printf("test_insertMinHeap passed\n");
}

void test_extractMin() {
    MinHeap* heap = createHeap(10);
    insertMinHeap(heap, 10);
    insertMinHeap(heap, 15);
    insertMinHeap(heap, 20);
    insertMinHeap(heap, 17);
    insertMinHeap(heap, 8);

    int min = extractMin(heap);
    assert(min == 8);
    assert(heap->data[0] == 10);
    freeHeap(heap);
    printf("test_extractMin passed\n");
}

void test_buildMinHeap_NlogN() {
    int array[] = {4, 10, 3, 5, 1};
    int n = sizeof(array) / sizeof(array[0]);
    MinHeap* heap = createHeap(n);

    buildMinHeap_NlogN(heap, array, n);

    assert(heap->data[0] == 1);
    freeHeap(heap);
    printf("test_buildMinHeap_NlogN passed\n");
}

void test_buildMinHeap_N() {
    int array[] = {4, 10, 3, 5, 1};
    int n = sizeof(array) / sizeof(array[0]);
    MinHeap* heap = createHeap(n);

    buildMinHeap_N(heap, array, n);

    assert(heap->data[0] == 1);
    freeHeap(heap);
    printf("test_buildMinHeap_N passed\n");
}

int main() {
    test_createHeap();
    test_insertMinHeap();
    test_extractMin();
    test_buildMinHeap_NlogN();
    test_buildMinHeap_N();

    printf("All tests passed successfully.\n");
    return 0;
}
