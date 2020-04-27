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

    /// On reccup�re l'orientation
    int orient=0;
    /// 0=non orient�
    monFlux >> orient;

    /// On reccup�re l'ordre
    int ordre=0;
    monFlux >> ordre;

    /// On cr�e le bon nombre de sommet
    int indice=-1;
    std::string nom="";
    int coordx=0;
    int coordy=0;

    for(int i=0;i<ordre;++i)
    {
        monFlux >> indice >> nom >> coordx >> coordy;
        m_sommets.push_back(new Sommet(indice,nom,coordx,coordy));
    }

    /// On reccup�re la taille
    int taille=0;
    monFlux >> taille;

    /// On cr�e le bon nombre d'Ar�te
    int num1=0;
    int num2=0;

    for(int i=0;i<taille;++i)
    {
        monFlux >> indice >> num1 >> num2;
        /// On cr�e la nouvelle ar�te
        m_aretes.push_back(new Arete(indice,m_sommets[num1],m_sommets[num2],1));
        /// On relie les sommets � l'ar�te
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


void Graphe::chargerPond(const std::string& nomfic)
{
    std::ifstream ifs{nomfic};
    int tempTaille = 0;

    if(!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomfic );

    ifs >> tempTaille;
    ifs.ignore();

    for(int i = 0; i<tempTaille; ++i)
    {
        std::string ligne;
        std::getline(ifs, ligne);
        std::istringstream iss(ligne);
        std::pair<int, float> values;

        iss >> values.first >> values.second;

        for(auto a : m_aretes)
        {
            if(a->changerPond(values))
                break;
        }
    }


}


void Graphe::Afficher() const
{
    for(auto i: m_sommets)
    {
        i->afficher();
    }

    for(auto i: m_aretes)
    {
        i->afficher();
    }

}
