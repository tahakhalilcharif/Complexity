#ifndef BTREES_H
#define BTREES_H

#include <stdbool.h>

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

BTreeNode* createBTreeNode(int isLeaf);
void splitChildBTree(BTreeNode* parent, int index, BTreeNode* fullChild);
void insertNonFullBTree(BTreeNode* node, int key);
void insertBTree(BTree* tree, int key);
void deleteBTreeKey(BTree* tree, int key);
void deleteFromNodeBTree(BTreeNode* node, int key);
void traverseBTree(BTreeNode* node);
BTree* createBTree();
void freeBTreeNode(BTreeNode *node);
void freeBTree(BTree *tree);

void borrowFromPrevBTree(BTreeNode* parent, int idx);
void borrowFromNextBTree(BTreeNode* parent, int idx);
int getPredecessorBTree(BTreeNode* node, int idx);
int getSuccessorBTree(BTreeNode* node, int idx);
void mergeBTree(BTreeNode* parent, int idx);

bool searchBTreeNode(BTreeNode *node, int key);
bool btree_search(BTree *tree, int key);

#endif
