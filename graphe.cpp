#include "graphe.h"

Graphe::Graphe()
{
    /// On ouvre un fichier:

    std::string nom_fichier="";
    std::cout << "Entrez le nom du fichier de topologie : ";
    std::cin >> nom_fichier;
    std::ifstream monFlux(nom_fichier);

    if(!monFlux)
    {
        std::cout<<"Fichier non trouve, reessayez svp !\n"<<std::endl;
        m_orientation = 2;
        return;
    }


    /// On teste si le fichier s'est bien ouvert:


    /// On reccupere l'orientation
    int orient=0;
    /// 0=non oriente
    monFlux >> orient;
    m_orientation = orient;

    /// On reccupere l'ordre
    int ordre=0;
    monFlux >> ordre;

    /// On cree le bon nombre de sommet
    int indice=-1;
    std::string nom="";
    float coordx=0;
    float coordy=0;

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
    {
        std::cout<<"Impossible d'ouvrir en lecture " + nomfic<<std::endl;
        return;
    }

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

/// AFFICHAGE

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
    float maxS = 0.0;
    for(auto s: m_sommets)
    {
        if(s->get_central_norm()> maxS)
            maxS = s->get_central_norm();
    }

    float maxA = 0.0;
    for(auto a: m_aretes)
    {
        if(a->get_central_normA()> maxA)
            maxA = a->get_central_normA();
    }

    for(auto i: m_aretes)
    {
        i->afficher_Svgfile(svgout,indice, m_orientation, maxA);
    }
    for(auto i: m_sommets)
    {
        i->afficher_Svgfile(svgout,indice, maxS);
    }

    dispLegend(svgout, maxS, maxA);
}

///permet d'afficher la legende
void Graphe::dispLegend(Svgfile& svgout, float maxS, float maxA)
{
    svgout.addRectangle(0,10,15,10,15,15,0,15, "red");
    svgout.addRectangle(0,15,15,15,15,20,0,20, "orange");
    svgout.addRectangle(0,20,15,20,15,25,0,25, "gold");
    svgout.addRectangle(0,25,15,25,15,30,0,30, "yellow");
    svgout.addRectangle(0,30,15,30,15,35,0,35, "greenyellow");
    svgout.addRectangle(0,35,15,35,15,40,0,40, "green");
    svgout.addRectangle(0,40,15,40,15,45,0,45, "lightseagreen");
    svgout.addRectangle(0,45,15,45,15,50,0,50, "lightskyblue");
    svgout.addRectangle(0,50,15,50,15,55,0,55, "blue");
    svgout.addRectangle(0,55,15,55,15,60,0,60, "purple");

    if(maxS == 0)
        maxS = 1;

    svgout.addText(20, 13.5, maxS, "red");
    svgout.addText(20, 39.25, "S", "black");
    svgout.addText(20, 65, 0, "purple");

    svgout.addRectangle(0,75,15,75,15,80,0,80, "red");
    svgout.addRectangle(0,80,15,80,15,85,0,85, "orange");
    svgout.addRectangle(0,85,15,85,15,90,0,90, "gold");
    svgout.addRectangle(0,90,15,90,15,95,0,95, "yellow");
    svgout.addRectangle(0,95,15,95,15,100,0,100, "greenyellow");
    svgout.addRectangle(0,100,15,100,15,105,0,105, "green");
    svgout.addRectangle(0,105,15,105,15,110,0,110, "lightseagreen");
    svgout.addRectangle(0,110,15,110,15,115,0,115, "lightskyblue");
    svgout.addRectangle(0,115,15,115,15,120,0,120, "blue");
    svgout.addRectangle(0,120,15,120,15,125,0,125, "purple");

    if(maxA == 0)
        maxA = 1;

    svgout.addText(20, 78.5, maxA, "red");
    svgout.addText(20, 104.25,"A", "black");
    svgout.addText(20, 130, 0, "purple");
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

/// CALCUL INDICES DE CENTRALITE

void Graphe::calcul_centralite()
{
    centralite_degre();
    centralite_vecteur_propre();
    centralite_proximite();
    //centralite_intermediarite();
}

void Graphe::centralite_degre()
{
    float cG = 0.0;
    float m = 0.0;
    float somme= 0.0;
    float n = (float)m_sommets.size();
    for(auto i: m_sommets)
    {
        /// l'indice de chaque sommet equivaux à son degrès
        if(i->get_degre()>m)
            m =i->get_degre();

        i->set_central(i->get_degre());
        i->set_central_norm(i->get_degre()/(m_sommets.size()-1));
        i->set_indice_central(0,i->get_central(),i->get_central_norm());
    }

    for(auto s : m_sommets)
    {
        somme+= (m - (float)s->get_degre());
    }
    cG = (somme / ((n*n) - (3*n) +2));
    std::cout<<"L indice globale de centralite de degre est : " << cG<<std::endl;
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
    float m = 0.0;
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

        if(s->get_central_norm() > m)
            m = s->get_central_norm();

        reset();/// on reset les parametres de parcours des sommets
    }

    float somme = 0.0;
    float pG = 0.0;
    float n = m_sommets.size();
    for(auto i: m_sommets)
    {
        i->set_indice_central(2,i->get_central(),i->get_central_norm());

        somme += (m - i->get_central_norm());
    }
    pG = ((somme * ((2 * n) - 3))/((n*n)-(3*n)+2));
    std::cout<<"L indice globale de centralite de proximite est : " << pG<<std::endl;
}

