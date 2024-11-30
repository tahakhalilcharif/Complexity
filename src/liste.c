#include <stdio.h>
#include <stdlib.h>
#include "../include/liste.h"

// Fonction pour créer un nouveau nœud avec une valeur donnée
DLNode* createDLNode(int data) {
    DLNode* newNode = (DLNode*)malloc(sizeof(DLNode));
    if (newNode == NULL) {
        printf("Erreur d'allocation memoire\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Fonction pour insérer un nœud au début de la liste
void insertAtBeginningDL(DLNode** head, int data) {
    DLNode* newNode = createDLNode(data);
    newNode->next = *head;
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

// Fonction pour insérer un nœud à la fin de la liste
void insertAtEndDL(DLNode** head, int data) {
    DLNode* newNode = createDLNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    DLNode* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Fonction pour insérer un nœud à une position donnée
void insertAtPositionDL(DLNode** head, int data, int position) {
    if (position == 0) {
        insertAtBeginningDL(head, data);
        return;
    }
    DLNode* temp = *head;
    int i = 0;
    while (temp != NULL && i < position - 1) {
        temp = temp->next;
        i++;
    }
    if (temp == NULL || temp->next == NULL) {
        insertAtEndDL(head, data);
    } else {
        DLNode* newNode = createDLNode(data);
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next != NULL) {
            temp->next->prev = newNode;
        }
        temp->next = newNode;
    }
}

// Fonction de recherche d'un nœud dans la liste
DLNode* searchDL(DLNode* head, int target) {
    DLNode* current = head;
    while (current != NULL) {
        if (current->data == target) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Fonction de recherche optimisée (avec double-scan)
DLNode* optimizedSearchDL(DLNode* head, int target) {
    if (head == NULL) return NULL;
    DLNode* start = head;
    DLNode* end = head;
    while (end->next != NULL) {
        end = end->next;
    }
    while (start != NULL && end != NULL && start != end && end->next != start) {
        if (start->data == target) {
            return start;
        }
        if (end->data == target) {
            return end;
        }
        start = start->next;
        end = end->prev;
    }
    if (start != NULL && start->data == target) {
        return start;
    }
    return NULL;
}

// Fonction pour supprimer un nœud de la liste
int deleteDLNode(DLNode** head, int data) {
    int supprimer;
    DLNode* nodeToDelete = searchDL(*head, data);
    if (nodeToDelete == NULL) {
        supprimer = 0;
        return supprimer;
    }
    if (nodeToDelete == *head) {
        *head = nodeToDelete->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
    } else if (nodeToDelete->next == NULL) {
        nodeToDelete->prev->next = NULL;
    } else {
        nodeToDelete->prev->next = nodeToDelete->next;
        if (nodeToDelete->next != NULL) {
            nodeToDelete->next->prev = nodeToDelete->prev;
        }
    }
    free(nodeToDelete);
    supprimer = 1;
    return supprimer;
}

// Fonction pour afficher la liste doublement chaînée
void printDLList(DLNode* head) {
    DLNode* temp = head;
    printf("Liste : ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Fonction pour libérer la mémoire de la liste
void freeDLList(DLNode* head) {
    DLNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
