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
