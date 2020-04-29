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
    m_orientation = orient;

    /// On reccup�re l'ordre
    int ordre=0;
    monFlux >> ordre;

    /// On cr�e le bon nombre de sommet
    int indice=-1;
    std::string nom="";
    int coordx=0;
    int coordy=0;

    for(int i=0; i<ordre; ++i)
    {
        monFlux >> indice >> nom >> coordx >> coordy;
        m_sommets.push_back(new Sommet(indice,nom,coordx,coordy));
    }

    /// On reccupere la taille
    int taille=0;
    monFlux >> taille;

    /// On cree le bon nombre d'Arete
    int num1=0;
    int num2=0;

    for(int i=0; i<taille; ++i)
    {
        monFlux >> indice >> num1 >> num2;
        /// On cree la nouvelle arete
        m_aretes.push_back(new Arete(indice,m_sommets[num1],m_sommets[num2],1));
        /// On relie les sommets a l'arete
        m_sommets[num1]->set_degre(m_sommets[num1]->get_degre()+1);//ajouter_liaison(m_aretes[m_aretes.size()]);
        if(orient==0)
        {
            m_sommets[num2]->set_degre(m_sommets[num2]->get_degre()+1);//ajouter_liaison(m_aretes[m_aretes.size()]);
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

    /*for(auto i: m_aretes)
    {
        i->afficher_console();
    }*/

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
        i->set_central_norm(i->get_degre()/(m_sommets.size()-1));
        i->set_indice_central(0,i->get_central(),i->get_central_norm());
    }
}

void Graphe::centralite_vecteur_propre()
{
    float lambda=0;
    float ancien_lambda=0;

    /// Initialisation (on met 1 à l'indice)
    for (auto i: m_sommets)
    {
        i->set_central(0);
        i->set_central_norm(1);
    }
    /// tant que lambda "varie trop"
    while(ancien_lambda-lambda>=0.01||ancien_lambda==0)
    {
        for(auto i: m_sommets)
        {
            i->set_central(0);
            for(auto j: m_aretes)
            {
                if(j->get_arc1()->get_nom()==i->get_nom())
                {
                    i->set_central(i->get_central()+j->get_arc2()->get_central_norm());
                }
                else if(j->get_arc2()->get_nom()==i->get_nom())
                {
                    i->set_central(i->get_central()+j->get_arc1()->get_central_norm());
                }
            }
        }
        /// Mise à jour des valeurs
        for(auto i: m_sommets)
        {
            i->set_central_norm(i->get_central());
        }

        ancien_lambda=lambda;
        lambda=0;
        /// Calcul lambda
        for(auto i: m_sommets)
        {
            lambda=lambda+(i->get_central()*i->get_central());
        }
        lambda=sqrt(lambda);
        std::cout << " Lambda " << lambda << std::endl;
        /// On recalcule l'indice
        for(auto i: m_sommets)
        {
            i->set_central(i->get_central()/lambda);
            i->set_central_norm(i->get_central_norm()/lambda);
        }

    }
    for(auto i: m_sommets)
    {
        i->set_indice_central(1,i->get_central(),i->get_central_norm());
    }
}

void Graphe::centralite_proximite()
{
    for(auto s: m_sommets)
    {
        std::queue<Sommet*> F;
        F.push(s);

        do
        {
            std::vector<std::pair<Sommet*, float>> adjacents;
            rechercheAdj(F.front(), adjacents);
            F.front()->traitementDij(F, adjacents);/// on applique le traitement de dijkstra au premier element de la file
        }
        while(F.size()>0); /// tant que la file n'est pas vide
        dijkstra(s);

        float poidsTot = 0;
        for(auto ss: m_sommets)
            poidsTot += ss->getDist();

        s->set_central(1/poidsTot);
        s->set_central_norm((m_sommets.size() - 1)/ poidsTot);

        reset();/// on reset les parametres de parcours des sommets
    }
    for(auto i: m_sommets)
    {
        i->set_indice_central(2,i->get_central(),i->get_central_norm());
    }
}

