#include <stdbool.h>
#ifndef BTREE_H
#define BTREE_H

#define MAX_KEYS 3
#define MIN_KEYS (MAX_KEYS / 2)

typedef struct BTreeNode {
    int keys[MAX_KEYS];
    struct BTreeNode *children[MAX_KEYS + 1];
    int numKeys;
    int isLeaf;
} BTreeNode;

typedef struct BTree {
    BTreeNode *root;
} BTree;

// Function Prototypes
BTreeNode* createNode(int isLeaf);
void splitChild(BTreeNode* parent, int index, BTreeNode* fullChild);
void insertNonFull(BTreeNode* node, int key);
void insert(BTree* tree, int key);
void deleteKey(BTree* tree, int key);
void deleteFromNode(BTreeNode* node, int key);
void traverse(BTreeNode* node);
BTree* createBTree();
void freeBTreeNode(BTreeNode *node);
void freeBTree(BTree *tree);

// Helper functions for deletion
void borrowFromPrev(BTreeNode* parent, int idx);
void borrowFromNext(BTreeNode* parent, int idx);
int getPredecessor(BTreeNode* node, int idx);
int getSuccessor(BTreeNode* node, int idx);
void merge(BTreeNode* parent, int idx);

bool search(BTreeNode *node, int key);
bool btree_search(BTree *tree, int key);

#endif
