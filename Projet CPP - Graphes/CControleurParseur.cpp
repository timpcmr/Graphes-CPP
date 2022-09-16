#include "CControleurParseur.h"


/******************************************************************************************************
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties :	CControleurParseur																   ****
**** Entra�ne : La construction d'un objet CControleurParseur par d�faut						   ****
******************************************************************************************************/
CControleurParseur::CControleurParseur()
{
	pcCONChemin = nullptr;
	pGRACONGraphe = new CGraphe();
}

/***********************************************************************************************************************
**** Entr�es : pcChemin : char*																						****
**** N�cessite :																		  							****
**** Sorties :	CControleurParseur																					****
**** Entra�ne : La construction d'un objet CControleurParseur poss�dant un chemin d'acc�s � un fichier de lecture	****
***********************************************************************************************************************/
CControleurParseur::CControleurParseur(char* pcChemin)
{
	pcCONChemin = pcChemin;
	pGRACONGraphe = new CGraphe();
}

/******************************************************************************************************
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : La destruction de l'objet CControleurParseur									   ****
******************************************************************************************************/
CControleurParseur::~CControleurParseur()
{
	pcCONChemin = nullptr;
	delete pGRACONGraphe;
	pGRACONGraphe = nullptr;
}

/******************************************************************************************************
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties :	pcConChemin : char*																   ****
**** Entra�ne : Renvoie le chemin d'acc�s au fichier de lecture									   ****
******************************************************************************************************/
char* CControleurParseur::CONLireChemin()
{
	return pcCONChemin;
}

/******************************************************************************************************
**** Entr�es : pcChemin : char*																	   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : Modifie le chemin d'acc�s au fichier de lecture									   ****
******************************************************************************************************/
void CControleurParseur::CONModifierChemin(char* pcChemin)
{
	pcCONChemin = pcChemin;
}

/******************************************************************************************************
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties :	pcConChemin : char*																   ****
**** Entra�ne : Renvoie le chemin d'acc�s au fichier de lecture									   ****
******************************************************************************************************/
CGraphe* CControleurParseur::CONLireGraphe()
{
	return pGRACONGraphe;
}

/******************************************************************************************************
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : Lis le fichier de lecture														   ****
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
	int* piSommets = nullptr;
	int** ppiArcs = nullptr;

	//R�cup�ration du nombre d'arcs
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
	
	//R�cup�ration du nombre de sommets
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

	//R�cup�ration des sommets
	try
	{
		piSommets = FICParseur.FICLireTabSansVirgule(uiNbSommets, (char*)"sommets", (char*)"numero");
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
	
	//R�cup�ration des arcs
	try {
		ppiArcs = FICParseur.FICLireTabAvecVirgule(uiNbArcs, (char*)"arcs", (char*)"debut", (char*)"fin");
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
		pGRACONGraphe->GRAAjouterSommet(piSommets[uiBoucle]);
	}

		//Arcs
	for (uiBoucle = 0; uiBoucle < uiNbArcs; uiBoucle++) {
		try {
			pGRACONGraphe->GRAAjouterArc(ppiArcs[uiBoucle][0], ppiArcs[uiBoucle][1]);
		}
		catch (CException EXCException) {
			if (EXCException.EXCLireErreur() == EXCPointeurSommetNul) {
				cout << "Erreur Interne (GRAAjouterArc) : Le ou les pointeur(s) de sommet passe(s) en parametre est/sont nul(s) !" << endl;
			}
			throw CException(EXCArretProgramme);
		}
	}
	
	//Lib�ration de la m�moire
	delete[] piSommets;
	for (uiBoucle = 0; uiBoucle < uiNbArcs; uiBoucle++) {
		delete[] ppiArcs[uiBoucle];
	}
	delete[] ppiArcs;
	
}
