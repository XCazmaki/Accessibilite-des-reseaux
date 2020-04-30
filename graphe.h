#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>

#include "sommet.h"
#include "arete.h"
#include <math.h>

class Graphe
{
private:
    std::vector<Sommet*> m_sommets;
    std::vector<Arete*> m_aretes;
    std::vector<Arete*> m_aretes_originales;
    std::vector<float> m_degres_svg;
    int m_orientation;

public:

    /// Constructeurs

    Graphe();


    /// Destructeur

    ~Graphe();


    /// Mise en place du graphe

    struct IntComparator{
        bool operator()(int a, int b)
        {
            if(a < b)
                return true;
            else
                return false;
        }
    };

    struct SommetComparatorIndice{
        bool operator()(Sommet* a, Sommet* b)
        {
            if(a->get_indice() < b->get_indice())
                return true;
            else
                return false;
        }
    };

    struct AreteComparatorIndice{
        bool operator()(Arete* a, Arete* b)
        {
            if(a->get_indice() < b->get_indice())
                return true;
            else
                return false;
        }
    };


    void chargerPond();

    void afficher_console() const;
    void afficher_Svgfile(Svgfile &svgout);

    /// Indices de centralité

    void centralite_degre();

    void centralite_vecteur_propre();

    float calcul_indice();

    void centralite_proximite();
    void dijkstra(Sommet*);
    void rechercheAdj(Sommet*, std::vector<std::pair<Sommet*, float>>&);
    void reset();


    /// Sauvegarde

    void sauvegarde_fichier();


    /// Vulnérabilité

    void k_connexite();
    bool k_connexite_test(int&);
    void recursion(int*, int&, int, bool&);
    void parcours_DFSK(int, int*, std::vector<int>&, int&);
    bool testSel(int*, int&, Arete*);

    //void DFS(int &indice,int selection,std::vector<int> &couleurs);
    //void parcours_DFS1(int indice,int selection,std::vector<int> &couleurs);
    //void parcours_DFS2(int indice,int selection1,int selection2,std::vector<int> &couleurs);

    void sauvagarde_aretes();
    void restaurer_aretes();
    void supprimer_aretes(int indice);



    void centralite_intermediarite();
    std::list<int>* defListeAdj(std::list<std::pair<int, float>>*);
    void seekAllPaths(int, int, bool[], int[], int&, std::list<int>*, std::list<std::pair<int, float>>*, const float&, int&, std::vector<int>&, std::vector<Arete*>&);
    void calculCentraliteInterSommet(const int&, std::vector<int>&);
    void calculCentraliteInterArete(const int&, std::vector<Arete*>&);
    Arete* seekArete(int&, int&);
    void freeMem(bool*, int*, std::list<int>*, std::list<std::pair<int, float>>*);

};

#endif // GRAPHE_H_INCLUDED
