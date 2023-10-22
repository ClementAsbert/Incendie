//
// Created by Clément ASBERT on 30/08/2023.
//

#ifndef PROJETC_SIMULATION_H
#define PROJETC_SIMULATION_H

#include "foret.h"

// Fonction pour simuler la propagation du feu
void simulerPropagationFeu(Foret* foret, int iterations);
void allumezCelulle(Foret* foret, int x, int y);

#endif //PROJETC_SIMULATION_H
