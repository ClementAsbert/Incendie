//
// Created by Clément ASBERT on 21/09/2023.
//
#include "../Interface/Foret.h"
#include "../Interface/simulation.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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


void retourArriere(Foret* foret, Historique* historique) {
    if(historique->index > 0) {
        historique->index--;
        copierForetDansForet(foret, historique[historique->index].foret);
    }else {
        printf("Pas d'état précédent disponible.\n");
    }
}

Historique* creationHistorique(int taille){
    Historique* historique = malloc(sizeof(Historique) * taille);
    if (historique == NULL) {
        printf("Erreur lors de l'allocation de mémoire");
    }
    for(int i = 0; i < taille; i++){
        historique[i].foret = malloc(sizeof(Foret));
    }
    return historique;
}

void detruireHistorique(Historique* historique, int taille){
    for(int i = 0; i < taille; i++){
        detruireForet(historique[i].foret);
    }
    free(historique);
}

void detruireHistoriqueIteration(Historique *historique, int taille, int iteration) {
    for (int i = iteration + 1; i < taille; i++) {
        if (historique[i].foret != NULL) {
        // Supposons que detruireForet libère correctement la mémoire de la forêt
        detruireForet(historique[i].foret);
        historique[i].foret = NULL; // Important de mettre le pointeur à NULL après la libération
        }

    }
    // Ne pas libérer l'ensemble de l'historique ici si vous comptez l'utiliser après
}

/**
 * Fonction qui permet de mettre a jour une cellule en fonction de son degré pour l'iteration suivante
 * @param foret fôret principale
 * @param copie copie de la forêt pour les iterations
 * @param i coordonnée de la cellule en cours
 * @param j coordonnée de la cellule en cours
 */
void conditionDegre(Foret* foret, Foret* copie, int i, int j){
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
}

/**
 * Fonction qui permet de regarder les voisins de la cellule pour savoir si elle doit bruler ou non
 * @param foret forêt principale
 * @param copie  copie de la forêt pour les iterations
 * @param i coordonnée de la cellule en cours
 * @param j coordonnée de la cellule en cours
 */
void conditionVoisin(Foret* foret, Foret* copie, int i, int j){
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

/**
 * Fonction qui simule la propagation du feu
 * @param foret ou ce déroule la simulation
 * @param iterations nombre d'iterations pour la simulation
 */
void simulerPropagationFeu(Foret* foret, int iterations) {
    // Créez une copie temporaire de la forêt pour stocker les modifications
    Foret* copie = copierForet(foret);
    Historique* historique = creationHistorique(iterations);
    int index = 0;

    while (index < iterations) {

        //On enregistre dans l'historique la forêt en cours
        historique[index].foret = copierForet(foret);
        historique->index = index;

        //On parcour toute la forêt pour trouver la celulle qui est allumer
        for (int i = 0; i < foret->longueur; i++) {
            for (int j = 0; j < foret->largeur; j++) {
                conditionDegre(foret, copie, i, j);
                conditionVoisin(foret, copie, i, j);
            }
        }

        printf("affichage forêt iteration %d \n", index);
        afficherForet(foret);
        printf("degree \n");
        afficherDegreeForet(foret);
        printf("historique %i\n", index);
        afficherForet(historique[index].foret);

        printf("Appuyez sur entrer pour continuer, 'q' pour quitter, 'r' pour revenir en arrière \n");
        int g = getchar();
        if (g == 'q') {
            printf("Vous quittez la simulation.\n");
            break;
        } else if (g == 'r') {
            int iterationChoisie;
            printf("Entrez le numéro de l'itération à laquelle vous souhaitez revenir (0 à %d): ", index -1);
            scanf("%d", &iterationChoisie);
            if (iterationChoisie >= 0 && iterationChoisie <= index) {
                copierForetDansForet(foret, historique[iterationChoisie].foret);
                copierForetDansForet(copie, historique[iterationChoisie].foret);
                detruireHistoriqueIteration(historique, iterations, iterationChoisie);
                index = iterationChoisie;
            } else {
                printf("Numéro d'itération invalide.\n");
            }
        } else {
            copierForetDansForet(foret, copie);
            index++;
        }
    }

    detruireHistorique(historique, iterations);
    detruireForet(copie);
}




