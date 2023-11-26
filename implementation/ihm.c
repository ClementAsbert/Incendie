//
// Created by Clément ASBERT on 20/11/2023.
//


#include <raylib.h>
#include <printf.h>
#include <stdlib.h>
#include "../Interface/ihm.h"
#include "../Interface/Foret.h"

#define MAX_LENGTH_MENU 9

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800
#define CELL_SIZE 32
#define MAX_INPUT_CHARS 9

// Tableau de textures pour chaque type de cellule
Texture2D textures[10];

bool IsAnyKeyPressed()
{
    bool keyPressed = false;
    int key = GetKeyPressed();

    if ((key >= 32) && (key <= 126)) keyPressed = true;

    return keyPressed;
}

void choixTaille(int screenWidth,int* longueur, int* largeur){

    bool exit = false;

    char name1[MAX_INPUT_CHARS + 1] = "\0";// NOTE: One extra space required for null terminator char '\0'
    char name2[MAX_INPUT_CHARS + 1] = "\0";// NOTE: One extra space required for null terminator char '\0'
    int letterCountBox1 = 0;
    int letterCountBox2 = 0;

    Rectangle textBox1 = { screenWidth/2.0f - 100, 75, 225, 50 };
    Rectangle textBox2 = { screenWidth/2.0f - 100, 400, 225, 50 };
    bool mouseOnText1 = false;
    bool mouseOnText2 = false;


    int framesCounter1 = 0;
    int framesCounter2 = 0;

    SetTargetFPS(10);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
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

        if ((mouseOnText1))
        {
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
            // Get char pressed (unicode character) on the queue
            int key = GetKeyPressed();
            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [48..57]
                if ((key >= 48) && (key <= 57) && (letterCountBox1 < MAX_INPUT_CHARS))
                {
                    name1[letterCountBox1] = key;
                    letterCountBox1++;
                }
                key = GetKeyPressed();  // Check next character in the queue
            }
            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCountBox1--;
                if (letterCountBox1 < 0) letterCountBox1 = 0;
                name1[letterCountBox1] = '\0';
            }
        }else if ((mouseOnText2)){
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
            int key = GetKeyPressed();
            while(key > 0){
                if((key >= 48) && (key <= 57) && (letterCountBox2 < MAX_INPUT_CHARS)){
                    name2[letterCountBox2] = key;
                    letterCountBox2++;
                }
                key = GetKeyPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCountBox2--;
                if (letterCountBox2 < 0) letterCountBox2 = 0;
                name2[letterCountBox2] = '\0';
            }
        }
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (mouseOnText1) framesCounter1++;
        else framesCounter1 = 0 ;
        if (mouseOnText2) framesCounter2++;
        else framesCounter2 = 0 ;

        if(IsKeyPressed(KEY_ENTER)){
            /**longueur = atoi(name1);
            *largeur = atoi(name2);
            printf("%i", *longueur);
            printf("%i", *largeur);*/
            CloseWindow();

        }


        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangleRec(textBox1, LIGHTGRAY);
        DrawRectangleRec(textBox2, LIGHTGRAY);
        DrawRectangleRec((Rectangle){textBox1.x, textBox1.y}, LIGHTGRAY);
        DrawRectangleRec((Rectangle){textBox2.x, textBox2.y}, LIGHTGRAY);
        if (mouseOnText1) DrawRectangleLines((int)textBox1.x, (int)textBox1.y, (int)textBox1.width, (int)textBox1.height, RED);
        else DrawRectangleLines((int)textBox1.x, (int)textBox1.y, (int)textBox1.width, (int)textBox1.height, DARKGRAY);
        if (mouseOnText2) DrawRectangleLines((int)textBox2.x, (int)textBox2.y, (int)textBox2.width, (int)textBox2.height, RED);
        else DrawRectangleLines((int)textBox2.x, (int)textBox2.y, (int)textBox2.width, (int)textBox2.height, DARKGRAY);

        DrawText(name1, (int)textBox1.x + 5, (int)textBox1.y + 8, 40, MAROON);
        DrawText(name2, (int)textBox2.x + 5, (int)textBox2.y + 8, 40, MAROON);
        DrawText("Entrer la longueur de le forêt",textBox1.x -25, textBox1.y - 25, 20, RED);
        DrawText("Entrer la largeur de le forêt",textBox2.x -25, textBox2.y - 25, 20, RED);
        DrawText(TextFormat("INPUT CHARS: %i/%i", letterCountBox1, MAX_INPUT_CHARS), textBox1.x + 15 , textBox1.y + 60, 20, DARKGRAY);
        DrawText(TextFormat("INPUT CHARS: %i/%i", letterCountBox2, MAX_INPUT_CHARS), textBox2.x +15, textBox2.y + 60, 20, DARKGRAY);

        if (mouseOnText1)
        {
            if (letterCountBox1 < MAX_INPUT_CHARS)
            {
                // Draw blinking underscore char
                if (((framesCounter1/20)%2) == 0) DrawText("_", (int)textBox1.x + 8 + MeasureText(name1, 40), (int)textBox1.y + 12, 40, MAROON);
            }
            else DrawText("Press BACKSPACE to delete chars...", screenWidth/2, 300, 20, GRAY);

        }else if (mouseOnText2){
            if (letterCountBox2 < MAX_INPUT_CHARS)
            {
                // Draw blinking underscore char
                if (((framesCounter2/20)%2) == 0) DrawText("_", (int)textBox2.x + 8 + MeasureText(name2, 40), (int)textBox2.y + 12, 40, MAROON);
            }
            else DrawText("Press BACKSPACE to delete chars...", screenWidth/2, 300, 20, GRAY);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}