void Graphe::dijkstra(Sommet* d)
{
    std::queue<Sommet*> F;
    F.push(d);

    do
    {
        std::vector<std::pair<Sommet*, float>> adjacents;
        rechercheAdj(F.front(), adjacents);
        F.front()->traitementDij(F, adjacents);/// on applique le traitement de dijkstra au premier element de la file
    }
    while(F.size()>0); /// tant que la file n'est pas vide
}

void Graphe::rechercheAdj(Sommet* depart, std::vector<std::pair<Sommet*, float>>& adjacents)
{
    for(auto ar: m_aretes)
    {
        if(ar->testAppartenance(depart, m_orientation))
            adjacents.push_back(std::make_pair(ar->getSommet(depart), ar->getPoids()));
    }
}

///-///////////////////////////////////////////////////
/// INDICE INTERMEDIARITE /////////////////////////////
///-///////////////////////////////////////////////////

void Graphe::intermediarite()
{
    std::vector<int> marquage;
    std::vector<int> preds;
    std::vector<float> poids;

    std::vector<std::pair<std::vector<int>,float>> chemins;

    float plus_court=1000000;
    float nombre_plus_courts=0;
    float indice_norm=0;
    /// Indice permettant de normaliser le code
    indice_norm=((m_sommets.size()*m_sommets.size())-(3*m_sommets.size())+2)/2;

    /// Utilisé pour calculer l'indice des aretes
    int suiv=0;
    int actu=0;




    for(auto i:m_sommets)
    {
        marquage.push_back(0);
        preds.push_back(-1);
        poids.push_back(0);
        i->set_central(0);
        i->set_central_norm(0);
    }

    for(auto i: m_aretes)
    {
        i->set_centralA(0);
        i->set_central_normA(0);
    }

    for(size_t i=0; i<m_sommets.size(); i++)
    {
        for(size_t j=0; j<m_sommets.size(); j++)
        {
            if(i!=j)
            {
                intermediarite_parcour(marquage,preds,i,j,i,poids,chemins);
                for(size_t t=0; t<m_sommets.size(); t++)
                {
                    marquage[t]=0;
                    preds[t]=-1;
                    poids[t]=0;
                }
                plus_court=1000000;
                /// Recherche du plus court chemin
                for(auto i: chemins)
                {
                    if(i.second<plus_court)
                    {
                        plus_court=i.second;
                    }
                }

                /// Suppression des chemin non plus court

                for(size_t i=0; i<chemins.size(); ++i)
                {
                    if(chemins[i].second>plus_court)
                    {
                        chemins.erase(chemins.begin()+i);
                        i--;
                    }
                }

                /// Augmentation de l'indice des sommets
                nombre_plus_courts=chemins.size();

                for(auto i: chemins)
                {
                    for(auto j:i.first)
                    {
                        m_sommets[j]->set_central(m_sommets[j]->get_central()+((1/nombre_plus_courts)));
                        m_sommets[j]->set_central_norm(m_sommets[j]->get_central()/indice_norm);
                    }
                }

                /// Augmentation de l'indice des sommets

                for(auto i: chemins)
                {
                    for(size_t j=0;j<i.first.size();++j)
                    {
                        /// i.first[j] = un num de sommet du parcours le plus court
                        /// Il faut regarder avant et apres si c'est l'autre extremité de l'arete
                        for(auto t: m_aretes)
                        {
                            /// Si le premier element de l'arete appartient au parcours le plus court
                            if(t->get_arc1()->get_indice()==i.first[j])
                            {
                                /// Si j n'est pas le dernier element de la liste
                                if(j!=i.first[i.first.size()-1])
                                {
                                    if(t->get_arc2()->get_indice()==i.first[j-1])
                                    {
                                        ///On met a jour l'indice
                                        t->set_centralA(t->get_centralA()+((1/nombre_plus_courts)));
                                        t->set_central_normA(t->get_centralA()/indice_norm);
                                    }
                                }
                            }
                            else if(t->get_arc2()->get_indice()==i.first[j])
                            {
                                /// Si j n'est pas le dernier element de la liste
                                if(j!=i.first[i.first.size()-1])
                                {
                                    if(t->get_arc1()->get_indice()==i.first[j+1])
                                    {
                                        ///On met a jour l'indice
                                        t->set_centralA(t->get_centralA()+((1/nombre_plus_courts)));
                                        t->set_central_normA(t->get_centralA()/indice_norm);
                                    }
                                }
                            }
                        }
                    }
                }

                while(chemins.size()!=0)
                {
                    chemins.pop_back();
                }
            }

        }
    }

    float maxS = 0.0;
    float somme = 0.0;
    float n = m_sommets.size();
    float bG = 0.0;

    for(auto s: m_sommets)
    {
        if(s->get_central_norm()> maxS)
            maxS = s->get_central_norm();
    }
    for(auto i: m_sommets)
    {
        i->set_indice_central(3,i->get_central(),i->get_central_norm());

        somme += (maxS - i->get_central_norm());
    }
    bG = (somme/((n -1)*((n*n)-(3*n)+2)));
    std::cout<<"L indice globale de centralite d intermediarite est : " << bG<<std::endl;
}

