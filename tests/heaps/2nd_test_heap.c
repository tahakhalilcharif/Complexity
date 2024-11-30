#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "minHeap.h"

void generateRandomArray(int* array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % size;
    }
}

int* generateSizes(int* numSizes) {
    int totalSizes = 1000;
    int start = 1000;      
    int max = 100000000;   
    int* sizes = (int*)malloc(totalSizes * sizeof(int));

    if (!sizes) {
        *numSizes = 0;
        return NULL;
    }

    double factor = pow((double)max / start, 1.0 / (totalSizes - 1));

    for (int i = 0; i < totalSizes; i++) {
        sizes[i] = (int)(start * pow(factor, i));
    }

    for (int i = 1; i < totalSizes; i++) {
        if (sizes[i] <= sizes[i - 1]) {
            sizes[i] = sizes[i - 1] + 1;
        }
    }

    *numSizes = totalSizes;
    return sizes;
}

void benchmarkHeapConstruction() {
    int numSizes;
    int* sizes = generateSizes(&numSizes);

    FILE* file = fopen("../../results/heaps/heap_construction_times.csv", "w");
    if (!file) {
        printf("Failed to create results file.\n");
        free(sizes);
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
        printf("iteration n : %d , Size: %d, Time_NlogN: %.6f s, Time_N: %.6f s\n", i ,size, time_NlogN, time_N);

        free(array);
        freeHeap(heap);
    }

    fclose(file);
    free(sizes);
}

int main() {
    srand(time(NULL));
    benchmarkHeapConstruction();
    return 0;
}
