#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

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
    float m_central_norm;
    std::vector<Arete*> m_liaison;

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
        return m_liaison.size();
    }

    /// Setter

    void set_central(float central)
    {
        m_central=central;
    }

    void set_central_norm(float central)
    {
        m_central_norm=central;
    }

    void ajouter_liaison(Arete* arc);


    /// Methodes

    void afficher_console() const;
    void afficher_Svgfile(Svgfile &svgout, float indice);
};

#endif // SOMMET_H_INCLUDED