void Graphe::intermediarite_parcour(std::vector<int> &marquage,
                                    std::vector<int> &preds,int num_sommet,
                                    int sfinal,int depart,std::vector<float> &poids,
                                    std::vector<std::pair<std::vector<int>,float>> &chemins)
{
    /// On part du nœud initial, on le marque.
    marquage[num_sommet]=1;
    /// On regarde les successeurs non marqués
    for(auto i:m_aretes)
    {
        /// Test successeur
        if(i->get_arc1()->get_indice()==num_sommet)
        {
            /// Test marquage
            if(marquage[i->get_arc2()->get_indice()]==0)
            {
                /// On test si c'est le sommet d'arivée
                if(i->get_arc2()->get_indice()==sfinal)
                {
                    /// SAUVEGARDE PARCOURS
                    poids[i->get_arc2()->get_indice()]=poids[num_sommet]+i->getPoids();
                    preds[i->get_arc2()->get_indice()]=num_sommet;
                    affichage_parcours(preds,depart,sfinal,poids,chemins);
                }
                else /// Sinon on le parcours
                {
                    poids[i->get_arc2()->get_indice()]=poids[num_sommet]+i->getPoids();
                    preds[i->get_arc2()->get_indice()]=num_sommet;
                    intermediarite_parcour(marquage,preds,i->get_arc2()->get_indice(),sfinal,depart,poids,chemins);
                }
            }
        }
        else if((i->get_arc2()->get_indice()==num_sommet)&&m_orientation==0)
        {
            /// Test marquage
            if(marquage[i->get_arc1()->get_indice()]==0)
            {
                /// On test si c'est le sommet d'arivée
                if(i->get_arc1()->get_indice()==sfinal)
                {
                    /// SAUVEGARDE PARCOURS
                    poids[i->get_arc1()->get_indice()]=poids[num_sommet]+i->getPoids();
                    preds[i->get_arc1()->get_indice()]=num_sommet;
                    affichage_parcours(preds,depart,sfinal,poids,chemins);
                }
                else /// Sinon on le parcours
                {
                    poids[i->get_arc1()->get_indice()]=poids[num_sommet]+i->getPoids();
                    preds[i->get_arc1()->get_indice()]=num_sommet;
                    intermediarite_parcour(marquage,preds,i->get_arc1()->get_indice(),sfinal,depart,poids,chemins);
                }
            }
        }
    }
    marquage[num_sommet]=0;
}

