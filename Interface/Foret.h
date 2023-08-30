//
// Created by Clément ASBERT on 30/08/2023.
//

#ifndef PROJETC_FORET_H
#define PROJETC_FORET_H
#include "cellule.h"

// Structure de données pour la forêt
typedef struct {
    int longueur;
    int largeur;
    Cellule** matrice; // Tableau à deux dimensions de cellules
} Foret;

// Fonctions pour la manipulation de la forêt
Foret* creerForet(int longueur, int largeur);
void detruireForet(Foret* foret); //Ne pas oublier de libérer la mémoir
void initialiserForet(Foret* foret);
void initialiserForetManuellement(Foret* foret);
void afficherForet(const Foret* foret);

#endif //PROJETC_FORET_H
