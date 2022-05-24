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
	ppSOMGRAListeSommet = nullptr;
}

CGraphe::CGraphe(CGraphe& GRAGraphe)
{
	unsigned int uiboucle;

	uiGRANbArcs = GRAGraphe.GRALireNbArcs();
	uiGRANbSommet = GRAGraphe.GRALireNbSommet();
	bGRAOriente = GRAGraphe.GRALireType();

	ppSOMGRAListeSommet = new CSommet * [GRAGraphe.GRALireNbSommet()];
	for (uiboucle = 0; uiboucle < GRAGraphe.GRALireNbSommet(); uiboucle++) {
		ppSOMGRAListeSommet[uiboucle] = new CSommet(*GRAGraphe.GRALireSommets()[uiboucle]);
	}
}

CGraphe::~CGraphe()
{
	unsigned int uiboucle;
	if (ppSOMGRAListeSommet != nullptr) {
		for (uiboucle = 0; uiboucle < uiGRANbSommet; uiboucle++) {
			delete ppSOMGRAListeSommet[uiboucle];
			ppSOMGRAListeSommet[uiboucle] = nullptr;
			}
		delete[] ppSOMGRAListeSommet;
		ppSOMGRAListeSommet = nullptr;
	}
	
}

CSommet** CGraphe::GRALireSommets()
{
	return ppSOMGRAListeSommet;
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

void CGraphe::GRAAjouterArc(CSommet* SOMDepart, CSommet* SOMArrivee)
{
	CArc * pARCNouvelArc = new CArc(SOMArrivee->SOMLireNumero());
	SOMDepart->SOMAjouterArcSortant(pARCNouvelArc);
	SOMArrivee->SOMAjouterArcEntrant(pARCNouvelArc);
	delete pARCNouvelArc;
	uiGRANbArcs++;
}

void CGraphe::GRAAjouterArc(int iDepart, int iArrivee)
{
	CArc* pARCNouvelArc = new CArc(iArrivee);
	GRARechercheSommet(iDepart)->SOMAjouterArcSortant(pARCNouvelArc);
	GRARechercheSommet(iArrivee)->SOMAjouterArcEntrant(pARCNouvelArc);
	delete pARCNouvelArc;
	uiGRANbArcs++;
}

void CGraphe::GRASupprimerArc(CArc* pARCParam)
{
	CSommet* SOMEntrant = nullptr, * SOMSortant = nullptr;
	try {
		SOMEntrant = GRARechercheSommetAvecArc(pARCParam, entrant);
		SOMSortant = GRARechercheSommetAvecArc(pARCParam, sortant);
	}
	catch (CException EXCException) {
		if (EXCException.EXCLireErreur() == EXCSuppImpossible) {
			cout << "Erreur : Suppression d'arc Impossible : La liste des arcs est vide !" << endl;
			throw CException(EXCArretProgramme);
		}
	}


	SOMEntrant->SOMSupprimerArcEntrant(pARCParam);
	SOMSortant->SOMSupprimerArcSortant(pARCParam);

	delete pARCParam;
	uiGRANbArcs--;
}

void CGraphe::GRAAjouterSommet(CSommet& SOMSommet)
{
	int iNum;
	unsigned int uiBoucle;
	char pcEntree[1024];

	while (!GRANumeroSommetUnique(SOMSommet.SOMLireNumero())) {
		cout << "Les numeros de sommets utilises sont :" << endl;
		for (uiBoucle = 0; uiBoucle < GRALireNbSommet(); uiBoucle++) {
			cout << GRALireSommets()[uiBoucle]->SOMLireNumero() << "  ";
		}
		cout << endl;
		cin >> pcEntree;
		iNum = atoi(pcEntree);
		SOMSommet.SOMModifierNumero(iNum);
		}

	CSommet** ppSOMGRAListeSommetTMP = new CSommet * [uiGRANbSommet + 1];
	for (uiBoucle = 0; uiBoucle < uiGRANbSommet + 1; uiBoucle++) {
		if (uiBoucle < uiGRANbSommet) {
			ppSOMGRAListeSommetTMP[uiBoucle] = new CSommet(*ppSOMGRAListeSommet[uiBoucle]);
		}
		else {
			ppSOMGRAListeSommetTMP[uiBoucle] = new CSommet(SOMSommet);
		}
	}

	for (uiBoucle = 0; uiBoucle < uiGRANbSommet; uiBoucle++) {
		delete ppSOMGRAListeSommet[uiBoucle];
	}
	delete[] ppSOMGRAListeSommet;
	
	ppSOMGRAListeSommet = ppSOMGRAListeSommetTMP;

	uiGRANbSommet++;
}

void CGraphe::GRAAjouterSommet(int iNum)
{
	unsigned int uiBoucle;
	char pcEntree[1024];
	CSommet* pSOMSommet = new CSommet(iNum);
	
	while (!GRANumeroSommetUnique(pSOMSommet->SOMLireNumero())) {
		cout << "Les numeros de sommets utilises sont :" << endl;
		for (uiBoucle = 0; uiBoucle < GRALireNbSommet(); uiBoucle++) {
			cout << GRALireSommets()[uiBoucle]->SOMLireNumero() << "  ";
		}
		cout << endl;
		cin >> pcEntree;
		iNum = atoi(pcEntree);
		pSOMSommet->SOMModifierNumero(iNum);
	}

	CSommet** ppSOMGRAListeSommetTMP = new CSommet * [uiGRANbSommet + 1];
	for (uiBoucle = 0; uiBoucle < uiGRANbSommet + 1; uiBoucle++) {
		if (uiBoucle < uiGRANbSommet) {
			ppSOMGRAListeSommetTMP[uiBoucle] = new CSommet(*ppSOMGRAListeSommet[uiBoucle]);
		}
		else {
			ppSOMGRAListeSommetTMP[uiBoucle] = new CSommet(*pSOMSommet);
		}
	}

	for (uiBoucle = 0; uiBoucle < uiGRANbSommet; uiBoucle++) {
		delete ppSOMGRAListeSommet[uiBoucle];
	}
	delete[] ppSOMGRAListeSommet;
	delete pSOMSommet;

	ppSOMGRAListeSommet = ppSOMGRAListeSommetTMP;

	uiGRANbSommet++;
}

void CGraphe::GRASupprimerSommet(int iNumSommet)
{
	unsigned int uiboucle, uiSommetTrouve = 0;
	int iNumeroSommetDestination;
	CArc* pARCArcASupprimer;

	for (uiboucle = 0; uiboucle < GRARechercheSommet(iNumSommet)->SOMLireNbArcsEntrants(); uiboucle++) {
		iNumeroSommetDestination = GRARechercheSommet(iNumSommet)->SOMLireArcsEntrants()[uiboucle]->ARCLireDestination();
		pARCArcASupprimer = GRARechercheSommet(iNumeroSommetDestination)->SOMRechercheArc(iNumSommet, entrant);

		GRARechercheSommet(iNumeroSommetDestination)->SOMSupprimerArcSortant(pARCArcASupprimer);
		GRARechercheSommet(iNumSommet)->SOMSupprimerArcEntrant(pARCArcASupprimer);
	}

	for (uiboucle = 0; uiboucle < GRARechercheSommet(iNumSommet)->SOMLireNbArcsSortants(); uiboucle++) {
		iNumeroSommetDestination = GRARechercheSommet(iNumSommet)->SOMLireArcsSortants()[uiboucle]->ARCLireDestination();
		pARCArcASupprimer = GRARechercheSommet(iNumeroSommetDestination)->SOMRechercheArc(iNumSommet, entrant);

		GRARechercheSommet(iNumeroSommetDestination)->SOMSupprimerArcEntrant(pARCArcASupprimer);
		GRARechercheSommet(iNumSommet)->SOMSupprimerArcSortant(pARCArcASupprimer);
	}


	for (uiboucle = 0; uiboucle < GRALireNbSommet() - 1; uiboucle++) {
		if (GRALireSommets()[uiboucle]->SOMLireNumero() == iNumSommet) {
			uiSommetTrouve = 1;
			delete ppSOMGRAListeSommet[uiboucle];
		}

		ppSOMGRAListeSommet[uiboucle] = ppSOMGRAListeSommet[uiboucle + uiSommetTrouve];
	}

	CSommet** ppSOMGRAListeSommetTMP = new CSommet * [uiGRANbSommet - 1];
	for (uiboucle = 0; uiboucle < uiGRANbSommet - 1; uiboucle++) {
		ppSOMGRAListeSommetTMP[uiboucle] = new CSommet(*ppSOMGRAListeSommet[uiboucle]);
	}


	for (uiboucle = 0; uiboucle < uiGRANbSommet; uiboucle++) {
		delete ppSOMGRAListeSommet[uiboucle];
		ppSOMGRAListeSommet[uiboucle] = nullptr;
	}
	delete[] ppSOMGRAListeSommet;


	uiGRANbSommet--;

}

void CGraphe::GRAModifierType(bool bParam)
{
	bGRAOriente = bParam;
}

CSommet* CGraphe::GRARechercheSommetAvecArc(CArc* pARCParam, int iParam)
{
	unsigned int uiboucle, uiboucle2;
	if (iParam == entrant) {
		for (uiboucle = 0; uiboucle < GRALireNbSommet(); uiboucle++) {
			for (uiboucle2 = 0; uiboucle < GRALireSommets()[uiboucle]->SOMLireNbArcsEntrants(); uiboucle2++) {
				if (GRALireSommets()[uiboucle]->SOMLireArcsEntrants()[uiboucle2] == pARCParam) {
					return GRALireSommets()[uiboucle];
				}
			}
		}
	}
	else if (iParam == sortant) {
		for (uiboucle = 0; uiboucle < GRALireNbSommet(); uiboucle++) {
			for (uiboucle2 = 0; uiboucle < GRALireSommets()[uiboucle]->SOMLireNbArcsSortants(); uiboucle2++) {
				if (GRALireSommets()[uiboucle]->SOMLireArcsSortants()[uiboucle2] == pARCParam) {
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

CSommet* CGraphe::GRARechercheSommet(int iVal)
{
	unsigned int uiboucle;
	for (uiboucle = 0; uiboucle < GRALireNbSommet(); uiboucle++) {
		if (GRALireSommets()[uiboucle]->SOMLireNumero() == iVal) {
			return GRALireSommets()[uiboucle];
		}
	}
	return nullptr;
}

int CGraphe::GRARechercheIndexSommet(int iSommet)
{
	unsigned int uiboucle;

	for (uiboucle = 0; uiboucle < GRALireNbSommet(); uiboucle++) {
		if (GRALireSommets()[uiboucle]->SOMLireNumero() == iSommet) {
			return (int)uiboucle;
		}
	}
	return -1;
}

bool CGraphe::GRANumeroSommetUnique(int iVal)
{
	unsigned int uiboucle;

	for (uiboucle = 0; uiboucle < GRALireNbSommet(); uiboucle++) {
		if (GRALireSommets()[uiboucle]->SOMLireNumero() == iVal) {
			return false;
		}
	}
	return true;
}

void CGraphe::GRAAffichage()
{
	if (ppSOMGRAListeSommet == nullptr) {
		throw CException(EXCListeSommetInexistante);
	}
	unsigned int uiboucleSommet;
	unsigned int uiboucleArc;

	if (bGRAOriente == true) {
		cout << "Type de Graphe : Oriente" << endl;
		for (uiboucleSommet = 0; uiboucleSommet < uiGRANbSommet; uiboucleSommet++) {
			cout << "Sommet " << GRALireSommets()[uiboucleSommet]->SOMLireNumero() << " : " << endl;
			for (uiboucleArc = 0; uiboucleArc < GRALireSommets()[uiboucleSommet]->SOMLireNbArcsSortants(); uiboucleArc++) {
				cout << "--> " << GRALireSommets()[uiboucleSommet]->SOMLireArcsSortants()[uiboucleArc]->ARCLireDestination() << endl;
			}
			cout << endl;
		}
	}
	else {
		cout << "Type de Graphe : Non-Oriente" << endl;
		for (uiboucleSommet = 0; uiboucleSommet < uiGRANbSommet; uiboucleSommet++) {
			cout << "Sommet " << GRALireSommets()[uiboucleSommet]->SOMLireNumero() << " : " << endl;
			for (uiboucleArc = 0; uiboucleArc < GRALireSommets()[uiboucleSommet]->SOMLireNbArcsSortants(); uiboucleArc++) {
				cout << "<--> " << GRALireSommets()[uiboucleSommet]->SOMLireArcsSortants()[uiboucleArc]->ARCLireDestination() << endl;
			}
			cout << endl;
		}
	}
}

CGraphe* CGraphe::GRAInversion()
{
	CGraphe* pGRARetour = new CGraphe();
	unsigned int uiboucle, uiboucle2;
	for (uiboucle = 0; uiboucle < GRALireNbSommet(); uiboucle++) {
		pGRARetour->GRAAjouterSommet(GRALireSommets()[uiboucle]->SOMLireNumero());
	}

	for (uiboucle = 0; uiboucle < GRALireNbSommet(); uiboucle++) {
		for (uiboucle2 = 0; uiboucle2 < GRALireSommets()[uiboucle]->SOMLireNbArcsSortants(); uiboucle2++) {
			pGRARetour->GRAAjouterArc(GRALireSommets()[uiboucle]->SOMLireArcsSortants()[uiboucle2]->ARCLireDestination(), GRALireSommets()[uiboucle]->SOMLireNumero());
		}
	}
	return pGRARetour;
}

CGraphe* CGraphe::GRANonOriente()
{
	CGraphe* pGRAGrapheRetour = new CGraphe();
	unsigned int uiboucle, uiboucle2;
	pGRAGrapheRetour->GRAModifierType(false);

	for (uiboucle = 0; uiboucle < GRALireNbSommet(); uiboucle++) {
		pGRAGrapheRetour->GRAAjouterSommet(GRALireSommets()[uiboucle]->SOMLireNumero());
	}
	for (uiboucle = 0; uiboucle < GRALireNbSommet(); uiboucle++) {
		for (uiboucle2 = 0; uiboucle2 < GRALireSommets()[uiboucle]->SOMLireNbArcsSortants(); uiboucle2++) {
			pGRAGrapheRetour->GRAAjouterArc(GRALireSommets()[uiboucle]->SOMLireNumero(), GRALireSommets()[uiboucle]->SOMLireArcsSortants()[uiboucle2]->ARCLireDestination());
			pGRAGrapheRetour->GRAAjouterArc(GRALireSommets()[uiboucle]->SOMLireArcsSortants()[uiboucle2]->ARCLireDestination(), GRALireSommets()[uiboucle]->SOMLireNumero());
		}
	}
	
	return pGRAGrapheRetour;
}
