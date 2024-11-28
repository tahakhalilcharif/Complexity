#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../../include/heap.h"

void ensure_directory(const char* path) {
    #ifdef _WIN32
        _mkdir(path);//windows
    #else
        mkdir(path, 0777);//unix
    #endif
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

    int iterations[] = {
        1, 10, 100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 
        20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000, 200000,
        300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000
    };
    int num_iterations = sizeof(iterations) / sizeof(iterations[0]);

    for (int i = 0; i < num_iterations; i++) {
        printf("Running test for n=%d...\n", iterations[i]);
        benchmark_heap_operations(results_file, iterations[i]);
    }

    printf("Completed tests, results saved in: %s\n", results_file);
    return 0;
}