void Graphe::dijkstra(Sommet* d)
{
    std::queue<Sommet*> F;
    F.push(d);

    do{
        std::vector<std::pair<Sommet*, float>> adjacents;
        rechercheAdj(F.front(), adjacents);
        F.front()->traitementDij(F, adjacents);/// on applique le traitement de dijkstra au premier element de la file
    }while(F.size()>0);/// tant que la file n'est pas vide
}

void Graphe::rechercheAdj(Sommet* depart, std::vector<std::pair<Sommet*, float>>& adjacents)
{
    for(auto ar: m_aretes)
    {
        if(ar->testAppartenance(depart, m_orientation))
            adjacents.push_back(std::make_pair(ar->getSommet(depart), ar->getPoids()));
    }
}

std::list<int>* Graphe::defListeAdj(std::list<std::pair<int, float>>* pond)
{
    std::list<int>* adjacence;
    adjacence = new std::list<int>[m_sommets.size()];

    if(m_orientation == 1)
    {
        for(auto a : m_aretes)
        {
            adjacence[((a->getPair()).first)->get_indice()].push_back(((a->getPair()).second)->get_indice());
            pond[((a->getPair()).first)->get_indice()].push_back(std::make_pair(((a->getPair()).second)->get_indice(),a->getPoids()));
        }
    }
    else
    {
        for(auto a : m_aretes)
        {
            adjacence[((a->getPair()).first)->get_indice()].push_back(((a->getPair()).second)->get_indice());
            pond[((a->getPair()).first)->get_indice()].push_back(std::make_pair(((a->getPair()).second)->get_indice(),a->getPoids()));

            adjacence[((a->getPair()).second)->get_indice()].push_back(((a->getPair()).first)->get_indice());
            pond[((a->getPair()).second)->get_indice()].push_back(std::make_pair(((a->getPair()).first)->get_indice(),a->getPoids()));
        }
    }

    return adjacence;
}

void Graphe::centralite_intermediarite()
{
    std::list<int>* adjacence;
    std::list<std::pair<int, float>>* pond;
    pond = new std::list<std::pair<int, float>>[m_sommets.size()];
    adjacence = defListeAdj(pond);

    for(auto d: m_sommets)
    {
        for(auto f: m_sommets)
        {
            ///recherche valeur plus court chemin entre d et f
            dijkstra(d);
            float pcc = f->getDist();
            reset();

            ///recherche de tous les chemins de d a f
            bool* visited = new bool[m_sommets.size()];
            int* path = new int[m_sommets.size()];
            int path_index = 0;

            for (int i = 0; i < (int)m_sommets.size(); i++)
                visited[i] = false;

            int nCC = 0;
            std::vector<int> tab;
            seekAllPaths(d->get_indice(), f->get_indice(), visited, path, path_index, adjacence, pond, pcc, nCC, tab);

            calculCentraliteInter(nCC, tab);

            freeMem(visited, path, adjacence, pond);
        }
    }
    for(auto so : m_sommets)
    {
        so->DefcentralInterNorm(m_sommets.size());
    }
}

void Graphe::calculCentraliteInter(const int& nCC, std::vector<int>& tab)
{
    std::sort(tab.begin(), tab.end(), IntComparator());
    std::queue<std::pair<int, int>> temp;
    int i = 0;
    int ii = 0;
    while(i< (int)tab.size())
    {
        temp.push(std::make_pair(tab[i], 1));
        if((i+1) < (int)tab.size())
        {
            while(tab[i] == tab[i+1])
            {
                (temp.back()).second++;
                i++;
            }
        }
        ii++;
        i++;
    }

    std::sort(m_sommets.begin(), m_sommets.end(), SommetComparatorIndice());
    for(auto s: m_sommets)
    {
            if(s->get_indice() == ((temp.front()).first))
            {
                s->DefcentralInter(nCC, (temp.front()).second);
                temp.pop();
            }
    }
}

