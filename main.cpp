#include <iostream>
#include "svgfile.h"
#include <string>

#include "sommet.h"
#include "arete.h"
#include "graphe.h"


void menu()
{
    Graphe nouv;
    {
        Svgfile svgout;
        nouv.afficher_Svgfile(svgout);
    }
    int choix=0;
    do
    {
        std::cout << "Que voulez vous faire ?" << std::endl;
        std::cout << "1: Charger un fichier de pondération" << std::endl;
        std::cout << "2: Afficher l'indice de centralite de degre" << std::endl;
        std::cout << "3: Afficher l'indice de centralite de vecteur propre" << std::endl;
        std::cout << "4: Afficher l'indice de centralite de proximité" << std::endl;
        std::cout << "5: Afficher l'indice de centralite de d'intermédiarité" << std::endl;
        std::cout << "0: Quitter" << std::endl;
        std::cin >> choix;

        switch (choix)
        {
        case 1 :
        {
            Svgfile svgout;
            nouv.chargerPond();
            nouv.afficher_Svgfile(svgout);
        }
        break;
        case 2 :
        {
            Svgfile svgout;
            nouv.centralite_degre();
            nouv.afficher_Svgfile(svgout);
        }
        break;
        case 3 :
        {
            Svgfile svgout;
            nouv.centralite_vecteur_propre();
            nouv.afficher_Svgfile(svgout);
        }
        break;
        case 4 :
        {
            Svgfile svgout;
            nouv.centralite_proximite();
            nouv.afficher_Svgfile(svgout);
        }
        break;
        case 5 :
        {
            Svgfile svgout;
            nouv.centralite_intermediarite();
            break;
        }
        default:
            std::cout << "Veuillez rentrer une reponse valide" << std::endl;
            break;
        }
        printf("\033c");
    }
    while (choix!=0);

}




int main()
{
    menu();
    return 0;
}