/*void chargerTextures() {
    // Chargez les textures pour chaque type de cellule
    textures['*'] = LoadTexture("../Interface/Assets/Sprites/arbre-4.png");
    printf("Texture ID: %d\n", textures['*'].id);
    textures[' '] = LoadTexture("../Interface/Assets/Sprites/feuille.png");
    printf("Texture ID: %d\n", textures[' '].id);
    textures['#'] = LoadTexture("../Interface/Assets/Sprites/pierre.png");
    printf("Texture ID: %d\n", textures['#'].id);
    textures['x'] = LoadTexture("../Interface/Assets/Sprites/buisson.png");
    printf("Texture ID: %d\n", textures['x'].id);
    textures['/'] = LoadTexture("../Interface/Assets/Sprites/laissez-tomber.png");
    printf("Texture ID: %d\n", textures['/'].id);
    // Ajoutez d'autres textures pour les autres types de cellules
}*/

/*void detruireTexture(){
    for(int i = 0; i < 10; i++){
        UnloadTexture(textures[i]);
    }
}*/

void drawMenu(){
    int longueur, largeur;
    bool tailleChoisie = false;
    Foret* foret;
    Color textColor = RAYWHITE;
    Color highlightColor = {0,102,204,255};
    const char *menuItems[MAX_LENGTH_MENU] = {
            "1. Creer foret de taille [n][n]",
            "2. Générer une forêt aléatoire",
            "3. Générer une forêt manuellement",
            "4. Detruire la foret générée",
            "5. Lancer la simulation",
            "6. Afficher la forêt",
            "7. Changer le type d'une cellule",
            "8. Sauvegarder la forêt",
            "9. Récupérer une forêt depuis un fichier",
            "10. Quitter"};

    int menuItemheight = 50; //hauteur de chaque ligne
    int menuItemSpaceing = 10; //Espacement entre chaque item

    int menuX = 50; // 50 pixels pour tous le menu
    int menuY = 50; // 50 pixels pour le premier item

    //On affiche le menu
    for (int i = 0; i < MAX_LENGTH_MENU; i++){
        int menuItemX = menuX;
        int menuItemY = menuY + i * (menuItemheight + menuItemSpaceing);//calcule de la position y pour afficher les un en dessous des autres
        int textWidth = MeasureText(menuItems[i],20); //On calcule la taille du texte
        int recWidth = textWidth + 30; // On adapte la taille du rectangle en fonction du texte
        Rectangle rec = {menuX, menuItemY, recWidth, menuItemheight};

        //on regarde si la souris survole un élement
        if(CheckCollisionPointRec(GetMousePosition(), rec)){
            //on dessine le rectangle de survole
            DrawRectangleRec(rec,highlightColor);
            //On dessine le text de chaque élement
            DrawText(menuItems[i],menuItemX + 10, menuItemY + 10,20,textColor);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                switch (i + 1) {
                    case 1:
                        choixTaille(WINDOW_WIDTH,&longueur,&largeur);
                        break;
                    case 2:
                        break;
                    case 3:

                        break;
                    case 4:

                        break;
                    case 5:

                        break;
                    case 6:
                        break;
                    case 7:

                        break;
                    case 8:

                        break;
                    case 9:
                        break;
                    default:
                        break;
                }
            }
        }else{
            //On dessine le texte quand la souris ne passe pas sur le menu
            DrawText(menuItems[i],menuItemX + 10, menuItemY + 10,20,textColor);
        }
    }
}

void drawForet(int tailleX, int tailleY, char* titre){
    InitWindow(tailleX,tailleY,titre);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(DARKGRAY);

        EndDrawing();
    }
}


void ouvertureFenetre(int tailleX, int tailleY, char* titre){
    InitWindow(tailleX,tailleY,titre);
    Button btn1 = {{50,600,100,50}, RED, "button"};
    while(!WindowShouldClose()){

        //On commence à mettre les élément dans la fenêtre
        BeginDrawing();
        ClearBackground(DARKGRAY);

        drawMenu();


        //Fin du dessin
        EndDrawing();
    }
    //On ferme la fenêtre
    CloseWindow();
}



