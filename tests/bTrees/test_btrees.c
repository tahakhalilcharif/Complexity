#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../include/bTrees.h"

void benchmarkBTreeOperations() {
    long long sizes[] = {1000000,  80000000, 90000000, 100000000}; // Use reasonable sizes
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int s = 0; s < numSizes; s++) {
        long long treeSize = sizes[s];

        BTree* tree = createBTree();
        if (tree == NULL) {
            fprintf(stderr, "Failed to create B-tree.\n");
            continue;
        }

        // Build the initial tree
        for (long long i = 0; i < treeSize; i++) {
            insert(tree, i);
        }
        printf("B-tree with %lld nodes created.\n", treeSize);

        // Measure insertion time
        clock_t start = clock();
        insert(tree, treeSize);
        clock_t end = clock();

        double insertionTime = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Time taken to insert one element in a B-tree with %lld nodes: %f ms\n", treeSize, insertionTime);

        // Free the B-tree
        freeBTree(tree);
    }
}

int main() {
    benchmarkBTreeOperations();
    return 0;
}
