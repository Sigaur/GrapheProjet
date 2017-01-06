#ifndef Graphe_hpp
#define Graphe_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include<fstream>
#include<string>

class Graphe
{
public:

    std::vector< std::vector<int> > m_alpha;
    std::vector< std::vector<int> > m_omega;

    std::vector <int> m_rangs;
    int m_compteur;
    bool m_boucle;
    int m_nbTaches;
    int m_nbsommets;
    int m_nbContraintes;
    int m_cle;
    std::vector<char> m_nomTaches;
    std::vector<int>m_durees;
    std::vector< std::vector<char> >m_contraintes;
    std::vector< std::vector<char> >m_preconstruction;// Contient les contraintes, liaisons et sommets pour construire le tab
    std::vector< std::vector<char> >m_DefTab;// Le tableau
    std::vector< std::vector<int> >m_DefTabDuree;
    std::vector<int> m_DureePreconstruction;

    Graphe();
    void affiche();
    void lecture();
    void grapheO();
    void testAZ();
    void graphe();
    std::vector< std::vector<char> >getTab();
    std::vector<int> getDuree();
    int getTaches();
    int getSommets();

    int calculRangRec(int sommet, int compteur);
    int maxVecteur(std::vector <int> vec);
    bool calculRangs();
    void affichageRangs();

    ~Graphe();
};


#endif /* Graphe_hpp */
