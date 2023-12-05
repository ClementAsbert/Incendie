//
// Created by Clément ASBERT on 30/08/2023.
//

#ifndef PROJETC_SIMULATION_H
#define PROJETC_SIMULATION_H

#include "foret.h"
#include <stdbool.h>

typedef struct{
    Foret* foret;
    int index;1
}Historique;

void simulerPropagationFeu(Foret* foret, int iterations);
void conditionDegre(Foret* foret, Foret* copie, int i, int j);
void conditionVoisin(Foret* foret, Foret* copie, int i, int j);
bool allumezCelulle(Foret* foret, int x, int y);
void copierForetDansForet(Foret* foret, const Foret* copie);
Foret* copierForet(const Foret* source);
Historique* creationHistorique(int taille);
void detruireHistorique(Historique* historique, int taille);

#endif //PROJETC_SIMULATION_H
