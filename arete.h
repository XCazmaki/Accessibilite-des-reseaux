#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include "sommet.h"

class Sommet;

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

    int get_indice()
    {
        return m_indice;
    }

    /// Destructeur

    ~Arete();

    /// Getter

    float getPoids()
    {
        return m_poids;
    }

    Sommet* getSommet(const Sommet* depart)
    {
        if(m_arc.first == depart)
            return m_arc.second;
        else
            return m_arc.first;
    }

    ///methodes
    /// Getters

    Sommet* get_arc1()
    {
        return  m_arc.first;
    }

    Sommet* get_arc2()
    {
        return  m_arc.second;
    }

    /// Setter

    void set_arc1(Sommet* nouv)
    {
        m_arc.first=nouv;
    }

    void set_arc2(Sommet* nouv)
    {
        m_arc.second=nouv;
    }


    bool changerPond(const std::pair<int, float>&);
    void afficher() const;
    void afficher_console() const;
    void afficher_Svgfile(Svgfile &svgout,float indice);

    bool testAppartenance(const Sommet*, const int&);
};

#endif // ARETE_H_INCLUDED