void Graphe::affichage_parcours(std::vector<int> preds,
                                int num_sommet, int sfinal,std::vector<float> poids,
                                std::vector<std::pair<std::vector<int>,float>> &chemins)
{
    std::pair<std::vector<int>,float> nouv;
    chemins.push_back(nouv);

    int actuel=preds[sfinal];

    chemins[chemins.size()-1].first.push_back(sfinal);

    while(actuel!=num_sommet)
    {
        chemins[chemins.size()-1].first.push_back(actuel);
        actuel=preds[actuel];
    }
    chemins[chemins.size()-1].first.push_back(actuel);

    chemins[chemins.size()-1].second=poids[sfinal];
}

/*std::list<int>* Graphe::defListeAdj(std::list<std::pair<int, float>>* pond)
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
    for(auto i:m_sommets)
    {
        i->set_central(0);
        i->set_central_norm(0);
    }

    for(auto a: m_aretes)
    {
        a->set_centralA(0);
        a->set_central_normA(0);
    }

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
            std::vector<Arete*> tab2;

            seekAllPaths(d->get_indice(), f->get_indice(), visited, path, path_index, adjacence, pond, pcc, nCC, tab, tab2);

            calculCentraliteInterSommet(nCC, tab);

            calculCentraliteInterArete(nCC, tab2);

            freeMem(visited, path, adjacence, pond);
        }
    }

    float m=0.0;
    float somme =0.0;
    float bG= 0.0;
    float n = (float)m_sommets.size();
    for(auto so : m_sommets)
    {
        if(so->get_central_norm()> m)
            m = so->get_central_norm();

        so->DefcentralInterNorm(m_sommets.size());
    }

    for(auto a: m_aretes)
        a->DefcentralInterNormA(m_aretes.size());

    for(auto i: m_sommets)
    {
        i->set_indice_central(3,i->get_central(),i->get_central_norm());

        somme += (m - i->get_central_norm());
    }
    bG = (somme/((n -1)*((n*n)-(3*n)+2)));
    std::cout<<"L indice globale de centralite d intermediarite est : " << bG<<std::endl;
}

void Graphe::calculCentraliteInterSommet(const int& nCC, std::vector<int>& tab)
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
            s->DefcentralInterSommet(nCC, (temp.front()).second);
            temp.pop();
        }
    }
}

void Graphe::calculCentraliteInterArete(const int& nCC, std::vector<Arete*>& tab)
{
    std::sort(tab.begin(), tab.end(), AreteComparatorIndice());
    std::queue<std::pair<Arete*, int>> temp;
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

    std::sort(m_aretes.begin(), m_aretes.end(), AreteComparatorIndice());
    for(auto a: m_aretes)
    {
        if(a == ((temp.front()).first))
        {
            a->DefcentralInterArete(nCC, (temp.front()).second);
            temp.pop();
        }
    }
}

void Graphe::seekAllPaths(int u, int d, bool visited[], int path[], int &path_index, std::list<int>* adj, std::list<std::pair<int, float>>* pond,
                          const float& PCC, int& nCC, std::vector<int>& tab, std::vector<Arete*>& tab2)
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
            for(int i = 1; i< (path_index - 1); ++i)
            {
                tab.push_back(path[i]);
                //std::cout<<path[i]<<" ";
            }
            //std::cout<<std::endl;

            for(int i = 0; i< (path_index-1); ++i)
                tab2.push_back(seekArete(path[i], path[i+1]));
        }
    }
    else
    {
        std::list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            if (!visited[*i])
                seekAllPaths(*i, d, visited, path, path_index, adj, pond, PCC, nCC, tab, tab2);
        }
    }

    path_index--;
    visited[u] = false;
}

Arete* Graphe::seekArete(int& a, int& b)
{
    for(auto ar : m_aretes)
    {
        Sommet* s1 = (Sommet*)ar->get_arc1();
        Sommet* s2 = (Sommet*)ar->get_arc2();

        int a1 = (int)s1->get_indice() ;
        int a2 = (int)s2->get_indice();

        if(m_orientation == 0)
        {
            if(((a1 == a)&&(a2 == b))||((a1 == b)&&(a2 == a)))
                return ar;
        }
        else
        {
            if((a1 == a)&&(a2 == b))
                return ar;
        }
    }
    return nullptr;
}*/

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
    if(!connexite())
        return;

    for(int i = 0; i< (int)(m_sommets.size()); ++i)
    {
        if(!k_connexite_test(i))
        {
            std::cout<<" Le graphe est " << i+1 << "-connexe "<<std::endl;
            break;
        }
    }
}

