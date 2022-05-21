#include "CSommet.h"


#pragma warning(disable : 6308)

using namespace std;


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

CSommet::CSommet(int iNumero)
{
    iSOMNumero = iNumero;

    uiSOMNbArcsSommetEntrants = 0;
    uiSOMNbArcsSommetSortants = 0;

    ppARCSOMEntrant = nullptr;
    ppARCSOMSortant = nullptr;
}

CSommet::~CSommet()
{
    
    unsigned int uiboucle;
    if (ppARCSOMEntrant != nullptr) {
        for (uiboucle = 0; uiboucle < SOMLireNbArcsEntrants(); uiboucle++) {
            delete[] ppARCSOMEntrant[uiboucle];
        }
        delete ppARCSOMEntrant;
        ppARCSOMEntrant = nullptr;
    }
        cout << "Del entrant\n";

    if (ppARCSOMSortant != nullptr) {
        for (uiboucle = 0; uiboucle < SOMLireNbArcsSortants(); uiboucle++) {
            delete[] ppARCSOMSortant[uiboucle];
        }
        delete ppARCSOMSortant;
        ppARCSOMSortant = nullptr;
        cout << "Del sortant\n";
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
	ppARCSOMEntrant = (CArc**)realloc(ppARCSOMEntrant, (SOMLireNbArcsEntrants() + 1) * sizeof(CArc *));
	ppARCSOMEntrant[SOMLireNbArcsEntrants()] = pARCArc;
	uiSOMNbArcsSommetEntrants++;

}

void CSommet::SOMSupprimerArcEntrant(CArc* pARCArc)
{
    unsigned int uiboucle, uiArcTrouve = 0;

	for (uiboucle = 0; uiboucle < SOMLireNbArcsEntrants() - 1; uiboucle++) {
		if (SOMLireArcsEntrants()[uiboucle] == pARCArc) {
			uiArcTrouve = 1;
		}
		ppARCSOMEntrant[uiboucle] = ppARCSOMEntrant[uiboucle + uiArcTrouve];
	}

	ppARCSOMEntrant = (CArc **)realloc(ppARCSOMEntrant, (SOMLireNbArcsEntrants() - 1) * sizeof(CArc*));
	uiSOMNbArcsSommetEntrants--;
    
}

void CSommet::SOMAjouterArcSortant(CArc* pARCArc)
{
	ppARCSOMSortant = (CArc**)realloc(ppARCSOMSortant, (SOMLireNbArcsSortants() + 1) * sizeof(CArc *));
	ppARCSOMSortant[SOMLireNbArcsSortants()] = pARCArc;
	uiSOMNbArcsSommetSortants++;
}

void CSommet::SOMSupprimerArcSortant(CArc* pARCArc)
{
	unsigned int uiboucle, uiArcTrouve = 0;

	for (uiboucle = 0; uiboucle < SOMLireNbArcsSortants() - 1; uiboucle++) {
		if (SOMLireArcsSortants()[uiboucle] == pARCArc) {
			uiArcTrouve = 1;
		}
		ppARCSOMSortant[uiboucle] = ppARCSOMSortant[uiboucle + uiArcTrouve];
	}

	ppARCSOMSortant = (CArc **)realloc(ppARCSOMSortant, (SOMLireNbArcsSortants() - 1) * sizeof(CArc*));
	uiSOMNbArcsSommetSortants--;
}

CArc* CSommet::SOMRechercheArc(int iDestination, int iParam)
{
    unsigned int uiboucle;

    if (iParam == entrant) {
        for (uiboucle = 0; uiboucle < SOMLireNbArcsEntrants(); uiboucle++) {
            if (SOMLireArcsEntrants()[uiboucle]->ARCLireDestination() == iDestination) {
                return SOMLireArcsEntrants()[uiboucle];
            }
        }
    }
    else if (iParam == sortant) {
        for (uiboucle = 0; uiboucle < SOMLireNbArcsSortants(); uiboucle++) {
            if (SOMLireArcsSortants()[uiboucle]->ARCLireDestination() == iDestination) {
                return SOMLireArcsSortants()[uiboucle];
            }
        }
    }
    else {
        return nullptr;
    }
}
