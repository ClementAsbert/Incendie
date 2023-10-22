//
// Created by Clément ASBERT on 30/08/2023.
//

#ifndef PROJETC_SIMULATION_H
#define PROJETC_SIMULATION_H

#include "foret.h"
#include <stdbool.h>

// Fonction pour simuler la propagation du feu
void simulerPropagationFeu(Foret* foret, int iterations);
bool allumezCelulle(Foret* foret, int x, int y);
void copierForetDansForet(Foret* foret, const Foret* copie);
Foret* copierForet(const Foret* source);

#endif //PROJETC_SIMULATION_H
