//
// Created by Clément ASBERT on 20/11/2023.
//

#include <raylib.h>

#ifndef PROJETC_IHM_H
#define PROJETC_IHM_H

#endif //PROJETC_IHM_H

//Structure pour les boutons
typedef struct{
    Rectangle rec;
    Color color;
    char* text;
}Button;
void ouvertureFenetre(int tailleX, int tailleY, char* titre);