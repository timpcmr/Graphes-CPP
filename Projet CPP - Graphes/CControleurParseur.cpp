#include "CControleurParseur.h"


/******************************************************************************************************
**** Entrées :																					   ****
**** Nécessite :																		  	       ****
**** Sorties :	CControleurParseur																   ****
**** Entraîne : La construction d'un objet CControleurParseur par défaut						   ****
******************************************************************************************************/
CControleurParseur::CControleurParseur()
{
	pcCONChemin = nullptr;
	pGRACONGraphe = new CGraphe();
}

/***********************************************************************************************************************
**** Entrées : pcChemin : char*																						****
**** Nécessite :																		  							****
**** Sorties :	CControleurParseur																					****
**** Entraîne : La construction d'un objet CControleurParseur possédant un chemin d'accès à un fichier de lecture	****
***********************************************************************************************************************/
CControleurParseur::CControleurParseur(char* pcChemin)
{
	pcCONChemin = pcChemin;
	pGRACONGraphe = new CGraphe();
}

/******************************************************************************************************
**** Entrées :																					   ****
**** Nécessite :																		  	       ****
**** Sorties :																					   ****
**** Entraîne : La destruction de l'objet CControleurParseur									   ****
******************************************************************************************************/
CControleurParseur::~CControleurParseur()
{
	pcCONChemin = nullptr;
	delete pGRACONGraphe;
	pGRACONGraphe = nullptr;
}

/******************************************************************************************************
**** Entrées :																					   ****
**** Nécessite :																		  	       ****
**** Sorties :	pcConChemin : char*																   ****
**** Entraîne : Renvoie le chemin d'accès au fichier de lecture									   ****
******************************************************************************************************/
char* CControleurParseur::CONLireChemin()
{
	return pcCONChemin;
}

/******************************************************************************************************
**** Entrées : pcChemin : char*																	   ****
**** Nécessite :																		  	       ****
**** Sorties :																					   ****
**** Entraîne : Modifie le chemin d'accès au fichier de lecture									   ****
******************************************************************************************************/
void CControleurParseur::CONModifierChemin(char* pcChemin)
{
	pcCONChemin = pcChemin;
}

/******************************************************************************************************
**** Entrées :																					   ****
**** Nécessite :																		  	       ****
**** Sorties :	pcConChemin : char*																   ****
**** Entraîne : Renvoie le chemin d'accès au fichier de lecture									   ****
******************************************************************************************************/
CGraphe* CControleurParseur::CONLireGraphe()
{
	return pGRACONGraphe;
}

