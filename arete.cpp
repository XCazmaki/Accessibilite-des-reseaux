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

void Arete::afficher_Svgfile(Svgfile &svgout,float indice)
{
    svgout.addLine(m_arc.first->get_coordx()*indice,m_arc.first->get_coordy()*indice,m_arc.second->get_coordx()*indice,m_arc.second->get_coordy()*indice,"black");
}

void Sommet::getAdjacence(std::vector< std::pair<Sommet*, float>>& adjacents)
{
    std::cout<< "\t\t2.1"<<std::endl;
    for(auto a : m_liaison)
    {
        std::cout<<"\t\t2.1.1"<<std::endl;
        Sommet* temp;// = a->getSommet(this);
        std::cout<<"\t\t2.1.2"<<std::endl;
        float poids = a->getPoids();
        std::cout<<"\t\t2.1.3"<<std::endl;
        adjacents.push_back(std::make_pair(temp, poids));
        std::cout<<"\t\t2.1.4"<<std::endl;
    }
    std::cout<<"\t\t2.2"<<std::endl;
}
