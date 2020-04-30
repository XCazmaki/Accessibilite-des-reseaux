#include "arete.h"

Arete::Arete()
{
    m_indice=-1;
    m_arc.first=nullptr;
    m_arc.second=nullptr;
    m_poids=0;
    m_centralA = 0;
    m_central_normA = 0;
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

void Arete::afficher_Svgfile(Svgfile &svgout,float indice)
{
    svgout.addLine(m_arc.first->get_coordx()*indice,m_arc.first->get_coordy()*indice,m_arc.second->get_coordx()*indice,m_arc.second->get_coordy()*indice,"black");

    float x=0;
    float y=0;

    x=(m_arc.first->get_coordx()+m_arc.second->get_coordx())/2;
    y=(m_arc.first->get_coordy()+m_arc.second->get_coordy())/2;

    svgout.addText(x*indice-25, y*indice-10, "N" ,"black");
    svgout.addText(x*indice-10, y*indice-10, m_indice,"black");
    svgout.addText(x*indice+10, y*indice-10, m_poids,"black");

}

bool Arete::testAppartenance(const Sommet* depart, const int& orient)
{
    if((orient == 0)&&((depart == m_arc.first)||(depart == m_arc.second)))
        return true;
    else if((orient == 1)&&(depart == m_arc.first))
        return true;
    else
        return false;
}

void Arete::DefcentralInterArete(const int& nCC, const int& occurence)
{
    m_centralA += (occurence / nCC);
}

void Arete::DefcentralInterNormA(const int& n)
{
    m_central_normA = (m_centralA / ((n*n)-(3*n)+2));
}
