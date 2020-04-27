#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include "sommet.h"

class Arete
{
private:
    int m_indice;       /// Indice de l'ar�te
    Sommet* m_dep;      /// Sommet de d�part
    Sommet* m_arr;      /// Sommet d'arriv�e
    int m_poid;         /// Poid (�ventuel) de l'ar�te

public:

    /// Constructeurs

    Arete();

    Arete(int indice, Sommet* dep, Sommet* arr, int poid);

    /// Destructeur

    ~Arete();

};

#endif // ARETE_H_INCLUDED
