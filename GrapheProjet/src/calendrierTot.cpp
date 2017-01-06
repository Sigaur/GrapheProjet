#include "calendrierTot.h"

calendrierTot::calendrierTot()
{
    std::vector <bool> temp;
    for(int i = 0; i < 50; i++)
    {
        temp.push_back(false);
    }

    m_temps = 0;
    m_nSommets = m_graphe.getSommets();
    for (int i = 0; i < m_nSommets; i++)
    {
        affichageTab.push_back(temp);
        /*for (int j = 0; j < m_temps; j++)
        {
            affichageTab[i][j] = false;
        }
        */
    }

    for (int i = 0; i < m_nSommets+2; i++)
    {
        affichageTabTard.push_back(temp);
        /*for (int j = 0; j < m_temps; j++)
        {
            affichageTab[i][j] = false;
        }
        */
    }

    m_arretitude = false;
}

void calendrierTot::lireOrdo()
{
    m_nSommets = m_graphe.getSommets();
    std::vector <bool> temp;
    for(int i = 0; i < 1129; i++)
    {
        temp.push_back(false);
    }
    for (int i = 0; i < m_nSommets; i++)
    {
        affichageTab.push_back(temp);
        /*for (int j = 0; j < m_temps; j++)
        {
            affichageTab[i][j] = false;
        }
        */
    }
    for(int i = 0; i < m_graphe.m_nbsommets; i++)
    {
        tachesRestantes.push_back(i);
    }
    //m_rangs = std::vector <bool> (m_graphe.m_nbsommets);//-2 avec alpha et omega!!!
}

void calendrierTot::tabOrdonnancement()
{
    m_graphe.lecture();
    m_graphe.grapheO();
    //m_graphe.testAZ();
    m_graphe.graphe();
    //m_graphe.~Graphe();
}

void calendrierTot::update()
{
    /*
    std::cout<<"Boucle"<<std::endl<<std::endl;

    std::cout<<std::endl<<std::endl<<"Taches restantes:"<< std::endl;
    for (int i = 0; i < tachesRestantes.size(); i++)
    {
        std::cout<<tachesRestantes[i]<<"/";
    }
    std::cout<<std::endl<<std::endl;

    std::cout<<std::endl<<std::endl<<"Taches Execution:"<< std::endl;
    for (int i = 0; i < tachesExecutions.size(); i++)
    {
        std::cout<<tachesExecutions[i][0]<<"/"<<tachesExecutions[i][1]<<std::endl;
    }
    std::cout<<std::endl<<std::endl;

    std::cout<<std::endl<<std::endl<<"Taches Finies:"<< std::endl;
    for (int i = 0; i < tachesFinies.size(); i++)
    {
        std::cout<<tachesFinies[i]<<"/";
    }
    std::cout<<std::endl<<std::endl;
    */
    testTachesRestantes();
    //std::cout<<"Trace A"<<std::endl<<std::endl;
    updateTachesExec();
    //std::cout<<"Trace B"<<std::endl<<std::endl;
    //affichage();
    //std::cout<<"Trace C"<<std::endl<<std::endl;

    m_temps ++;

    if(isFinit() && m_temps > 1)
    {
        this->affichage();
    }
    else
    {
        this->update();
    }
}

bool calendrierTot::isFinit()
{
    if(m_temps > 29)
    {
        std::cout<<std::endl<<"Graphe presentant une boucle!!";
        m_arretitude = true;
        return true;
    }
    for (int i = 0; i < tachesExecutions.size(); i++)
    {
        if (tachesExecutions[i][0] != -1)
        {
            return false;
        }
    }
    for (int i = 0; i < tachesRestantes.size(); i++)
    {
        if (tachesRestantes[i] != -1)
        {
            return false;
        }
    }
    return true;
}

void calendrierTot::testTachesRestantes()
{
    int numTacheTemp;
    bool executionPossible;
    int contrainteTemp;

    for (int i = 0; i < tachesRestantes.size(); i++)
    {
        if(tachesRestantes[i] != -1)
        {
            numTacheTemp = tachesRestantes[i];//recuperation d une tache restante
            executionPossible = true;

            for (int j = 1; j < m_graphe.m_DefTabDuree[0].size(); j++)
            {

                contrainteTemp = m_graphe.m_DefTabDuree[j][numTacheTemp+1];
                if(contrainteTemp != 0)
                {
                    if(! tacheEstFinit(j-1))
                    {
                        executionPossible = false;
                    }
                }
            }
        }
        else
        {
            executionPossible = false;
        }


        if (executionPossible)
        {
            //std::cout<<"Debut tache:" << i<< std::endl;
            debutTache(i);
        }
    }
}

bool calendrierTot::tacheEstFinit(int tache)
{
    bool estFinie = false;
    for (int i = 0; i < tachesFinies.size(); i++)
    {
        if (tachesFinies[i] == tache)
        {
            estFinie = true;
        }
    }

    return estFinie;
}

