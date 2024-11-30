#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ArbreBinaire.h"
#include "BTrees.h"
#include "Liste.h"
#include "MaxHeap.h"

void saveToCSV(const char *fileName, int iterations, double bstTime, double btreeTime, double dllTime, double heapTime) {
    FILE *csvFile = fopen(fileName, "a");
    if (!csvFile) {
        perror("Unable to open CSV file");
        return;
    }
    fprintf(csvFile, "%d,%lf,%lf,%lf,%lf\n", iterations, bstTime, btreeTime, dllTime, heapTime);
    fclose(csvFile);
}

void saveToHeapCSV(const char *fileName, int iterations, double HeapTimeNLogN ,double heapTimeN ) {
    FILE *csvFile = fopen(fileName, "a");
    if (!csvFile) {
        perror("Unable to open CSV file");
        return;
    }
    fprintf(csvFile, "%d,%lf,%lf\n", iterations, HeapTimeNLogN, heapTimeN);
    fclose(csvFile);
}

void testStructureCreationComparison(int maxIterations) {
    const char *fileName = "Creation_Comparison.csv";
    FILE *csvFile = fopen(fileName, "w");
    fprintf(csvFile, "Iterations,BST,BTree,DLL,Heap\n");
    fclose(csvFile);

    for (int i = 10; i <= maxIterations; i += 10000) {
        clock_t start, end;
        double bstTime, btreeTime, dllTime, heapTime;

        // BST Creation
        start = clock();
        BSTNode *bstRoot = NULL;
        for (int j = 0; j < i; j++) {
            bstRoot = insertBST(bstRoot, j);
        }
        end = clock();
        bstTime = (double)(end - start) / CLOCKS_PER_SEC;
        freeBST(bstRoot);

        // BTree Creation
        start = clock();
        BTree *bTree = createBTree();
        for (int j = 0; j < i; j++) {
            insertBTree(bTree, j);
        }
        end = clock();
        btreeTime = (double)(end - start) / CLOCKS_PER_SEC;
        freeBTree(bTree);

        // Doubly Linked List Creation
        start = clock();
        DLNode *dllHead = NULL;
        for (int j = 0; j < i; j++) {
            insertAtEndDL(&dllHead, j);
        }
        end = clock();
        dllTime = (double)(end - start) / CLOCKS_PER_SEC;
        freeDLList(dllHead);

        // MaxHeap Creation
        start = clock();
        MaxHeap *heap = createMaxHeap(i);
        for (int j = 0; j < i; j++) {
            insertMaxHeap(heap, j);
        }
        end = clock();
        heapTime = (double)(end - start) / CLOCKS_PER_SEC;
        freeMaxHeap(heap);

        // Save results
        saveToCSV(fileName, i, bstTime, btreeTime, dllTime, heapTime);
    }
}


// Test insertion performance
void testInsertionComparison(int maxIterations) {
    const char *fileName = "Insertion_Comparison.csv";
    FILE *csvFile = fopen(fileName, "w");
    fprintf(csvFile, "Iterations,BST,BTree,DLL,Heap\n");
    fclose(csvFile);

    for (int i = 10; i <= maxIterations; i += 10000) {
        clock_t start, end;
        double bstTime, btreeTime, dllTime, heapTime;

        // BST
        BSTNode *bstRoot = NULL;
        start = clock();
        for (int j = 0; j < i; j++) {
            bstRoot = insertBST(bstRoot, j);
        }
        end = clock();
        bstTime = (double)(end - start) / CLOCKS_PER_SEC;

        // BTree
        BTree *bTree = createBTree();
        start = clock();
        for (int j = 0; j < i; j++) {
            insertBTree(bTree, j);
        }
        end = clock();
        btreeTime = (double)(end - start) / CLOCKS_PER_SEC;

        // Doubly Linked List
        DLNode *dllHead = NULL;
        start = clock();
        for (int j = 0; j < i; j++) {
            insertAtEndDL(&dllHead, j);
        }
        end = clock();
        dllTime = (double)(end - start) / CLOCKS_PER_SEC;

        // Heap
        MaxHeap *heap = createMaxHeap(i);
        start = clock();
        for (int j = 0; j < i; j++) {
            insertMaxHeap(heap, j);
        }
        end = clock();
        heapTime = (double)(end - start) / CLOCKS_PER_SEC;

        // Save results
        saveToCSV(fileName, i, bstTime, btreeTime, dllTime, heapTime);

        // Free memory
        freeBST(bstRoot);
        freeBTree(bTree);
        freeDLList(dllHead);
        freeMaxHeap(heap);
    }
}

