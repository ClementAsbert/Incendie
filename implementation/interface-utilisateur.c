//
// Created by Clément ASBERT on 01/09/2023.
//
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../Interface/interface_utilisateur.h"

/**
 * Fonction qui permet à l'utilisateur d'éxécuter les actions qu'il choisie
 * Ne ce ferme pas temps que l'utilisteur ne choisie pas de quitter
 */
void menu(){
    int choix;
    int longueur, largeur;
    Foret* foret;
    bool tailleChoisie = false;

    do {
        printf("\n");
        printf("Bienvenue dans la simulation d'incendie\n");
        printf("1.Creer foret de taille n/n\n");
        printf("2. Générer une forêt aléatoire\n");
        printf("3. Générer une forêt manuellement\n");
        printf("4. Detruire la foret generer\n");
        printf("5.Lancer la simulation\n");
        printf("6.Afficher la forêt\n");
        printf("7. Quitter\n");
        printf("\n");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                while (!tailleChoisie) {
                    printf("Choisir la taille de la forêt (longueur) : ");
                    scanf("%d", &longueur);
                    printf("Choisir la taille de la forêt (largeur) : ");
                    scanf("%d", &largeur);
                    if (longueur <= 0 || largeur <= 0) {
                        printf("La taille doit être supérieure à zéro.\n");
                    } else {
                        foret = creerForet(longueur, largeur);
                        tailleChoisie = true; // Marquer que la taille a été choisie
                    }
                }
                break;
            case 2:
                if(!tailleChoisie){
                    printf("\033[31m"); //mais la couleur du texte suivant en rouge
                    printf("Veuillez construire une forêt\n");
                    printf("\033[0m"); // réinitialise la couleur en blanc
                } else{
                    initialiserForet(foret);
                    afficherForet(foret);
                }
                break;
            case 3:
                if(!tailleChoisie){
                    printf("\033[31m"); //mais la couleur du texte suivant en rouge
                    printf("Veuillez construire une forêt\n");
                    printf("\033[0m"); // réinitialise la couleur en blanc
                } else{
                    initialiserForetManuellement(foret);
                    afficherForet(foret);
                }
                break;
            case 4:
                detruireForet(foret);
                tailleChoisie = false;
                break;
            case 5:
                //Lancer la simulation
                break;
            case 6:
                tailleChoisie ? afficherForet(foret) : printf("Aucune forêt à afficher\n");
                break;
            case 7:
                detruireForet(foret);
                break;
            default:
                printf("Option invalide. Réessayez.\n");
                break;
        }
    } while (choix != 7);
}


