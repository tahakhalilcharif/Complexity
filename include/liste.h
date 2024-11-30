#ifndef LISTE_H
#define LISTE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct DLNode {
    int data;
    struct DLNode* prev;
    struct DLNode* next;
} DLNode;

DLNode* createDLNode(int data);
void insertAtBeginningDL(DLNode** head, int data);
void insertAtEndDL(DLNode** head, int data);
void insertAtPositionDL(DLNode** head, int data, int position);
DLNode* searchDL(DLNode* head, int target);
DLNode* optimizedSearchDL(DLNode* head, int target);
int deleteDLNode(DLNode** head, int data);
void printDLList(DLNode* head);
void freeDLList(DLNode* head);

#endif
