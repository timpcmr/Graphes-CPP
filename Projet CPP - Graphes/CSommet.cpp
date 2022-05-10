#include "CSommet.h"

CSommet::CSommet()
{
    iSOMNumero = 0;
    uiSOMNbArcsSommetEntrants = 0;
    uiSOMNbArcsSommetSortants = 0;
    ppARCSOMEntrant = nullptr;
    ppARCSOMSortant = nullptr;
}

CSommet::CSommet(CSommet& SOMParam)
{
    unsigned int uiboucle1;

    iSOMNumero = SOMParam.SOMLireNumero();
    uiSOMNbArcsSommetEntrants = SOMParam.SOMLireNbArcsEntrants();
    uiSOMNbArcsSommetSortants = SOMParam.SOMLireNbArcsSortants();
    
    ppARCSOMEntrant = new CArc * [uiSOMNbArcsSommetEntrants];
    ppARCSOMSortant = new CArc * [uiSOMNbArcsSommetSortants];

    for (uiboucle1 = 0; uiboucle1 < uiSOMNbArcsSommetEntrants; uiboucle1++) {
        ppARCSOMEntrant[uiboucle1] = new CArc(*SOMParam.SOMLireArcsEntrants()[uiboucle1]);
    }
    for (uiboucle1 = 0; uiboucle1 < uiSOMNbArcsSommetSortants; uiboucle1++) {
        ppARCSOMSortant[uiboucle1] = new CArc(*SOMParam.SOMLireArcsSortants()[uiboucle1]);
    }
}

CSommet::CSommet(int iNumero, unsigned int uiNbArcSommetEntrants, unsigned int uiNbArcSommetSortants)
{
    unsigned int uiboucle1;

    iSOMNumero = iNumero;
    uiSOMNbArcsSommetEntrants = uiNbArcSommetEntrants;
    uiSOMNbArcsSommetSortants = uiNbArcSommetSortants;

    ppARCSOMEntrant = new CArc * [uiSOMNbArcsSommetEntrants];
    ppARCSOMSortant = new CArc * [uiSOMNbArcsSommetSortants];

    for (uiboucle1 = 0; uiboucle1 < uiSOMNbArcsSommetEntrants; uiboucle1++) {
        ppARCSOMEntrant[uiboucle1] = new CArc;
    }
    for (uiboucle1 = 0; uiboucle1 < uiSOMNbArcsSommetSortants; uiboucle1++) {
        ppARCSOMSortant[uiboucle1] = new CArc;
    }
}


int CSommet::SOMLireNumero()
{
    return iSOMNumero;
}

unsigned int CSommet::SOMLireNbArcsEntrants()
{
    return uiSOMNbArcsSommetEntrants;
}

unsigned int CSommet::SOMLireNbArcsSortants()
{
    return uiSOMNbArcsSommetSortants;
}

CArc** CSommet::SOMLireArcsSortants()
{
    return ppARCSOMSortant;
}

CArc** CSommet::SOMLireArcsEntrants()
{
    return ppARCSOMEntrant;
}

void CSommet::SOMModifierNumero(int iNumero)
{
    iSOMNumero = iNumero;
}

void CSommet::SOMAjouterArcEntrant(CArc* pARCArc)
{
    unsigned int uiboucle;

    CArc** ppARCTemp = new CArc * [SOMLireNbArcsEntrants() + 1];
    for (uiboucle = 0; uiboucle < SOMLireNbArcsEntrants() + 1; uiboucle++) {
        ppARCTemp[uiboucle] = new CArc;
    }

    //Copie des Arcs + affectation du nouvel arc

    for (uiboucle = 0; uiboucle < SOMLireNbArcsEntrants() + 1; uiboucle++) {
        if (uiboucle == SOMLireNbArcsEntrants()) {
            ppARCTemp[uiboucle] = pARCArc;
        }
        else {
            ppARCTemp[uiboucle] = SOMLireArcsEntrants()[uiboucle];
        }
    }
    
    //Deletion de l'ancien tableau

    for (uiboucle = 0; uiboucle < SOMLireNbArcsEntrants(); uiboucle++) {
        delete[] ppARCSOMEntrant[uiboucle];
    }
    delete[] ppARCSOMEntrant;

    //Affectation des nouvelles valeurs

    ppARCSOMEntrant = ppARCTemp;
    uiSOMNbArcsSommetEntrants += 1;
}

