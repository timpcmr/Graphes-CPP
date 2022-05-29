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

CGraphe::CGraphe(const CGraphe& GRAGraphe)
{
	unsigned int uiboucle;

	uiGRANbArcs = GRAGraphe.GRALireNbArcs();
	uiGRANbSommet = GRAGraphe.GRALireNbSommet();
	bGRAOriente = GRAGraphe.GRALireType();

	//Allocation de la liste de sommets
	ppSOMGRAListeSommet = new CSommet * [GRAGraphe.GRALireNbSommet()];
	for (uiboucle = 0; uiboucle < GRAGraphe.GRALireNbSommet(); uiboucle++) {
		ppSOMGRAListeSommet[uiboucle] = new CSommet(*GRAGraphe.GRALireSommets()[uiboucle]);
	}
}

CGraphe::~CGraphe()
{
	unsigned int uiboucle;
	
	//Libération de la mémoire allouée pour la liste de sommets
	if (ppSOMGRAListeSommet != nullptr) {
		for (uiboucle = 0; uiboucle < uiGRANbSommet; uiboucle++) {
			delete ppSOMGRAListeSommet[uiboucle];
			ppSOMGRAListeSommet[uiboucle] = nullptr;
			}
		delete[] ppSOMGRAListeSommet;
		ppSOMGRAListeSommet = nullptr;
	}
	
}

const CSommet* const* CGraphe::GRALireSommets() const
{
	return ppSOMGRAListeSommet;
}

unsigned int CGraphe::GRALireNbSommet() const
{
	return uiGRANbSommet;
}

unsigned int CGraphe::GRALireNbArcs() const
{
	return uiGRANbArcs;
}

bool CGraphe::GRALireType() const
{
	return bGRAOriente;
}

void CGraphe::GRAAjouterArc(CSommet* pSOMDepart, CSommet* pSOMArrivee)
{
	if (pSOMDepart == nullptr || pSOMArrivee == nullptr) {
		throw CException(EXCPointeurSommetNul);
	}
	
	//Création d'arcs entre les deux sommets sur base du nuéro de sommet à relier
	CArc * pARCNouvelArcE = new CArc(pSOMDepart->SOMLireNumero());
	CArc * pARCNouvelArcS = new CArc(pSOMArrivee->SOMLireNumero());
	try {
		pSOMDepart->SOMAjouterArcSortant(pARCNouvelArcS);
		pSOMArrivee->SOMAjouterArcEntrant(pARCNouvelArcE);
	}
	catch (CException EXCException) {
		if (EXCException.EXCLireErreur() == EXCPointeurArcNul) {
			cout << "Erreur interne (GRAAjouterArc) : Le pointeur d'arc est nul !" << endl;
		}
		throw CException(EXCArretProgramme);
	}
	
	delete pARCNouvelArcE;
	delete pARCNouvelArcS;
	uiGRANbArcs++;
}

void CGraphe::GRAAjouterArc(int iDepart, int iArrivee)
{
	//Création d'arcs entre les deux sommets sur base du nuéro de sommet à relier
	CArc* pARCNouvelArcE = new CArc(iDepart);
	CArc* pARCNouvelArcS = new CArc(iArrivee);
	
	CSommet* pSOMDepart = nullptr, * pSOMArrivee = nullptr;
	
	//Obtention des pointeurs de sommets (+vérification de leur existence)
	pSOMDepart = GRARechercheSommet(iDepart);
	pSOMArrivee = GRARechercheSommet(iArrivee);
	
	if(pSOMDepart == nullptr || pSOMArrivee == nullptr) {
		throw CException(EXCPointeurSommetNul);
	}
	try {
		pSOMDepart->SOMAjouterArcSortant(pARCNouvelArcS);
		pSOMArrivee->SOMAjouterArcEntrant(pARCNouvelArcE);
	}
	catch (CException EXCException) {
		if (EXCException.EXCLireErreur() == EXCPointeurArcNul) {
			cout << "Erreur interne (GRAAjouterArc) : Le pointeur d'arc est nul !" << endl;
		}
		throw CException(EXCArretProgramme);
	}
	delete pARCNouvelArcE;
	delete pARCNouvelArcS;
	uiGRANbArcs++;
}

