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
    float m_coordx;           /// Coordonnée en X du sommet
    float m_coordy;           /// Coordonnée en Y du sommet
    float m_central;        /// Indice de centralité
    float m_central_norm;   /// Indice de centralité normalisé

    /// Vecteur qui va contenir l'ensemble des indice de centralité de chaque sommet
    /// par exemple vector[0].second correspond à l'indice de centralité de degre normalisé
    std::vector<std::pair<float,float>> m_indices_centralite;

    /// Varibales utilisés pour différents Algo de parcours
    float m_distance;
    char m_etat;

    /// Stocke le degré du sommet
    float m_degre;

    /// Selection si on doit afficher le sommet ou pas
    bool m_afficher;

public:

    /// Constructeurs

    Sommet();
    Sommet(int indice, std::string nom, float coordx, float coordy);

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

    float get_coordx() const
    {
        return m_coordx;
    }

    float get_coordy() const
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

    bool get_afficher()
    {
        return m_afficher;
    }

    /// Setter

    void set_indice(int x)
    {
        m_indice=x;
    }

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

<<<<<<< HEAD
    void set_afficher(bool x)
    {
        m_afficher=x;
    }

=======
    void set_indiceS(const int& i)
    {
        m_indice = i;
    }
>>>>>>> Romain
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

    /// Methodes d'affichage
    void afficher_console() const;
    void afficher_Svgfile(Svgfile &svgout, float indice);
};

#endif // SOMMET_H_INCLUDED
