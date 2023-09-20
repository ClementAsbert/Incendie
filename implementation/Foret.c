//
// Created by Clément ASBERT on 30/08/2023.
//

#include <stdlib.h>
#include <stdio.h>

#include "../Interface/Foret.h"

Foret* creerForet(int longueur, int largeur) {
    Foret* foret = malloc(sizeof(Foret));
    if (foret == NULL) {
        // Gérer l'échec de l'allocation mémoire
    }

    foret->longueur = longueur;
    foret->largeur = largeur;

    // Allouer un tableau de pointeurs (lignes)
    foret->matrice = malloc(longueur * sizeof(Cellule*));
    if (foret->matrice == NULL) {
        // Gérer l'échec de l'allocation mémoire
    }

    // Allouer un tableau de cellules pour chaque ligne
    for (int i = 0; i < longueur; i++) {
        foret->matrice[i] = malloc(largeur * sizeof(Cellule));
        if (foret->matrice[i] == NULL) {
            // Gérer l'échec de l'allocation mémoire
        }
    }

    return foret;
}

void detruireForet(Foret* foret) {
    // Libérez la mémoire pour chaque ligne de la matrice
    for (int i = 0; i < foret->longueur; i++) {
        free(foret->matrice[i]);
    }

    // Libérez la mémoire pour le tableau de pointeurs
    free(foret->matrice);

    // Libérez la mémoire pour la structure Foret
    free(foret);
}

void initialiserForet(Foret* foret) {
    for (int i = 0; i < foret->longueur; i++) {
        for (int j = 0; j < foret->largeur; j++) {
            // Générer un nombre aléatoire entre 0 et 7 pour le type de cellule
            int randomType = rand() % 8;

            switch (randomType) {
                case 0:
                    foret->matrice[i][j].type = SOL;
                    foret->matrice[i][j].etat = proprietesTypes[SOL].etat;
                    foret->matrice[i][j].degre = proprietesTypes[SOL].degre;
                    break;
                case 1:
                    foret->matrice[i][j].type = ARBRE;
                    foret->matrice[i][j].etat = proprietesTypes[ARBRE].etat;
                    foret->matrice[i][j].degre = proprietesTypes[ARBRE].degre;
                    break;
                case 2:
                    foret->matrice[i][j].type = FEUILLE;
                    foret->matrice[i][j].etat = proprietesTypes[FEUILLE].etat;
                    foret->matrice[i][j].degre = proprietesTypes[FEUILLE].degre;
                    break;
                case 3:
                    foret->matrice[i][j].type = ROCHE;
                    foret->matrice[i][j].etat = proprietesTypes[ROCHE].etat;
                    foret->matrice[i][j].degre = proprietesTypes[ROCHE].degre;
                    break;
                case 4:
                    foret->matrice[i][j].type = HERBE;
                    foret->matrice[i][j].etat = proprietesTypes[HERBE].etat;
                    foret->matrice[i][j].degre = proprietesTypes[HERBE].degre;
                    break;
                case 5:
                    foret->matrice[i][j].type = EAU;
                    foret->matrice[i][j].etat = proprietesTypes[EAU].etat;
                    foret->matrice[i][j].degre = proprietesTypes[EAU].degre;
                    break;
                case 6:
                    foret->matrice[i][j].type = CENDRES;
                    foret->matrice[i][j].etat = proprietesTypes[CENDRES].etat;
                    foret->matrice[i][j].degre = proprietesTypes[CENDRES].degre;
                    break;
                case 7:
                    foret->matrice[i][j].type = CENDRES_ETEINTES;
                    foret->matrice[i][j].etat = proprietesTypes[CENDRES_ETEINTES].etat;
                    foret->matrice[i][j].degre = proprietesTypes[CENDRES_ETEINTES].degre;
                    break;
            }
        }
    }
}

void afficherForet(const Foret* foret) {
    for (int i = 0; i < foret->longueur; i++) {
        for (int j = 0; j < foret->largeur; j++) {
            int type = foret->matrice[i][j].type;
            char symbole = proprietesTypes[type].symbole;
            printf("\033[32m");
            printf("%c ", symbole);
            printf("\033[0m");
        }
        printf("\n");
    }
}

void initialiserForetManuellement(Foret* foret) {
    for (int i = 0; i < foret->longueur; i++) {
        for (int j = 0; j < foret->largeur; j++) {
            printf("Entrez le type pour la cellule [%d][%d] : ", i, j);
            int type;
            scanf("%d", &type);

            // Assurez-vous que le type est valide
            if (type >= SOL && type <= CENDRES_ETEINTES) {
                foret->matrice[i][j].type = type;
                foret->matrice[i][j].etat = proprietesTypes[type].etat;
                foret->matrice[i][j].degre = proprietesTypes[type].degre;
            } else {
                printf("Type invalide. Utilisation du type par défaut.\n");
                foret->matrice[i][j].type = SOL; // Type par défaut
                foret->matrice[i][j].etat = proprietesTypes[SOL].etat;
                foret->matrice[i][j].degre = proprietesTypes[SOL].degre;
            }
        }
    }
}