
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "calendrierTot.h"
using namespace std;

int main(int argc, const char * argv[])

{
    calendrierTot calendrier;
    int saisie=0;
    bool fin=false;
    do
    {

        system("cls");
        cout<<"=========Projet Theorie des Graphes L3==========\n"<<endl;
        cout<<"---------Resolution de pb d'ordonnancement------\n"<<endl;
        cout<<"1. Charger un fichier texte"<<endl;
        cout<<"2. Quitter le programme\n"<<endl;

        do
        {
            cout<<"Votre choix: ";
            cin>> saisie;
        }
        while(saisie !=1 && saisie != 2);

        switch (saisie)
        {
            case 1:
/*
                // On peut tout regrouper dans une fonction
                //cout<<"Trace 1"<<endl;
                //g.graphe();
                //cout<<"Trace 2"<<endl;
                g.lecture();
                //cout<<"Trace 3"<<endl;
                g.grapheO();
                //cout<<"Trace 4"<<endl;
                g.testAZ();
                //cout<<"Trace 5"<<endl;
                g.graphe();
                //cout<<"Trace 6"<<endl;
                g.~Graphe();
                //cout<<"Trace 7"<<endl;
*/

                calendrier.tabOrdonnancement();

                calendrier.lireOrdo();
                calendrier.update();
                calendrier.~calendrierTot();
                exit(0);
            break;
            case 2:
                cout<<"\n Programme developpé par Gayraud, Laversanne et Zuber\n"<<endl;
                fin =true;
                break;

            default:
                cout<<"Erreur de saisie, veuillez relancer le programme"<<endl;
                exit(0);
                break;
        }

    }while(fin == false);
return 0;
}
