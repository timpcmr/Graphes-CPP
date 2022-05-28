#ifndef CONTROL_PARSER
#define CONTROL_PARSER

#include "CGraphe.h"
#include "CFichier.h"

#define EXCArretProgramme 50

#define EXCCheminVideCtrlParseur 30

class CControleurParseur {
private:
	char* pcCONChemin;
	CGraphe* pGRACONGraphe;
public:

	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties :	CControleurParseur																   ****
	**** Entraîne : La construction d'un objet CControleurParseur par défaut						   ****
	******************************************************************************************************/
	CControleurParseur();

	/***********************************************************************************************************************
	**** Entrées : pcChemin : char*																						****
	**** Nécessite :																		  							****
	**** Sorties :	CControleurParseur																					****
	**** Entraîne : La construction d'un objet CControleurParseur possédant un chemin d'accès à un fichier de lecture	****
	***********************************************************************************************************************/
	CControleurParseur(char* pcChemin);

	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : La destruction de l'objet CControleurParseur									   ****
	******************************************************************************************************/
	~CControleurParseur();

	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties :	pcConChemin : char*																   ****
	**** Entraîne : Renvoie le chemin d'accès au fichier de lecture									   ****
	******************************************************************************************************/
	char* CONLireChemin();

	/******************************************************************************************************
	**** Entrées : pcChemin : char*																	   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Modifie le chemin d'accès au fichier de lecture									   ****
	******************************************************************************************************/
	void CONModifierChemin(char* pcChemin);

	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties :	pcConChemin : char*																   ****
	**** Entraîne : Renvoie le chemin d'accès au fichier de lecture									   ****
	******************************************************************************************************/
	CGraphe* CONLireGraphe();

	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Lis le fichier de lecture														   ****
	******************************************************************************************************/
	void CONLireFichierGraphe();
};

#endif // !CONTROL_PARSER
