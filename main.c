#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Interface/ihm.h"
#include "Interface/interface_utilisateur.h"


void start(){
    printf(" (                                             \n");
    printf(" )\\ )                          (               \n");
    printf("(()/(               (          )\\ )  (     (   \n");
    printf("  /(_)) (      (    ))\\  (     (()/(  )\\   ))\\ \n");
    printf("(_))   )\\ )   )\\  /((_) )\\ )   ((_))((_) /((_)\n");
    printf("|_ _| _(_/(  ((_)(_))  _(_/(   _| |  (_)(_))  \n");
    printf(" | | | ' \\))/ _| / -_)| ' \\))/ _` |  | |/ -_)  \n");
    printf("|___||_||_| \\__| \\___||_||_| \\__,_|  |_|\\___|  \n");
}

int main() {
    start();
    srand(time(NULL)); //Permet de générer à chaque éxecution une nouvelle forêt aléatoire
    ouvertureFenetre(800,600,"toto");
    //menu();
    return 0;
}
