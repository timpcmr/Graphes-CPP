#pragma once

#pragma warning(disable : 6308)

#include "CGraphe.h"
#include "CSommet.h"

using namespace std;

CGraphe::CGraphe()
{
	uiGRANbArcs = 0;
	uiGRANbSommet = 0;
	bGRAOriente = true;
	pSOMGRAListeSommet = nullptr;
}

CGraphe::~CGraphe()
{
	unsigned int uiboucle;
	/*
	for (uiboucle = 0; uiboucle < uiGRANbSommet; uiboucle++) {
		delete pSOMGRAListeSommet[uiboucle];
	}
	*/
	delete[] pSOMGRAListeSommet;
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
	CArc * pARCNouvelArc = new CArc(SOMArrivee.SOMLireNumero());
	SOMDepart.SOMAjouterArcSortant(pARCNouvelArc);
	SOMArrivee.SOMAjouterArcEntrant(pARCNouvelArc);
	uiGRANbArcs++;
}

void CGraphe::GRAAjouterArc(int iDepart, int iArrivee)
{
	CArc* pARCNouvelArc = new CArc(iArrivee);
	GRARechercheSommet(iDepart).SOMAjouterArcSortant(pARCNouvelArc);
	GRARechercheSommet(iArrivee).SOMAjouterArcEntrant(pARCNouvelArc);
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
	int iNum;
	unsigned int uiBoucle;
	char pcEntree[1024];
	pSOMGRAListeSommet = (CSommet *)realloc(pSOMGRAListeSommet, (GRALireNbSommet() + 1) * sizeof(CSommet));
	while (!GRANumeroSommetUnique(SOMSommet.SOMLireNumero())) {
		cout << "Les numeros de sommets utilises sont :" << endl;
		for (uiBoucle = 0; uiBoucle < GRALireNbSommet(); uiBoucle++) {
			cout << GRALireSommets()[uiBoucle].SOMLireNumero() << "  ";
		}
		cout << endl;
		cin >> pcEntree;
		iNum = atoi(pcEntree);
		SOMSommet.SOMModifierNumero(iNum);
	}
	pSOMGRAListeSommet[GRALireNbSommet()] = SOMSommet;

	uiGRANbSommet++;
}

void CGraphe::GRAAjouterSommet(int iNum)
{
	unsigned int uiBoucle;
	char pcEntree[1024];
	CSommet SOMSommet(iNum);
	pSOMGRAListeSommet = (CSommet*)realloc(pSOMGRAListeSommet, (GRALireNbSommet() + 1) * sizeof(CSommet));
	while (!GRANumeroSommetUnique(SOMSommet.SOMLireNumero())) {
		cout << "Les numeros de sommets utilises sont :" << endl;
		for (uiBoucle = 0; uiBoucle < GRALireNbSommet(); uiBoucle++) {
			cout << GRALireSommets()[uiBoucle].SOMLireNumero() << "  ";
		}
		cout << endl;
		cin >> pcEntree;
		iNum = atoi(pcEntree);
		SOMSommet.SOMModifierNumero(iNum);
	}
	pSOMGRAListeSommet[GRALireNbSommet()] = SOMSommet;

	uiGRANbSommet++;
}

void CGraphe::GRASupprimerSommet(CSommet& SOMSommet)
{
	int NumeroSommetDestination;
	unsigned int uiboucle1, uiboucle2, uiSommetTrouve = 0;

	//Suppression des arcs sortants du tableau des arcs entrants des sommets pointes
	for (uiboucle1 = 0; uiboucle1 < SOMSommet.SOMLireNbArcsSortants(); uiboucle1++) {
		NumeroSommetDestination = SOMSommet.SOMLireArcsSortants()[uiboucle1]->ARCLireDestination();
		GRARechercheSommet(NumeroSommetDestination).SOMSupprimerArcEntrant(SOMSommet.SOMLireArcsSortants()[uiboucle1]);
	}

	//Suppression des arcs entrants des tableaux des arcs sortants qui pointent sur SOMSommet
	for (uiboucle1 = 0; uiboucle1 < GRALireNbSommet(); uiboucle1++) {
		for (uiboucle2 = 0; uiboucle2 < GRALireSommets()[uiboucle1].SOMLireNbArcsSortants(); uiboucle2++) {
			if (GRALireSommets()[uiboucle1].SOMLireArcsSortants()[uiboucle2]->ARCLireDestination() == SOMSommet.SOMLireNumero()) {
				GRALireSommets()[uiboucle1].SOMSupprimerArcSortant(GRALireSommets()[uiboucle1].SOMLireArcsSortants()[uiboucle2]);
			}
		}
	}

	for (uiboucle1 = 0; uiboucle1 < GRALireNbSommet() - 1; uiboucle1++) {
		if (GRALireSommets()[uiboucle1].SOMLireNumero() == SOMSommet.SOMLireNumero()) {
			uiSommetTrouve = 1;
		}
		pSOMGRAListeSommet[uiboucle1] = pSOMGRAListeSommet[uiboucle1 + uiSommetTrouve];
	}

	pSOMGRAListeSommet = (CSommet *)realloc(pSOMGRAListeSommet, (GRALireNbSommet() - 1) * sizeof(CSommet));

	uiGRANbSommet--;
	//Suppression du sommet
	SOMSommet.~CSommet();
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

bool CGraphe::GRANumeroSommetUnique(int iVal)
{
	unsigned int uiboucle;

	for (uiboucle = 0; uiboucle < GRALireNbSommet(); uiboucle++) {
		if (GRALireSommets()[uiboucle].SOMLireNumero() == iVal) {
			return false;
		}
	}
	return true;
}

void CGraphe::GRAAffichage()
{
	if (pSOMGRAListeSommet == nullptr) {
		throw CException(EXCListeSommetInexistante);
	}
	unsigned int uiboucleSommet;
	unsigned int uiboucleArc;

	if (bGRAOriente == true) {
		cout << "Type de Graphe : Oriente" << endl;
		for (uiboucleSommet = 0; uiboucleSommet < uiGRANbSommet; uiboucleSommet++) {
			cout << "Sommet " << GRALireSommets()[uiboucleSommet].SOMLireNumero() << " : " << endl;
			for (uiboucleArc = 0; uiboucleArc < GRALireSommets()[uiboucleSommet].SOMLireNbArcsSortants(); uiboucleArc++) {
				cout << "--> " << GRALireSommets()[uiboucleSommet].SOMLireArcsSortants()[uiboucleArc]->ARCLireDestination() << endl;
			}
			cout << "\n";
		}
	}
	else {
		cout << "Type de Graphe : Non-Oriente" << endl;
		cout << "Affichage a faire" << endl;
	}
}
