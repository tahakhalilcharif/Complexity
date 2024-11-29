#include <stdio.h>
#include <stdlib.h>


// Definition de la structure d'un noeud
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node; 



// Fonction pour creer un nouveau noeud
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Erreur d'allocation memoire\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}



// Fonction pour inserer un noeud au debut de la liste
void insertAtBeginning(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}



// Fonction pour inserer un noeud a la fin de la liste
void insertAtEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}



// Fonction pour inserer un noeud a une position specifique
void insertAtPosition(Node** head, int data, int position) {
    if (position == 0) {
        // Appeler insertAtBeginning si la position est 0
        insertAtBeginning(head, data);
        return;
    }

    // Parcourir la liste pour trouver la position
    Node* temp = *head;
    int i = 0;
    while (temp != NULL && i < position - 1) {
        temp = temp->next;
        i++;
    }

    // Si la position est hors limite (fin de la liste)
    if (temp == NULL || temp->next == NULL) {
        // Appeler insertAtEnd si la position est au-dela de la liste
        insertAtEnd(head, data);
    } else {
        // Inserer au milieu de la liste
        Node* newNode = createNode(data);
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next != NULL) {
            temp->next->prev = newNode;
        }
        temp->next = newNode;
    }
}




// Fonction de recherche optimisee dans une liste doublement chainee
Node* optimizedSearch(Node* head, int target) {
    if (head == NULL) return NULL;

    Node* start = head;           // Pointeur de debut
    Node* end = head;             // Pointeur de fin

    // Deplacer `end` au dernier noeud
    while (end->next != NULL) {
        end = end->next;
    }

    // Effectuer la recherche a partir des deux extremites
    while (start != NULL && end != NULL && start != end && end->next != start) {
        if (start->data == target) {
            return start;          // Trouve a partir du debut
        }
        if (end->data == target) {
            return end;            // Trouve a partir de la fin
        }
        start = start->next;
        end = end->prev;
    }

    // Verifier si l'element est au noeud de rencontre
    if (start != NULL && start->data == target) {
        return start;
    }

    return NULL; // Si l'element n'est pas trouve
}

// Fonction de recherche dans une liste doublement chainee
Node* search(Node* head, int target) {
    Node* current = head;  // Debut de la liste

    // Parcourir la liste tant qu'on n'a pas trouve l'element ou qu'on n'atteint pas la fin
    while (current != NULL) {
        if (current->data == target) {
            return current;  // Retourner le noeud trouve
        }
        current = current->next;  // Avancer au noeud suivant
    }

    return NULL;  // Retourner NULL si l'element n'a pas ete trouve
}

// Fonction de suppression d'un noeud avec recherche optimisee
int deleteNode(Node** head, int data) {
    int supprimer;
    // Utiliser la fonction de recherche optimisee pour trouver le noeud a supprimer
    Node* nodeToDelete = search(*head, data);

    // Si l'element n'est pas trouve
    if (nodeToDelete == NULL) {
        supprimer=0;
        //printf("Element %d non trouve dans la liste.\n", data);
        return supprimer;
    }

    // Si l'element a supprimer est le premier noeud
    if (nodeToDelete == *head) {
        *head = nodeToDelete->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
    } 
    // Si l'element a supprimer est le dernier noeud
    else if (nodeToDelete->next == NULL) {
        nodeToDelete->prev->next = NULL;
    } 
    // Si l'element a supprimer est un noeud du milieu
    else {
        nodeToDelete->prev->next = nodeToDelete->next;
        if (nodeToDelete->next != NULL) {
            nodeToDelete->next->prev = nodeToDelete->prev;
        }
    }

    free(nodeToDelete); // Liberer la memoire du noeud supprime
    supprimer=1;
    return supprimer;
    //printf("Element %d supprime de la liste.\n", data);
}



// Fonction pour afficher la liste
void printList(Node* head) {
    Node* temp = head;
    printf("Liste : ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Fonction pour liberer la memoire de la liste
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}