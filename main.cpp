#include <iostream>
#include "svgfile.h"
#include <string>

#include "sommet.h"
#include "arete.h"
#include "graphe.h"

int main()
{
    std::string choixpond;
    Graphe nouv;

    Svgfile svgout;

    nouv.afficher_console();
    nouv.afficher_Svgfile(svgout);

    std::cout << "Nom du fichier de ponderation : ";
    std::cin>> choixpond;
    std::cout<<std::endl;
    nouv.chargerPond(choixpond);
    nouv.Afficher();

    return 0;
}
