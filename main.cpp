#include <iostream>
#include "svgfile.h"
#include <string>

#include "sommet.h"
#include "arete.h"
#include "graphe.h"

int main()
{

    Graphe nouv;
    nouv.Afficher();
    nouv.chargerPond("graphe_pond.txt");
    nouv.Afficher();

    std::cout << "Hello world!" << std::endl;
    return 0;
}
