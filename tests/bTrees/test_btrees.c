#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#include <string.h>
#include "../../include/bTrees.h"

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

void benchmarkBTreeOperations(FILE *file, int n)
{

    BTree *tree = createBTree();

    for (int i = 0; i < n; i++)
    {
    insert(tree, i);
    }

    clock_t start = clock();
    insert(tree, n);
    clock_t end = clock();

    double insert_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    bool found = btree_search(tree, n);
    end = clock();

    double search_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    deleteKey(tree, n);
    end = clock();

    double delete_time = ((double)(end - start)) / CLOCKS_PER_SEC;


    freeBTree(tree);
    fprintf(file, "%d,%.6f,%.6f,%.6f\n", n, insert_time, search_time,delete_time);
    // fprintf(file, "n=%d, insert time=%.6f\n", n, insert_time);
    fflush(file);
}

int main()
{
    // const char *results_file = "../../results/bTrees/bTree_benchmark.txt";
    const char *results_file = "../../results/bTrees/bTree_benchmark.csv";
    const char* iterations_file = "../../tests/test_values.csv";

    FILE *file = fopen(results_file, "w");
    fprintf(file, "Size,insertion,search,delete\n");
    if (file == NULL)
    {
        perror("Cant open results file.\n");
        exit(EXIT_FAILURE);
    }

    int numIterations;
    int* iterations = readIterationsFromCSV(iterations_file, &numIterations);

    for (int i = 0; i < numIterations; i++)
    {
        printf("running test for n=%d...\n", iterations[i]);
        benchmarkBTreeOperations(file, iterations[i]);
    }

    fclose(file);
    printf("completed tests , resulsts saved in : %s\n", results_file);
    return 0;
}
