#pragma once

#include "CGraphe.h"
#include "CSommet.h"

using namespace std;

CGraphe::CGraphe()
{
	pSOMGRAListeSommet = new CSommet();
	uiGRANbArcs = 0;
	uiGRANbSommet = 0;
	bGRAOriente = true;
}

CGraphe::~CGraphe()
{
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
	CArc * pARCNouvelArc = new CArc(&SOMArrivee);
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
	pSOMGRAListeSommet = (CSommet *)realloc(pSOMGRAListeSommet, (GRALireNbSommet() + 1) * sizeof(CSommet));
	pSOMGRAListeSommet[GRALireNbSommet()] = SOMSommet;

	uiGRANbSommet++;
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
	return GRALireSommets()[0];
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

void CGraphe::GRAAffichage()
{
	if (pSOMGRAListeSommet == nullptr) {
		throw CException(EXCListeSommetInexistante);
	}
	unsigned int uiboucleSommet;
	unsigned int uiboucleArc;
	if (bGRAOriente == true) {
		for (uiboucleSommet = 0; uiboucleSommet < uiGRANbSommet; uiboucleSommet++) {
			cout << "Sommet " << uiboucleSommet << " : " << endl;
			for (uiboucleArc = 0; uiboucleArc < GRALireSommets()[uiboucleSommet].SOMLireNbArcsSortants(); uiboucleArc++) {
				cout << "--> " << GRALireSommets()[uiboucleSommet].SOMLireArcsSortants()[uiboucleArc]->ARCLireDestination()->SOMLireNumero() << endl;
			}
			cout << "\n";
		}
	}
	else {
		for (uiboucleSommet = 0; uiboucleSommet < uiGRANbSommet; uiboucleSommet++) {
			cout << "Sommet " << uiboucleSommet << " : " << endl;
			for (uiboucleArc = 0; uiboucleArc < GRALireSommets()[uiboucleSommet].SOMLireNbArcsSortants(); uiboucleArc++) {
				cout << "<--> " << GRALireSommets()[uiboucleSommet].SOMLireArcsSortants()[uiboucleArc]->ARCLireDestination()->SOMLireNumero() << endl;
			}
			cout << "\n";
		}
	}
}
