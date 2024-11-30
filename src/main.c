#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include "../include/liste.h"
#include "../include/arbrebinaire.h"
#include "../include/btrees.h"
#include "../include/maxheap.h"
#include "../include/minheap.h"

void compareOperations(int size, const char *operation);
void runPythonScript(const char *scriptName);

int main() {
    int choice, size;
    const char *csvFileName = "comparison_results.csv";
    const char *heapCsvFileName = "heap_sort_results.csv";

    FILE *csvFile = fopen(csvFileName, "w");
    if (!csvFile) {
        perror("Unable to create CSV file");
        return 1;
    }
    fprintf(csvFile, "Structure,Operation,Size,TimeTaken\n");
    fclose(csvFile);


    FILE *heapCsvFile = fopen(heapCsvFileName, "w");
    if (!heapCsvFile) {
      perror("Unable to open Heap CSV file");
      return 1;
    }
    fprintf(heapCsvFile,"Heap Type,Operation,Size,TimeTaken\n");
    fclose(heapCsvFile);

    while (1) {
        printf("\n--- Menu Principal ---\n");
        printf("1. Comparer les Insertion\n");
        printf("2. Comparer les Recherche\n");
        printf("3. Comparer les Suppression\n");
        printf("4. Comparer le Tri par Tas (Heap Sort)\n");
        printf("5. Terminer la comparaison et générer le graphique\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choice);

        if (choice == 5) {
            printf("Génération du graphique...\n");
            runPythonScript("visualize_comparison.py");
            runPythonScript("heap_visualize_comparison.py");
            printf("Au revoir !\n");
            break;
        }

        printf("Entrez la taille des données (max: %d): ", INT_MAX);
        scanf("%d", &size);
        if (size <= 0 || size > INT_MAX) {
            printf("Taille invalide, veuillez réessayer.\n");
            continue;
        }

        switch (choice) {
            case 1:
                compareOperations(size, "Insertion");
                break;
            case 2:
                compareOperations(size, "Recherche");
                break;
            case 3:
                compareOperations(size, "Suppression");
                break;
            case 4:
                compareOperations(size, "Heap Sort");
                break;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
    }

    return 0;
}

void compareOperations(int size, const char *operation) {
    const char *csvFileName = "comparison_results.csv";
    const char *heapCsvFileName = "heap_sort_results.csv";

    FILE *csvFile = fopen(csvFileName, "a");
    if (!csvFile) {
        perror("Unable to open CSV file");
        return;
    }

    FILE *heapCsvFile = NULL;
    if (strcmp(operation, "Heap Sort") == 0) {
        heapCsvFile = fopen(heapCsvFileName, "a");
        if (!heapCsvFile) {
            perror("Unable to open Heap CSV file");
            fclose(csvFile);
            return;
        }
    }

    printf("\n--- Comparaison des %s ---\n", operation);
    clock_t start, end;
    double timeTaken;

    //Arbe binaire de recherche
    BSTNode *root = NULL;
    start = clock();
    if (strcmp(operation, "Insertion") == 0) {
        printf("Insertion des valeurs pour un arbre binaire de recherche.\n");
        for (int i = 0; i < size; i++) {
            root = insertBST(root, i);
        }
    } else if (strcmp(operation, "Recherche") == 0) {
        printf("Recherche des valeurs pour un arbre binaire de recherche.\n");
        for (int i = 0; i < size; i++) {
            searchBST(root, i);
        }
    } else if (strcmp(operation, "Suppression") == 0) {
        printf("Suppression des valeurs pour un arbre binaire de recherche.\n");
        for (int i = 0; i < size; i++) {
            root = deleteBSTNode(root, i);
        }
    }
    end = clock();
    timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
    fprintf(csvFile, "Binary Search Tree,%s,%d,%lf\n", operation, size, timeTaken);
    freeBST(root);

    //b-tree
    BTree *tree = createBTree();
    start = clock();
    if (strcmp(operation, "Insertion") == 0) {
        printf("Insertion des valeurs pour un b-tree.\n");
        for (int i = 0; i < size; i++) {
            insertBTree(tree, i);
        }
    } else if (strcmp(operation, "Recherche") == 0) {
        printf("Recherche des valeurs pour un b-tree.\n");
        for (int i = 0; i < size; i++) {
            btree_search(tree, i);
        }
    } else if (strcmp(operation, "Suppression") == 0) {
        printf("Suppression des valeurs pour un b-tree.\n");
        for (int i = 0; i < size; i++) {
            deleteBTreeKey(tree, i);
        }
    }
    end = clock();
    timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
    fprintf(csvFile, "B-Tree,%s,%d,%lf\n", operation, size, timeTaken);
    freeBTree(tree);

    //Liset doublement chainée
    if (strcmp(operation, "Insertion") == 0 || strcmp(operation, "Recherche") == 0 || strcmp(operation, "Suppression") == 0) {
        DLNode *head = NULL;

        start = clock();
        if (strcmp(operation, "Insertion") == 0) {
            printf("Insertion des valeurs pour une liste doublement chainee.\n");
            for (int i = 0; i < size; i++) {
                insertAtEndDL(&head, i);
            }
        } else if (strcmp(operation, "Recherche") == 0) {
            printf("Recherche des valeurs pour une liste doublement chainee.\n");
            for (int i = 0; i < size; i++) {
                searchDL(head, i);
            }
        } else if (strcmp(operation, "Suppression") == 0) {
            printf("Suppression des valeurs pour une liste doublement chainee.\n");
            for (int i = 0; i < size; i++) {
                deleteDLNode(&head, i);
            }
        }
        end = clock();
        timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
        fprintf(csvFile, "Doubly Linked List,%s,%d,%lf\n", operation, size, timeTaken);
        freeDLList(head);
    }

    if (strcmp(operation, "Heap Sort") == 0) {
        int *array = (int *)malloc(size * sizeof(int));
        for (int i = 0; i < size; i++) {
            array[i] = rand() % size;
        }

        MaxHeap *maxHeap = createMaxHeap(size);

        start = clock();
        buildMaxHeap_NlogN(maxHeap, array, size);
        end = clock();
        timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
        fprintf(heapCsvFile, "MaxHeap,Build NlogN,%d,%lf\n", size, timeTaken);

        freeMaxHeap(maxHeap);
        maxHeap = createMaxHeap(size);

        start = clock();
        buildMaxHeap_N(maxHeap, array, size);
        end = clock();
        timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
        fprintf(heapCsvFile, "MaxHeap,Build N,%d,%lf\n", size, timeTaken);

        freeMaxHeap(maxHeap);

        MinHeap *minHeap = createHeap(size);

        start = clock();
        buildMinHeap_NlogN(minHeap, array, size);
        end = clock();
        timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
        fprintf(heapCsvFile, "MinHeap,Build NlogN,%d,%lf\n", size, timeTaken);

        freeHeap(minHeap);
        minHeap = createHeap(size);

        start = clock();
        buildMinHeap_N(minHeap, array, size);
        end = clock();
        timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
        fprintf(heapCsvFile, "MinHeap,Build N,%d,%lf\n", size, timeTaken);

        freeHeap(minHeap);
        free(array);
    }

    fclose(csvFile);
    fclose(heapCsvFile);


    printf("Les résultats ont été sauvegardés dans %s et/ou %s\n", csvFileName, heapCsvFileName);
}

void runPythonScript(const char *scriptName) {
    char command[256];
    snprintf(command, sizeof(command), "python %s", scriptName);
    system(command);
}