// Test search performance
void testSearchComparison(int maxIterations) {
    const char *fileName = "Search_Comparison.csv";
    FILE *csvFile = fopen(fileName, "w");
    fprintf(csvFile, "Iterations,BST,BTree,DLL,Heap\n");
    fclose(csvFile);

    for (int i = 10; i <= maxIterations; i += 10000) {
        clock_t start, end;
        double bstTime, btreeTime, dllTime, heapTime;

        // Create structures
        BSTNode *bstRoot = NULL;
        BTree *bTree = createBTree();
        DLNode *dllHead = NULL;
        MaxHeap *heap = createMaxHeap(i);

        for (int j = 0; j < i; j++) {
            bstRoot = insertBST(bstRoot, j);
            insertBTree(bTree, j);
            insertAtEndDL(&dllHead, j);
            insertMaxHeap(heap, j);
        }

        // BST search
        start = clock();
        for (int j = 0; j < i; j++) {
            searchBST(bstRoot, rand() % i);
        }
        end = clock();
        bstTime = (double)(end - start) / CLOCKS_PER_SEC;

        // BTree search
        start = clock();
        for (int j = 0; j < i; j++) {
            btree_search(bTree, rand() % i);
        }
        end = clock();
        btreeTime = (double)(end - start) / CLOCKS_PER_SEC;

        // DLL search
        start = clock();
        for (int j = 0; j < i; j++) {
            optimizedSearchDL(dllHead, rand() % i);
        }
        end = clock();
        dllTime = (double)(end - start) / CLOCKS_PER_SEC;

        // Heap search (linear scan, as heaps aren't designed for efficient search)
        start = clock();
        for (int j = 0; j < i; j++) {
            searchMaxHeap(heap, rand() % i);
        }
        end = clock();
        heapTime = (double)(end - start) / CLOCKS_PER_SEC;

        // Save results
        saveToCSV(fileName, i, bstTime, btreeTime, dllTime, heapTime);

        // Free memory
        freeBST(bstRoot);
        freeBTree(bTree);
        freeDLList(dllHead);
        freeMaxHeap(heap);
    }
}

// Test deletion performance
void testDeletionComparison(int maxIterations) {
    const char *fileName = "Deletion_Comparison.csv";
    FILE *csvFile = fopen(fileName, "w");
    fprintf(csvFile, "Iterations,BST,BTree,DLL,Heap\n");
    fclose(csvFile);

    for (int i = 10; i <= maxIterations; i += 10000) {
        clock_t start, end;
        double bstTime, btreeTime, dllTime, heapTime;

        // Create structures
        BSTNode *bstRoot = NULL;
        BTree *bTree = createBTree();
        DLNode *dllHead = NULL;
        MaxHeap *heap = createMaxHeap(i);

        for (int j = 0; j < i; j++) {
            bstRoot = insertBST(bstRoot, j);
            insertBTree(bTree, j);
            insertAtEndDL(&dllHead, j);
            insertMaxHeap(heap, j);
        }

        // BST deletion
        start = clock();
        for (int j = 0; j < i; j++) {
            bstRoot = deleteBSTNode(bstRoot, rand() % i);
        }
        end = clock();
        bstTime = (double)(end - start) / CLOCKS_PER_SEC;

        // BTree deletion
        start = clock();
        for (int j = 0; j < i; j++) {
            deleteBTreeKey(bTree, rand() % i);
        }
        end = clock();
        btreeTime = (double)(end - start) / CLOCKS_PER_SEC;

        // DLL deletion
        start = clock();
        for (int j = 0; j < i; j++) {
            deleteDLNode(&dllHead, rand() % i);
        }
        end = clock();
        dllTime = (double)(end - start) / CLOCKS_PER_SEC;

        // Heap deletion
        start = clock();
        for (int j = 0; j < i; j++) {
            extractMax(heap);
        }
        end = clock();
        heapTime = (double)(end - start) / CLOCKS_PER_SEC;

        // Save results
        saveToCSV(fileName, i, bstTime, btreeTime, dllTime, heapTime);

        // Free memory
        freeBST(bstRoot);
        freeBTree(bTree);
        freeDLList(dllHead);
        freeMaxHeap(heap);
    }
}

// Test heap sort
void testHeapSort(int maxIterations) {
    const char *fileName = "HeapSort_Comparison.csv";
    FILE *csvFile = fopen(fileName, "w");
    fprintf(csvFile, "Iterations,Build_NlogN,Build_N\n");
    fclose(csvFile);

    for (int i = 10; i <= maxIterations*10; i += 10000) {
        clock_t start, end;
        double buildNlogNTime, buildNTime;

        int *array = malloc(i * sizeof(int));
        for (int j = 0; j < i; j++) {
            array[j] = rand();
        }

        // Build heap (NlogN)
        MaxHeap *heap = createMaxHeap(i);
        start = clock();
        buildMaxHeap_NlogN(heap, array, i);
        end = clock();
        buildNlogNTime = (double)(end - start) / CLOCKS_PER_SEC;

        // Build heap (N)
        start = clock();
        buildMaxHeap_N(heap, array, i);
        end = clock();
        buildNTime = (double)(end - start) / CLOCKS_PER_SEC;

        // Save results
        saveToHeapCSV(fileName, i, buildNlogNTime, buildNTime);

        // Free memory
        freeMaxHeap(heap);
        free(array);
    }
}

// Menu
void displayMenu() {
    printf("1- Comparer les insertions\n");
    printf("2- Comparer la recherche\n");
    printf("3- Comparer la suppression\n");
    printf("4- Comparer le tri par tas\n");
    printf("5- Comparer la creation des structures\n");
    printf("6- Terminer et generer les graphes\n");
}

int main() {
    int choice, maxIterations = 1000000;

    do {
        displayMenu();
        printf("Choisissez une option : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                testInsertionComparison(maxIterations);
                break;
            case 2:
                testSearchComparison(maxIterations);
                break;
            case 3:
                testDeletionComparison(maxIterations);
                break;
            case 4:
                testHeapSort(maxIterations);
                break;
            case 5:
                testStructureCreationComparison(maxIterations);
                break;
            case 6:
                printf("Fin du programme. Les fichiers CSV sont prêts.\n");
                break;
            default:
                printf("Option invalide. Veuillez reessayer.\n");
        }
    } while (choice != 6);

    return 0;
}
