#include <stdio.h>
#include <stdlib.h>
#include "../include/liste.h"

// Programme principal
int main() {
    Node* head = NULL;
    int data, position,target,supp;
    Node* result;
    char i;

    while (1) {
        // Demander a l'utilisateur s'il veut inserer un nombre
        printf("\nEntrez le nombre que vous souhaitez inserer (ou -1 pour quitter) : ");
        scanf("%d", &data);
        if (data == -1) break;

        printf("Entrez la position ou inserer le nombre ( par ex 0 pour debut, -1 pour fin) : ");
        scanf("%d", &position);

        // Gestion de la position en fonction de l'entree
        if (position == -1) {
            insertAtEnd(&head, data);  // Insertion a la fin
        } else {
            insertAtPosition(&head, data, position);  // Insertion a la position donnee
        }

        // Affichage de la liste apres chaque insertion
        printList(head);
    }

    while (1)
    {
        // Demander a l'utilisateur s'il veut rechercher un nombre
    printf("Voulez-vous rechercher un nombre ? (o/n) : ");
    scanf(" %c", &i);  

    // Sortir de la boucle si l'utilisateur entre 'n' ou 'N'
    if (i == 'n' || i == 'N') {
        break;
    }

    if (i == 'o' || i == 'O') {  
        printf("Entrez le nombre a rechercher : ");
        scanf("%d", &target);

        result = optimizedSearch(head, target);

        if (result != NULL) {
            printf("Element %d trouve dans la liste.\n", result->data);
        } else {
            printf("Element %d non trouve dans la liste.\n", target);
        }
    } 
    }


    while (1)
    {
        // Demander a l'utilisateur s'il veut supprimer un nombre
    printf("Voulez-vous supprimer un nombre ? (o/n) : ");
    scanf(" %c", &i);  

    // Sortir de la boucle si l'utilisateur entre 'n' ou 'N'
    if (i == 'n' || i == 'N') {
        break;
    }

    if (i == 'o' || i == 'O') {  
        
        printf("Entrez le nombre a supprimer : ");
        scanf("%d", &supp);

       int supprimer= deleteNode(&head, supp);

        if(supprimer==0) {
            printf("Element %d non trouve dans la liste.\n", supp);
        } else {
            printf("Element %d supprime de la liste.\n", supp);
        }
        // Afficher la liste apres suppression
        printList(head);
    } 
    }
    // Liberation de la memoire
    freeList(head);
    printf("FIN. ");
    return 0;
}