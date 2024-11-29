#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../include/heap.h"

void generateRandomArray(int* array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % size;
    }
}

void benchmarkHeapConstruction() {
    int sizes[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 30000, 40000, 50000, 60000
        , 70000, 80000, 90000, 100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000
         , 1000000,2000000 ,3000000, 4000000, 5000000 , 6000000 , 7000000,
          8000000, 9000000 , 10000000 ,20000000 ,30000000, 40000000, 50000000 , 60000000 , 70000000,
          80000000, 90000000 ,100000000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    FILE* file = fopen("../../results/heaps/heap_construction_times.csv", "w");

    if (!file) {
        printf("Failed to create results file.\n");
        return;
    }

    fprintf(file, "Size,Time_NlogN,Time_N\n");

    for (int i = 0; i < numSizes; i++) {
        int size = sizes[i];
        int* array = (int*)malloc(size * sizeof(int));
        generateRandomArray(array, size);

        MinHeap* heap = createHeap(size);

        clock_t start = clock();
        buildMinHeap_NlogN(heap, array, size);
        clock_t end = clock();
        double time_NlogN = (double)(end - start) / CLOCKS_PER_SEC;

        heap->size = 0;

        start = clock();
        buildMinHeap_N(heap, array, size);
        end = clock();
        double time_N = (double)(end - start) / CLOCKS_PER_SEC;

        fprintf(file, "%d,%.6f,%.6f\n", size, time_NlogN, time_N);
        printf("number: %d, time_of_nlogn: %.6f s, time_of_n: %.6f s\n", size, time_NlogN, time_N);

        free(array);
        freeHeap(heap);
    }

    fclose(file);
}

int main() {
    srand(time(NULL));
    benchmarkHeapConstruction();
    return 0;
}
