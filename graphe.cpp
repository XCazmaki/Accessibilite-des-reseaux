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
        /// On relie les sommets a l'arete
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


void Graphe::chargerPond()
{
     std::string nomfic;

    std::cout << "Nom du fichier de ponderation : ";
    std::cin>> nomfic;
    std::cout<<std::endl;

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


/// Affiche le graphe dans la console
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

/// Affiche le graphe dans Svgfile
void Graphe::afficher_Svgfile(Svgfile &svgout)
{
    float indice=this->calcul_indice();

    for(auto i: m_aretes)
    {
        i->afficher_Svgfile(svgout,indice);
    }
    for(auto i: m_sommets)
    {
        i->afficher_Svgfile(svgout,indice);
    }
}
/// Sous programme permettant de calculer l'indice d'ajustement de la taille du graphe lors de l'affichage
float Graphe::calcul_indice()
{
    float indice=0;
    float Xmax=0;
    float Ymax=0;

    /// On prend la coordonnée maximale en X et en Y
    for(auto i: m_sommets)
    {
        if(i->get_coordx()>Xmax)
        {
            Xmax=i->get_coordx();
        }
        if(i->get_coordy()>Ymax)
        {
            Ymax=i->get_coordy();
        }
    }
    /// On trouve l'indice en X et en Y
    Xmax=950/Xmax;
    Ymax=550/Ymax;

    /// On séléctionne le plus petit pour qu'il devienne l'indice général
    if(Xmax>Ymax)
    {
        indice=Ymax;
    }
    else
    {
        indice=Xmax;
    }
    return indice;
}


void Graphe::centralite_degre()
{
    for(auto i: m_sommets)
    {
        /// l'indice de chaque sommet equivaux à son degrès
        i->set_central(i->get_degre());
        std::cout << " test liaison " << i->get_degre() << std::endl;
        i->set_central_norm(i->get_degre()/(m_sommets.size()-1));
        std::cout << " test liaison 2 " << (i->get_degre())/4 << std::endl;
    }
}

void Graphe::centralite_vecteur_propre()
{
    float lambda=100;
    float lambda2=0;
    float valeur_max=0;     /// va permettre de sortir de la boucle while quand les valeurs seront normalisée

    /// Initialisation (on met 1 à l'indice)
    for (auto i: m_sommets)
    {
        i->set_central(1);
        i->set_central_norm(1);
    }
    /// tant que lambda "varie trop"
    do
    {
        lambda2=lambda;
        lambda=0;
        valeur_max=0;
        for(auto i: m_sommets)
        {
            for(auto j: m_aretes)
            {
                if(j->get_arc1()->get_nom()==i->get_nom())
                {
                    i->set_central(i->get_central()+j->get_arc2()->get_central());
                    i->set_central_norm(i->get_central()+j->get_arc2()->get_central());
                }
                if(j->get_arc2()->get_nom()==i->get_nom())
                {
                    i->set_central(i->get_central()+j->get_arc1()->get_central());
                    i->set_central_norm(i->get_central()+j->get_arc1()->get_central());
                }
            }
        }
        /// Calcul lambda
        for(auto i: m_sommets)
        {
            lambda+=(i->get_central()*i->get_central());
        }
        lambda=sqrt(lambda);
        std::cout << "lambda"<< lambda << std::endl;
        for(auto i: m_sommets)
        {
            i->set_central(i->get_central()/lambda);
            i->set_central_norm(i->get_central_norm()/lambda);
        }
        /// Test valeur max
        for(auto i: m_sommets)
        {
            if(i->get_central()>valeur_max)
                valeur_max=i->get_central();
        }
        std::cout << " Lamba " << lambda << " Lambda 2 " << lambda2 << std::endl;
    }while(lambda2-lambda>=0.00000001);
}
