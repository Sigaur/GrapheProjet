#ifndef CALENDRIERTOT_H
#define CALENDRIERTOT_H

#include "Graphe.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>

class calendrierTot
{
    public:
        calendrierTot();

        void tabOrdonnancement();

        void update();//Méthode principale, incremente le tempsActuel et appelle les autres méthodes
        void lireOrdo();//Lecture du tableau d ordonancement
        void affichage();//affiche le affichageTab
        //////////////////////////////TARD/////////////////////
        void updateTard();//Méthode principale, incremente le tempsActuel et appelle les autres méthodes
        void affichageTard();//affiche le affichageTab
        void lancementTard();
        void initialisationTard();

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
        //////////////////////////////TARD/////////////////////
        bool isFinitTard();
        void testTachesRestantesTard();//tests des etats resstants et de leurs contraintes.
                         //Si toutes les contraintes sont presentes dans le vector etatsFinis alors debut de cette tache
                         //Si le vector est vide alors afficher affichageTab
        bool tacheEstexecution(int tache);
        void debutTacheTard(int tache);//ecriture de la tache dans le tableau d'affichage et transfert de etats finis a etats exectutions
        void updateTachesExecTard();//decrementation temps restant du vectorExecutions et appel de la methode finTaches pour les taches finies
        void finTacheTard(int tache);//suppression de l etat du vector tacheExecution et ajout dans le vector tachesFinies
        bool tacheEstFinitTard(int tache);//Cherche dans le tableau des taches finies pour voir si lentier d entree est present


    private:
        int m_temps;
        int m_nTaches, m_nSommets;
        bool m_arretitude;
        Graphe m_graphe;

        std::vector <int> tachesRestantes;
        std::vector <std::vector <int> > tachesExecutions;//tabelau deux rangees: num de la tache et temp restant
        std::vector <int> tachesFinies;
        std::vector <std::vector <bool> > affichageTab;

        //Tableaux lus depuis lordonancement

        //////////////////////////////TARD/////////////////////
        int m_tempsTard;
        std::vector <std::vector <int> > tachesExecutionsTard;//tabelau deux rangees: num de la tache et temp restant
        std::vector <int> tachesFiniesTard;
        std::vector <std::vector <bool> > affichageTabTard;

        //Tableaux lus depuis lordonancement
        std::vector <int> dureeTachesTard;

};

#endif // CALENDRIERTOT_H