void CSommet::SOMSupprimerArcEntrant(CArc* pARCArc)
{
    unsigned int uiboucle, uiArcTrouve = 0;

    CArc** ppARCTemp = new CArc * [SOMLireNbArcsEntrants() - 1];
    for (uiboucle = 0; uiboucle < SOMLireNbArcsEntrants() - 1; uiboucle++) {
        ppARCTemp[uiboucle] = new CArc;
    }

    //Copie des Arcs restants

    for (uiboucle = 0; uiboucle < SOMLireNbArcsEntrants() - 1; uiboucle++) {
        if (SOMLireArcsEntrants()[uiboucle] == pARCArc) {
            uiArcTrouve = 1;
        }
        ppARCTemp[uiboucle] = SOMLireArcsEntrants()[uiboucle + uiArcTrouve];
    }

    //Deletion de l'ancien tableau

    for (uiboucle = 0; uiboucle < SOMLireNbArcsEntrants(); uiboucle++) {
        delete[] ppARCSOMEntrant[uiboucle];
    }
    delete[] ppARCSOMEntrant;

    //Affectation des nouvelles valeurs

    ppARCSOMEntrant = ppARCTemp;
    uiSOMNbArcsSommetEntrants -= 1;
}

void CSommet::SOMAjouterArcSortant(CArc* pARCArc)
{
    unsigned int uiboucle;

    CArc** ppARCTemp = new CArc * [SOMLireNbArcsSortants() + 1];
    for (uiboucle = 0; uiboucle < SOMLireNbArcsSortants() + 1; uiboucle++) {
        ppARCTemp[uiboucle] = new CArc;
    }

    //Copie des Arcs + affectation du nouvel arc

    for (uiboucle = 0; uiboucle < SOMLireNbArcsSortants() + 1; uiboucle++) {
        if (uiboucle == SOMLireNbArcsSortants()) {
            ppARCTemp[uiboucle] = pARCArc;
        }
        else {
            ppARCTemp[uiboucle] = SOMLireArcsSortants()[uiboucle];
        }
    }

    //Deletion de l'ancien tableau

    for (uiboucle = 0; uiboucle < SOMLireNbArcsSortants(); uiboucle++) {
        delete[] ppARCSOMSortant[uiboucle];
    }
    delete[] ppARCSOMSortant;

    //Affectation des nouvelles valeurs

    ppARCSOMSortant = ppARCTemp;
    uiSOMNbArcsSommetSortants += 1;
}

void CSommet::SOMSupprimerArcSortant(CArc* pARCArc)
{
    unsigned int uiboucle, uiArcTrouve = 0;

    CArc** ppARCTemp = new CArc * [SOMLireNbArcsSortants() - 1];
    for (uiboucle = 0; uiboucle < SOMLireNbArcsSortants() - 1; uiboucle++) {
        ppARCTemp[uiboucle] = new CArc;
    }

    //Copie des Arcs restants

    for (uiboucle = 0; uiboucle < SOMLireNbArcsSortants() - 1; uiboucle++) {
        if (SOMLireArcsSortants()[uiboucle] == pARCArc) {
            uiArcTrouve = 1;
        }
        ppARCTemp[uiboucle] = SOMLireArcsSortants()[uiboucle + uiArcTrouve];
    }

    //Deletion de l'ancien tableau

    for (uiboucle = 0; uiboucle < SOMLireNbArcsSortants(); uiboucle++) {
        delete[] ppARCSOMSortant[uiboucle];
    }
    delete[] ppARCSOMSortant;

    //Affectation des nouvelles valeurs

    ppARCSOMSortant = ppARCTemp;
    uiSOMNbArcsSommetSortants -= 1;
}
