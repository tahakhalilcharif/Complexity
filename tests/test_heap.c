#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/heap.h"

void benchmark_heap_operations(const char* filename, int n) {
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        perror("Cant open results file.\n");
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

    fprintf(file, "n=%d, insert time=%.6f, delete time=%.6f, search time=%.6f\n", n, insert_time, delete_time, search_time);

    fclose(file);
    freeHeap(heap);
}

int main() {
    const char* results_file = "../results/heaps/heap_benchmark.txt";

    system("mkdir -p ../results");

    int iterations[] = {
        1, 10, 100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 30000, 40000, 50000, 60000
        , 70000, 80000, 90000, 100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000
         , 1000000,2000000 ,3000000, 4000000, 5000000 , 6000000 , 7000000,
          8000000, 9000000 , 10000000 ,20000000 ,30000000, 40000000, 50000000 , 60000000 , 70000000,
          80000000, 90000000 ,100000000 ,200000000 ,300000000 ,400000000 ,500000000 ,600000000 ,700000000 ,800000000 ,
          900000000 ,1000000000
        };
    int num_iterations = sizeof(iterations) / sizeof(iterations[0]);

    for (int i = 0; i < num_iterations; i++) {
        printf("running test for n=%d...\n", iterations[i]);
        benchmark_heap_operations(results_file, iterations[i]);
    }

    printf("completed tests , resulsts saved in : %s\n", results_file);
    return 0;
}
