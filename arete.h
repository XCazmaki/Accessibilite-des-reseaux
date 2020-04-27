#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include "sommet.h"

class Arete
{
private:
    int m_indice;                       /// Indice de l'arête
    std::pair<Sommet*,Sommet*> m_arc;   /// Pair de pointeurs vers les deux sommets de l'arête
    float m_poid;                         /// Poid (éventuel) de l'arête (vaut 1 par default - en
                                        /// cas de graphe non orienté

public:

    /// Constructeurs

    Arete();
    Arete(int indice, Sommet* dep, Sommet* arr, float poid);

    /// Destructeur

    ~Arete();

    void afficher() const;

};

#endif // ARETE_H_INCLUDED