/******************************************************************************************************
**** Entrées :																					   ****
**** Nécessite :																		  	       ****
**** Sorties :																					   ****
**** Entraîne : Lis le fichier de lecture														   ****
******************************************************************************************************/
void CControleurParseur::CONLireFichierGraphe()
{
	if (pcCONChemin == nullptr) {
		throw CException(EXCCheminVideCtrlParseur);
	}
	
	//Initilisations
	CFichier FICParseur(pcCONChemin);
	unsigned int uiNbArcs = 0, uiNbSommets = 0;
	unsigned int uiBoucle;
	unsigned int* puiSommets = nullptr;
	unsigned int** ppuiArcs = nullptr;

	//Récupération du nombre d'arcs
	try {
		uiNbArcs = FICParseur.FICLireChiffre((char*)"nbarcs");
	}
	catch (CException EXCException) {

		cout << "ERREUR INTERNE PARSEUR : FICLireChiffre (Nb Arcs)" << endl;

		if (EXCException.EXCLireErreur() == EXCParserPointeurNul) {
			cout << "Le pointeur pcToken est nul !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCFichierNonOuvert) {
			cout << "Aucun chemin d'acces au fichier precise ou Flot non initialise !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCTokenNulSuppChar) {
			cout << "Le pointeur passe en parametre de FICSuppChar est nul !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCTokenNulMinuscule) {
			cout << "Le pointeur passe en parametre de FICMinuscule est nul !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCBoucleInfinie) {
			cout << "Une boucle infinie a ete declenchee dans FICLigneSuivante !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCLigneNulle) {
			cout << "Le pointeur passe en parametre de FICLigneSuivante est nul !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCValeurNeg) {
			cout << "Valeur parsee negative ou nulle !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCMiseEnFormeIncorecte) {
			cout << "Mise en forme incorrecte ou valeur manquante !" << endl;
		}

		throw CException(EXCArretProgramme);
	}
	
	//Récupération du nombre de sommets
	try {
		uiNbSommets = FICParseur.FICLireChiffre((char*)"nbsommets");
	}
	catch (CException EXCException) {

		cout << "ERREUR INTERNE PARSEUR : FICLireChiffre (Nb Sommets)" << endl;

		if (EXCException.EXCLireErreur() == EXCParserPointeurNul) {
			cout << "Le pointeur pcToken est nul !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCFichierNonOuvert) {
			cout << "Aucun chemin d'acces au fichier precise ou Flot non initialise !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCTokenNulSuppChar) {
			cout << "Le pointeur passe en parametre de FICSuppChar est nul !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCTokenNulMinuscule) {
			cout << "Le pointeur passe en parametre de FICMinuscule est nul !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCBoucleInfinie) {
			cout << "Une boucle infinie a ete declenchee dans FICLigneSuivante !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCLigneNulle) {
			cout << "Le pointeur passe en parametre de FICLigneSuivante est nul !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCValeurNeg) {
			cout << "Valeur parsee negative ou nulle !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCMiseEnFormeIncorecte) {
			cout << "Mise en forme incorrecte ou valeur manquante !" << endl;
		}
		throw CException(EXCArretProgramme);
	}

	//Récupération des sommets
	try
	{
		puiSommets = FICParseur.FICLireTabSansVirgule(uiNbSommets, (char*)"sommets", (char*)"numero");
	}
	catch (CException EXCException)
	{
		cout << "ERREUR INTERNE PARSEUR : FICLireTabSansVirgule" << endl;

		if (EXCException.EXCLireErreur() == EXCParserPointeurNul) {
			cout << "Le pointeur pcToken est nul !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCFichierNonOuvert) {
			cout << "Aucun chemin d'acces au fichier precise ou Flot non initialise !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCTokenNulSuppChar) {
			cout << "Le pointeur passe en parametre de FICSuppChar est nul !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCTokenNulMinuscule) {
			cout << "Le pointeur passe en parametre de FICMinuscule est nul !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCBoucleInfinie) {
			cout << "Une boucle infinie a ete declenchee dans FICLigneSuivante !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCLigneNulle) {
			cout << "Le pointeur passe en parametre de FICLigneSuivante est nul !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCValeurNeg) {
			cout << "Valeur parsee negative ou nulle !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCMiseEnFormeIncorecte) {
			cout << "Mise en forme incorrecte ou valeur manquante !" << endl;
		}
		throw CException(EXCArretProgramme);
	}
	
	//Récupération des arcs
	try {
		ppuiArcs = FICParseur.FICLireTabAvecVirgule(uiNbSommets, (char*)"arcs", (char*)"debut", (char*)"fin");
	}
	catch (CException EXCException)
	{
		cout << "ERREUR INTERNE PARSEUR : FICLireTabAvecVirgule" << endl;

		if (EXCException.EXCLireErreur() == EXCParserPointeurNul) {
			cout << "Le pointeur pcToken est nul !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCFichierNonOuvert) {
			cout << "Aucun chemin d'acces au fichier precise ou Flot non initialise !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCTokenNulSuppChar) {
			cout << "Le pointeur passe en parametre de FICSuppChar est nul !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCTokenNulMinuscule) {
			cout << "Le pointeur passe en parametre de FICMinuscule est nul !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCBoucleInfinie) {
			cout << "Une boucle infinie a ete declenchee dans FICLigneSuivante !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCLigneNulle) {
			cout << "Le pointeur passe en parametre de FICLigneSuivante est nul !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCValeurNeg) {
			cout << "Valeur parsee negative ou nulle !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCMiseEnFormeIncorecte) {
			cout << "Mise en forme incorrecte ou valeur manquante !" << endl;
		}
		throw CException(EXCArretProgramme);
	}

	//Affectation Graphe
		//Sommets
	for (uiBoucle = 0; uiBoucle < uiNbSommets; uiBoucle++) {
		pGRACONGraphe->GRAAjouterSommet(puiSommets[uiBoucle]);
	}

		//Arcs
	for (uiBoucle = 0; uiBoucle < uiNbArcs; uiBoucle++) {
		try {
			pGRACONGraphe->GRAAjouterArc(ppuiArcs[uiBoucle][0], ppuiArcs[uiBoucle][1]);
		}
		catch (CException EXCException) {
			if (EXCException.EXCLireErreur() == EXCPointeurSommetNul) {
				cout << "Erreur Interne (GRAAjouterArc) : Le ou les pointeur(s) de sommet passe(s) en parametre est/sont nul(s) !" << endl;
			}
			throw CException(EXCArretProgramme);
		}
	}
	
	//Libération de la mémoire
	delete[] puiSommets;
	for (uiBoucle = 0; uiBoucle < uiNbArcs; uiBoucle++) {
		delete[] ppuiArcs[uiBoucle];
	}
	delete[] ppuiArcs;
	
}
