#include <iostream>
#include "svgfile.h"
#include <string>

#include "sommet.h"
#include "arete.h"
#include "graphe.h"

int main()
{
    Graphe nouv;

    Svgfile svgout;
    //nouv.afficher_console();

    nouv.chargerPond();

    //nouv.afficher_console();

    nouv.centralite_proximite();


    nouv.afficher_console();

    nouv.afficher_Svgfile(svgout);


    return 0;
}
