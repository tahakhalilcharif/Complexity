#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../include/bTrees.h"

void benchmarkBTreeOperations(FILE *file, int n)
{

    BTree *tree = createBTree();
    int max =0;
    int random;
    clock_t start = clock();
    for (int i = 0; i < n; i++)
    {
        random = rand() % 1000;
        if (random > max){
            max = random;
        }
        insert(tree, random);
    }
    clock_t end = clock();
    double insert_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    bool found = btree_search(tree, max);
    
    end = clock();

    double search_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    freeBTree(tree);
    end = clock();

    double delete_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    fprintf(file, "%d,%.6f,%.6f,%.6f\n", n, insert_time, search_time,delete_time);
    // fprintf(file, "n=%d, insert time=%.6f\n", n, insert_time);
    fflush(file);
}

int main()
{
    // const char *results_file = "../../results/bTrees/bTree_benchmark.txt";
    const char *results_file = "../../results/bTrees/bTree_benchmark.csv";
    int iterations[] = {
        1, 10, 100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000, 2000000, 3000000, 4000000, 5000000, 6000000, 7000000,
        8000000, 9000000, 10000000, 20000000, 30000000, 40000000, 50000000, 60000000, 70000000,
        80000000, 90000000, 100000000, 200000000, 300000000, 400000000};
    int num_iterations = sizeof(iterations) / sizeof(iterations[0]);

    FILE *file = fopen(results_file, "w");
    fprintf(file, "Size,insertion,search,delete\n");
    if (file == NULL)
    {
        perror("Cant open results file.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_iterations; i++)
    {
        printf("running test for n=%d...\n", iterations[i]);
        benchmarkBTreeOperations(file, iterations[i]);
    }

    fclose(file);
    printf("completed tests , resulsts saved in : %s\n", results_file);
    return 0;
}
