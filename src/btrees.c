#include <stdio.h>
#include <stdlib.h>
#include "../include/bTrees.h"
#include <time.h>
#include <stdbool.h>

// Function to create a new B-tree node
BTreeNode* createBTreeNode(int isLeaf) {
    BTreeNode* newNode = (BTreeNode*)malloc(sizeof(BTreeNode));
    newNode->isLeaf = isLeaf;
    newNode->numKeys = 0;
    for (int i = 0; i < MAX_KEYS + 1; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// Function to split a full child node
void splitChildBTree(BTreeNode* parent, int index, BTreeNode* fullChild) {
    BTreeNode* newChild = createBTreeNode(fullChild->isLeaf);
    newChild->numKeys = MIN_KEYS;

    // Move the last MIN_KEYS keys from fullChild to newChild
    for (int i = 0; i < MIN_KEYS; i++) {
        newChild->keys[i] = fullChild->keys[i + MIN_KEYS + 1];
    }

    // If not a leaf node, move the last MIN_KEYS + 1 children
    if (!fullChild->isLeaf) {
        for (int i = 0; i < MIN_KEYS + 1; i++) {
            newChild->children[i] = fullChild->children[i + MIN_KEYS + 1];
        }
    }

    // Reduce the number of keys in fullChild
    fullChild->numKeys = MIN_KEYS;

    // Shift the children of parent to make room for newChild
    for (int i = parent->numKeys; i >= index + 1; i--) {
        parent->children[i + 1] = parent->children[i];
    }
    parent->children[index + 1] = newChild;

    // Move a key from fullChild to parent
    for (int i = parent->numKeys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }
    parent->keys[index] = fullChild->keys[MIN_KEYS];
    parent->numKeys++;
}

// Function to insert a key into a non-full node
void insertNonFullBTree(BTreeNode* node, int key) {
    int i = node->numKeys - 1;

    // If this is a leaf node
    if (node->isLeaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->numKeys++;
    } else { // If this is not a leaf node
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++; // Child index to insert the key

        // If the child is full, split it
        if (node->children[i]->numKeys == MAX_KEYS) {
            splitChildBTree(node, i, node->children[i]);
            // After splitting, the middle key of the child goes up
            // Check which of the two children to recurse into
            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFullBTree(node->children[i], key);
    }
}

// Function to insert a key into the B-tree
void insertBTree(BTree* tree, int key) {
    BTreeNode* root = tree->root;

    // If root is full, then tree grows in height
    if (root->numKeys == MAX_KEYS) {
        BTreeNode* newRoot = createBTreeNode(0);
        newRoot->children[0] = root;
        splitChildBTree(newRoot, 0, root);
        tree->root = newRoot;
        insertNonFullBTree(newRoot, key);
    } else {
        insertNonFullBTree(root, key);
    }
}

// Function to delete a key from a node
void deleteFromNodeBTree(BTreeNode* node, int key) {
    int idx = 0;
    while (idx < node->numKeys && node->keys[idx] < key) {
        idx++;
    }

    if (idx < node->numKeys && node->keys[idx] == key) {
        if (node->isLeaf) {
            // Case 1: The key is in a leaf node
            for (int i = idx + 1; i < node->numKeys; i++) {
                node->keys[i - 1] = node->keys[i];
            }
            node->numKeys--;
        } else {
            // Case 2: The key is in an internal node
            if (node->children[idx]->numKeys >= MIN_KEYS) {
                // Get the predecessor
                int predecessor = getPredecessorBTree(node, idx);
                node->keys[idx] = predecessor;
                deleteFromNodeBTree(node->children[idx], predecessor);
            } else if (node->children[idx + 1]->numKeys >= MIN_KEYS) {
                // Get the successor
                int successor = getSuccessorBTree(node, idx);
                node->keys[idx] = successor;
                deleteFromNodeBTree(node->children[idx + 1], successor);
            } else {
                // Merge the two children
                mergeBTree(node, idx);
                deleteFromNodeBTree(node->children[idx], key);
            }
        }
    } else {
        if (node->isLeaf) {
            printf("The key %d is not present in the tree.\n", key);
            return;
        }

        if (node->children[idx]->numKeys < MIN_KEYS) {
            if (idx != 0 && node->children[idx - 1]->numKeys >= MIN_KEYS) {
                borrowFromPrevBTree(node, idx);
            } else if (idx != node->numKeys && node->children[idx + 1]->numKeys >= MIN_KEYS) {
                borrowFromNextBTree(node, idx);
            } else {
                if (idx != node->numKeys) {
                    mergeBTree(node, idx);
                } else {
                    mergeBTree(node, idx - 1);
                }
            }
        }
        deleteFromNodeBTree(node->children[idx], key);
    }
}

// Wrapper function to delete a key from the B-tree
void deleteBTreeKey(BTree* tree, int key) {
    BTreeNode* root = tree->root;

    deleteFromNodeBTree(root, key);

    if (root->numKeys == 0) {
        BTreeNode* temp = root;
        if (root->isLeaf) {
            free(root);
            tree->root = NULL;
        } else {
            tree->root = root->children[0];
            free(temp);
        }
    }
}

// Search function for B-tree node
bool searchBTreeNode(BTreeNode *node, int key) {
    int i = 0;
    while (i < node->numKeys && key > node->keys[i]) {
        i++;
    }

    if (i < node->numKeys && node->keys[i] == key) {
        return true;
    } else if (node->isLeaf) {
        return false;
    } else {
        return searchBTreeNode(node->children[i], key);
    }
}

// Public function to search in the B-tree
bool btree_search(BTree *tree, int key) {
    if (tree->root != NULL) {
        return searchBTreeNode(tree->root, key);
    }
    return false;
}

// Function to traverse the tree and print keys
void traverseBTree(BTreeNode* node) {
    if (node != NULL) {
        int i;
        for (i = 0; i < node->numKeys; i++) {
            if (!node->isLeaf) {
                traverseBTree(node->children[i]);
            }
            printf("%d ", node->keys[i]);
        }
        if (!node->isLeaf) {
            traverseBTree(node->children[i]);
        }
    }
}

// Function to create a B-tree
BTree* createBTree() {
    BTree* tree = (BTree*)malloc(sizeof(BTree));
    tree->root = createBTreeNode(1); // root is a leaf node initially
    return tree;
}

// Function to free memory of a B-tree node
void freeBTreeNode(BTreeNode *node) {
    if (node != NULL) {
        for (int i = 0; i <= node->numKeys; i++) {
            freeBTreeNode(node->children[i]);
        }
        free(node);
    }
}

// Function to free the entire B-tree
void freeBTree(BTree *tree) {
    if (tree != NULL) {
        freeBTreeNode(tree->root);
        free(tree);
    }
}

// Helper functions for deletion
void borrowFromPrevBTree(BTreeNode* parent, int idx) {
    BTreeNode* child = parent->children[idx];
    BTreeNode* sibling = parent->children[idx - 1];

    // Move a key from the parent to the child
    for (int i = child->numKeys - 1; i >= 0; i--) {
        child->keys[i + 1] = child->keys[i];
    }
    child->keys[0] = parent->keys[idx - 1];
    parent->keys[idx - 1] = sibling->keys[sibling->numKeys - 1];

    // Move the child pointer of the sibling to the child
    if (!child->isLeaf) {
        for (int i = child->numKeys; i >= 0; i--) {
            child->children[i + 1] = child->children[i];
        }
        child->children[0] = sibling->children[sibling->numKeys];
    }

    child->numKeys++;
    sibling->numKeys--;
}

void borrowFromNextBTree(BTreeNode* parent, int idx) {
    BTreeNode* child = parent->children[idx];
    BTreeNode* sibling = parent->children[idx + 1];

    // Move a key from the parent to the child
    child->keys[child->numKeys] = parent->keys[idx];
    parent->keys[idx] = sibling->keys[0];

    // Move the first child pointer of the sibling to the child
    if (!child->isLeaf) {
        child->children[child->numKeys + 1] = sibling->children[0];
    }

    // Shift the keys and children of the sibling
    for (int i = 1; i < sibling->numKeys; i++) {
        sibling->keys[i - 1] = sibling->keys[i];
    }
    if (!sibling->isLeaf) {
        for (int i = 1; i <= sibling->numKeys; i++) {
            sibling->children[i - 1] = sibling->children[i];
        }
    }

    child->numKeys++;
    sibling->numKeys--;
}

int getPredecessorBTree(BTreeNode* node, int idx) {
    BTreeNode* current = node->children[idx];
    while (!current->isLeaf) {
        current = current->children[current->numKeys];
    }
    return current->keys[current->numKeys - 1];
}

int getSuccessorBTree(BTreeNode* node, int idx) {
    BTreeNode* current = node->children[idx + 1];
    while (!current->isLeaf) {
        current = current->children[0];
    }
    return current->keys[0];
}

void mergeBTree(BTreeNode* parent, int idx) {
    BTreeNode* leftChild = parent->children[idx];
    BTreeNode* rightChild = parent->children[idx + 1];

    // Move the key from the parent to the left child
    leftChild->keys[leftChild->numKeys] = parent->keys[idx];
    for (int i = 0; i < rightChild->numKeys; i++) {
        leftChild->keys[leftChild->numKeys + 1 + i] = rightChild->keys[i];
    }

    // If not a leaf, move the children
    if (!leftChild->isLeaf) {
        for (int i = 0; i <= rightChild->numKeys; i++) {
            leftChild->children[leftChild->numKeys + i + 1] = rightChild->children[i];
        }
    }

    // Update the number of keys
    leftChild->numKeys += rightChild->numKeys + 1;

    // Shift remaining keys and children in the parent
    for (int i = idx + 1; i < parent->numKeys; i++) {
        parent->keys[i - 1] = parent->keys[i];
    }
    for (int i = idx + 2; i <= parent->numKeys; i++) {
        parent->children[i - 1] = parent->children[i];
    }

    parent->numKeys--;
    free(rightChild);
}









// double getTime() {
//     struct timeval time;
//     gettimeofday(&time, NULL);
//     return time.tv_sec * 1000.0 + time.tv_usec / 1000.0; // Time in milliseconds
// }

// int main() {
//     long long sizes[] = {1000000, 80000000,90000000,100000000}; // Use reasonable sizes
//     int numSizes = sizeof(sizes) / sizeof(sizes[0]);

//     for (int s = 0; s < numSizes; s++) {
//         long long treeSize = sizes[s];

//         BTree* tree = createBTree();
//         if (tree == NULL) {
//             fprintf(stderr, "Failed to create B-tree.\n");
//             continue;
//         }

//         // Build the initial tree
//         for (long long i = 0; i < treeSize; i++) {
//             insert(tree, i);
//         }
//         printf("B-tree with %lld nodes created.\n", treeSize);

//         // Measure insertion time
//         double start = getTime();
//         printf("start time: %f\n", start);
//         insert(tree, treeSize);
//         double end = getTime();
//         printf("end time: %f\n", end);

//         printf("Time taken to insert one element in a B-tree with %lld nodes: %f ms\n", treeSize, end - start);

//         // Free the B-tree
//         freeBTree(tree);
//     }

//     return 0;
// }
