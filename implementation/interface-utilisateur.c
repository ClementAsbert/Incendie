//
// Created by Clément ASBERT on 01/09/2023.
//
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../Interface/interface_utilisateur.h"
#include "../Interface/Foret.h"

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
        printf("Bienvenue dans la simulation d'incendie\n");
        printf("1.Creer foret de taille n/n\n");
        printf("2. Générer une forêt aléatoire\n");
        printf("3. Générer une forêt manuellement\n");
        printf("4. Detruire la foret generer\n");
        printf("5.Lancer la simulation\n");
        printf("6. Quitter\n");
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
                if(foret == NULL){
                    printf("Veuillez construire une forêt");
                } else{
                    initialiserForet(foret);
                    afficherForet(foret);
                    break;
                }
            case 3:
                if(foret == NULL){
                    printf("Veuillez construire une forêt");
                } else{
                    initialiserForetManuellement(foret);
                    afficherForet(foret);
                    break;
                }
            case 4:
                detruireForet(foret);
                break;
            case 5:
                //Lancer la simulation
                break;
            case 6:
                break;
            default:
                printf("Option invalide. Réessayez.\n");
                break;
        }
    } while (choix != 6);
}


