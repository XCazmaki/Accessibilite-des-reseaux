#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>

#include "sommet.h"
#include "arete.h"
#include <math.h>

class Graphe
{
private:
    std::vector<Sommet*> m_sommets;
    std::vector<Arete*> m_aretes;
    std::vector<Arete*> m_aretes_originales;
    std::vector<float> m_degres_svg;
    int m_orientation;

public:

    /// Constructeurs

    Graphe();


    /// Destructeur

    ~Graphe();

    /// Mise en place du graphe

    void chargerPond();

    void afficher_console() const;
    void afficher_Svgfile(Svgfile &svgout);

    /// Indices de centralité

    void centralite_degre();
    void centralite_vecteur_propre();

    float calcul_indice();

    void centralite_proximite();
    void rechercheAdj(Sommet*, std::vector<std::pair<Sommet*, float>>&);
    void reset();

    /// Vulnérabilité

    void k_connexite();
    void DFS(int &indice,int selection,std::vector<int> &couleurs);
    void parcours_DFS1(int indice,int selection,std::vector<int> &couleurs);
    void parcours_DFS2(int indice,int selection1,int selection2,std::vector<int> &couleurs);

    void sauvagarde_aretes();
    void restaurer_aretes();
    void supprimer_aretes(int indice);

};

#endif // GRAPHE_H_INCLUDED
