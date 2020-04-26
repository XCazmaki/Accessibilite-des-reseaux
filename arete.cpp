#include "arete.h"

Arete::Arete()
{
    m_indice=-1;
    m_dep=nullptr;
    m_arr=nullptr;
    m_poid=0;
}


Arete::Arete(int indice, Sommet* dep, Sommet* arr, int poid)
{
    m_indice=indice;
    m_dep=dep;
    m_arr=arr;
    m_poid=poid;
}

