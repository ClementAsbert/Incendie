//
// Created by Clément ASBERT on 30/08/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../Interface/Foret.h"
#include "../Interface/interface_utilisateur.h"


/**
 * permet de creer une forêt de taille nxn
 * @param longueur de la forêt
 * @param largeur de la forêt
 * @return Foret*
 */
Foret* creerForet(int longueur, int largeur) {
    Foret* foret = malloc(sizeof(Foret));
    if (foret == NULL) {
        printf("Erreur lors de l'allocation de mémoire");
    }

    foret->longueur = longueur;
    foret->largeur = largeur;

    // Allouer un tableau de pointeurs (lignes)
    foret->matrice = malloc(longueur * sizeof(Cellule*));
    if (foret->matrice == NULL) {
        printf("Erreur lors de l'allocation de mémoire");
    }

    // Allouer un tableau de cellules pour chaque ligne
    for (int i = 0; i < longueur; i++) {
        foret->matrice[i] = malloc(largeur * sizeof(Cellule));
        if (foret->matrice[i] == NULL) {
            printf("Erreur lors de l'allocation de mémoire");
        }
    }

    return foret;
}

/**
 * Detruit une forêt
 * @param foret
 */
void detruireForet(Foret* foret) {
    // Libérez la mémoire pour chaque ligne de la matrice
    for (int i = 0; i < foret->longueur; i++) {
        free(foret->matrice[i]);
    }

    // Libérez la mémoire pour le tableau de pointeurs
    free(foret->matrice);

    // Libérez la mémoire pour la structure Foret
    free(foret);
}

/**
 * Initialise la forêt automatiquement en placer les cellules aléatoirement
 * @param foret
 */
void initialiserForet(Foret* foret) {
    for (int i = 0; i < foret->longueur; i++) {
        for (int j = 0; j < foret->largeur; j++) {
            int randomType = rand() % 6;
            foret->matrice[i][j].type = (enum TypeCellule)randomType;
            foret->matrice[i][j].etat = proprietesTypes[randomType].etat;
            foret->matrice[i][j].degre = proprietesTypes[randomType].degre;
            foret->matrice[i][j].symbole = proprietesTypes[randomType].symbole;
        }
    }
}

/**
 * Affiche la forêt sour forme avec les symboles de chaque cellule
 * @param foret
 */
void afficherForet(const Foret* foret) {
    for (int i = 0; i < foret->longueur; i++) {
        for (int j = 0; j < foret->largeur; j++) {
            char symbole = foret->matrice[i][j].symbole;
            //printf("\033[32m");
            printf("%c ", symbole);
            //printf("\033[0m");
        }
        printf("\n");
    }
}

/**
 * Affiche la forêt avec degrées de chaque cellules
 * @param foret
 */
void afficherDegreeForet(const Foret* foret) {
    for (int i = 0; i < foret->longueur; i++) {
        for (int j = 0; j < foret->largeur; j++) {
            int degree = foret->matrice[i][j].degre;
            //printf("\033[32m");
            printf("%d ", degree);
            //printf("\033[0m");
        }
        printf("\n");
    }
}


/**
 * Initialise la forêt manuellement, on place manuellement le type de chaque cellule
 * @param foret
 */
void initialiserForetManuellement(Foret* foret) {
    for (int i = 0; i < foret->longueur; i++) {
        for (int j = 0; j < foret->largeur; j++) {
            printf("Entrez le type pour la cellule [%d][%d] : ", i, j);
            int type = saisirEntier();

            // Assurez-vous que le type est valide
            if (type >= SOL && type <= EAU) {
                foret->matrice[i][j].type = type;
                foret->matrice[i][j].etat = proprietesTypes[type].etat;
                foret->matrice[i][j].degre = proprietesTypes[type].degre;
                foret->matrice[i][j].symbole = proprietesTypes[type].symbole;
            } else {
                printf("Type invalide. Utilisation du type par défaut.\n");
                foret->matrice[i][j].type = SOL; // Type par défaut
                foret->matrice[i][j].etat = proprietesTypes[SOL].etat;
                foret->matrice[i][j].degre = proprietesTypes[SOL].degre;
                foret->matrice[i][j].symbole = proprietesTypes[type].symbole;
            }
        }
    }
}

/**
 * Permet de changer le type d'une cellule et ses attribus associé dans une forêt
 * @param foret
 */
void changerTypeCellule(Foret* foret){
    int x,y; //coordonnée de la cellule
    int type;
    bool coordValid = false;

    while(!coordValid){
        printf("Entrez les coordonnées de la cellule (ligne) : ");
        x = saisirEntier();

        printf("Entrez les coordonnées de la cellule (colonne) : ");
        y = saisirEntier();

        if(x < 0 || x >= foret->longueur || y < 0 || y >= foret->largeur){
            printf("Les coordonnée sont invalides\n");
        } else{
            coordValid = true;
        }
    }
    printf("Entrez le nouveau type(int) de la cellule [%d][%d] : ",x,y);
    type = saisirEntier();
    foret->matrice[x][y].type = type;
    foret->matrice[x][y].etat = proprietesTypes[type].etat;
    foret->matrice[x][y].degre = proprietesTypes[type].degre;
    foret->matrice[x][y].symbole = proprietesTypes[type].symbole;
}

