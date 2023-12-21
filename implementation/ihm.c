//
// Created by Clément ASBERT on 20/11/2023.
//


#include <raylib.h>
#include <printf.h>
#include <stdlib.h>
#include "../Interface/ihm.h"
#include "../Interface/Foret.h"
#include "../Interface/simulation.h"

#define MAX_LENGTH_MENU 9

#define MAX_INPUT_CHARS 9
#define CELLSIZE 50

// Tableau de textures pour chaque type de cellule
Texture2D textures[10];

/**
 * Charge les texture en fonction pour chaque symbole
 */
void chargerTextures() {
    // Chargez les textures pour chaque type de cellule
    textures['*'] = LoadTexture("../Interface/Assets/Sprites/arbre-4.png");
    textures[' '] = LoadTexture("../Interface/Assets/Sprites/feuille.png");
    textures['#'] = LoadTexture("../Interface/Assets/Sprites/pierre.png");
    textures['x'] = LoadTexture("../Interface/Assets/Sprites/buisson.png");
    textures['/'] = LoadTexture("../Interface/Assets/Sprites/laissez-tomber.png");
    textures['+'] = LoadTexture("../Interface/Assets/Sprites/sol.png");
    textures['1'] = LoadTexture("../Interface/Assets/Sprites/flamme.png");

    // Ajoutez d'autres textures pour les autres types de cellules
}

/**
 * Detruit les textures
 */
void detruireTexture(){
    for(int i = 0; i < 10; i++){
        UnloadTexture(textures[i]);
    }
}

/**
 * Dessine la forêt
 * @param foret
 */
void dessinForet(Foret *foret){
    chargerTextures();
    for (int i = 0; i < foret->longueur; i++) {
        for (int j = 0; j < foret->largeur; j++) {
            char symbole = foret->matrice[i][j].symbole;
            if(foret->matrice[i][j].etat == 1){
                DrawTexture(textures['1'], i * CELLSIZE, j * CELLSIZE, WHITE);
            }else{
                DrawTexture(textures[symbole], i * CELLSIZE, j * CELLSIZE, WHITE);
            }


        }
    }
}

/**
 * Dessine le menu
 * @return l'index de l'onglet cliqué
 */
int drawMenu(){
    Color textColor = RAYWHITE;
    Color highlightColor = {0,102,204,255};
    const char *menuItems[MAX_LENGTH_MENU] = {
            "1. Générer une forêt aléatoire",
            "2. Detruire la foret générée",
            "3. Lancer la simulation",
            "4. Afficher la forêt",
            "5. Sauvegarder la forêt"};
    int menuItemheight = 50; //hauteur de chaque ligne
    int menuItemSpaceing = 10; //Espacement entre chaque item

    int menuX = 50; // 50 pixels pour tous le menu
    int menuY = 50; // 50 pixels pour le premier item

        //On affiche le menu
        for (int i = 0; i < MAX_LENGTH_MENU; i++) {
            int menuItemX = menuX;
            int menuItemY = menuY + i * (menuItemheight +
                                         menuItemSpaceing);//calcule de la position y pour afficher les un en dessous des autres
            int textWidth = MeasureText(menuItems[i], 20); //On calcule la taille du texte
            int recWidth = textWidth + 30; // On adapte la taille du rectangle en fonction du texte
            Rectangle rec = {menuX, menuItemY, recWidth, menuItemheight};

            //on regarde si la souris survole un élement
            if (CheckCollisionPointRec(GetMousePosition(), rec)) {
                //on dessine le rectangle de survole
                DrawRectangleRec(rec, highlightColor);
                //On dessine le text de chaque élement
                DrawText(menuItems[i], menuItemX + 10, menuItemY + 10, 20, textColor);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    switch (i + 1) {
                        case 1:
                            return 1;
                            break;
                        case 2:
                            return 2;
                            break;
                        case 3:
                            return 3;
                            break;
                        case 4:
                            return 4;
                            break;
                        case 5:
                            return 5;

                    }
                }
            } else {
                //On dessine le texte quand la souris ne passe pas sur le menu
                DrawText(menuItems[i], menuItemX + 10, menuItemY + 10, 20, textColor);
            }
        }
}


/**
 * Fonction qui ouvre la fenêtre raylib et gère le stateManagement
 * @param tailleX taille x de la fenêtre
 * @param tailleY taille y de la fenêtre
 * @param titre de la fenêtre
 */
void ouvertureFenetre(int tailleX, int tailleY, char* titre){
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(tailleX,tailleY,titre);
    int longueur, largeur;
    bool tailleChoisie = false;
    bool celluleAllumer = false;
    Foret* foret;
    GameScreen currentScreen = MENU;
    SetTargetFPS(30);
    while(!WindowShouldClose()){
        //Logique du changment de state
        switch (currentScreen) {
            case MENU:
                switch (drawMenu()) {
                    case 1:
                        //Pour le moment j'initialise la forêt automatiquement car je ne gère pas la taille de la fenetre
                        longueur = 16;
                        largeur = 12;
                        foret = creerForet(longueur, largeur);
                        initialiserForet(foret);
                        tailleChoisie = true;
                        currentScreen = SIZE;
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        if(tailleChoisie){
                            currentScreen = FOREST;
                        }else{
                            currentScreen = ERRORTAILLE;
                        }
                        break;
                    case 5:
                        break;
                }
                break;
            case SIZE:
                if(IsKeyDown(KEY_ENTER)){
                    currentScreen = MENU;
                }
                break;
            case FOREST:
                if(IsKeyDown(KEY_ENTER)){
                    currentScreen = MENU;
                }
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    int mouseX = GetMouseX();
                    int mouseY = GetMouseY();
                    int x = mouseX/CELLSIZE;
                    int y = mouseY/CELLSIZE;
                    allumezCelulle(foret,x,y);
                    celluleAllumer = true;
                    //simulerPropagationFeu(foret,10,10);
                }
                break;
            case ERRORTAILLE:
                if(IsKeyDown(KEY_ENTER)){
                    currentScreen = MENU;
                }
                break;
        }
        //On Dessine le contenue des fenètres
        ClearBackground(DARKGRAY);
        BeginDrawing();
        switch (currentScreen) {
            case MENU:
                drawMenu();
                break;
            case SIZE:
                DrawText("Forêt initialiser en 16 par 12",100,tailleY/2,40,RED);
                break;
            case FOREST:
                dessinForet(foret);
                break;
            case ERRORTAILLE:
                DrawText("La forêt n'est pas inistialisé",100,100,40,RED);
                DrawText("Appuyer sur Entrer",200,300,40,RED);
                break;
        }
        //Fin du dessin
        EndDrawing();
    }
    //On ferme la fenêtre
    CloseWindow();
}




