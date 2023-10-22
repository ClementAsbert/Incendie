//
// Created by Clément ASBERT on 30/08/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../Interface/Foret.h"
#include "../Interface/interface_utilisateur.h"


/**
 * permet de creer une forêt de taille nxn
 * @param longueur de la forêt
 * @param largeur de la forêt
 * @return Foret*
 */
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

/**
 * Detruit une forêt
 * @param foret
 */
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

/**
 * Initialise la forêt automatiquement en placer les cellules aléatoirement
 * @param foret
 */
void initialiserForet(Foret* foret) {
    for (int i = 0; i < foret->longueur; i++) {
        for (int j = 0; j < foret->largeur; j++) {
            // Générer un nombre aléatoire entre 0 et 7 pour le type de cellule
            int randomType = rand() % 6;

            switch (randomType) {
                case 0:
                    foret->matrice[i][j].type = SOL;
                    foret->matrice[i][j].etat = proprietesTypes[SOL].etat;
                    foret->matrice[i][j].degre = proprietesTypes[SOL].degre;
                    foret->matrice[i][j].symbole = proprietesTypes[SOL].symbole;
                    break;
                case 1:
                    foret->matrice[i][j].type = ARBRE;
                    foret->matrice[i][j].etat = proprietesTypes[ARBRE].etat;
                    foret->matrice[i][j].degre = proprietesTypes[ARBRE].degre;
                    foret->matrice[i][j].symbole = proprietesTypes[ARBRE].symbole;
                    break;
                case 2:
                    foret->matrice[i][j].type = FEUILLE;
                    foret->matrice[i][j].etat = proprietesTypes[FEUILLE].etat;
                    foret->matrice[i][j].degre = proprietesTypes[FEUILLE].degre;
                    foret->matrice[i][j].symbole = proprietesTypes[FEUILLE].symbole;
                    break;
                case 3:
                    foret->matrice[i][j].type = ROCHE;
                    foret->matrice[i][j].etat = proprietesTypes[ROCHE].etat;
                    foret->matrice[i][j].degre = proprietesTypes[ROCHE].degre;
                    foret->matrice[i][j].symbole = proprietesTypes[ROCHE].symbole;
                    break;
                case 4:
                    foret->matrice[i][j].type = HERBE;
                    foret->matrice[i][j].etat = proprietesTypes[HERBE].etat;
                    foret->matrice[i][j].degre = proprietesTypes[HERBE].degre;
                    foret->matrice[i][j].symbole = proprietesTypes[HERBE].symbole;
                    break;
                case 5:
                    foret->matrice[i][j].type = EAU;
                    foret->matrice[i][j].etat = proprietesTypes[EAU].etat;
                    foret->matrice[i][j].degre = proprietesTypes[EAU].degre;
                    foret->matrice[i][j].symbole = proprietesTypes[EAU].symbole;
                    break;
            }
        }
    }
}

/**
 * Affiche la forêt sour forme avec les symboles de chaque cellule
 * @param foret
 */
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

/**
 * Affiche la forêt avec degrées de chaque cellules
 * @param foret
 */
void afficherDegreeForet(const Foret* foret) {
    for (int i = 0; i < foret->longueur; i++) {
        for (int j = 0; j < foret->largeur; j++) {
            int degree = foret->matrice[i][j].degre;
            printf("\033[32m");
            printf("%d ", degree);
            printf("\033[0m");
        }
        printf("\n");
    }
}

/**
 * Initialise la forêt manuellement, on place manuellement le type de chaque cellule
 * @param foret
 */
void initialiserForetManuellement(Foret* foret) {
    for (int i = 0; i < foret->longueur; i++) {
        for (int j = 0; j < foret->largeur; j++) {
            printf("Entrez le type pour la cellule [%d][%d] : ", i, j);
            int type = saisirEntier();

            // Assurez-vous que le type est valide
            if (type >= SOL && type <= EAU) {
                foret->matrice[i][j].type = type;
                foret->matrice[i][j].etat = proprietesTypes[type].etat;
                foret->matrice[i][j].degre = proprietesTypes[type].degre;
                foret->matrice[i][j].symbole = proprietesTypes[type].symbole;
            } else {
                printf("Type invalide. Utilisation du type par défaut.\n");
                foret->matrice[i][j].type = SOL; // Type par défaut
                foret->matrice[i][j].etat = proprietesTypes[SOL].etat;
                foret->matrice[i][j].degre = proprietesTypes[SOL].degre;
                foret->matrice[i][j].symbole = proprietesTypes[type].symbole;
            }
        }
    }
}

/**
 * Permet de changer le type d'une cellule et ses attribus associé dans une forêt
 * @param foret
 */
void changerTypeCellule(Foret* foret){
    int x,y; //coordonnée de la cellule
    int type;
    bool coordValid = false;

    while(!coordValid){
        printf("Entrez les coordonnées de la cellule (ligne) : ");
        x = saisirEntier();

        printf("Entrez les coordonnées de la cellule (colonne) : ");
        y = saisirEntier();

        if(x < 0 || x >= foret->longueur || y < 0 || y >= foret->largeur){
            printf("Les coordonnée sont invalides\n");
        } else{
            coordValid = true;
        }
    }
    printf("Entrez le nouveau type(int) de la cellule [%d][%d] : ",x,y);
    type = saisirEntier();
    foret->matrice[x][y].type = type;
    foret->matrice[x][y].etat = proprietesTypes[type].etat;
    foret->matrice[x][y].degre = proprietesTypes[type].degre;
    foret->matrice[x][y].symbole = proprietesTypes[type].symbole;
}