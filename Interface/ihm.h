//
// Created by Clément ASBERT on 20/11/2023.
//

#include <raylib.h>

#ifndef PROJETC_IHM_H
#define PROJETC_IHM_H

#endif //PROJETC_IHM_H


typedef enum GameScreen{MENU,SIZE,FOREST,ERRORTAILLE}GameScreen;

void ouvertureFenetre(int tailleX, int tailleY, char* titre);
int choixTaille(int screenWidth);
int drawMenu();