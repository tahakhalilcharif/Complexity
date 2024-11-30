#include <stdio.h>
#include <stdlib.h>
#include "../include/ArbreBinaire.h"

// Fonction pour créer un nouveau nœud avec une valeur donnée
BSTNode *newBSTNode(int data)
{
    BSTNode *node = (BSTNode *)malloc(sizeof(BSTNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Fonction d'insertion dans un arbre binaire de recherche (BST)
BSTNode *insertBST(BSTNode *root, int data)
{
    if (root == NULL)
        return newBSTNode(data);

    if (data < root->data)
        root->left = insertBST(root->left, data);
    else if (data > root->data)
        root->right = insertBST(root->right, data);

    return root;
}

// Fonction pour afficher l'arbre en ordre (in-order traversal)
void inorderBST(BSTNode *root)
{
    if (root != NULL)
    {
        inorderBST(root->left);
        printf("%d ", root->data);
        inorderBST(root->right);
    }
}

// Fonction pour trouver le successeur (le plus petit élément dans le sous-arbre droit)
BSTNode *minValueBSTNode(BSTNode *node)
{
    BSTNode *current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Fonction pour supprimer un nœud dans un arbre binaire de recherche
BSTNode *deleteBSTNode(BSTNode *root, int key)
{
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = deleteBSTNode(root->left, key);
    else if (key > root->data)
        root->right = deleteBSTNode(root->right, key);
    else
    {
        if (root->left == NULL)
        {
            BSTNode *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            BSTNode *temp = root->left;
            free(root);
            return temp;
        }

        BSTNode *temp = minValueBSTNode(root->right);
        root->data = temp->data;
        root->right = deleteBSTNode(root->right, temp->data);
    }
    return root;
}

// Fonction de recherche d'un élément dans un arbre binaire de recherche
BSTNode *searchBST(BSTNode *root, int key)
{
    if (root == NULL || root->data == key)
        return root;

    if (key < root->data)
        return searchBST(root->left, key);

    return searchBST(root->right, key);
}

// Fonction pour libérer la mémoire de l'arbre
void freeBST(BSTNode *root)
{
    if (root != NULL)
    {
        freeBST(root->left);
        freeBST(root->right);
        free(root);
    }
}
