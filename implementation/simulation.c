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

Historique* creationHistorique(int taille){
    Historique* historique = malloc(sizeof(historique) * taille);
    if (historique == NULL) {
        printf("Erreur lors de l'allocation de mémoire");
    }
    return historique;
}

void detruireHistorique(Historique* historique, int taille){
    for(int i = 0; i < taille; i++){
        detruireForet(historique[i].foret);
    }
    free(historique);
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
void simulerPropagationFeu(Foret* foret, int iterations, int tailleHistorique) {
    // Créez une copie temporaire de la forêt pour stocker les modifications
    Foret* copie = copierForet(foret);

    Historique* historique= creationHistorique(tailleHistorique);
    int index = 0;

    while (iterations > 0) {

        //On enregistre dans l'historique la forêt en cours
        if(index + 1 == tailleHistorique){
            detruireForet(historique[0].foret);
            for(int i = 0 ; i < tailleHistorique - 1 ; i ++){
                historique[i] = historique[i + 1];
            }
            index--;
        }
        historique[index].foret = copierForet(foret);
        index = (index + 1) % tailleHistorique;

        //On parcour toute la forêt pour trouver la celulle qui est allumer
        for (int i = 0; i < foret->longueur; i++) {
            for (int j = 0; j < foret->largeur; j++) {
                conditionDegre(foret, copie,i,j);
                //Pour les types ARBRE,FEUILLE,ROCHE,HERBE on verifie les voisins pour voir si il brule
                conditionVoisin(foret, copie, i, j);
            }
        }
        printf("affichage forêt iteration %d \n", iterations);
        afficherForet(foret);
        printf("degree \n");
        afficherDegreeForet(foret);

        //On attend que l'utilisateur appuis sur une touche pour continuer
        printf("Appuiez sur Entrer pour continue ou q pour quitter et r pour revenir en arrière dans la simulation \n");
        int g = getchar();
        if(g == 'q'){
            printf("Vous quittez la simulation \n");
            break;
        }else if (g == 'r'){
            index = (index - 1 + tailleHistorique) % tailleHistorique;
            copierForetDansForet(foret, historique[index].foret);
            iterations++;
        }else{
            copierForetDansForet(foret, copie);
            iterations--;
        }
    }
    detruireHistorique(historique,tailleHistorique);
    detruireForet(copie);
}

