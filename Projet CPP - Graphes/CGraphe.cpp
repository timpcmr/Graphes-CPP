#pragma once

#pragma warning(disable : 6308)

#include "CGraphe.h"
#include "CSommet.h"

using namespace std;

/******************************************************************************************************
**** Entrées :																					   ****
**** Nécessite :																		  	       ****
**** Sorties :																					   ****
**** Entraîne : Construction d'un objet CGraphe par défaut										   ****
******************************************************************************************************/
CGraphe::CGraphe()
{
	uiGRANbArcs = 0;
	uiGRANbSommet = 0;
	bGRAOriente = true;
	ppSOMGRAListeSommet = nullptr;
}

/******************************************************************************************************
**** Entrées : GRAGraphe : CGraphe&																   ****
**** Nécessite :																		  	       ****
**** Sorties :																					   ****
**** Entraîne : Construction d'un objet CGraphe par recopie de GRAGraphe						   ****
******************************************************************************************************/
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

/******************************************************************************************************
**** Entrées :																					   ****
**** Nécessite :																		  	       ****
**** Sorties :																					   ****
**** Entraîne : Destruction de l'objet CGraphe													   ****
******************************************************************************************************/
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

/******************************************************************************************************
**** Entrées :																					   ****
**** Nécessite :																		  	       ****
**** Sorties : ppSOMGRAListeSommet : CSommet**													   ****
**** Entraîne : Renvoie la liste des sommets de l'objet CGraphe									   ****
******************************************************************************************************/
const CSommet* const* CGraphe::GRALireSommets() const
{
	return ppSOMGRAListeSommet;
}

/******************************************************************************************************
**** Entrées :																					   ****
**** Nécessite :																		  	       ****
**** Sorties : uiGRANbSommet : unsigned int														   ****
**** Entraîne : Renvoie le nombre de sommet de l'objet CGraphe									   ****
******************************************************************************************************/
unsigned int CGraphe::GRALireNbSommet() const
{
	return uiGRANbSommet;
}

/******************************************************************************************************
**** Entrées :																					   ****
**** Nécessite :																		  	       ****
**** Sorties : uiGRANbArcs : unsigned int														   ****
**** Entraîne : Renvoie le nombre d'arcs de l'objet CGraphe										   ****
******************************************************************************************************/
unsigned int CGraphe::GRALireNbArcs() const
{
	return uiGRANbArcs;
}

/******************************************************************************************************
**** Entrées :																					   ****
**** Nécessite :																		  	       ****
**** Sorties : bGRAOriente : bool																   ****
**** Entraîne : Renvoie le type de l'objet CGraphe (1 si oriente, 0 si non-oriente)				   ****
******************************************************************************************************/
bool CGraphe::GRALireType() const
{
	return bGRAOriente;
}

/******************************************************************************************************
**** Entrées : pSomDepart : CSommet*, pSOMArrivee : CSommet*									   ****
**** Nécessite :																		  	       ****
**** Sorties :																					   ****
**** Entraîne : Crée un arc partant du sommet pSOMDepart allant vers le sommet pSOMArrivee		   ****
******************************************************************************************************/
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

/*****************************************************************************************************************
**** Entrées : iDepart : int, iArrivee : int															      ****
**** Nécessite :																		  				      ****
**** Sorties :																								  ****
**** Entraîne : Crée un arc partant du sommet ayant le numero iDepart vers le sommet ayant le numéro iArrivee ****
*****************************************************************************************************************/
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

/*********************************************************************************************************
**** Entrées : iDepart : int, iArrivee : int														  ****
**** Nécessite :																		  			  ****
**** Sorties :																						  ****
**** Entraîne : Supprime l'arc partant du sommet numéro iDepart allant vers le sommet numéro iArrivee ****
*********************************************************************************************************/
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