void calendrierTot::debutTache(int tache)
{

    int positionTache;
    std::vector <int> nouvelleColonne;


    //Suppression du tableau tachesRestantes
    for (int i = 0; i < tachesRestantes.size(); i++)
    {
        if (tachesRestantes[i] == tache)
        {
            //positionTache = i;
            tachesRestantes[i] = -1;
        }
    }
    //tachesFinies.erase(tachesRestantes.begin() + positionTache);

    //Ajout dans le Tableau Taches Executions
    nouvelleColonne.push_back(tache);
    nouvelleColonne.push_back(m_graphe.m_durees[tache]);
    tachesExecutions.push_back(nouvelleColonne);

    //Ecriture dans le tableau affichage
    //std::cout<<std::endl<<std::endl<<"Ecriture Tache :"<<tache<<" de " << m_temps << " a " << (m_temps + m_graphe.m_durees[tache]);
    for (int i = m_temps; i < (m_temps + m_graphe.m_durees[tache]); i++)
    {

        affichageTab[tache][i] = true;
    }
    //std::cout<<"Trace 2";
}

void calendrierTot::updateTachesExec()
{
    for (int i = 0; i < tachesExecutions.size(); i++)
    {
        if(tachesExecutions[i][0] != -1)
        {
            tachesExecutions[i][1] --;
        }
    }
    for (int i = 0; i < tachesExecutions.size(); i++)
    {
        if(tachesExecutions[i][0] != -1)
        {
            if (tachesExecutions[i][1] <= 0)
            {
                finTache(tachesExecutions[i][0]);
            }
        }
    }
}

void calendrierTot::finTache(int tache)
{
    int positionTache;
    //Suppression du tableau tachesExecutions
    for (int i = 0; i < tachesExecutions.size(); i++)
    {
        if (tachesExecutions[i][0] == tache)
        {
            positionTache = i;
            tachesExecutions[i][0] = -1;
            tachesExecutions[i][1] = -1;
        }
    }
    //tachesExecutions.erase(tachesExecutions.begin() + positionTache);

    //Ajout dans le vector taches finies
    //std::cout<<"Fin tache:" << tache << std::endl;
    tachesFinies.push_back(tache);
}

void calendrierTot::affichage()
{
    std::cout << std::endl << std::endl << "CALENDRIER AU PLUS TOT" << std::endl << std::endl;
    char numTache;
    for (int i = 0; i <= (2 * m_temps); i++)
    {
        if(i == 0)
            std::cout << " ";
        else if (i%2 == 0)
            std::cout << " ";
        else
            std::cout << (i - 1)/2;
    }
    std::cout << std::endl;

    for (int i = 0; i < m_nSommets; i++)
    {
        numTache = 65 + i;
        std::cout << numTache;

        for (int j = 0; j < (2 * m_temps); j++)
        {
            if(j%2 == 0)
                std::cout << "|";
            else if(affichageTab[i][j/2])
                std::cout << "=";
            else
                std::cout << " ";
        }
        std::cout << std::endl;
    }
    system("pause");
    if(m_arretitude)
    {
        exit(0);
    }
}





/////////////////////////////TARD//////////////////
void calendrierTot::lancementTard()
{
    if(!m_graphe.m_boucle)
        initialisationTard();
}

void calendrierTot::initialisationTard()
{
    std::cout<<"Initialisation"<<std::endl;
    int tempTache;
    int j = m_graphe.m_DefTabTard.size()-1;

        tempTache = (int)(m_graphe.m_DefTabTard[0][j] - 65);
        for (int i = 1; i < m_graphe.m_DefTabTard[0].size(); i++)
        {
            if(m_graphe.m_DefTabDureeTard[i][j] != 0)
            {
                debutTacheTard(i-1);
            }
        }
    m_tempsTard = m_temps;
    updateTard();
}

void calendrierTot::updateTard()
{/*
    std::cout<<"Boucle"<<std::endl<<std::endl;

    std::cout<<std::endl<<std::endl<<"Taches Execution:"<< std::endl;
    for (int i = 0; i < tachesExecutionsTard.size(); i++)
    {
        std::cout<<tachesExecutionsTard[i][0]<<"/"<<tachesExecutionsTard[i][1]<<std::endl;
    }
    std::cout<<std::endl<<std::endl;

    std::cout<<std::endl<<std::endl<<"Taches Finies:"<< std::endl;
    for (int i = 0; i < tachesFiniesTard.size(); i++)
    {
        std::cout<<tachesFiniesTard[i]<<"/";
    }
    std::cout<<std::endl<<std::endl;

*/
    //std::cout<<"Update"<<std::endl;
    testTachesRestantesTard();
    //std::cout<<"Trace A"<<std::endl<<std::endl;
    //std::cout<<"Update1"<<std::endl;
    updateTachesExecTard();
    //std::cout<<"Trace B"<<std::endl<<std::endl;
    //affichage();
    //std::cout<<"Trace C"<<std::endl<<std::endl;
    //std::cout<<"Update2"<<std::endl;
    m_temps --;
    //affichageTard();

    //system("pause");

    if(isFinitTard())
    {
        this->affichageTard();
    }
    else
    {
        this->updateTard();
    }
}

