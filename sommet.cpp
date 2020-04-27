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
    std::cout << "Son indice est : " << m_central_norm << std::endl;
}

void Sommet::afficher_Svgfile(Svgfile &svgout, float indice)
{
    std::string couleur="black";
    if(m_central_norm>0.80)
    {
        couleur="red";
    }
    else if(m_central_norm>0.60)
    {
        couleur="orange";
    }
    else if(m_central_norm>0.40)
    {
        couleur="yellow";
    }
    else if(m_central_norm>0.20)
    {
        couleur="blue";
    }
    else if(m_central_norm<=0.20)
    {
        couleur="purple";
    }

    svgout.addDisk(m_coordx*indice,m_coordy*indice,5,couleur);
    svgout.addText(m_coordx*indice,m_coordy*indice-10,m_nom,"black");
    svgout.addText(m_coordx*indice,m_coordy*indice+10,m_central_norm,"black");
}
