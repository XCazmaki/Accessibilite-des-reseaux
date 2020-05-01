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
    m_centralA = 0;
    m_central_normA = 0;
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
void Arete::afficher_Svgfile(Svgfile &svgout,float indice, const int& orient)
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
    if(orient == 1)
        dessinerTriangle(m_arc.first->get_coordx()*indice,m_arc.first->get_coordy()*indice,m_arc.second->get_coordx()*indice,m_arc.second->get_coordy()*indice,couleur, svgout);

    svgout.addText(x*indice-25, y*indice-10, "N" ,"black");
    svgout.addText(x*indice-10, y*indice-10, m_indice,"black");
    //svgout.addText(x*indice+25, y*indice-10, m_central_normA,"black");
    svgout.addText(x*indice+10, y*indice-10, m_poids,"black");

}

void Arete::dessinerTriangle(const float& x1, const float& y1, const float& x2, const float& y2, const std::string& couleur, Svgfile& svgout)
{
    float m, h;
    float solx, soly;

    float pm, ph;
    float a2, b2,c2;
    float R=4;

    float x1F, y1F, x2F, y2F;

    if(x1 != x2)
    {
        if(y1 > y2)
        {
            m = ((y1 - y2)/(x1 - x2));
            h = (y1 - (m * x1));
        }
        else if(y1 < y2)
        {
            m = ((y2 - y1)/(x2 - x1));
            h = (y1 - (m * x1));
        }
        else if(y1 == y2)
        {
            m=0;
            h=y1;
        }
    }

    std::pair<float, float> sol1 = defsol(x1, y1, x2, y2, 5.0, m, h);
    std::pair<float, float> sol2 = defsol(x1, y1, x2, y2, 10.0, m, h);

    solx = sol2.first;
    soly = sol2.second;

    if(y1==y2)
    {
            a2=1;
            b2 = ((-2)* soly);
            c2 = (soly * soly) - (R*R);
            x1F = solx;
            x2F = solx;
            y1F = ((-b2 - sqrt((b2 * b2) - 4*a2*c2)) / (2*a2));
            y2F = ((-b2 + sqrt((b2 * b2) - 4*a2*c2)) / (2*a2));
    }
    else
    {
        if(x1 != x2)
        {
            pm = (-(1/m));
            ph = (soly - (pm * solx));
        }
        else
        {
            pm= 0;
            ph = soly;
        }

        a2 = (1 + (pm*pm));
        b2 = ((-2)*solx + 2*pm*(ph- soly));
        c2 = ((solx * solx) + ((ph - soly)*(ph - soly)) - (R*R));

        x1F= ((-b2 - sqrt((b2 * b2) - 4*a2*c2)) / (2*a2));
        x2F= ((-b2 + sqrt((b2 * b2) - 4*a2*c2)) / (2*a2));
        y1F = ((pm * x1F) + ph);
        y2F = ((pm * x2F) + ph);
    }

    svgout.addTriangle(sol1.first, sol1.second, x1F, y1F, x2F, y2F, couleur);
}

std::pair<float, float> Arete::defsol(const float& x1, const float& y1, const float& x2, const float& y2, const float& r, const float& m, const float& h)
{
    float a, b, c;
    float solx, soly;

    float ix1;
    float ix2;
    float iy1;
    float iy2;

    if(x1 != x2)
    {
        a = (1 + (m*m));
        b = ((-2)*x2 + 2*m*(h- y2));
        c = ((x2 * x2) + ((h - y2)*(h - y2)) - (r*r));

        std::cout<<a<< " "<< b<< " "<< c <<std::endl;


         ix1= ((-b - std::sqrt((b * b) - 4*a*c)) / (2*a));
         ix2= ((-b + std::sqrt((b * b) - 4*a*c)) / (2*a));
         iy1 = ((m * ix1) + h);
         iy2 = ((m * ix2) + h);
    }
    else
    {
        a=1;
        b = ((-2)* y2);
        c = (y2 * y2) - (r*r);
        ix1 = x2;
        ix2 = x2;
        iy1 = ((-b - sqrt((b * b) - 4*a*c)) / (2*a));
        iy2 = ((-b + sqrt((b * b) - 4*a*c)) / (2*a));
    }

    if(x1 < x2)
    {
        if(ix1 < x2)
        {
            solx = ix1;
            soly = iy1;
        }
        else
        {
            solx = ix2;
            soly = iy2;
        }
    }
    else if(x1>=x2)
    {
        if(ix1 > x2)
        {
            solx = ix1;
            soly = iy1;
        }
        else if(ix1<x2)
        {
            solx = ix2;
            soly = iy2;
        }
        else
        {
            if(y1 > y2)
            {
                if(iy1 > y2)
                {
                    solx = ix1;
                    soly = iy1;
                }
                else
                {
                    solx = ix2;
                    soly = iy2;
                }
            }
            else
            {
                if(iy1 < y2)
                {
                    solx = ix1;
                    soly = iy1;
                }
                else
                {
                    solx = ix2;
                    soly = iy2;
                }
            }
        }
    }
    return std::make_pair((float)solx, (float)soly);
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
    if(nCC > 0)
        m_centralA += (occurence / nCC);
}

void Arete::DefcentralInterNormA(const int& n)
{
    m_central_normA = (m_centralA / ((n*n)-(3*n)+2));
}