bool calendrierTot::isFinitTard()
{
    if(m_temps <= 0)
    {
        //std::cout<<std::endl<<"Erreur Temps depasse";
        return true;
    }
    if(tachesFiniesTard.size()>= m_graphe.m_nbsommets)
        return true;

    return false;
}

void calendrierTot::testTachesRestantesTard()
{
    int tempTache;
    bool finitude;
    for (int j = 0; j < tachesFiniesTard.size(); j++)
    {
        //std::cout<<"TEST :"<<tachesFiniesTard[j]+1<<std::endl;
        tempTache = (int)(m_graphe.m_DefTabTard[0][tachesFiniesTard[j]+1] - 65);
        for (int i = 1; i < m_graphe.m_DefTabTard[0].size()-2; i++)
        {
            finitude = true;
            for(int k = 1; k < m_graphe.m_DefTabDureeTard[i].size(); k++)
            {
                if(m_graphe.m_DefTabDureeTard[i][k]!= 0)
                {
                    if(! tacheEstFinitTard(k-1))
                        finitude = false;
                }
            }
            if(finitude)
            {
                if(m_graphe.m_DefTabDureeTard[i][tachesFiniesTard[j]+1]!=0)
                {
                    if(!tacheEstFinitTard(i-1))
                    {
                        if(!tacheEstexecution(i-1))
                        {
                            //std::cout<<"Gagne!!!!!!!!!:"<<i<<std::endl;
                            debutTacheTard(i-1);
                        }
                    }
                }
            }
        }
    }
}

bool calendrierTot::tacheEstexecution(int tache)
{
    bool estFinie = false;
    for (int i = 0; i < tachesExecutionsTard.size(); i++)
    {
        if (tachesExecutionsTard[i][0] == tache)
        {
            estFinie = true;
        }
    }

    return estFinie;
}

bool calendrierTot::tacheEstFinitTard(int tache)
{
    bool estFinie = false;
    for (int i = 0; i < tachesFiniesTard.size(); i++)
    {
        if (tachesFiniesTard[i] == tache)
        {
            estFinie = true;
        }
    }

    return estFinie;
}

void calendrierTot::debutTacheTard(int tache)
{
    std::vector<int> temp(2,0);

    //Suppression du tableau tachesRestantes

    //tachesFinies.erase(tachesRestantes.begin() + positionTache);

    //Ajout dans le Tableau Taches Executions
    temp[0] = tache;
    temp[1] = m_graphe.m_durees[tache];
    tachesExecutionsTard.push_back(temp);

    //Ecriture dans le tableau affichage

    //std::cout<<std::endl<<std::endl<<"Ecriture Tache :"<<tache<<" de " << m_temps << " a " << (m_temps - m_graphe.m_durees[tache]-1);
    for (int i = m_temps-1; i > (m_temps - m_graphe.m_durees[tache]-1); i--)
    {
        affichageTabTard[tache][i] = true;
    }
    //std::cout<<"Trace 2";
}

void calendrierTot::updateTachesExecTard()
{
    for (int i = 0; i < tachesExecutionsTard.size(); i++)
    {
        if(tachesExecutionsTard[i][0] != -1)
        {
            tachesExecutionsTard[i][1] --;
        }
    }
    for (int i = 0; i < tachesExecutionsTard.size(); i++)
    {
        if(tachesExecutionsTard[i][0] != -1)
        {
            if (tachesExecutionsTard[i][1] <= 0)
            {
                finTacheTard(tachesExecutionsTard[i][0]);
            }
        }
    }
}

void calendrierTot::finTacheTard(int tache)
{
    int positionTache;
    //Suppression du tableau tachesExecutions
    for (int i = 0; i < tachesExecutionsTard.size(); i++)
    {
        if (tachesExecutionsTard[i][0] == tache)
        {
            positionTache = i;
            tachesExecutionsTard[i][0] = -1;
            tachesExecutionsTard[i][1] = -1;
        }
    }
    //tachesExecutions.erase(tachesExecutions.begin() + positionTache);

    //Ajout dans le vector taches finies
    //std::cout<<"Fin tache:" << tache << std::endl;
    tachesFiniesTard.push_back(tache);
}

void calendrierTot::affichageTard()
{
    std::cout << std::endl << std::endl << "CALENDRIER AU PLUS TARD" << std::endl << std::endl;
    char numTache;
    for (int i = 0; i <= (2 * m_tempsTard); i++)
    {
        if(i == 0)
            std::cout << " ";
        else if (i%2 == 0)
            std::cout << " ";
        else
            std::cout << (i - 1)/2;
    }
    std::cout << std::endl;

    for (int i = 0; i < m_nSommets; i++)
    {
        numTache = 65 + i;
        std::cout << numTache;

        for (int j = 0; j < (2 * m_tempsTard); j++)
        {
            if(j%2 == 0)
                std::cout << "|";
            else if(affichageTabTard[i][j/2])
                std::cout << "=";
            else
                std::cout << " ";
        }
        std::cout << std::endl;
    }
    system("pause");
}




calendrierTot::~calendrierTot()
{
    m_graphe.~Graphe();
    //dtor
}
