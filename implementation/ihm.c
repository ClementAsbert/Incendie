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

int choixTaille(int screenWidth){

    char name1[MAX_INPUT_CHARS + 1] = "\0";// NOTE: One extra space required for null terminator char '\0'
    char name2[MAX_INPUT_CHARS + 1] = "\0";// NOTE: One extra space required for null terminator char '\0'
    int letterCountBox1 = 0;
    int letterCountBox2 = 0;

    Rectangle textBox1 = { screenWidth/2.0f - 100, 75, 225, 50 };
    Rectangle textBox2 = { screenWidth/2.0f - 100, 400, 225, 50 };
    bool mouseOnText1 = false;
    bool mouseOnText2 = false;
        // Update
        //----------------------------------------------------------------------------------
        if (CheckCollisionPointRec(GetMousePosition(), textBox1)) {
            mouseOnText1 = true;
            mouseOnText2 = false;  // Désactiver l'autre champ de texte
        } else if (CheckCollisionPointRec(GetMousePosition(), textBox2)) {
            mouseOnText1 = false;  // Désactiver l'autre champ de texte
            mouseOnText2 = true;
        } else {
            mouseOnText1 = false;
            mouseOnText2 = false;
        }

        if ((mouseOnText1)) {
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
            // Get char pressed (unicode character) on the queue
            int key = GetKeyPressed();
            // Check if more characters have been pressed on the same frame
            while (key > 0) {
                // NOTE: Only allow keys in range [48..57]
                if ((key >= 48) && (key <= 57) && (letterCountBox1 < MAX_INPUT_CHARS)) {
                    name1[letterCountBox1] = key;
                    letterCountBox1++;
                }
                key = GetKeyPressed();// Check next character in the queue
            }
            if (IsKeyDown(KEY_BACKSPACE)) {
                letterCountBox1--;
                if (letterCountBox1 < 0) letterCountBox1 = 0;
                name1[letterCountBox1] = '\0';
            }
        } else if ((mouseOnText2)) {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
            int key = GetKeyPressed();
            while (key > 0) {
                if ((key >= 48) && (key <= 57) && (letterCountBox2 < MAX_INPUT_CHARS)) {
                    name2[letterCountBox2] = key;
                    letterCountBox2++;
                }
                key = GetKeyPressed();
            }
            if (IsKeyDown(KEY_BACKSPACE)) {
                letterCountBox2--;
                if (letterCountBox2 < 0) letterCountBox2 = 0;
                name2[letterCountBox2] = '\0';
            }
        } else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        DrawRectangleRec(textBox1, LIGHTGRAY);
        DrawRectangleRec(textBox2, LIGHTGRAY);
        DrawRectangleRec((Rectangle) {textBox1.x, textBox1.y}, LIGHTGRAY);
        DrawRectangleRec((Rectangle) {textBox2.x, textBox2.y}, LIGHTGRAY);
        if (mouseOnText1)
            DrawRectangleLines((int) textBox1.x, (int) textBox1.y, (int) textBox1.width, (int) textBox1.height,
                               RED);
        else
            DrawRectangleLines((int) textBox1.x, (int) textBox1.y, (int) textBox1.width, (int) textBox1.height,
                               DARKGRAY);
        if (mouseOnText2)
            DrawRectangleLines((int) textBox2.x, (int) textBox2.y, (int) textBox2.width, (int) textBox2.height,
                               RED);
        else
            DrawRectangleLines((int) textBox2.x, (int) textBox2.y, (int) textBox2.width, (int) textBox2.height,
                               DARKGRAY);

        DrawText(name1, (int) textBox1.x + 5, (int) textBox1.y + 8, 40, MAROON);
        DrawText(name2, (int) textBox2.x + 5, (int) textBox2.y + 8, 40, MAROON);
        DrawText("Entrer la longueur de le forêt", textBox1.x - 25, textBox1.y - 25, 20, RED);
        DrawText("Entrer la largeur de le forêt", textBox2.x - 25, textBox2.y - 25, 20, RED);
        DrawText(TextFormat("INPUT CHARS: %i/%i", letterCountBox1, MAX_INPUT_CHARS), textBox1.x + 15,
                 textBox1.y + 60,
                 20, DARKGRAY);
        DrawText(TextFormat("INPUT CHARS: %i/%i", letterCountBox2, MAX_INPUT_CHARS), textBox2.x + 15,
                 textBox2.y + 60,
                 20, DARKGRAY);

        if (mouseOnText1) {
            if (letterCountBox1 < MAX_INPUT_CHARS) {
                // Draw blinking underscore char
                DrawText("_", (int) textBox1.x + 8 + MeasureText(name1, 40), (int) textBox1.y + 12, 40, MAROON);
            } else DrawText("Press BACKSPACE to delete chars...", screenWidth / 2, 300, 20, GRAY);

        } else if (mouseOnText2) {
            if (letterCountBox2 < MAX_INPUT_CHARS) {
                // Draw blinking underscore char
                DrawText("_", (int) textBox2.x + 8 + MeasureText(name2, 40), (int) textBox2.y + 12, 40, MAROON);
            } else DrawText("Press BACKSPACE to delete chars...", screenWidth / 2, 300, 20, GRAY);
        }
}

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

void detruireTexture(){
    for(int i = 0; i < 10; i++){
        UnloadTexture(textures[i]);
    }
}


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
        switch (currentScreen) {
            case MENU:
                switch (drawMenu()) {
                    case 1:
                        longueur = 16;
                        largeur = 12;
                        foret = creerForet(longueur, largeur);
                        initialiserForet(foret);
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        currentScreen = FOREST;
                        break;
                    case 5:
                        break;
                }
                break;
            case SIZE:
                if(IsKeyDown(KEY_ENTER)){
                    currentScreen = MENU;
                    longueur = 16;
                    largeur = 16;
                    foret = creerForet(longueur, largeur);
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
        }
        //On commence à mettre les élément dans la fenêtre
        ClearBackground(DARKGRAY);
        BeginDrawing();
        switch (currentScreen) {
            case MENU:
                drawMenu();
                break;
            case SIZE:
                if(!tailleChoisie){
                    choixTaille(tailleX);
                }
                break;
            case FOREST:
                dessinForet(foret);
                break;
        }
        //Fin du dessin
        EndDrawing();
    }
    //On ferme la fenêtre
    CloseWindow();
}




