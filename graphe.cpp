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
    int tempTaille = 0;
    std::vector<float> tab;

    if(!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomfic );

    ifs >> tempTaille;
    ifs.ignore();

    for(int i = 0; i<tempTaille; ++i)
    {
        std::string ligne;
        std::getline(ifs, ligne);
        std::istringstream iss(ligne);
        int tempIndice;
        float tempPond;

        iss >> tempIndice >> tempPond;
        tab.push_back(tempPond);
    }

    for(auto a : m_arete)
    {
        a->changerPond(tab);
    }
}
