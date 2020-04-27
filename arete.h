#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include "sommet.h"

class Arete
{
private:
    int m_indice;       /// Indice de l'arête
    Sommet* m_dep;      /// Sommet de départ
    Sommet* m_arr;      /// Sommet d'arrivée
    int m_poid;         /// Poid (éventuel) de l'arête

public:

    /// Constructeurs

    Arete();

    Arete(int indice, Sommet* dep, Sommet* arr, int poid);

    /// Destructeur

    ~Arete();

};

#endif // ARETE_H_INCLUDED
