//
// Created by Clément ASBERT on 21/09/2023.
//
#include "../Interface/Foret.h"
#include <stdio.h>
#include <stdbool.h>

/**
 * Permet de copier la forêt
 * @param source forêt à copier
 * @return Foret*
 */
Foret* copierForet(const Foret* source) {
    Foret* copie = creerForet(source->longueur, source->largeur);

    for (int i = 0; i < source->longueur; i++) {
        for (int j = 0; j < source->largeur; j++) {
            copie->matrice[i][j] = source->matrice[i][j];
        }
    }

    return copie;
}

/**
 * Permet de copier la copie de la forêt dans la forêt principal
 * @param foret d'origine
 * @param copie de la forêt
 */
void copierForetDansForet(Foret* foret, const Foret* copie) {
    for (int i = 0; i < foret->longueur; i++) {
        for (int j = 0; j < foret->largeur; j++) {
            foret->matrice[i][j] = copie->matrice[i][j];
        }
    }
}

/**
 * Permet d'allumer une cellule pour commencer la simulation
 * @param foret ou on allume la cellule
 * @param x coordonnée x de la cellule
 * @param y coordonnée y de la cellule
 * @return boolean
 */
bool allumezCelulle(Foret* foret, int x, int y){
    if(x >= 0 && x < foret->longueur && y >= 0 && y < foret->largeur && foret->matrice[x][y].type != SOL && foret->matrice[x][y].type != EAU){
        foret->matrice[x][y].etat = 1;
        return true;
    }
    else{
        printf("coordonnée invalide ou type de celulle impossible à allumer \n");
        return false;
    }
}

/**
 * Fonction qui simule la propagation du feu
 * @param foret ou ce déroule la simulation
 * @param iterations nombre d'iterations pour la simulation
 */
void simulerPropagationFeu(Foret* foret, int iterations) {
    // Créez une copie temporaire de la forêt pour stocker les modifications
    Foret *copie = copierForet(foret);

    while (iterations > 0) {
        //On parcour toute la forêt pour trouver la celulle qui est allumer
        for (int i = 0; i < foret->longueur; i++) {
            for (int j = 0; j < foret->largeur; j++) {
                //On trouve une cellule en feu
                if (foret->matrice[i][j].etat == 1) {
                    //EN fonction du degré de la cellule on fait différentes actions
                    if (foret->matrice[i][j].degre > 2) {
                        copie->matrice[i][j].degre--;
                    } else if (foret->matrice[i][j].degre == 2) {
                        copie->matrice[i][j].degre--;
                        copie->matrice[i][j].type = CENDRES;
                        copie->matrice[i][j].symbole = proprietesTypes[CENDRES].symbole;

                    } else if (foret->matrice[i][j].degre == 1) {
                        copie->matrice[i][j].degre--;
                        copie->matrice[i][j].type = CENDRES_ETEINTES;
                        copie->matrice[i][j].symbole = proprietesTypes[CENDRES_ETEINTES].symbole;
                    }else if(foret->matrice[i][j].degre == 0){
                        copie->matrice[i][j].symbole = proprietesTypes[CENDRES_ETEINTES].symbole;
                        copie->matrice[i][j].etat = 0;
                        copie->matrice[i][j].type = CENDRES_ETEINTES;
                    }
                }
                //Pour les types ARBRE,FEUILLE,ROCHE,HERBE on verifie les voisins pour voir si il brule
                if (foret->matrice[i][j].type == ARBRE || foret->matrice[i][j].type == FEUILLE ||
                    foret->matrice[i][j].type == ROCHE || foret->matrice[i][j].type == HERBE) {
                    for (int dx = -1; dx <= 1; dx++) { //On génére les combinaisons pour verification du carrer de 3X3
                        for (int dy = -1; dy <= 1; dy++) {
                            int x = i + dx;
                            int y = j + dy;

                            if (dx == 0 && dy == 0) {
                                // Ignorer la cellule en cours
                                continue;
                            }
                            //verification avant de mettre à jour la cellule
                            if (x >= 0 && x < foret->longueur && y >= 0 && y < foret->largeur &&
                                foret->matrice[x][y].etat == 1 &&
                                foret->matrice[x][y].type != SOL && foret->matrice[x][y].type != EAU &&
                                copie->matrice[i][j].degre != 0)
                            {
                                copie->matrice[i][j].degre--;
                                copie->matrice[i][j].etat = 1;
                            }
                        }
                    }
                }
            }
        }
        printf("affichage forêt iteration %d \n", iterations);
        afficherForet(foret);
        printf("degree \n");
        afficherDegreeForet(foret);
        copierForetDansForet(foret, copie);
        iterations--;
    }
    detruireForet(copie);
}

