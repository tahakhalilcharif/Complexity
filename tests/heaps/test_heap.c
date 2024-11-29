#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../../include/heap.h"

void ensure_directory(const char* path) {
    #ifdef _WIN32
        _mkdir(path); // Windows
    #else
        mkdir(path, 0777); // Unix
    #endif
}

int* generateIterations(int* numIterations) {
    int totalIterations = 100;
    int start = 1;
    int max = 100000000;
    int* iterations = (int*)malloc(totalIterations * sizeof(int));

    if (!iterations) {
        *numIterations = 0;
        return NULL;
    }

    double factor = pow((double)max / start, 1.0 / (totalIterations - 1));

    for (int i = 0; i < totalIterations; i++) {
        iterations[i] = (int)(start * pow(factor, i));
    }

    for (int i = 1; i < totalIterations; i++) {
        if (iterations[i] <= iterations[i - 1]) {
            iterations[i] = iterations[i - 1] + 1;
        }
    }

    *numIterations = totalIterations;
    return iterations;
}

void benchmark_heap_operations(const char* filename, int n) {
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        perror("Can't open results file.\n");
        exit(EXIT_FAILURE);
    }

    MinHeap* heap = createHeap(n);

    clock_t start = clock();
    for (int i = 0; i < n; i++) {
        insertMinHeap(heap, rand() % 1000); 
    }
    clock_t end = clock();
    double insert_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    for (int i = 0; i < n; i++) {
        extractMin(heap);
    }
    end = clock();
    double delete_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < heap->size; j++) {
            if (heap->data[j] == (rand() % 1000)) {
                break;
            }
        }
    }
    end = clock();
    double search_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    fprintf(file, "%d,%.6f,%.6f,%.6f\n", n, insert_time, delete_time, search_time);

    fclose(file);
    freeHeap(heap);
}

int main() {
    const char* results_file = "../../results/heaps/heap_benchmark.csv";

    ensure_directory("../../results/heaps");

    FILE* file = fopen(results_file, "r");
    if (file == NULL) {
        file = fopen(results_file, "w");
        fprintf(file, "n,insert_time,delete_time,search_time\n");
    }
    fclose(file);

    int numIterations;
    int* iterations = generateIterations(&numIterations);

    for (int i = 0; i < numIterations; i++) {
        printf("Running test for n=%d...\n", iterations[i]);
        benchmark_heap_operations(results_file, iterations[i]);
    }

    printf("Completed tests, results saved in: %s\n", results_file);
    free(iterations);
    return 0;
}
