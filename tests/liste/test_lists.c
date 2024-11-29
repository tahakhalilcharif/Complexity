#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../../include/liste.h" // Remplacez par le chemin correct

// Fonction pour créer le dossier si nécessaire
void ensure_directory(const char* path) {
    #ifdef _WIN32
        _mkdir(path); // Windows
    #else
        mkdir(path, 0777); // Unix-like systems
    #endif
}

// Fonction de benchmark des opérations sur la liste
void benchmark_list_operations(const char* filename, int n) {
    int i;
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        perror("Can't open results file.\n");
        exit(EXIT_FAILURE);
    }

    Node* head = NULL;

    // Benchmark pour l'insertion au début
    clock_t start = clock();
    for ( i = 0; i < n; i++) {
        insertAtBeginning(&head, rand() % 1000);
    }
    clock_t end = clock();
    double insert_beginning_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Benchmark pour la recherche
    start = clock();
    for ( i = 0; i < n; i++) {
        search(head, rand() % 1000);
    }
    end = clock();
    double search_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Benchmark pour la suppression
    start = clock();
    for ( i = 0; i < n; i++) {
        deleteNode(&head, rand() % 1000);
    }
    end = clock();
    double delete_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Écrire les résultats dans le fichier
    fprintf(file, "n=%d, insert_beginning_time=%.6f, search_time=%.6f, delete_time=%.6f\n", 
            n, insert_beginning_time, search_time, delete_time);

    fclose(file);
    freeList(head);
}

int main() {
   // const char* results_file = "../../results/lists/list_benchmark.txt";
    int i;
     const char *results_file = "../../results/lists/list_benchmark.csv";
    // Garantir que le dossier existe
    ensure_directory("../../results/lists");

    int iterations[] = {
        1, 10, 100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 30000, 40000, 50000, 60000,
        70000, 80000, 90000, 100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000,
        1000000, 2000000, 3000000, 4000000, 5000000, 6000000, 7000000, 8000000, 9000000, 10000000,
        20000000, 30000000, 40000000, 50000000, 60000000, 70000000, 80000000, 90000000, 100000000,
        200000000, 300000000, 400000000, 500000000, 600000000, 700000000, 800000000, 900000000, 1000000000
    };
    int num_iterations = sizeof(iterations) / sizeof(iterations[0]);

    for ( i = 0; i < num_iterations; i++) {
        printf("Running test for n=%d...\n", iterations[i]);
        benchmark_list_operations(results_file, iterations[i]);
    }

    printf("Completed tests, results saved in: %s\n", results_file);
    return 0;
}
