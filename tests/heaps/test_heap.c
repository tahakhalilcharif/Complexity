#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "minHeap.h"

void ensure_directory(const char* path) {
    #ifdef _WIN32
        _mkdir(path); // Windows
    #else
        mkdir(path, 0777); // Unix
    #endif
}

int* readTestValuesFromCSV(const char* filename, int* numValues) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Can't open test values file.\n");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        fclose(file);
        *numValues = 0;
        return NULL;
    }

    int count = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        count++;
    }

    int* values = (int*)malloc(count * sizeof(int));
    if (!values) {
        perror("Memory allocation failed.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    rewind(file);
    fgets(buffer, sizeof(buffer), file);

    int index = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        values[index++] = atoi(buffer);
    }

    fclose(file);
    *numValues = count;
    return values;
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
        searchHeap(heap, rand() % 1000);
    }
    end = clock();
    double search_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    fprintf(file, "%d,%.6f,%.6f,%.6f\n", n, insert_time, delete_time, search_time);

    fclose(file);
    freeHeap(heap);
}

int main() {
    const char* results_file = "../../results/heaps/heap_benchmark.csv";
    const char* test_values_file = "../../tests/test_values.csv";

    ensure_directory("../../results/heaps");
    ensure_directory("../../tests");

    FILE* file = fopen(results_file, "r");
    if (file == NULL) {
        file = fopen(results_file, "w");
        fprintf(file, "n,insert_time,delete_time,search_time\n");
    }
    fclose(file);

    int numIterations;
    int* iterations = readTestValuesFromCSV(test_values_file, &numIterations);

    if (iterations == NULL || numIterations == 0) {
        fprintf(stderr, "No test values found in %s.\n", test_values_file);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < numIterations; i++) {
        printf("Running test for n=%d...\n", iterations[i]);
        benchmark_heap_operations(results_file, iterations[i]);
    }

    printf("Completed tests, results saved in: %s\n", results_file);
    free(iterations);
    return 0;
}