bool Graphe::k_connexite_test(int& tour)
{
    int* selection = (int*)malloc(tour+1 * sizeof(int));

    int curseur = 0;
    bool connexe = true;

    recursion(selection, tour,curseur, connexe);

    free(selection);

    return connexe;
}

void Graphe::recursion(int* selection, int& tour, int curseur, bool& connexe)
{
    if(curseur == tour)
    {
        for(auto a : m_aretes)
        {
            std::vector<int> couleurs;
            for(size_t i=0; i<m_sommets.size(); i++)
            {
                couleurs.push_back(0);
            }

            selection[tour] = a->get_indice();

            int depart = 0;
            parcours_DFSK(depart,selection,couleurs, tour);

            for(size_t i=0; i<couleurs.size(); i++)
            {
                if(couleurs[i]!=2)
                {
                    connexe=false;
                }
                couleurs[i]=0;
            }
        }
    }
    else
    {
        for(auto a : m_aretes)
        {
            selection[curseur] = a->get_indice();
            recursion(selection, tour, curseur +1, connexe);
        }
    }
}

bool Graphe::connexite()
{
    int* selection = (int*)malloc(sizeof(int));
    selection[0] = m_aretes.size() +1;
    int tour =0;
    bool connexe = true;

    std::vector<int> couleurs;
    for(size_t i=0; i<m_sommets.size(); i++)
    {
        couleurs.push_back(0);
    }

    int depart = 0;
    parcours_DFSK(depart,selection,couleurs, tour);

    for(size_t i=0; i<couleurs.size(); i++)
    {
        if(couleurs[i]!=2)
        {
            connexe=false;
        }
        couleurs[i]=0;
    }
    if(connexe)
        return true;
    else
    {
        std::cout<<"Le graphe n est pas connexe"<<std::endl;
        return false;
    }

}

void Graphe::parcours_DFSK(int indice,int* selection, std::vector<int> &couleurs, int& tour)
{
    /// marquer le sommet s
    couleurs[indice]=2;

    /// afficher(s)
    //std::cout << "On parcours le sommet : " << m_sommets[indice]->get_indice()<< std::endl;

    /// Pour chaque adjacent du sommet actuel
    for (auto i: m_aretes)
    {
        /// On n'utilise pas l'arête supprimée
        if(testSel(selection, tour, i))
        {

            /// Si le sommet est l'une des extrémitées de l'arête
            if(i->get_arc1()->get_indice()==indice)
            {
                /// Si le sommet n'a pas déjà été observé (qu'il n'est pas noir)
                if(couleurs[i->get_arc2()->get_indice()]!=2)
                {
                    /// On le met en gris
                    couleurs[i->get_arc2()->get_indice()]=1;
                    parcours_DFSK(i->get_arc2()->get_indice(), selection, couleurs, tour);
                }
            }
            else if(i->get_arc2()->get_indice()==indice)//&&m_orientation==1)
            {
                if(couleurs[i->get_arc1()->get_indice()]!=2)
                {
                    couleurs[i->get_arc1()->get_indice()]=1;
                    parcours_DFSK(i->get_arc1()->get_indice(), selection, couleurs, tour);
                }
            }
        }
    }
}

