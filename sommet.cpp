#include "sommet.h"

Sommet::Sommet()
{
    m_indice=-1;
    m_nom="";
    m_coordx=0;
    m_coordy=0;
}

Sommet::Sommet(int indice, std::string nom, int coordx, int coordy)
{
    m_indice=indice;
    m_nom=nom;
    m_coordx=coordx;
    m_coordy=coordy;
}

Sommet::~Sommet()
{}