void Graphe::seekAllPaths(int u, int d, bool visited[], int path[], int &path_index, std::list<int>* adj, std::list<std::pair<int, float>>* pond, const float& PCC, int& nCC, std::vector<int>& tab)
{
    visited[u] = true;
    path[path_index] = u;

    path_index++;

    if (u == d)
    {
        float longueur = 0;
        for (int i = 0; i<path_index; i++)
        {
            std::list<std::pair<int,float>>::iterator ii;
            for(ii = pond[path[i]].begin(); ii != pond[path[i]].end(); ++ii)
            {
                if((i+1)<path_index)
                {
                    if((*ii).first == path[i+1])
                        longueur += (*ii).second;
                }
            }
        }
        if(longueur == PCC)
        {
            nCC++;
            for(int i = 1; i< (path_index - 1); i++)
                tab.push_back(path[i]);
        }
    }
    else
    {
        std::list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            if (!visited[*i])
                seekAllPaths(*i, d, visited, path, path_index, adj, pond, PCC, nCC, tab);
        }
    }

    path_index--;
    visited[u] = false;
}

void Graphe::reset()
{
    for(auto s : m_sommets)
    {
        s->setEtat('B');
        s->setDist(0);
    }
}

void Graphe::k_connexite()
{
    int selection=0;        /// La première arête que l'on va ignorer
    int selection2=0;       /// La deuxième arête que l'on va ingorer
    int depart=0;
    bool connexe=true;
    /// On crée un vecteur pour stocker les couleurs de chaque sommet
    std::vector<int> couleurs;
    for(size_t i=0; i<m_sommets.size(); i++)
    {
        couleurs.push_back(0);
    }

    /// 1 CONNEXITE

    /// On va selectionne l'arete que l'on va "enlever"
    for(auto i: m_aretes)
    {
        selection=i->get_indice();
        /// On va lancer un parcours DFS en ignorant l'arete selectionnée
        //std::cout << std::endl << " Parcours DFS sans l'arete "<< selection << std::endl << std::endl;
        parcours_DFS1(depart,selection,couleurs);

        for(size_t i=0; i<couleurs.size(); i++)
        {
            if(couleurs[i]!=2)
            {
                connexe=false;
            }
            //std::cout << couleurs.size() << i << " -> " << couleurs[i]<< std::endl;
            couleurs[i]=0;
        }
    }
    if(connexe==false)
    {
        std::cout << "Le graphe est 1-arete-connexe" << std::endl;
    }
    if(connexe==true)
    {
        /// 2 CONNEXITE
        std::cout << "Le graphe est au moin 2-arete-connexe" << std::endl;

        for(auto i: m_aretes)
        {
            for(auto j: m_aretes)
            {
                selection=i->get_indice();
                selection2=j->get_indice();
                /// On va lancer un parcours DFS en ignorant l'arete selectionnée
                //std::cout << std::endl << " Parcours DFS sans l'arete "<< selection << "et " << selection2 << std::endl << std::endl;
                parcours_DFS2(depart,selection,selection2,couleurs);

                for(size_t i=0; i<couleurs.size(); i++)
                {
                    if(couleurs[i]!=2)
                    {
                        connexe=false;
                    }
                    //std::cout << couleurs.size() << i << " -> " << couleurs[i]<< std::endl;
                    couleurs[i]=0;
                }
            }
        }
        if(connexe==true)
        {
            std::cout << "Le graphe est au moin 3-arete-connexe" << std::endl;
        }
        else
        {
            std::cout << "Le graphe est 2-arete-connexe" << std::endl;
        }
    }

}

