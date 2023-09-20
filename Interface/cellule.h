//
// Created by Clément ASBERT on 30/08/2023.
//

#ifndef PROJETC_CELLULE_H
#define PROJETC_CELLULE_H

// Types possibles d'une cellule
enum TypeCellule {
    SOL,
    ARBRE,
    FEUILLE,
    ROCHE,
    HERBE,
    EAU,
    CENDRES,
    CENDRES_ETEINTES
};

typedef struct {
    int etat;
    int degre;
    char symbole;
} ProprietesType;

// Table de hachage associant chaque type à ses propriétés
static ProprietesType proprietesTypes[] = {
        { 0, 0, '+' },   // SOL
        { 0, 4, '*'},   // ARBRE
        { 0, 2, ' ' },   // FEUILLE
        { 0, 5, '#' },   // ROCHE
        { 0, 3, 'x' },   // HERBE
        { 0, 0, '/' },   // EAU
        { 0, 1, '-' },   // CENDRES
        { 0, 0, '@' }    // CENDRES_ETEINTES
};

// Structure de données pour une cellule
typedef struct {
    enum TypeCellule type;
    int etat;
    int degre;
    char symbole;
} Cellule;



#endif //PROJETC_CELLULE_H
