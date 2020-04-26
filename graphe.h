#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <iostream>
#include <vector>

#include "sommet.h"
#include "arete.h"

class Graphe
{
private:
    int ordre;
    int taille;
    std::vector<Sommet*> m_sommet;
    std::vector<Arete*> m_arete;

public:

    /// Constructeurs

    Graphe();

    /// Destructeur

    ~Graphe();

};

#endif // GRAPHE_H_INCLUDED
