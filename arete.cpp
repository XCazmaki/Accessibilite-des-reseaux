#include "arete.h"

Arete::Arete()
{
    m_indice=-1;
    m_arc.first=nullptr;
    m_arc.second=nullptr;
    m_poid=0;
}


Arete::Arete(int indice, Sommet* dep, Sommet* arr, float poid)
{
    m_indice=indice;
    m_arc.first=dep;
    m_arc.second=arr;
    m_poid=poid;
}

Arete::~Arete()
{}

void Arete::afficher() const
{
    std::cout << "Arete numero : " << m_indice << " de poid " << m_poid << " reliant " << m_arc.first->get_nom();
    std::cout << m_arc.second->get_nom() << std::endl;
}