/******************************************************************************************************
**** Entrées : SOMSommet CSommet&																   ****
**** Nécessite :																		  	       ****
**** Sorties :																					   ****
**** Entraîne : Ajoute le sommet SOMSommet au graphe											   ****
******************************************************************************************************/
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

/******************************************************************************************************
**** Entrées : iNum : int																		   ****
**** Nécessite :																		  	       ****
**** Sorties :																					   ****
**** Entraîne : Ajoute le sommet numero iNum au graphe											   ****
******************************************************************************************************/
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

/******************************************************************************************************
**** Entrées : pSOMParam : CSommet*																   ****
**** Nécessite :																		  	       ****
**** Sorties :																					   ****
**** Entraîne : Supprime le sommet pSOMParam du graphe											   ****
******************************************************************************************************/
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

/******************************************************************************************************
**** Entrées : pSOMParam : CSommet*, iNum : int													   ****
**** Nécessite :																		  	       ****
**** Sorties :																					   ****
**** Entraîne : Modifie le numéro du sommet pSOMParam par le numero iNum						   ****
******************************************************************************************************/
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

/******************************************************************************************************
**** Entrées : bParam : bool																	   ****
**** Nécessite :																		  	       ****
**** Sorties :																					   ****
**** Entraîne : Modifie le type du graphe (0 = non-orienté, 1 = orienté)						   ****
******************************************************************************************************/
void CGraphe::GRAModifierType(bool bParam)
{
	bGRAOriente = bParam;
}

/*************************************************************************************************************
**** Entrées : iVal : int																				  ****
**** Nécessite :																		  				  ****
**** Sorties : CSommet*																					  ****
**** Entraîne : Renvoie un pointeur sur le sommet numéro iVal s'il existe, renvoie un pointeur null sinon ****
*************************************************************************************************************/
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

/******************************************************************************************************
**** Entrées : iSommet : int																	   ****
**** Nécessite :																		  	       ****
**** Sorties : int																				   ****
**** Entraîne : Renvoie la position du sommet numéro iSommet s'il existe, -1 sinon				   ****
******************************************************************************************************/
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

/******************************************************************************************************
**** Entrées : iVal	: int																		   ****
**** Nécessite :																		  	       ****
**** Sorties : bool																				   ****
**** Entraîne : Renvoie true si le sommet numéro iVal n'existe pas, false sinon					   ****
******************************************************************************************************/
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

/******************************************************************************************************
**** Entrées :																					   ****
**** Nécessite :																		  	       ****
**** Sorties :																					   ****
**** Entraîne : Fonction d'affichage du graphe													   ****
******************************************************************************************************/
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

/******************************************************************************************************
**** Entrées : GRAParam : CGraphe&																   ****
**** Nécessite :																		  	       ****
**** Sorties :																					   ****
**** Entraîne : La copie de l'objet CGraphe en paramètre										   ****
******************************************************************************************************/
CGraphe& CGraphe::operator=(const CGraphe &GRAParam)
{
	unsigned int uiboucle;
	bGRAOriente = GRAParam.GRALireType();

	//Copie par duplication des objets
	CSommet** ppSOMGRAListeSommetTMP = new CSommet * [GRAParam.GRALireNbSommet()];
	for (uiboucle = 0; uiboucle < GRAParam.GRALireNbSommet(); uiboucle++) {
		ppSOMGRAListeSommetTMP[uiboucle] = new CSommet(*GRAParam.GRALireSommets()[uiboucle]);
	}

	for (uiboucle = 0; uiboucle < uiGRANbSommet; uiboucle++) {
		delete ppSOMGRAListeSommet[uiboucle];
		ppSOMGRAListeSommet[uiboucle] = nullptr;
	}
	delete[] ppSOMGRAListeSommet;

	uiGRANbArcs = GRAParam.GRALireNbArcs();
	uiGRANbSommet = GRAParam.GRALireNbSommet();

	ppSOMGRAListeSommet = ppSOMGRAListeSommetTMP;

	return *this;
}
