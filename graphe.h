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
    int m_orientation;

public:

    /// Constructeurs

    Graphe();

    /// Destructeur

    ~Graphe();


    void chargerPond();

    void afficher_console() const;
    void afficher_Svgfile(Svgfile &svgout);

    void centralite_degre();
    void centralite_vecteur_propre();

    float calcul_indice();

    void centralite_proximite();
    void dijkstra(Sommet*);
    void rechercheAdj(Sommet*, std::vector<std::pair<Sommet*, float>>&);
    void reset();

    void centralite_intermediarite();
    std::list<int>* defListeAdj(std::list<float>*);
    void seekAllPaths(int, int, bool[], int[], int&, std::list<int>*);
    void freeMem(bool*, int*, std::list<int>*, std::list<float>*);
};

#endif // GRAPHE_H_INCLUDED
