#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>
#include <list>

#include "sommet.h"
#include "arete.h"
#include <math.h>

class Graphe
{
private:
    std::vector<Sommet*> m_sommets;
    std::vector<Arete*> m_aretes;
    std::vector<std::vector<Arete*>> m_aretes_originales;
    std::vector<std::vector<float>> m_degres_svg;
    //std::vector<std::vector<Sommet>> m_sommets_originaux;
    //std::vector<std::vector<Sommet>> m_sommets_svg;
   // std::vector<std::vector<Sommet*>> m_sommets_originaux;
    std::vector<std::vector<bool>> m_sommet_affichage_svg;

    std::vector<std::vector<Sommet>> m_sommets_svg;
    std::vector<std::vector<Sommet*>> m_sommets_originaux;
    int m_orientation;

public:

    /// Constructeurs

    Graphe();


    /// Destructeur

    ~Graphe();

    int get_orientation()
    {
        return m_orientation;
    }

    /// Mise en place du graphe

    struct IntComparator{
        bool operator()(int a, int b)
        {
            if(a < b)
                return true;
            else
                return false;
        }
    };

    struct SommetComparatorIndice{
        bool operator()(Sommet* a, Sommet* b)
        {
            if(a->get_indice() < b->get_indice())
                return true;
            else
                return false;
        }
    };

    struct AreteComparatorIndice{
        bool operator()(Arete* a, Arete* b)
        {
            if(a->get_indice() < b->get_indice())
                return true;
            else
                return false;
        }
    };


    void chargerPond();

    void afficher_console() const;
    void afficher_Svgfile(Svgfile &svgout);
    void dispLegend(Svgfile& svgout, float, float);

    /// Indices de centralité

    void calcul_centralite();/// Appel les autres sous programmes

    void centralite_degre();

    void centralite_vecteur_propre();

    float calcul_indice();

    void centralite_proximite();
    void dijkstra(Sommet*);
    void rechercheAdj(Sommet*, std::vector<std::pair<Sommet*, float>>&);
    void reset();


    /// Sauvegarde

    void sauvegarde_fichier();



    /// Vulnérabilité

    void k_connexite();
    bool k_connexite_test(int&);
    void recursion(int*, int&, int, bool&);
    void parcours_DFSK(int, int*, std::vector<int>&, int&);
    bool testSel(int*, int&, Arete*);
    bool connexite();

    void forte_connexite();
    void parcours_DFSF(int indice, std::vector<int> &couleurs);
    void parcours_DFS(int indice, std::vector<int> &couleur);

    /// Suppression arete/sommet

    void sauvegarde_aretes();
    void restaurer_aretes();
    void supprimer_aretes(int indice);
    void reinitialiser_indice_aretes();

    void sauvegarde_sommets();
    void restaurer_sommets();
    void supprimer_sommets(int indice);

    void sauvegarde_sommets_indices();

    void reinitialiser_centralite();

    void comparer_indices();


    ///Centralité intermédiaire

    //void centralite_intermediarite();
    //std::list<int>* defListeAdj(std::list<std::pair<int, float>>*);
    //void seekAllPaths(int, int, bool[], int[], int&, std::list<int>*, std::list<std::pair<int, float>>*, const float&, int&, std::vector<int>&, std::vector<Arete*>&);
    //void calculCentraliteInterSommet(const int&, std::vector<int>&);
    //void calculCentraliteInterArete(const int&, std::vector<Arete*>&);
    //Arete* seekArete(int&, int&);
    //void freeMem(bool*, int*, std::list<int>*, std::list<std::pair<int, float>>*);

    ///centralite intermediarite 2
    void intermediarite();
    void intermediarite_parcour(std::vector<int> &marquage,
                                    std::vector<int> &preds,int num_sommet,
                                    int sfinal,int depart,std::vector<float> &poids,
                                    std::vector<std::pair<std::vector<int>,float>> &chemins);
    void affichage_parcours(std::vector<int> preds,
                                int num_sommet, int sfinal,std::vector<float> poids,
                                std::vector<std::pair<std::vector<int>,float>> &chemins);
};

#endif // GRAPHE_H_INCLUDED
