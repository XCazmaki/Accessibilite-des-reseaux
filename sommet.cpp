#include "sommet.h"

Sommet::Sommet()
{
    m_indice=-1;
    m_nom="";
    m_coordx=0;
    m_coordy=0;
    m_central=0;
    m_central_norm=0;
    m_distance = 0;
    m_etat = 'B';
}

Sommet::Sommet(int indice, std::string nom, int coordx, int coordy)
{
    m_indice=indice;
    m_nom=nom;
    m_coordx=coordx;
    m_coordy=coordy;
    m_central=0;
    m_central_norm=0;
    m_distance = 0;
    m_etat = 'B';
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
}

void Sommet::afficher_Svgfile(Svgfile &svgout)
{
    svgout.addDisk(m_coordx*100,m_coordy*100,10,"red");
}



void Sommet::traitementDij(std::queue<Sommet*>& F, std::vector<std::pair<Sommet*, float>>& adjacents)
{
    (F.front())->setEtat('N'); /// le plus court chemin pour ce sommet a ete trouve, on le marque
    F.pop(); /// on defile la pile

    for(auto a : adjacents)
    {
        if((a.first)->m_etat == 'B')///si le sommet adjacent n a pas ete exploré
        {
            F.push(a.first);/// on l'ajoute a la file
            (a.first)->m_etat = 'G'; /// on dit que ce sommet est dans la file , il est explore
            (a.first)->m_distance = m_distance + a.second; /// on definit sa distance par rapport a celui du predecesseur et sa distance par rapport a celui ci
        }
        else if(((a.first)->m_etat == 'G')&&(m_distance + a.second < (a.first)->m_distance))/// si le sommet a deja ete explore et qu'on lui attribut une distance plus petite que celle actuelle
        {
            (a.first)->m_distance = m_distance + a.second; /// on definit alors cette nouvelle distance
        }
    }

    std::vector<Sommet*> temp;
    while(F.size()>0)
    {
        temp.push_back(F.front()); /// on vide la pile dans un tableau
        F.pop();
    }
    std::sort(temp.begin(), temp.end(), SommetComparator());/// on tri le tableau par ordre croissant de la distance du sommet
    for(auto s : temp)
        F.push(s); /// on remplit a nouveau la file de telle sorte que le sommet avec la plus petite distance soit en front
}