bool Graphe::testSel(int* selection, int& tour, Arete* a)
{
    bool retour = true;
    int indice = a->get_indice();

    for(int i=0; i<tour+1; ++i)
    {
        if(selection[i] == indice)
            retour = false;
    }
    return retour;
}

void Graphe::parcours_DFS(int indice,std::vector<int> &couleurs)
{
    couleurs[indice]=2;
    std::cout << "On passe au sommet " << indice << std::endl;
    for(auto i: m_aretes)
    {
        if(i->get_arc1()->get_indice()==indice&&couleurs[i->get_arc2()->get_indice()]!=2)
        {
            std::cout << "il a pour adjacent le sommet " << indice << std::endl;
            parcours_DFS(i->get_arc2()->get_indice(),couleurs);
        }
        if(i->get_arc2()->get_indice()==indice&&couleurs[i->get_arc1()->get_indice()]!=2)
        {
            std::cout << "il a pour adjacent le sommet " << indice << std::endl;
            parcours_DFS(i->get_arc1()->get_indice(),couleurs);
        }
    }
    std::cout << "on termine le sommet " << indice << std::endl;
}


void Graphe::forte_connexite()
{
    if(!connexite())
        return;

    bool connexe=true;
    std::vector<int> couleurs;
    for(size_t i=0; i<m_sommets.size(); i++)
    {
        couleurs.push_back(0);
    }
    for(auto a : m_sommets)
    {
        for(size_t i=0; i<couleurs.size(); i++)
        {
            couleurs[i]=0;
        }

        int depart = a->get_indice();
        parcours_DFSF(depart,couleurs);

        for(size_t i=0; i<couleurs.size(); i++)
        {
            if(couleurs[i]!=2)
            {
                connexe=false;
            }
            couleurs[i]=0;
        }
    }
    if(connexe==false)
    {
        std::cout << "Le graphe n'est pas fortement connexe" << std::endl;
    }
    else if (connexe==true)
    {
        std::cout << "Le graphe est fortement connexe" << std::endl;
    }
}


void Graphe::parcours_DFSF(int indice, std::vector<int> &couleurs)
{
    /// marquer le sommet s
    couleurs[indice]=2;

    /// afficher(s)
    //std::cout << "On parcours le sommet : " << m_sommets[indice]->get_indice()<< std::endl;

    /// Pour chaque adjacent du sommet actuel
    for (auto i: m_aretes)
    {
        /// Si le sommet est l'une des extrémitées de l'arête
        if(i->get_arc1()->get_indice()==indice)
        {
            /// Si le sommet n'a pas déjà été observé (qu'il n'est pas noir)
            if(couleurs[i->get_arc2()->get_indice()]!=2)
            {
                /// On le met en gris
                couleurs[i->get_arc2()->get_indice()]=1;
                parcours_DFSF(i->get_arc2()->get_indice(), couleurs);
            }
        }
    }
}


void Graphe::sauvegarde_aretes()
{
    std::vector<float> degres_svg;

    for(auto i: m_sommets)
    {
        degres_svg.push_back(i->get_degre());
    }

    m_degres_svg.push_back(degres_svg);
    m_aretes_originales.push_back(m_aretes);

    for(size_t i=0;i<m_aretes.size();i++)
    {
        m_aretes[i]->set_indice(i);
    }
}

