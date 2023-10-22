//
// Created by Clément ASBERT on 21/09/2023.
//
#include "../Interface/Foret.h"
#include <stdio.h>

Foret* copierForet(const Foret* source) {
    Foret* copie = creerForet(source->longueur, source->largeur);

    for (int i = 0; i < source->longueur; i++) {
        for (int j = 0; j < source->largeur; j++) {
            copie->matrice[i][j] = source->matrice[i][j];
        }
    }

    return copie;
}

void copierForetDansForet(Foret* foret, const Foret* copie) {
    for (int i = 0; i < foret->longueur; i++) {
        for (int j = 0; j < foret->largeur; j++) {
            foret->matrice[i][j] = copie->matrice[i][j];
        }
    }
}

void allumezCelulle(Foret* foret, int x, int y){
    if(x >= 0 && x < foret->longueur && y >= 0 && y < foret->largeur){
        foret->matrice[x][y].etat = 1;
    }
    else{
        printf("coordonnée invalide \n");
    }
}

void simulerPropagationFeu(Foret* foret, int iterations){
    // Créez une copie temporaire de la forêt pour stocker les modifications
    Foret* copie = copierForet(foret);

    for(int t=0; t<iterations; t++){
        //On parcour toute la forêt pour trouver la celulle qui est allumer
        for(int i=0; i<foret->longueur;i++){
            for(int j=0; j<foret->largeur;j++){
                //On trouve une cellule en feu
                if(foret->matrice[i][j].etat = 1){
                    //EN fonction du degré de la cellule on fait différentes actions
                    if(foret->matrice[i][j].degre > 2){
                        copie->matrice[i][j].degre--;
                    }else if(foret->matrice[i][j].degre = 2){
                        copie->matrice[i][j].degre--;
                        copie->matrice[i][j].type = CENDRES;
                        copie->matrice[i][j].symbole = proprietesTypes[CENDRES].symbole;

                    }else if(foret->matrice[i][j].degre = 1){
                        copie->matrice[i][j].degre--;
                        copie->matrice[i][j].type = CENDRES_ETEINTES;
                        copie->matrice[i][j].symbole = proprietesTypes[CENDRES_ETEINTES].symbole;
                    }
                }

                //Pour les types ARBRE,FEUILLE,ROCHE,HERBE on verifie les voisins pour voir si il brule
                if(foret->matrice[i][j].type == ARBRE || foret->matrice[i][j].type == FEUILLE || foret->matrice[i][j].type == ROCHE || foret->matrice[i][j].type == HERBE){
                    //on regarde ses voison pour savoir si il brûle
                    for(int x = i-1; x <= x+1; x++){
                        for(int y = j-1; y <= j+1;y++){
                            if(x >= 0 && x < foret->longueur && y >= 0 && y < foret->largeur &&
                                foret->matrice[i][j].etat == 1){
                                copie->matrice[i][j].degre--;
                                copie->matrice[i][j].etat = 1;
                            }
                        }
                    }
                }
            }
        }
        afficherForet(foret);
        copierForetDansForet(foret, copie);
    }
    detruireForet(copie);
}

