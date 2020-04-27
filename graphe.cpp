#include "graphe.h"

Graphe::Graphe()
{
    /// On ouvre un fichier:
    std::string nom_fichier="";
    std::cout << "Entrez le nom du fichier de topologie : ";
    std::cin >> nom_fichier;
    std::ifstream monFlux(nom_fichier);

    /// On teste si le fichier s'est bien ouvert:
    if(!monFlux)
        std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;

    /// On reccupère l'orientation
    int orient=0;
    /// 0=non orienté
    monFlux >> orient;

    /// On reccupère l'ordre
    int ordre=0;
    monFlux >> ordre;

    /// On crée le bon nombre de sommet
    int indice=-1;
    std::string nom="";
    int coordx=0;
    int coordy=0;

    for(int i=0;i<ordre;++i)
    {
        monFlux >> indice >> nom >> coordx >> coordy;
        m_sommets.push_back(new Sommet(indice,nom,coordx,coordy));
    }

    /// On reccupère la taille
    int taille=0;
    monFlux >> taille;

    /// On crée le bon nombre d'Arête
    int num1=0;
    int num2=0;

    for(int i=0;i<taille;++i)
    {
        monFlux >> indice >> num1 >> num2;
        /// On crée la nouvelle arête
        m_aretes.push_back(new Arete(indice,m_sommets[num1],m_sommets[num2],1));
        /// On relie les sommets à l'arête
        m_sommets[num1]->ajouter_liaison(m_aretes[m_aretes.size()]);
        if(orient==0)
        {
            m_sommets[num2]->ajouter_liaison(m_aretes[m_aretes.size()]);
        }
    }
}

Graphe::~Graphe()
{
    for(auto i: m_sommets)
    {
        delete i;
    }
    for(auto i: m_aretes)
    {
        delete i;
    }
}


void Graphe::afficher_console() const
{
    for(auto i: m_sommets)
    {
        i->afficher_console();
    }

    for(auto i: m_aretes)
    {
        i->afficher_console();
    }

}

void Graphe::afficher_Svgfile(Svgfile &svgout)
{
    for(auto i: m_aretes)
    {
        i->afficher_Svgfile(svgout);
    }
    for(auto i: m_sommets)
    {
        i->afficher_Svgfile(svgout);
    }

}
