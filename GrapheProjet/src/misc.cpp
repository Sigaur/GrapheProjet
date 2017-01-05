#include "misc.h"

int calculRangRec(ordonancement ordo, int sommet)//Si un sommet n'a pas de contrainte alors il est de rang 1 A VERIFIER
{
    std::vector <int> tempRecursif;
    bool tempTrouvitude = false;

    for (int i = 0; i < ordo.getSommets(); i ++)//Placeholder pour getSommet
    {
        if (ordo.tabOrdo[i][sommet] != (-1))
        {
            tempRecursif.push_back(calculRangRec(ordo, i));//Si une contrainte est trouvée, on l'insère dans le vecteur temporaire
            tempTrouvitude = true;
        }
    }
    if (tempTrouvitude)
        return (1 + (calculRangRec(ordo, maxVecteur(tempRecursif))));//Si il a trouve des contraintes, il calul le rang maximum des branches et l'incremente
    else
        return 1;//Le premier sommet est de rang 1
}

int maxVecteur(std::vector <int> vec)
{
    int maximum = -1;
    for (int i = 0; i < vec.size(); i ++)
    {
        if(maximum < vec[i])
            maximum = vec[i];
    }
    return maximum;
}
