#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include <iostream>

class Arete;

class Sommet
{
private:
    int m_indice;       /// Indice du sommet
    std::string m_nom;  /// Nom du sommet
    int m_coordx;       /// Coordonn�e en X du sommet
    int m_coordy;       /// Coordonn�e en Y du sommet
    int m_central;      /// Indice de centralit�
public:

    /// Constructeurs

    Sommet();

    Sommet(int indice, std::string nom, int coordx, int coordy);

    /// Destructeur

    ~Sommet();

    /// Getters

    int get_indice()
    {
        return m_indice;
    }

    std::string get_nom()
    {
        return m_nom;
    }

    int get_coordx()
    {
        return m_coordx;
    }

    int get_coordy()
    {
        return m_coordy;
    }


};

#endif // SOMMET_H_INCLUDED
