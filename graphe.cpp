#include "graphe.h"

Graphe::Graphe()
{

}

Graphe::~Graphe()
{
    for(auto i: m_sommet)
    {
        delete i;
    }
    for(auto i: m_arete)
    {
        delete i;
    }
}

void Graphe::chargerPond(const std::string& nomfic)
{
    std::ifstream ifs{nomfic};

    if(!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomfic );

    ifs.ignore();

    for(auto a: m_arete)
    {
        a->changerPond(ifs);
    }

}
