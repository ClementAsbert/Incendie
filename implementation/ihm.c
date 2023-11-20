//
// Created by Clément ASBERT on 20/11/2023.
//


#include <raylib.h>
#include <printf.h>
#include "../Interface/ihm.h"
#define MAX_LENGTH_MENU 9

void drawMenu(){
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
                        printf("111111111");
                        break;
                    case 2:
                        printf("2222222");
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



