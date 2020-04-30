#include "arete.h"

/// Constructeur par défaut d'Arête
Arete::Arete()
{
    m_indice=-1;
    m_arc.first=nullptr;
    m_arc.second=nullptr;
    m_poids=0;
    m_centralA = 0;
    m_central_normA = 0;
}

/// Constructeur d'Arête avec paramètres
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

/// Affichache de l'Arête dans la console
/// Affiche le numéro de l'Arête, son poid et le numéro des 2 Sommets qu'elle relit
void Arete::afficher_console() const
{
    std::cout << std::endl << "Indices de l'Arete numero " << m_indice << std::endl;
    std::cout << "non nomralise : " << m_centralA << std::endl << "non normalise  : " << m_central_normA << std::endl;
    //std::cout << "Arete numero : " << m_indice << " de poid " << m_poids << " reliant " << m_arc.first->get_nom();
    //std::cout << m_arc.second->get_nom() << std::endl;
}

/// Affiche l'Arete dans Svgfile
/// Affiche l'Arete, son numéro et son poid
void Arete::afficher_Svgfile(Svgfile &svgout,float indice)
{
    float x=0;
    float y=0;

    x=(m_arc.first->get_coordx()+m_arc.second->get_coordx())/2;
    y=(m_arc.first->get_coordy()+m_arc.second->get_coordy())/2;


    std::string couleur="black";
    if(m_central_normA>0.080)
    {
        couleur="red";
    }
    else if(m_central_normA>0.060)
    {
        couleur="orange";
    }
    else if(m_central_normA>0.040)
    {
        couleur="yellow";
    }
    else if(m_central_normA>0.020)
    {
        couleur="blue";
    }
    else if(m_central_normA<=0.020)
    std::string couleur="black";

    if(m_central_normA>0.80)
    {
        couleur="red";
    }
    else if(m_central_normA>0.60)
    {
        couleur="orange";
    }
    else if(m_central_normA>0.40)
    {
        couleur="yellow";
    }
    else if(m_central_normA>0.20)
    {
        couleur="blue";
    }
    else if(m_central_normA<=0.20)
    {
        couleur="purple";
    }
    svgout.addLine(m_arc.first->get_coordx()*indice,m_arc.first->get_coordy()*indice,m_arc.second->get_coordx()*indice,m_arc.second->get_coordy()*indice,couleur);

    svgout.addText(x*indice-25, y*indice-10, "N" ,"black");
    svgout.addText(x*indice-10, y*indice-10, m_indice,"black");
    //svgout.addText(x*indice+25, y*indice-10, m_central_normA,"black");
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
