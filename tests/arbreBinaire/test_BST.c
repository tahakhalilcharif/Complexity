#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../include/arbreBinaire.h" // Inclure l'en-tête de votre arbre binaire

void benchmarkBSTOperations(FILE *file, int n)
{
    // Création d'un arbre binaire vide
    Node *tree = NULL;
    int max = 0;
    int random;
    int FirstValue = 0;

    // Mesurer le temps d'insertion
    clock_t start = clock();
    for (int i = 0; i < n; i++)
    {
        random = rand() % 1000;
        if (i == 0)
        {
            FirstValue = random;
        } // Générer un nombre aléatoire
        if (random > max)
        {
            max = random; // Garder la valeur maximale pour la recherche
        }
        tree = insert(tree, random); // Insérer le nombre dans l'arbre
    }
    clock_t end = clock();
    double insert_time = ((double)(end - start)) / CLOCKS_PER_SEC; // Temps d'insertion

    // Mesurer le temps de recherche (n fois)
    start = clock();
    for (int i = 0; i < n; i++)
    {
        Node *found_node = search(tree, max); // Rechercher la valeur maximale
        // Vous pouvez également effectuer une recherche aléatoire si nécessaire
    }
    end = clock();
    double search_time = ((double)(end - start)) / CLOCKS_PER_SEC; // Temps de recherche

    // Mesurer le temps de suppression (n fois)
    start = clock();
    for (int i = 0; i < n; i++)
    {
        tree = deleteNode(tree, FirstValue); // Supprimer le nœud avec la valeur maximale
        // Vous pouvez supprimer une valeur aléatoire si vous le souhaitez
    }
    end = clock();
    double delete_time = ((double)(end - start)) / CLOCKS_PER_SEC; // Temps de suppression

    // Écrire les résultats dans le fichier
    fprintf(file, "%d,%.6f,%.6f,%.6f\n", n, insert_time, search_time, delete_time);
    fflush(file); // Assurer que les données sont écrites immédiatement
}

int main()
{
    // Définir les fichiers pour les résultats et les tailles de test
    const char *results_file = "../../results/arbreBinaire/arbre_benchmark.csv";
    const char *test_values_file = "../test_values.csv";

    // Ouvrir le fichier de test_values.csv pour lire les tailles d'itération
    FILE *test_values = fopen(test_values_file, "r");
    if (test_values == NULL)
    {
        perror("Can't open test values file.\n");
        exit(EXIT_FAILURE);
    }

    // Lire les tailles d'itération à partir du fichier CSV
    int *iterations = NULL;
    int num_iterations = 0;
    char line[256];

    // Ignorer la première ligne (en-tête)
    fgets(line, sizeof(line), test_values);

    // Lire les tailles ligne par ligne
    while (fgets(line, sizeof(line), test_values))
    {
        iterations = realloc(iterations, (num_iterations + 1) * sizeof(int));
        if (iterations == NULL)
        {
            perror("Memory allocation failed.\n");
            fclose(test_values);
            exit(EXIT_FAILURE);
        }
        iterations[num_iterations++] = atoi(line);
    }
    fclose(test_values);

    // Ouvrir le fichier pour écrire les résultats
    FILE *file = fopen(results_file, "w");
    if (file == NULL)
    {
        perror("Can't open results file.\n");
        exit(EXIT_FAILURE);
    }

    // Écrire l'en-tête du fichier CSV
    fprintf(file, "Size,insertion,search,delete\n");

    // Exécuter les tests pour chaque taille d'arbre
    for (int i = 0; i < num_iterations; i++)
    {
        printf("Running test for n=%d...\n", iterations[i]);
        benchmarkBSTOperations(file, iterations[i]); // Effectuer le benchmark
    }

    // Fermer le fichier après les tests
    fclose(file);
    free(iterations);
    printf("Completed tests, results saved in: %s\n", results_file);

    return 0;
}
