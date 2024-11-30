#ifndef ARBREBINAIRE_H
#define ARBREBINAIRE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct BSTNode {
    int data;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

BSTNode *newBSTNode(int data);
BSTNode *insertBST(BSTNode *root, int data);
void inorderBST(BSTNode *root);
BSTNode *minValueBSTNode(BSTNode *node);
BSTNode *deleteBSTNode(BSTNode *root, int key);
BSTNode *searchBST(BSTNode *root, int key);
void freeBST(BSTNode *root);

#endif
