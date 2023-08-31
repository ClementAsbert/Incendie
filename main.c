#include <stdlib.h>
#include <time.h>
#include "Interface/Foret.h"

int main() {
    srand(time(NULL)); //Permet de générer à chaque éxecution une nouvelle forêt aléatoire
    Foret* foret = creerForet(5,5);
    initialiserForet(foret);
    //initialiserForetManuellement(foret);
    afficherForet(foret);
    detruireForet(foret);
    return 0;
}