void CGraphe::GRASupprimerArc(int iDepart, int iArrivee)
{
	CSommet* pSOMDepart = nullptr, * pSOMArrivee = nullptr;

	//Obtention des pointeurs de sommets (+vérification de leur existence)
	pSOMDepart = GRARechercheSommet(iDepart);
	if (pSOMDepart == nullptr) {
		throw CException(EXCValeurSommetIntrouvable);
	}
	pSOMArrivee = GRARechercheSommet(iArrivee);
	if (pSOMArrivee == nullptr) {
		throw CException(EXCValeurSommetIntrouvable);
	}

	try {
		pSOMDepart->SOMSupprimerArcEntrant((CArc*)pSOMDepart->SOMRechercheArc(iArrivee, sortant));
		pSOMArrivee->SOMSupprimerArcSortant((CArc*)pSOMArrivee->SOMRechercheArc(iDepart, entrant));
	}
	catch (CException EXCException) {
		if (EXCException.EXCLireErreur() == EXCSuppImpossible) {
			cout << "Erreur : Suppression d'arc Impossible : La liste des arcs est vide !" << endl;
			throw CException(EXCArretProgramme);
		}
		if (EXCException.EXCLireErreur() == EXCPointeurArcNul) {
			cout << "Erreur : Suppression d'arc Impossible : L'arc n'existe pas !" << endl;
			throw CException(EXCArretProgramme);
		}
	}

	uiGRANbArcs--;
}

