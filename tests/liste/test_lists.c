#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include "../../include/liste.h" // Ensure correct path

// Function to create directory if necessary
void ensure_directory(const char* path) {
    #ifdef _WIN32
        _mkdir(path); // Windows
    #else
        mkdir(path, 0777); // Unix-like systems
    #endif
}

// Benchmark function for list operations
void benchmark_list_operations(const char* filename, int n) {
    int i;
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        perror("Can't open results file.\n");
        exit(EXIT_FAILURE);
    }

    DLNode* head = NULL;

    // Benchmark for insert at position
    clock_t start = clock();
    for (i = 0; i < n; i++) {
        insertAtPositionDL(&head, i, rand() % n);
    }
    clock_t end = clock();
    double insertAtPosition_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Benchmark for search
    start = clock();
    searchDL(head, rand() % n); // Search for an element that isn't in the list
    end = clock();
    double search_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Benchmark for delete
    start = clock();
    deleteDLNode(&head , rand() % n); // Deleting a node
    end = clock();
    double delete_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Write results to CSV file
    fprintf(file,"%d,%.6f,%.6f,%.6f\n", n,insertAtPosition_time,search_time,delete_time);

    fclose(file);
    freeDLList(head); // Clean up memory
}

// Function to read iterations from a CSV file
int* readIterationsFromCSV(const char* filename, int* numIterations) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier CSV.");
        exit(EXIT_FAILURE);
    }

    int* iterations = NULL;
    int count = 0;
    char line[1024];

    // Read the file line by line
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ",");
        while (token) {
            iterations = realloc(iterations, (count + 1) * sizeof(int));
            if (iterations == NULL) {
                perror("Erreur d'allocation mémoire.");
                fclose(file);
                exit(EXIT_FAILURE);
            }
            iterations[count++] = atoi(token);
            token = strtok(NULL, ",");
        }
    }

    fclose(file);
    *numIterations = count;
    return iterations;
}

int main() {
    int i;
    const char* results_file = "../../results/lists/list_benchmark.csv";
    const char* iterations_file = "../../tests/test_values.csv"; // File containing iterations

    ensure_directory("../../results/lists");

    // Open or create the results file
    FILE* file = fopen(results_file, "r");
    if (file == NULL) {
        file = fopen(results_file, "w");
        fprintf(file, "n,insertAtPosition_time,search_time,delete_time\n");// CSV header

    }
    fclose(file);

    // Read iterations from the CSV file
    int numIterations;
    int* iterations = readIterationsFromCSV(iterations_file, &numIterations);

    // Execute tests
    for (i = 100; i < numIterations; i++) {
        printf("Running test for n=%d...\n", iterations[i]);
        benchmark_list_operations(results_file, iterations[i]);
    }

    printf("Completed tests, results saved in: %s\n", results_file);
    free(iterations);
    return 0;
}
