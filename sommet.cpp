#include "sommet.h"

Sommet::Sommet()
{
    m_indice=-1;
    m_nom="";
    m_coordx=0;
    m_coordy=0;
    m_central=0;
    m_central_norm=0;
}

Sommet::Sommet(int indice, std::string nom, int coordx, int coordy)
{
    m_indice=indice;
    m_nom=nom;
    m_coordx=coordx;
    m_coordy=coordy;
    m_central=0;
    m_central_norm=0;
}

Sommet::~Sommet()
{}


void Sommet::ajouter_liaison(Arete* arc)
{
    m_liaison.push_back(arc);
}

void Sommet::afficher_console() const
{
    std::cout << "Sommet numero : " << m_indice << " de nom " << m_nom << "" << m_coordx<< m_coordy << std::endl;
}

void Sommet::afficher_Svgfile(Svgfile &svgout)
{
    svgout.addDisk(m_coordx*100,m_coordy*100,10,"red");
}
