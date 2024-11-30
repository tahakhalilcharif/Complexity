#ifndef ARBREBINAIRE_H
#define ARBREBINAIRE_H

#include <stdio.h>
#include <stdlib.h>

// Définition de la structure d'un nœud de l'arbre
typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Prototypes des fonctions
Node *newNode(int data);               // Crée un nouveau nœud
Node *insert(Node *root, int data);    // Insère une valeur dans l'arbre
void inorder(Node *root);              // Affiche l'arbre en ordre (in-order traversal)
Node *minValueNode(Node *node);        // Trouve le nœud avec la valeur minimale
Node *deleteNode(Node *root, int key); // Supprime un nœud de l'arbre
Node *search(Node *root, int key);     // Recherche un nœud dans l'arbre
void freeTree(Node *root);             // Libère la mémoire allouée à l'arbre

#endif // ARBREBINAIRE_H
