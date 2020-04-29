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
        nouv.sauvagarde_aretes();
    }
    int choix=0;
    do
    {

        std::cout << "Que voulez vous faire ?" << std::endl;
        std::cout << "1: Charger un fichier de ponderation" << std::endl;
        std::cout << "2: Afficher l'indice de centralite de degre" << std::endl;
        std::cout << "3: Afficher l'indice de centralite de vecteur propre" << std::endl;
        std::cout << "4: Afficher l'indice de centralite de proximite" << std::endl;
        std::cout << "5: Afficher l'indice de centralite de d'intermediarite" << std::endl;
        std::cout << "6: Teste la k-connexite du graphe" << std::endl;
        std::cout << "7: Supprimer une arete du graphe" << std::endl;
        std::cout << "8: Restituer l'etat initial du graphe" << std::endl;
        std::cout << "10: Lancer l'affichage en console" << std::endl;
        std::cout << "11: Sauvegarder dans un fichier" << std::endl;
        std::cout << "0: Quitter" << std::endl;
        std::cout<< "Choix : ";
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
            nouv.afficher_Svgfile(svgout);
            break;
        }
        break;
        case 6 :
        {
            Svgfile svgout;
            nouv.k_connexite();
            nouv.afficher_Svgfile(svgout);
        }
        break;
        case 7 :
        {
            Svgfile svgout;
            std::cout << "Quelle arete voulez-vous supprimer ? " << std::endl;
            std::cin >> choix;
            nouv.supprimer_aretes(choix);
            nouv.afficher_Svgfile(svgout);
        }
        break;
        case 8 :
        {
            Svgfile svgout;
            nouv.restaurer_aretes();
            nouv.afficher_Svgfile(svgout);
        }
        break;
        case 10 :
        {
            Svgfile svgout;
            nouv.afficher_console();
            nouv.afficher_Svgfile(svgout);
        }
        break;
        case 11 :
        {
            Svgfile svgout;
            nouv.sauvegarde_fichier();
            nouv.afficher_Svgfile(svgout);
        }
        break;

        default:
            std::cout << "Veuillez rentrer une reponse valide" << std::endl;
            break;
        }
        system("pause");
        system("cls");
    }
    while (choix!=0);

}


int main()
{
    menu();

    return 0;
}
