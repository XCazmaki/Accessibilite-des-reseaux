#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>

#include "sommet.h"
#include "arete.h"

class Graphe
{
private:
    std::vector<Sommet*> m_sommets;
    std::vector<Arete*> m_aretes;

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
    void reset();
};

#endif // GRAPHE_H_INCLUDED
