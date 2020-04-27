#include "arete.h"

Arete::Arete()
{
    m_indice=-1;
    m_arc.first=nullptr;
    m_arc.second=nullptr;
    m_poid=0;
}


Arete::Arete(int indice, Sommet* dep, Sommet* arr, int poid)
{
    m_indice=indice;
    m_arc.first=dep;
    m_arc.second=arr;
    m_poid=poid;
}

Arete::~Arete()
{}


void Arete::changerPond(const std::istream& is)
{
    std::string ligne;
    std::getline(is, ligne);
    std::istringstream iss(ligne);
    int tempIndice;
    float tempPond;

    iss >> tempIndice >> tempPond;

    if(m_indice == tempIndice)
        m_poid = tempPond;
}
