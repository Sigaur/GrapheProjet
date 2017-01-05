#include "Graphe.h"

using namespace std;

Graphe::Graphe()
{

}

void Graphe::affiche()
{
    cout<<"ORDO AFFICHE:"<<endl;
    for(int i = 0; i < m_DefTab.size(); i++)
    {
        for(int j = 0; j < m_DefTab[i].size(); j ++)
        {
            if(i==0 || j==0)
            cout << m_DefTab[i][j];
            else
            cout << m_DefTabDuree[i][j];
        }
        cout << endl;
    }
}
// ============== Lecture==============
void Graphe::lecture()
{
    string saisie = "test.txt";
    string line;
    int countTemp;
    bool testSaisie=false;
    do
    {
        cout<< "================ Lecture fichier =================="<<endl;
        cout<<"Veuillez choisir votre fichier texte: "<<endl;
        cin>>saisie;
        ifstream monFlux(saisie.c_str());

        if(monFlux)
        {
            testSaisie=true;
            cout<<"Lecture du fichier en cours"<<endl;
            char tacheCourante, contrainteCourante;
            int dureeTache;

            //Ligne 1 nombre de taches
            //Preciser le nombre de taches
            monFlux >> m_nbTaches;
            cout<<"Nombre de taches : "<< m_nbTaches<<endl;
            // Ligne 2 à nbdetaches+1: durées des taches
            cout<<"Dureees : \n"<<endl;
            for(int i = 0; i < m_nbTaches; i++)
            {
                monFlux >> tacheCourante;
                m_nomTaches.push_back(tacheCourante);
            }
            for(int i = 0; i < m_nbTaches; i++)
            {
                monFlux >> dureeTache;
                m_durees.push_back(dureeTache);
            }
            //Affichage nom des taches + durees
            for (int i = 0; i < m_nbTaches; i++)
            {
                cout<< m_nomTaches[i] << " " << m_durees[i] << endl;
            }
            //Ligne suivante : contraintes
            monFlux >> m_nbContraintes;
            cout<<"Nombre Contraintes :" << m_nbContraintes <<endl;
            m_contraintes = std::vector< std::vector<char> > (m_nbContraintes, std::vector<char> ('A') );
            m_preconstruction = std::vector< std::vector<char> > ((m_nbContraintes + 10), std::vector<char> (2) );
            // Une ligne par tâche
            cout<<"Contraintes :"<<endl;
            for (int t = 0; t < m_nbTaches; t++)
            {
                monFlux >> tacheCourante;
                cout<< endl << tacheCourante<<": ";
                m_contraintes[t][0] = tacheCourante;
                monFlux >> contrainteCourante;

                countTemp = 0;
                while (contrainteCourante != '.')// Condition de fin d'une contrainte '.'
                {
                    countTemp ++;
                    cout<< contrainteCourante<<" - ";
                    m_contraintes[t][countTemp] = contrainteCourante;
                    monFlux >> contrainteCourante;
                }
                cout<<"\n"<<endl;
            }
            cout<<"Lecture terminee"<<endl;
            /*
            for (int i = 0; i < m_contraintes.size(); i++)
            {
                for (int j = 0; j < m_contraintes[i].size(); j++)
                {
                    cout << m_contraintes[i][j];
                }
                cout << endl;
            }
            */
        }
        else
        {
            cout<<"Erreur, impossible d'ouvrir le fichier en lecture"<<endl;
        }
    }while(testSaisie==false);
}

//=========== Les Getters================
std::vector< std::vector<char> > Graphe::getTab()
{
    return m_DefTab;
}
std::vector<int> Graphe::getDuree()
{
    return m_durees;
}

int Graphe::getTaches()
{
    return m_nbTaches;
}
int Graphe::getSommets()
{
    return m_nbsommets;
}

