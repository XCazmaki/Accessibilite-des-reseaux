#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

#include <queue>
#include <stack>
#include <list>

#include <algorithm>

#include "svgfile.h"

class Arete;

class Sommet
{
private:
    int m_indice;           /// Indice du sommet
    std::string m_nom;      /// Nom du sommet
    int m_coordx;           /// Coordonnée en X du sommet
    int m_coordy;           /// Coordonnée en Y du sommet
    float m_central;        /// Indice de centralité
    float m_central_norm;   /// Indice de centralité normalisé

    /// Vecteur qui va contenir l'ensemble des indice de centralité de chaque sommet
    /// par exemple vector[0].second correspond à l'indice de centralité de degre normalisé
    std::vector<std::pair<float,float>> m_indices_centralite;

    float m_distance;
    char m_etat;

    float m_degre;

public:

    /// Constructeurs

    Sommet();
    Sommet(int indice, std::string nom, int coordx, int coordy);

    /// Destructeur

    ~Sommet();

    /// Getters

    int get_indice() const
    {
        return m_indice;
    }

    std::string get_nom() const
    {
        return m_nom;
    }

    int get_coordx() const
    {
        return m_coordx;
    }

    int get_coordy() const
    {
        return m_coordy;
    }

    float get_degre() const
    {
        return m_degre;
    }

    float getDist() const
    {
        return m_distance;
    }
    float get_central() const
    {
        return m_central;
    }

    float get_central_norm() const
    {
        return m_central_norm;
    }

    std::vector<std::pair<float,float>> get_indice_central()
    {
        return m_indices_centralite;
    }

    /// Setter

    void set_degre(float x)
    {
        m_degre=x;
    }

    void set_central(const float& central)
    {
        m_central=central;
    }

    void set_central_norm(const float& central_norm)
    {
        m_central_norm = central_norm;
    }

    void setDist(int d)
    {
        m_distance = d;
    }

    void setEtat(char e)
    {
        m_etat = e;
    }

    void set_indice_central(float num,float val1,float val2)
    {
        m_indices_centralite[num].first=val1;
        m_indices_centralite[num].second=val2;
    }

    /// comparator

    struct SommetComparator
    {
        bool operator()(Sommet* a, Sommet* b)
        {
            if(a->m_distance < b->m_distance)
                return true;
            else
                return false;
        }
    };


    /// Methodes
    void augmenter_degre();

    void traitementDij(std::queue<Sommet*>&, std::vector<std::pair<Sommet*, float>>&);

    void DefcentralInterSommet(const int&, const int& occurence);
    void DefcentralInterNorm(const int&);
    void afficher_console() const;
    void afficher_Svgfile(Svgfile &svgout, float indice);
};

#endif // SOMMET_H_INCLUDED
