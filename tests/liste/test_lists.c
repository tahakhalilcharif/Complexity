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

    // Benchmark pour l'insertion au position
    clock_t start = clock();
    for ( i = 0; i < n; i++) {
       // insertAtPosition(&head, rand() % 1000, rand() % n);
       insertAtPosition(&head, i , rand() % n);
    }
    clock_t end = clock();
    double insertAtPosition_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Benchmark pour la recherche
    start = clock();
    search(head, n+1);
    end = clock();
    double search_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Benchmark pour la suppression
    start = clock();
    deleteNode(&head, n);
    end = clock();
    double delete_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Écrire les résultats dans le fichier
    fprintf(file, "n=%d , insertAtPosition_time=%.6f,search_time=%.6f, delete_time=%.6f\n",
    n ,insertAtPosition_time ,search_time, delete_time);

    fclose(file);
    freeList(head);
}

// Fonction pour lire les itérations depuis un fichier CSV
int* readIterationsFromCSV(const char* filename, int* numIterations) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier CSV.");
        exit(EXIT_FAILURE);
    }

    int* iterations = NULL;
    int count = 0;
    char line[1024]; // Taille du buffer pour lire les lignes

    // Lire le fichier ligne par ligne
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
    const char* iterations_file = "../../tests/test_values.csv"; // Fichier contenant les itérations

    ensure_directory("../../results/lists");

    // Ouvrir ou créer le fichier de résultats
    FILE* file = fopen(results_file, "r");
    if (file == NULL) {
        file = fopen(results_file, "w");
        fprintf(file, "n,,insertAtPosition_time,,delete_time,search_time\n");
    }
    fclose(file);

    // Lire les itérations depuis le fichier CSV
    int numIterations;
    int* iterations = readIterationsFromCSV(iterations_file, &numIterations);

    // Exécuter les tests
    for (i = 0; i < numIterations; i++) {
        printf("Running test for n=%d...\n", iterations[i]);
        benchmark_list_operations(results_file, iterations[i]);
    }

    printf("Completed tests, results saved in: %s\n", results_file);
    free(iterations);
    return 0;
}