void Graphe::grapheO()
{
    char tempChar;
    int i = 0;
    int l = 0;
    m_nbsommets=m_nbTaches;// initialisation nb de sommets

    cout<<"====================Creation du Graphe d ordonnancement===================="<<endl<<endl;
    cout<<"-----------------------------Creation du graphe----------------------------"<<endl;
    cout<<"Propriete du graphe :"<<endl;
    cout<<"- nombre de sommets: "<<m_nbsommets<<endl;  // rajout des deux taches(initiale et finale)
    cout<<"- graphe oriente"<<endl;
    cout<<"- 1 valeur (numerique) pour chaque arc"<<endl;
    cout<<"- maximum 1 arc d'un sommet X donné vers un sommet Y donne"<<endl;
    /*
    for (int i = 0; i < m_contraintes.size(); i++)
    {
        for (int j = 0; j < m_contraintes[i].size(); j++)
        {
            cout << m_contraintes[i][j];
        }
        cout << endl;
    }
    */
    int numEntree = 0;
    for (int j = 0; j<m_nbTaches; j++ )
    {
        i=1;// On commence à la premiere contrainte du tableau
        while(m_contraintes[j][i]!= '\0')
        {
            //cout<<m_contraintes[j][0]<<"-- ["<<m_durees[j]<<"]-->"<<m_contraintes[j][i]<< endl;
            cout<<m_contraintes[j][i]<<"-- ["<<m_durees[(int)(m_contraintes[j][i] - 65)]<<"]-->"<<m_contraintes[j][0]<< endl;
            //cout<<"Duree de tache :" << (int)(m_contraintes[j][i] - 65)<< endl;
            //m_preconstruction[j].push_back(m_contraintes[j][0]);// Stocker ces valeurs dans un tableau
            //m_DureePreconstruction.push_back(m_durees[j]);
            //m_preconstruction[j].push_back(m_contraintes[j][i]);
            m_preconstruction[numEntree][0]=(m_contraintes[j][i]);// Stocker ces valeurs dans un tableau
            m_DureePreconstruction.push_back(m_durees[(int)(m_contraintes[j][i] - 65)]);
            m_preconstruction[numEntree][1]=(m_contraintes[j][0]);
            i++;
            numEntree++;
        }
        l++;
    }
    m_cle=l;// Recupere le nombre de ligne dans le tableau preconstruction
/*
    for(int i = 0; i < m_preconstruction.size(); i++)
    {
        cout << m_preconstruction[i][0];
        cout << m_DureePreconstruction[i];
        cout << m_preconstruction[i][1];
        cout << endl;
    }
*/
}

void Graphe::testAZ()
{
    int presenceA = 0;
    int m =1;
    int n =1;
    int contraintesA = 1;
    int contraintesZ = 1;
    int cleDuree = 0;

    // ==== Test A==========

    m_contraintes.push_back(vector <char> ('a'));
    m_durees[m_nbTaches]=0;// Duree de la liaison a

    for(int i = 0; i<=m_nbTaches;i++)
    {
        for(int j = 0; j<m_cle; j++)
        {
            if(m_nomTaches[i]==m_preconstruction[j][2])
            {
                presenceA++;// Teste si la contrainte est presente dans la liste
            }

        }
        if(presenceA == 0)// Si elle nest pas presente, alors condition de a
        {
            m_contraintes[m_nbTaches][contraintesA] = m_nomTaches[i];
            contraintesA++;
        }
    }

    // ===== Test z=====
    m_contraintes.push_back(vector <char> ('z'));
    for(int k =0; k<m_nbTaches; k++)
    {
        if(m_contraintes[k][1]=='\0')// Si le resultat est vide, alors il n'y a pas de contraintes, conditions de Z
        {
            m_contraintes[m_nbTaches+1][contraintesZ]=m_contraintes[k][0];
            contraintesZ++;
        }
    }

//==Affichage de A======
/*
    do
    {
        if(m_contraintes[m_nbTaches][m]!='\0')// Verification que la contrainte existe
        {
            cout<<m_contraintes[m_nbTaches][0]<<"--[ "<<m_durees[m_nbTaches]<<" ]--"<<m_contraintes[m_nbTaches][m]<<endl;

            //m_preconstruction.push_back(vector <char>);
            m_preconstruction[m_cle].push_back(m_contraintes[m_nbTaches][0]);// Stocker ces valeurs dans un tableau
            cout<<"TestA"<<endl;
            m_preconstruction[m_cle].push_back(m_durees[m_nbTaches]);
            m_preconstruction[m_cle].push_back(m_contraintes[m_nbTaches][m]);
            m++;
            m_cle++;
        }
    }while(m_contraintes[m_nbTaches][m]!='\0');

// === Affichage de z======
    do
    {
        if(m_contraintes[m_nbTaches+1][n]!='\0')
        {
            // Recherche de la durée
            for(int b = 0; b<m_nbTaches; b++)
            {
                if(m_nomTaches[b] == m_contraintes[m_nbTaches+1][n])// Retrouver la duree de la contrainte
                {
                    cleDuree = m_durees[b];
                }
            }
            cout<<m_contraintes[m_nbTaches+1][0]<<"--[ "<<cleDuree<<" ]--"<<m_contraintes[m_nbTaches+1][n]<<endl;
            m_preconstruction[m_cle].push_back(m_contraintes[m_nbTaches+1][0]);// Stocker ces valeurs dans un tableau
            m_preconstruction[m_cle].push_back(cleDuree);
            m_preconstruction[m_cle].push_back(m_contraintes[m_nbTaches+1][n]);
            n++;
            m_cle++;
        }
    }while(m_contraintes[m_nbTaches][m]!='\0');
*/
}

