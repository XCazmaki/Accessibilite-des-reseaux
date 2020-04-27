#include "arete.h"

Arete::Arete()
{
    m_indice=-1;
    m_arc.first=nullptr;
    m_arc.second=nullptr;
    m_poids=0;
}


Arete::Arete(int indice, Sommet* dep, Sommet* arr, float poids)
{
    m_indice=indice;
    m_arc.first=dep;
    m_arc.second=arr;
    m_poids=poids;
}

Arete::~Arete()
{}


bool Arete::changerPond(const std::pair<int, float>& values)
{
    if(m_indice == values.first)
    {
        m_poids = values.second;
        return true;
    }
    else
        return false;
}

void Arete::afficher_console() const
{
    std::cout << "Arete numero : " << m_indice << " de poid " << m_poids << " reliant " << m_arc.first->get_nom();
    std::cout << m_arc.second->get_nom() << std::endl;
}

void Arete::afficher_Svgfile(Svgfile &svgout)
{
    svgout.addLine(m_arc.first->get_coordx()*100,m_arc.first->get_coordy()*100,m_arc.second->get_coordx()*100,m_arc.second->get_coordy()*100,"black");
}

void Sommet::getAdjacence(std::vector< std::pair<Sommet*, float>>& adjacents)
{
    for(auto a : m_liaison)
    {
        Sommet* temp = a->getSommet(this);
        float poids = a->getPoids();
        adjacents.push_back(std::make_pair(temp, poids));
    }
}
