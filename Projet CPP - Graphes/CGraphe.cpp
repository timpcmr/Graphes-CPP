#pragma once

#include "CGraphe.h"
#include "CSommet.h"

CGraphe::CGraphe()
{
	pSOMGRAListeSommet = new CSommet();
	uiGRANbArcs = 0;
	uiGRANbSommet = 0;
	bGRAOriente = true;
}

CGraphe::CGraphe(unsigned int uiNbSommet)
{
	uiGRANbArcs = uiNbSommet;
	uiGRANbSommet = 0;
	bGRAOriente = true;

	pSOMGRAListeSommet = new CSommet[uiGRANbSommet];
}


CSommet* CGraphe::GRALireSommets()
{
	return pSOMGRAListeSommet;
}

unsigned int CGraphe::GRALireNbSommet()
{
	return uiGRANbSommet;
}

unsigned int CGraphe::GRALireNbArcs()
{
	return uiGRANbArcs;
}

bool CGraphe::GRALireType()
{
	return bGRAOriente;
}

void CGraphe::GRAAjouterArc(CSommet& SOMDepart, CSommet& SOMArrivee)
{
	CArc * pARCNouvelArc = new CArc(SOMArrivee);
	SOMDepart.SOMAjouterArcSortant(pARCNouvelArc);
	SOMArrivee.SOMAjouterArcEntrant(pARCNouvelArc);
	uiGRANbArcs++;
}

void CGraphe::GRASupprimerArc(CArc* pARCParam)
{
	CSommet SOMEntrant = GRARechercheArc(pARCParam, entrant);
	CSommet SOMSortant = GRARechercheArc(pARCParam, sortant);

	SOMEntrant.SOMSupprimerArcEntrant(pARCParam);
	SOMSortant.SOMSupprimerArcSortant(pARCParam);

	delete[] pARCParam;
	uiGRANbArcs--;
}

void CGraphe::GRAAjouterSommet(CSommet& SOMSommet)
{
	unsigned int uiboucle;

	//Initialisation du nouveau tableau de sommets
	CSommet* pSOMTemp = new CSommet[GRALireNbSommet() + 1];

	//Copie des sommets dans le nouveu tableau + ajout du sommet a ajouter
	for (uiboucle = 0; uiboucle < GRALireNbSommet() + 1; uiboucle++) {
		if (uiboucle == GRALireNbSommet()) {
			pSOMTemp[uiboucle] = SOMSommet;
		}
		else {
			pSOMTemp[uiboucle] = GRALireSommets()[uiboucle];
		}
	}

	//Deletion de l'ancien tableau de sommets
	delete[] pSOMGRAListeSommet;

	//Affectation de nouvelles valeurs
	uiGRANbSommet++;
	pSOMGRAListeSommet = pSOMTemp;

}

CSommet& CGraphe::GRARechercheArc(CArc* pARCParam, int iParam)
{
	unsigned int uiboucle, uiboucle2;
	if (iParam == entrant) {
		for (uiboucle = 0; uiboucle < GRALireNbSommet(); uiboucle++) {
			for (uiboucle2 = 0; uiboucle < GRALireSommets()[uiboucle].SOMLireNbArcsEntrants(); uiboucle2++) {
				if (GRALireSommets()[uiboucle].SOMLireArcsEntrants()[uiboucle2] == pARCParam) {
					return GRALireSommets()[uiboucle];
				}
			}
		}
	}
	else if (iParam == sortant) {
		for (uiboucle = 0; uiboucle < GRALireNbSommet(); uiboucle++) {
			for (uiboucle2 = 0; uiboucle < GRALireSommets()[uiboucle].SOMLireNbArcsSortants(); uiboucle2++) {
				if (GRALireSommets()[uiboucle].SOMLireArcsSortants()[uiboucle2] == pARCParam) {
					return GRALireSommets()[uiboucle];
				}
			}
		}
	}
	else {
		throw CException(EXCAucunParamRecherche);
	}
}

CSommet& CGraphe::GRARechercheSommet(int iVal)
{
	unsigned int uiboucle;
	for (uiboucle = 0; uiboucle < GRALireNbSommet(); uiboucle++) {
		if (GRALireSommets()[uiboucle].SOMLireNumero() == iVal) {
			return GRALireSommets()[uiboucle];
		}
	}
	throw CException(EXCValeurSommetIntrouvable);
}