/**
 * Sauvegarde une foret dans un fichier texte
 * @param foret à sauvegarder
 * @param nomfichier ou l'on sauvegarde la foret
 */
void saveForet(const Foret* foret, const char* nomFichier){
    //On ouvre le fichier en mode write
    FILE* fichier= fopen(nomFichier, "w");

    if(fichier == NULL){
        printf("impossible d'ouvrir le fichier");
        return;
    }

    //On écris les dimmensions de la forêt dans le fichier
    fprintf(fichier, "%d %d \n",foret->longueur, foret->largeur);

    //On parcours la matrice pour enregistrer les cellules dans le fichier
    for(int i = 0; i < foret->longueur;i++){
        for(int j=0; j < foret->largeur;j++){
            fprintf(fichier, "%c", foret->matrice[i][j].symbole);
        }
    }
    //On ferme le fichier après l'écriture
    fclose(fichier);
    printf("Forêt sauvegarder dans le fichier : %s \n", nomFichier);
}

/**
 * fonction qui recupère une forêt depuis un fichier
 * @param nomFichier
 * @return Foret
 */
void readForet(Foret* foret, const char* nomFichier){
    //On ouvre le fichier en mode read
    FILE* fichier= fopen(nomFichier, "r");

    if(fichier == NULL){
        printf("impossible d'ouvrir le fichier");
    }

    int longueur, largeur;
    if (fscanf(fichier, "%d %d", &longueur, &largeur) != 2) {
        fclose(fichier);
        printf("erreur lors de la lecture des dimensions");
    }

    //On ignore la premiere ligne vus que ce sont les dimenssions
    char ligneIgnorer[100];
    fgets(ligneIgnorer, sizeof(ligneIgnorer), fichier);

    foret = creerForet(longueur, largeur);

    for (int i = 0; i < longueur; i++) {
        for (int j = 0; j < largeur; j++) {
            int c = fgetc(fichier);
            char symbole = (char)c;
            if (c == EOF || symbole == '\n') {
                fclose(fichier);
                detruireForet(foret);
                printf("Erreur lors de la lecture des symboles");
            }
            int type;
            //printf("%c",symbole);
                switch (symbole) {
                    case '+':
                        type = SOL;
                        foret->matrice[i][j].type = type;
                        foret->matrice[i][j].symbole = proprietesTypes[type].symbole;
                        foret->matrice[i][j].etat = proprietesTypes[type].etat;
                        foret->matrice[i][j].degre = proprietesTypes[type].degre;
                        break;
                    case '*':
                        type = ARBRE;
                        foret->matrice[i][j].type = type;
                        foret->matrice[i][j].symbole = proprietesTypes[type].symbole;
                        foret->matrice[i][j].etat = proprietesTypes[type].etat;
                        foret->matrice[i][j].degre = proprietesTypes[type].degre;
                        break;
                    case ' ':
                        type = FEUILLE;
                        foret->matrice[i][j].type = type;
                        foret->matrice[i][j].symbole = proprietesTypes[type].symbole;
                        foret->matrice[i][j].etat = proprietesTypes[type].etat;
                        foret->matrice[i][j].degre = proprietesTypes[type].degre;
                        break;
                    case '#':
                        type = ROCHE;
                        foret->matrice[i][j].type = type;
                        foret->matrice[i][j].symbole = proprietesTypes[type].symbole;
                        foret->matrice[i][j].etat = proprietesTypes[type].etat;
                        foret->matrice[i][j].degre = proprietesTypes[type].degre;
                        break;
                    case 'x':
                        type = HERBE;
                        foret->matrice[i][j].type = type;
                        foret->matrice[i][j].symbole = proprietesTypes[type].symbole;
                        foret->matrice[i][j].etat = proprietesTypes[type].etat;
                        foret->matrice[i][j].degre = proprietesTypes[type].degre;
                        break;
                    case '/':
                        type = EAU;
                        foret->matrice[i][j].type = type;
                        foret->matrice[i][j].symbole = proprietesTypes[type].symbole;
                        foret->matrice[i][j].etat = proprietesTypes[type].etat;
                        foret->matrice[i][j].degre = proprietesTypes[type].degre;
                        break;
                    case '-':
                        type = CENDRES;
                        foret->matrice[i][j].type = type;
                        foret->matrice[i][j].symbole = proprietesTypes[type].symbole;
                        foret->matrice[i][j].etat = proprietesTypes[type].etat;
                        foret->matrice[i][j].degre = proprietesTypes[type].degre;
                        break;
                    case '@':
                        type = CENDRES_ETEINTES;
                        foret->matrice[i][j].type = type;
                        foret->matrice[i][j].symbole = proprietesTypes[type].symbole;
                        foret->matrice[i][j].etat = proprietesTypes[type].etat;
                        foret->matrice[i][j].degre = proprietesTypes[type].degre;
                        break;
                    default:
                        break;

                }
            printf("%c \n", foret->matrice[i][j].symbole);
            }
        }
    fclose(fichier);
}