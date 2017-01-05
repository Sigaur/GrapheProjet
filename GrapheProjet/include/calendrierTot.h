#ifndef CALENDRIERTOT_H
#define CALENDRIERTOT_H

#include "Graphe.h"
#include <vector>
#include <iostream>
#include <cstdlib>

class calendrierTot
{
    public:
        calendrierTot();

        void tabOrdonnancement();

        void update();//Méthode principale, incremente le tempsActuel et appelle les autres méthodes
        void lireOrdo();//Lecture du tableau d ordonancement
        void affichage();//affiche le affichageTab

        virtual ~calendrierTot();

    protected:
        bool isFinit();
        void testTachesRestantes();//tests des etats resstants et de leurs contraintes.
                         //Si toutes les contraintes sont presentes dans le vector etatsFinis alors debut de cette tache
                         //Si le vector est vide alors afficher affichageTab
        void debutTache(int tache);//ecriture de la tache dans le tableau d'affichage et transfert de etats finis a etats exectutions
        void updateTachesExec();//decrementation temps restant du vectorExecutions et appel de la methode finTaches pour les taches finies
        void finTache(int tache);//suppression de l etat du vector tacheExecution et ajout dans le vector tachesFinies
        bool tacheEstFinit(int tache);//Cherche dans le tableau des taches finies pour voir si lentier d entree est present


    private:
        int m_temps;
        int m_nTaches, m_nSommets;

        Graphe m_graphe;

        std::vector <int> tachesRestantes;
        std::vector <std::vector <int> > tachesExecutions;//tabelau deux rangees: num de la tache et temp restant
        std::vector <int> tachesFinies;
        std::vector <std::vector <bool> > affichageTab;

        //Tableaux lus depuis lordonancement
        std::vector <std::vector <int> > tabOrdo;
        std::vector <int> dureeTaches;
};

#endif // CALENDRIERTOT_H
