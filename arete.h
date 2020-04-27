#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include "sommet.h"

class Arete
{
private:
    int m_indice;                       /// Indice de l'ar�te
    std::pair<Sommet*,Sommet*> m_arc;   /// Pair de pointeurs vers les deux sommets de l'ar�te
    int m_poid;                         /// Poid (�ventuel) de l'ar�te (vaut 1 par default - en
                                        /// cas de graphe non orient�

public:

    /// Constructeurs

    Arete();

    Arete(int indice, Sommet* dep, Sommet* arr, int poid);

    /// Destructeur

    ~Arete();

};

#endif // ARETE_H_INCLUDED