void Graphe::restaurer_aretes()
{
    std::vector<float> degres_svg=m_degres_svg[m_degres_svg.size()-1];
    for(size_t i=0; i<m_sommets.size(); ++i)
    {
        m_sommets[i]->set_degre(degres_svg[i]);
    }
    m_aretes=m_aretes_originales[m_aretes_originales.size()-1];

    m_degres_svg.pop_back();
    m_aretes_originales.pop_back();

    for(int i = 0; i< (int)m_aretes.size(); ++i)
        m_aretes[i]->set_indiceA(i);

}

void Graphe::supprimer_aretes(int indice)
{
    if(indice < (int)(m_aretes.size()+1))
    {
        int compteur=0;
        for(auto i:m_aretes)
        {
            if(i->get_indice()==indice)
            {
                (i->get_arc1())->set_degre(i->get_arc1()->get_degre()-1);
                (i->get_arc2())->set_degre(i->get_arc2()->get_degre()-1);

                m_aretes.erase(m_aretes.begin() + compteur);
            }
            compteur++;
        }
        for(int i = 0; i< (int)m_aretes.size(); ++i)
            m_aretes[i]->set_indiceA(i);

    }
}


void Graphe::sauvegarde_sommets_indices()
{
    std::vector<Sommet> svg;

    for(auto i: m_sommets)
    {
        svg.push_back(*i);
    }

    m_sommets_svg.push_back(svg);
}

void Graphe::restaurer_sommets()
{
    m_sommets=m_sommets_originaux[m_sommets_originaux.size()-1];
    m_sommets_originaux.pop_back();

    for(int i = 0; i<(int)m_sommets.size();++i)
        m_sommets[i]->set_indiceS(i);

    restaurer_aretes();
}

void Graphe::supprimer_sommets(int indice)
{
    m_sommets_originaux.push_back(m_sommets);
    sauvegarde_aretes();

    if(indice < (int)(m_sommets.size()+1))
    {
        //int compteur=0;
        for(auto i:m_sommets)
        {
            if(i->get_indice()==indice)
            {
                for(auto j: m_aretes)
                {
                    if(j->get_arc1()->get_indice()==indice)
                    {
                        supprimer_aretes(j->get_indice());
                    }
                    else if(j->get_arc2()->get_indice()==indice)
                    {
                        supprimer_aretes(j->get_indice());
                    }
                }
                std::cout << "SUPRESSION " << indice << std::endl;
                m_sommets.erase(m_sommets.begin() + indice);
            }
            //compteur++;
        }

    }
    for(int i = 0; i<(int)m_sommets.size();++i)
        m_sommets[i]->set_indiceS(i);

}

void Graphe::comparer_indices()
{
    if(m_sommets_svg.size()>0)
    {
        for(size_t i=0; i<m_sommets.size(); ++i)
        {
            std::cout << "Indices de centralites actuels :" << std::endl;
            m_sommets[i]->afficher_console();

            std::cout << "Indices de centralites au temps t-1 :" << std::endl;
            m_sommets_svg[m_sommets_svg.size()-1][i].afficher_console();

            std::cout << "Ils ont donc variés de : " << std::endl;

            for(size_t j=0; j<4; ++j)
            {
                std::cout << ((m_sommets[i]->get_indice_central()[j].first)-(m_sommets_svg[m_sommets_svg.size()-1][i].get_indice_central()[j].first)) << " ";
                std::cout << ((m_sommets[i]->get_indice_central()[j].second)-(m_sommets_svg[m_sommets_svg.size()-1][i].get_indice_central()[j].second)) << " ";
                std::cout << std::endl;
            }

        }
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
}

/*void Graphe::freeMem(bool* visited, int* path, std::list<int>* adj, std::list<std::pair<int, float>>* pond)
{
    free(visited);
    free(path);
    free(adj);
    free(pond);
}*/

void Graphe::reinitialiser_centralite()
{
    for(auto i: m_sommets)
    {
        i->set_central(0);
        i->set_central_norm(0);
    }
    for(auto a : m_aretes)
    {
        a->set_centralA(0);
        a->set_central_normA(0);
    }
}

void Graphe::reinitialiser_indice_aretes()
{
    for(size_t i=0; i<m_aretes.size(); ++i)
    {
        m_aretes[i]->set_indice(i);
    }
}
