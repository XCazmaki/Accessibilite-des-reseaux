#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include "sommet.h"

class Arete
{
private:
    int m_indice;                       /// Indice de l'arête
    std::pair<Sommet*,Sommet*> m_arc;   /// Pair de pointeurs vers les deux sommets de l'arête
    float m_poids;                       /// Poid (éventuel) de l'arête (vaut 1 par default - en
                                        /// cas de graphe non orienté

public:

    /// Constructeurs

    Arete();
    Arete(int indice, Sommet* dep, Sommet* arr, float poid);

    /// Destructeur

    ~Arete();

    /// Getter

    float getPoids()
    {
        return m_poids;
    }

    Sommet* getSommet(const Sommet* depart)
    {
        std::cout<<"\t\t\t2.1.1.1"<<std::endl;
        if(m_arc.first == depart)
            return m_arc.second;
        else
            return m_arc.first;
        std::cout<<"\t\t\t2.1.1.2"<<std::endl;
    }

    ///methodes

    bool changerPond(const std::pair<int, float>&);
    void afficher() const;
    void afficher_console() const;
    void afficher_Svgfile(Svgfile &svgout,float indice);

};

#endif // ARETE_H_INCLUDED