//=====Graphe====
void Graphe::graphe()
{
    int abs = 0;
    int ord = 0;
    // Initialisation de toutes les cases du graphe à -1 (case vide)
    std::vector< std::vector<char> > m_Tab = std::vector< std::vector<char> > (m_nbContraintes + 1, std::vector<char> (m_nbContraintes + 1));
    std::vector< std::vector<int> > m_TabDuree = std::vector< std::vector<int> > (m_nbContraintes + 1, std::vector<int> (m_nbContraintes + 1));
    m_Tab[0][0]= '/';

    for (int v =0; v< m_Tab.size();v++)
    {
        for (int w =0; w < m_Tab[v].size();w++)
        {
            m_Tab[v][w] = '/';
        }
    }
    for (int v =0; v< m_TabDuree.size();v++)
    {
        for (int w =0; w < m_TabDuree[v].size();w++)
        {
            m_TabDuree[v][w] = 0;
        }
    }

    for (int i = 1; i< m_Tab.size(); i++)
    {
        m_Tab[0][i] = (char)64 + i;
    }
    for (int i = 1; i< m_Tab.size(); i++)
    {
        m_Tab[i][0] = (char)64 + i;
    }
/*
    for(int l =0; l<m_cle+1; l++)
    {

        for(int m=0; m<m_nbsommets; m++)
        {
            if(m_preconstruction[l][0]==m_nomTaches[m])// Recuperer l'abscisse du sommet
            {
                cout << "Trace A"<<endl;
                abs=m;
            }

            if(m_preconstruction[l][2]==m_nomTaches[m])// Recuperer l'ordonnée de la contrainte
            {
                ord=m;
            }
        }
        m_Tab[abs][ord]=m_preconstruction[l][1];// Stockage de la duree selon le sommet et la contrainte

    }
*/
    char column, row;
    for(int i = 1; i < m_Tab.size(); i++)
    {
        for(int j = 1; j < m_Tab[0].size(); j++)
        {
            column = 64+i;
            row = 64+j;
            for (int k = 0; k < m_preconstruction.size(); k++)
            {
                //cout<<"test :"<< row << "/" << m_preconstruction[k][0]<<endl;
                //cout<< column << "/" << m_preconstruction[k][1]<<endl;
                //cout<<"TEST "<<row<<endl;
                if( (row == m_preconstruction[k][0]) && (column == m_preconstruction[k][1]) )
                {
                    m_TabDuree[j][i] = m_DureePreconstruction[k];
                }
            }
        }
    }
/*
    for(int i = 0; i < m_preconstruction.size(); i++)
    {
        cout << m_preconstruction[i][0];
        cout << m_DureePreconstruction[i];
        cout << m_preconstruction[i][1];
        cout << endl;
    }
*/
    cout <<endl<<endl<< "TABLEAU ORDONNANCEMENT:"<<endl<<endl;
    for(int i = 0; i < m_Tab.size(); i++)
    {
        for(int j = 0; j < m_Tab[i].size(); j ++)
        {
            if(i==0 || j==0)
            cout << m_Tab[i][j]<<"  ";
            else
            cout << m_TabDuree[i][j]<<"  ";
        }
        cout << endl;
    }

    m_DefTab = m_Tab;
    m_DefTabDuree = m_TabDuree;
    /*
    // ============== Affichage Graphe =====================
    cout<<"\n -----------------------------------\n"<<endl;
    cout<<"         Graphe d'ordonnancement     "<<endl;
    cout<<"\n -----------------------------------\n\n"<<endl;
    cout<<m_nbTaches<<" Taches\n"<<endl;
    cout<<m_nbsommets<<" Sommets\n\n"<<endl;
    cout<<"Matrice d'ajacence et de valeurs"<<endl;

    for(int i= 0; i<m_nbsommets; i++)
     {
     cout<<"  "<<m_nomTaches[i]<<"  "<<endl;
     }

     for(int j =0; j< m_nbsommets; j++)
     {
         cout<<m_nomTaches[j]<<endl;
         for(int k = 0; k<m_nbsommets; k++)
         {
            cout<< "  "<<m_Tab[j][k]<<"  "<<endl;

         }
     }
     */
}

Graphe::~Graphe()
{

}
// Ligne-> [][]<-colonne