void Graphe::parcours_DFS1(int indice,int selection,std::vector<int> &couleurs)
{
    /// marquer le sommet s
    couleurs[indice]=2;

    /// afficher(s)
    //std::cout << "On parcours le sommet : " << m_sommets[indice]->get_indice()<< std::endl;

    /// Pour chaque adjacent du sommet actuel
    for (auto i: m_aretes)
    {
        /// On n'utilise pas l'arête supprimée
        if(i->get_indice()!=selection)
        {
            /// Si le sommet est l'une des extrémitées de l'arête
            if(i->get_arc1()->get_indice()==indice)
            {
                /// Si le sommet n'a pas déjà été observé (qu'il n'est pas noir)
                if(couleurs[i->get_arc2()->get_indice()]!=2)
                {
                    /// On le met en gris
                    couleurs[i->get_arc2()->get_indice()]=1;
                    indice=i->get_arc2()->get_indice();
                    parcours_DFS1(indice,selection,couleurs);
                }
            }
            else if(i->get_arc2()->get_indice()==indice)
            {
                if(couleurs[i->get_arc1()->get_indice()]!=2)
                {
                    couleurs[i->get_arc1()->get_indice()]=1;
                    indice=i->get_arc1()->get_indice();
                    parcours_DFS1(indice,selection,couleurs);
                }
            }
        }
    }
}

void Graphe::parcours_DFS2(int indice,int selection1,int selection2,std::vector<int> &couleurs)
{
    /// marquer le sommet s
    couleurs[indice]=2;

    /// afficher(s)
    //std::cout << "On parcours le sommet : " << m_sommets[indice]->get_indice()<< std::endl;

    /// Pour chaque adjacent du sommet actuel
    for (auto i: m_aretes)
    {
        /// On n'utilise pas l'arête supprimée
        if(i->get_indice()!=selection1&&i->get_indice()!=selection2)
        {
            /// Si le sommet est l'une des extrémitées de l'arête
            if(i->get_arc1()->get_indice()==indice)
            {
                /// Si le sommet n'a pas déjà été observé (qu'il n'est pas noir)
                if(couleurs[i->get_arc2()->get_indice()]!=2)
                {
                    /// On le met en gris
                    couleurs[i->get_arc2()->get_indice()]=1;
                    indice=i->get_arc2()->get_indice();
                    parcours_DFS2(indice,selection1,selection2,couleurs);
                }
            }
            else if(i->get_arc2()->get_indice()==indice)
            {
                if(couleurs[i->get_arc1()->get_indice()]!=2)
                {
                    couleurs[i->get_arc1()->get_indice()]=1;
                    indice=i->get_arc1()->get_indice();
                    parcours_DFS2(indice,selection1,selection2,couleurs);
                }
            }
        }
    }
}

void Graphe::sauvagarde_aretes()
{
    for(auto i: m_sommets)
    {
        m_degres_svg.push_back(i->get_degre());
    }
    m_aretes_originales=m_aretes;
}

void Graphe::restaurer_aretes()
{
    for(size_t i=0; i<m_sommets.size(); ++i)
    {
        m_sommets[i]->set_degre(m_degres_svg[i]);
    }
    m_aretes=m_aretes_originales;
}

void Graphe::supprimer_aretes(int indice)
{
    if(indice < static_cast<int>(m_aretes.size()))
    {
        m_aretes[indice]->get_arc1()->set_degre(m_aretes[indice]->get_arc1()->get_degre()-1);
        m_aretes[indice]->get_arc2()->set_degre(m_aretes[indice]->get_arc2()->get_degre()-1);
        m_aretes.erase(m_aretes.begin() + indice);
    }
}

void Graphe::sauvegarde_fichier()
{
    std::ofstream monFlux("sauvegarde.txt");
    std::vector<std::pair<float,float>> temp;
    if(monFlux)
    {
        for(auto i: m_sommets)
        {
            monFlux << i->get_indice() << " ";
            temp=i->get_indice_central();
            for(int i=0; i<4; ++i)
            {
                monFlux << temp[i].first << " " << temp[i].second << " ";
            }
            monFlux << std::endl;
        }
    }
void Graphe::freeMem(bool* visited, int* path, std::list<int>* adj, std::list<std::pair<int, float>>* pond)
{
    free(visited);
    free(path);
    free(adj);
    free(pond);
}
