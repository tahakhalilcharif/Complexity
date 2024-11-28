#include <stdio.h>
#include <stdlib.h>
#include "../include/bTrees.h"
#include <time.h>
#include <stdbool.h>
#include <sys/time.h>

// Function to create a new B-tree node
BTreeNode* createNode(int isLeaf) {
    BTreeNode* newNode = (BTreeNode*)malloc(sizeof(BTreeNode));
    newNode->isLeaf = isLeaf;
    newNode->numKeys = 0;
    for (int i = 0; i < MAX_KEYS + 1; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// Function to split a full child node
void splitChild(BTreeNode* parent, int index, BTreeNode* fullChild) {
    BTreeNode* newChild = createNode(fullChild->isLeaf);
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
void insertNonFull(BTreeNode* node, int key) {
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
            splitChild(node, i, node->children[i]);
            // After splitting, the middle key of the child goes up
            // Check which of the two children to recurse into
            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

// Function to insert a key into the B-tree
void insert(BTree* tree, int key) {
    BTreeNode* root = tree->root;

    // If root is full, then tree grows in height
    if (root->numKeys == MAX_KEYS) {
        BTreeNode* newRoot = createNode(0);
        newRoot->children[0] = root;
        splitChild(newRoot, 0, root);
        tree->root = newRoot;
        insertNonFull(newRoot, key);
    } else {
        insertNonFull(root, key);
    }
}



// Function to borrow a key from the previous sibling
void borrowFromPrev(BTreeNode* parent, int idx) {
    BTreeNode* child = parent->children[idx];
    BTreeNode* sibling = parent->children[idx - 1];

    // Moving a key from parent to child
    for (int i = child->numKeys - 1; i >= 0; i--) {
        child->keys[i + 1] = child->keys[i];
    }
    if (!child->isLeaf) {
        for (int i = child->numKeys; i >= 0; i--) {
            child->children[i + 1] = child->children[i];
        }
    }
    child->keys[0] = parent->keys[idx - 1];
    child->numKeys++;

    // Moving the last child of sibling to child
    if (!child->isLeaf) {
        child->children[0] = sibling->children[sibling->numKeys];
    }
    parent->keys[idx - 1] = sibling->keys[sibling->numKeys - 1];
    sibling->numKeys--;
}

// Function to borrow a key from the next sibling
void borrowFromNext(BTreeNode* parent, int idx) {
    BTreeNode* child = parent->children[idx];
    BTreeNode* sibling = parent->children[idx + 1];

    // Copy the next key from parent to child
    child->keys[child->numKeys] = parent->keys[idx];
    child->numKeys++;

    // Moving the first child of sibling to child
    if (!child->isLeaf) {
        child->children[child->numKeys] = sibling->children[0];
    }
    parent->keys[idx] = sibling->keys[0];

    // Shifting keys in sibling
    for (int i = 1; i < sibling->numKeys; i++) {
        sibling->keys[i - 1] = sibling->keys[i];
    }
    if (!sibling->isLeaf) {
        for (int i = 1; i <= sibling->numKeys; i++) {
            sibling->children[i - 1] = sibling->children[i];
        }
    }
    sibling->numKeys--;
}



// Function to get the predecessor of a key
int getPredecessor(BTreeNode* node, int idx) {
    BTreeNode* current = node->children[idx];
    while (!current->isLeaf) {
        current = current->children[current->numKeys];
    }
    return current->keys[current->numKeys - 1];
}

// Function to get the successor of a key
int getSuccessor(BTreeNode* node, int idx) {
    BTreeNode* current = node->children[idx + 1];
    while (!current->isLeaf) {
        current = current->children[0];
    }
    return current->keys[0];
}


// Function to merge two children
void merge(BTreeNode* parent, int idx) {
    BTreeNode* leftChild = parent->children[idx];
    BTreeNode* rightChild = parent->children[idx + 1];

    // Move the middle key from parent to left child
    leftChild->keys[leftChild->numKeys] = parent->keys[idx];
    leftChild->numKeys++;

    // Copy keys from right child to left child
    for (int i = 0; i < rightChild->numKeys; i++) {
        leftChild->keys[leftChild->numKeys + i] = rightChild->keys[i];
    }
    if (!leftChild->isLeaf) {
        for (int i = 0; i <= rightChild->numKeys; i++) {
            leftChild->children[leftChild->numKeys + i] = rightChild->children[i];
        }
    }
    leftChild->numKeys += rightChild->numKeys;

    // Shift the keys and children in the parent
    for (int i = idx + 1; i < parent->numKeys; i++) {
        parent->keys[i - 1] = parent->keys[i];
    }
    for (int i = idx + 2; i <= parent->numKeys; i++) {
        parent->children[i - 1] = parent->children[i];
    }
    parent->numKeys--;

    // Free the right child
    free(rightChild);
}

// Function to delete a key from a node
void deleteFromNode(BTreeNode* node, int key) {
    int idx = 0;
    while (idx < node->numKeys && node->keys[idx] < key) {
        idx++;
    }

    // If the key is found in this node
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
                int predecessor = getPredecessor(node, idx);
                node->keys[idx] = predecessor;
                deleteFromNode(node->children[idx], predecessor);
            } else if (node->children[idx + 1]->numKeys >= MIN_KEYS) {
                // Get the successor
                int successor = getSuccessor(node, idx);
                node->keys[idx] = successor;
                deleteFromNode(node->children[idx + 1], successor);
            } else {
                // Merge the two children
                merge(node, idx);
                deleteFromNode(node->children[idx], key);
            }
        }
    } else {
        // If this node is a leaf, then the key is not present
        if (node->isLeaf) {
            printf("The key %d is not present in the tree.\n", key);
            return;
        }

        // If the child that is supposed to have the key is less than MIN_KEYS, ensure it has enough keys
        if (node->children[idx]->numKeys < MIN_KEYS) {
            if (idx != 0 && node->children[idx - 1]->numKeys >= MIN_KEYS) {
                borrowFromPrev(node, idx);
            } else if (idx != node->numKeys && node->children[idx + 1]->numKeys >= MIN_KEYS) {
                borrowFromNext(node, idx);
            } else {
                if (idx != node->numKeys) {
                    merge(node, idx);
                } else {
                    merge(node, idx - 1);
                }
            }
        }
        deleteFromNode(node->children[idx], key);
    }
}

// Function to delete a key from the B-tree
void deleteKey(BTree* tree, int key) {
    BTreeNode* root = tree->root;

    // Call the delete function on the root
    deleteFromNode(root, key);

    // If the root node has no keys, make the first child the new root
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

bool search(BTreeNode *node, int key) {
    if (node == NULL) {
        return false;  // Base case: if the node is NULL, the key is not found
    }

    int idx = 0;

    // Find the first key greater than or equal to the key
    while (idx < node->numKeys && key > node->keys[idx]) {
        idx++;
    }

    // If the found key is equal to the key we are searching for
    if (idx < node->numKeys && node->keys[idx] == key) {
        return true;  // Key found
    }

    // If the node is a leaf, the key is not present
    if (node->isLeaf) {
        return false;  // Key not found
    }

    // Go to the appropriate child
    return search(node->children[idx], key);
}

// Wrapper function to search for a key in the B-tree
bool btree_search(BTree *tree, int key) {
    if (tree == NULL || tree->root == NULL) {
        return false;  // Tree is empty
    }
    return search(tree->root, key);
}




// Function to traverse the B-tree in sorted order
void traverse(BTreeNode* node) {
    int i;
    for (i = 0; i < node->numKeys; i++) {
        // If this is not a leaf, traverse the child before printing the key
        if (!node->isLeaf) {
            traverse(node->children[i]);
        }
        printf("%d ", node->keys[i]);
    }
    // Traverse the last child
    if (!node->isLeaf) {
        traverse(node->children[i]);
    }
}

// Function to create a new B-tree
BTree* createBTree() {
    BTree* newTree = (BTree*)malloc(sizeof(BTree));
    newTree->root = createNode(1); // Create a root node as a leaf
    return newTree;
}

// Function to free a B-tree node and its children recursively
void freeBTreeNode(BTreeNode *node) {
    if (node == NULL) {
        return;
    }

    // Recursively free child nodes
    for (int i = 0; i <= node->numKeys; i++) {
        if (node->children[i] != NULL) {
            freeBTreeNode(node->children[i]);
        }
    }

    // Free the current node
    free(node);
}

// Function to free the entire B-tree
void freeBTree(BTree *tree) {
    if (tree == NULL) {
        return;
    }

    // Free the root node and all its children
    freeBTreeNode(tree->root);

    // Free the B-tree structure itself
    free(tree);
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