void CGraphe::GRAAjouterSommet(CSommet& SOMSommet)
{
	int iNum;
	unsigned int uiBoucle;
	char pcEntree[1024];

	//Vérification de l'unicité du numéro de sommet et changement de la valeur si besoin
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

	//Equivalent de realloc pour les sommets en passant par un tableau temporaire pour la copie des valeurs
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
	
	//Verificvation unicité du numéro de sommet et changement si besoin
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

	//Equivalent de realloc pour la liste des sommets en passant par un tableau temporaire pour la copie des valeurs
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

void CGraphe::GRASupprimerSommet(CSommet* pSOMParam)
{
	unsigned int uiboucle, uiSommetTrouve = 0;

	for (uiboucle = 0; uiboucle < pSOMParam->SOMLireNbArcsEntrants(); uiboucle++) {

		//Suppression de l'arc dans le sommet antérieur
		CSommet* pSOMSommetPrecedent;
		try {
			pSOMSommetPrecedent = (CSommet*)GRARechercheSommet(pSOMParam->SOMLireArcsEntrants()[uiboucle]->ARCLireDestination());
			if (pSOMSommetPrecedent == nullptr) {
				throw  CException(EXCValeurSommetIntrouvable);
			}
			pSOMSommetPrecedent->SOMSupprimerArcSortant((CArc*)pSOMSommetPrecedent->SOMRechercheArc(pSOMParam->SOMLireNumero(), sortant));
		}
		catch (CException EXCException) {
			if (EXCException.EXCLireErreur() == EXCValeurSommetIntrouvable) {
				cout << "Erreur : Suppression du sommet impossible : Le sommet n'existe pas !" << endl;
			}
			if (EXCException.EXCLireErreur() == EXCPointeurArcNul) {
				cout << "Erreur : Suppression d'arc Impossible : L'arc n'existe pas !" << endl;
			}
			throw CException(EXCArretProgramme);
		}

		//Suppression de l'arc dans le sommet à supprimer
		try {
			pSOMParam->SOMSupprimerArcEntrant((CArc*)pSOMParam->SOMRechercheArc(pSOMSommetPrecedent->SOMLireNumero(), entrant));
		}
		catch (CException EXCException) {
			if (EXCException.EXCLireErreur() == EXCPointeurArcNul) {
				cout << "Erreur : Suppression d'arc Impossible : L'arc n'existe pas !" << endl;
			}
			throw CException(EXCArretProgramme);
		}
		uiGRANbArcs--;
	}

	for (uiboucle = 0; uiboucle < pSOMParam->SOMLireNbArcsSortants(); uiboucle++) {

		//Suppression de l'arc dans le sommet suivant
		CSommet* pSOMSommetSuivant;
		try {
			pSOMSommetSuivant = (CSommet*)GRARechercheSommet(pSOMParam->SOMLireArcsSortants()[uiboucle]->ARCLireDestination());
			if (pSOMSommetSuivant == nullptr) {
				throw  CException(EXCValeurSommetIntrouvable);
			}
			pSOMSommetSuivant->SOMSupprimerArcEntrant((CArc*)pSOMSommetSuivant->SOMRechercheArc(pSOMParam->SOMLireNumero(), entrant));
		}
		catch (CException EXCException) {
			if (EXCException.EXCLireErreur() == EXCValeurSommetIntrouvable) {
				cout << "Erreur : Suppression du sommet impossible : Le sommet n'existe pas !" << endl;
			}
			if (EXCException.EXCLireErreur() == EXCPointeurArcNul) {
				cout << "Erreur : Suppression d'arc Impossible : L'arc n'existe pas !" << endl;
			}
			throw CException(EXCArretProgramme);
		}
		

		//Suppression de l'arc dans le sommet à supprimer
		try {
			pSOMParam->SOMSupprimerArcSortant((CArc*)pSOMParam->SOMRechercheArc(pSOMSommetSuivant->SOMLireNumero(), sortant));
		}
		catch (CException EXCException) {
			if (EXCException.EXCLireErreur() == EXCPointeurArcNul) {
				cout << "Erreur : Suppression d'arc Impossible : L'arc n'existe pas !" << endl;
			}
			throw CException(EXCArretProgramme);
		}
		uiGRANbArcs--;
	}

	//Suppression du sommet dans la liste et realloc par tableau temporaire
	CSommet** ppSOMGRAListeSommetTMP = new CSommet * [uiGRANbSommet - 1];
	for (uiboucle = 0; uiboucle < GRALireNbSommet() - 1; uiboucle++) {
		if (GRALireSommets()[uiboucle]->SOMLireNumero() == pSOMParam->SOMLireNumero()) {
			uiSommetTrouve = 1;
		}
		ppSOMGRAListeSommetTMP[uiboucle] = new CSommet(*ppSOMGRAListeSommet[uiboucle + uiSommetTrouve]);
	}


	for (uiboucle = 0; uiboucle < uiGRANbSommet; uiboucle++) {
		delete ppSOMGRAListeSommet[uiboucle];
		ppSOMGRAListeSommet[uiboucle] = nullptr;
	}
	delete[] ppSOMGRAListeSommet;

	ppSOMGRAListeSommet = ppSOMGRAListeSommetTMP;

	uiGRANbSommet--;

}

void CGraphe::GRAModifierNumSommet(CSommet* pSOMParam, int iNum)
{
	if (pSOMParam == nullptr) {
		throw CException(EXCPointeurSommetNul);
	}
	if (GRANumeroSommetUnique(iNum) == false) {
		throw CException(EXCNumeroIndisponible);
	}
	pSOMParam->SOMModifierNumero(iNum);

}

void CGraphe::GRAModifierType(bool bParam)
{
	bGRAOriente = bParam;
}


CSommet* CGraphe::GRARechercheSommet(int iVal) const
{
	unsigned int uiboucle;
	for (uiboucle = 0; uiboucle < GRALireNbSommet(); uiboucle++) {
		if (GRALireSommets()[uiboucle]->SOMLireNumero() == iVal) {
			return (CSommet*)GRALireSommets()[uiboucle];
		}
	}
	return nullptr;
}

int CGraphe::GRARechercheIndexSommet(int iSommet) const
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

void CGraphe::GRAAffichage() const
{
	if (ppSOMGRAListeSommet == nullptr) {
		throw CException(EXCListeSommetInexistante);
	}
	unsigned int uiboucleSommet;
	unsigned int uiboucleArc;

	if (bGRAOriente == true) {
		cout << "Type de Graphe : Oriente" << endl;
		cout << "Nombre de sommets : " << GRALireNbSommet() << endl;
		cout << "Nombre d'arcs : " << GRALireNbArcs() << endl << endl;
		
		//Lecture des sommets sortants uniquement pour le graphe orienté
		for (uiboucleSommet = 0; uiboucleSommet < uiGRANbSommet; uiboucleSommet++) {
			if (GRALireSommets()[uiboucleSommet]->SOMLireNbArcsSortants() > 0) {
				cout << "Sommet " << GRALireSommets()[uiboucleSommet]->SOMLireNumero() << " : " << endl;
				for (uiboucleArc = 0; uiboucleArc < GRALireSommets()[uiboucleSommet]->SOMLireNbArcsSortants(); uiboucleArc++) {
					cout << "--> " << GRALireSommets()[uiboucleSommet]->SOMLireArcsSortants()[uiboucleArc]->ARCLireDestination() << endl;
				}
				cout << endl;
			}
		}
	}
	else {
		cout << "Type de Graphe : Non-Oriente" << endl;
		cout << "Nombre de sommets : " << GRALireNbSommet() << endl;
		cout << "Nombre d'arcs : " << GRALireNbArcs() << endl << endl;

		//Lecture des sommets sortants et entrants pour le graphe non-orienté
		for (uiboucleSommet = 0; uiboucleSommet < uiGRANbSommet; uiboucleSommet++) {
			cout << "Sommet " << GRALireSommets()[uiboucleSommet]->SOMLireNumero() << " : " << endl;
			if (GRALireSommets()[uiboucleSommet]->SOMLireNbArcsEntrants() > 0) {
				for (uiboucleArc = 0; uiboucleArc < GRALireSommets()[uiboucleSommet]->SOMLireNbArcsEntrants(); uiboucleArc++) {
					cout << "<--> " << GRALireSommets()[uiboucleSommet]->SOMLireArcsEntrants()[uiboucleArc]->ARCLireDestination() << endl;
				}
			}
			if (GRALireSommets()[uiboucleSommet]->SOMLireNbArcsSortants() > 0) {
				for (uiboucleArc = 0; uiboucleArc < GRALireSommets()[uiboucleSommet]->SOMLireNbArcsSortants(); uiboucleArc++) {
					cout << "<--> " << GRALireSommets()[uiboucleSommet]->SOMLireArcsSortants()[uiboucleArc]->ARCLireDestination() << endl;
				}
			}
			cout << endl;
		}
	}
}

CGraphe& CGraphe::operator=(const CGraphe &GRAparam)
{
	unsigned int uiboucle;
	bGRAOriente = GRAparam.GRALireType();

	//Copie par duplication des objets
	CSommet** ppSOMGRAListeSommetTMP = new CSommet * [GRAparam.GRALireNbSommet()];
	for (uiboucle = 0; uiboucle < GRAparam.GRALireNbSommet(); uiboucle++) {
		ppSOMGRAListeSommetTMP[uiboucle] = new CSommet(*GRAparam.GRALireSommets()[uiboucle]);
	}

	for (uiboucle = 0; uiboucle < uiGRANbSommet; uiboucle++) {
		delete ppSOMGRAListeSommet[uiboucle];
		ppSOMGRAListeSommet[uiboucle] = nullptr;
	}
	delete[] ppSOMGRAListeSommet;

	uiGRANbArcs = GRAparam.GRALireNbArcs();
	uiGRANbSommet = GRAparam.GRALireNbSommet();

	ppSOMGRAListeSommet = ppSOMGRAListeSommetTMP;

	return *this;
}
