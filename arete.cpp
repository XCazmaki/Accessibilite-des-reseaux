#include "arete.h"

Arete::Arete()
{
    m_indice=-1;
    m_arc.first=nullptr;
    m_arc.second=nullptr;
    m_poids=0;
    m_centralA = 0;
    m_central_normA = 0;
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
    //svgout.addText((m_arc.second->get_coordx()*indice)-(m_arc.first->get_coordx()*indice),(m_arc.second->get_coordy()*indice)-(m_arc.second->get_coordy()*indice), m_poids,"black");
    /*int x1 = m_arc.first->get_coordx();
    int y1 = m_arc.first->get_coordy();
    int x2 = m_arc.second->get_coordx();
    int y2 = m_arc.second->get_coordy();


    float m, h;
    float a, b, c;

    float solx, soly;
    float r = 5;

    float pm, ph;
    float a2, b2,c2;
    float R=4;

    float x1F, y1F, x2F, y2F;

    int orient = 1;
    if(orient == 1)
    {
        if(y1 > y2)
            m = ((x1 - x2)/(y1 - y2));
        else
            m = ((x2 - x1)/(y2 - y1));

        h = (y1 - (m * x1));
        a = (1 + (m*m));
        b = ((-2)*x2 + 2*m*(h- y2));
        c = ((x2 * x2) + ((h - y2)*(h - y2)) - (r*r));

        float ix1= ((-b - sqrt((b * b) - 4*a*c)) / (2*a));
        float ix2= ((b - sqrt((b * b) - 4*a*c)) / (2*a));
        float iy1 = ((m * ix1) + h);
        float iy2 = ((m * ix2) + h);

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

        pm = (-(1/m));
        ph = (y2 - (pm * x2));

        a2 = (1 + (pm*pm));
        b2 = ((-2)*solx + 2*pm*(ph- soly));
        c2 = ((solx * solx) + ((ph - soly)*(ph - soly)) - (R*R));

        x1F= ((-b2 - sqrt((b2 * b2) - 4*a2*c2)) / (2*a2));
        x2F= ((b2 - sqrt((b2 * b2) - 4*a2*c2)) / (2*a2));
        y1F = ((pm * x1F) + ph);
        y2F = ((pm * x2F) + ph);

        svgout.addTriangle(x2, y2, x2F, y2F, x1F, y1F,"black");
        std::cout<<"mmmmmm"<<std::endl;
    }*/
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
