//
// Created by Clément ASBERT on 01/09/2023.
//
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../Interface/interface_utilisateur.h"

/**
 * Fonction qui permet de verifier que l'utilisateur rentre bien un nombre entier et non pas une lettre ou autre
 * @return l'entier taper par l'utilisateur
 */
int saisirEntier() {
    int entier;
    while (1) {
        if (scanf("%d", &entier) == 1) {
            while (getchar() != '\n'); // Nettoyer le flux d'entrée
            return entier;
        }
        printf("Veuillez entrer un nombre valide : ");
        while (getchar() != '\n'); // Nettoyer le flux d'entrée
    }
}

/**
 * fonction qui permet à l'utilisateur de choisir la taille de la forêt
 * Gère le cas ou l'utilisateur rentre des lettres
 * @param longueur
 * @param largeur
 */
void choixTailleForêt(int* longueur, int* largeur){
    bool exit = false;
    do {
        printf("Choisir la taille de la forêt (longueur) : ");
        *longueur = saisirEntier();

        printf("Choisir la taille de la forêt (largeur) : ");
        *largeur = saisirEntier();

        if (*longueur <= 0 || *largeur <= 0) {
            printf("La taille doit être supérieure à zéro.\n");
        } else {
            exit = true; // Marquer que la taille a été choisie
        }
    } while (!exit);
}

void messageErreurConstructionForet(){
    printf("\033[31m"); //mais la couleur du texte suivant en rouge
    printf("Veuillez construire une forêt\n");
    printf("\033[0m"); // réinitialise la couleur en blanc
}

/**
 * Fonction qui permet à l'utilisateur d'éxécuter les actions qu'il choisie
 * Ne ce ferme pas temps que l'utilisteur ne choisie pas de quitter
 */
void menu(){
    int choix;
    int longueur, largeur;
    Foret* foret;
    bool tailleChoisie = false;

    do {
        printf("\n");
        printf("Bienvenue dans la simulation d'incendie\n");
        printf("1.Creer foret de taille [n][n]\n");
        printf("2.Générer une forêt aléatoire\n");
        printf("3.Générer une forêt manuellement\n");
        printf("4.Detruire la foret générée\n");
        printf("5.Lancer la simulation\n");
        printf("6.Afficher la forêt\n");
        printf("7.Changer le type d'une cellule\n");
        printf("8.Quitter\n");
        printf("\n");

        choix = saisirEntier();

        switch (choix) {
            case 1:
                choixTailleForêt(&longueur,&largeur);
                tailleChoisie = true;
                foret = creerForet(longueur,largeur);
                break;
            case 2:
                if(!tailleChoisie){
                    messageErreurConstructionForet();
                } else{
                    initialiserForet(foret);
                    afficherForet(foret);
                }
                break;
            case 3:
                if(!tailleChoisie){
                    messageErreurConstructionForet();
                } else{
                    initialiserForetManuellement(foret);
                    afficherForet(foret);
                }
                break;
            case 4:
                tailleChoisie ? detruireForet(foret)
                : messageErreurConstructionForet();
                tailleChoisie = false;
                break;
            case 5:
                if(tailleChoisie){
                    int x,y,t;
                    do{
                        printf("Choisissez la cellule à allumer \n");
                        printf("choisisez la position x \n");
                        x = saisirEntier();
                        printf("choisisez la position y \n");
                        y = saisirEntier();
                    } while(!allumezCelulle(foret, x,y));
                    printf("Choisissez le nombre d'itération \n");
                    t = saisirEntier();
                    simulerPropagationFeu(foret,t);
                }else{
                    messageErreurConstructionForet();
                }
                break;
            case 6:
                tailleChoisie ? afficherForet(foret) : printf("Aucune forêt à afficher\n");
                break;
            case 7:
                tailleChoisie ? changerTypeCellule(foret)
                : messageErreurConstructionForet();
                break;
            case 8:
                foret != NULL ? detruireForet(foret) : NULL;
                break;
            default:
                printf("Option invalide. Réessayez.\n");
                break;
        }
    } while (choix != 8);
}


