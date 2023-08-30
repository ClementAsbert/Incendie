#include <stdio.h>
#include "Interface/Foret.h"

int main() {
    Foret* foret = creerForet(5,5);
    initialiserForet(foret);
    //initialiserForetManuellement(foret);
    afficherForet(foret);
    detruireForet(foret);
    return 0;
}
