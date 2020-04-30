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
    float m_centralA;                         /// Indice de centralité
    float m_central_normA;                   /// cas de graphe non orienté

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

    /// Getters

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

    std::pair<Sommet*, Sommet*> getPair()
    {
        return m_arc;
    }

    Sommet* get_arc1()
    {
        return  m_arc.first;
    }

    Sommet* get_arc2()
    {
        return  m_arc.second;
    }

    /// Setter
    void set_indiceA(const int& i)
    {
        m_indice = i;
    }

    void set_indice(float nbr)
    {
        m_indice=nbr;
    }

    void set_arc1(Sommet* nouv)
    {
        m_arc.first=nouv;
    }

    void set_arc2(Sommet* nouv)
    {
        m_arc.second=nouv;
    }

    void set_centralA(const float& central)
    {
        m_centralA=central;
    }

    void set_central_normA(const float& central_norm)
    {
        m_central_normA = central_norm;
    }
    /// Methodes

    bool changerPond(const std::pair<int, float>&);
    //void afficher() const;
    void afficher_console() const;
    void afficher_Svgfile(Svgfile &svgout,float indice,const int&);
    void dessinerTriangle(const float&, const float&, const float&, const float&, const std::string&, Svgfile&);
    std::pair<float, float> defsol(const float&, const float&, const float&, const float&, const float&, const float&, const float&);

    bool testAppartenance(const Sommet*, const int&);

    void DefcentralInterArete(const int&, const int&);
    void DefcentralInterNormA(const int&);

};

#endif // ARETE_H_INCLUDED
