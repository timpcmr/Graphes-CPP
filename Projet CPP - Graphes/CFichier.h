#ifndef FIC
#define FIC
#include "CGraphe.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <cctype>

#define STR_LENGTH 1024
#define MAX_LOOPING 10000

#define EXCCheminNul 1
#define EXCFichierNonOuvert 2
#define EXCParserPointeurNul 3
#define EXCTokenNulMinuscule 4
#define EXCTokenNulSuppChar 5
#define EXCBoucleInfinie 6
#define EXCLigneNulle 7
#define EXCBaliseIncorrecte 8
#define EXCMiseEnFormeIncorecte 9
#define EXCValeurNeg 10

using namespace std;

class CFichier {
private:
	//Flot de lecture du fichier
	ifstream IFSFICFichier;

public:
	//Constructeurs et Destructeur

	/******************************************************************************************************
	**** Entrées : 																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Construction d'un object Cfichier par défaut									   ****
	******************************************************************************************************/
	CFichier();

	/******************************************************************************************************
	**** Entrées : 	char * pcChemin																	   ****
	**** Nécessite : pcChemin non nul comme chemin du fichier à lire						  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Construction d'un object Cfichier par défaut									   ****
	******************************************************************************************************/
	CFichier(char* pcChemin);

	/******************************************************************************************************
	**** Entrées : 																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Destruction de l'objet CFichier par défaut										   ****
	******************************************************************************************************/
	~CFichier();

	//Modifieur

	/******************************************************************************************************
	**** Entrées : pcChemin : char*																	   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Initialise le flot de lecture du fichier										   ****
	******************************************************************************************************/
	void FICInitialiserFlot(char* pcChemin);

	//Parseur

	/******************************************************************************************************
	**** Entrées : pcTag : char*																	   ****
	**** Nécessite :																		  	       ****
	**** Sorties :	uiValeurRetournee : unsigned int												   ****
	**** Entraîne : Renvoie le chiffre lu dans le fichier											   ****
	******************************************************************************************************/
	unsigned int FICLireChiffre(char* pcTag);



	unsigned int* FICLireTabSansVirgule(const unsigned int uiNbLignes, char* pcTag1, char* pcTag2);

	unsigned int** FICLireTabAvecVirgule(const unsigned int uiNbLignes, char* pcTag1, char* pcTag2, char* pcTag3);
	/***********************************************************************************************************************
	**** Entrées : char* pcChaine, ifstream& fichier																    ****
	**** Nécessite : Un fichier ouvert et une chaine non nulle								  							****
	**** Sorties :																										****
	**** Entraîne : Renvoie la chaine pcChaine passée en paramètre et dont tous les tabh et espaces sont supprimés	    ****
	***********************************************************************************************************************/
	void FICLigneSuivante(char* pcLigne);

	//Fonctions de handle mauvaise mise en forme

	/***********************************************************************************************************************
	**** Entrées : char* pcChaine																					    ****
	**** Nécessite :																		  							****
	**** Sorties :	char* pcChaine																						****
	**** Entraîne : Renvoie la chaine pcChaine passée en paramètre et dont toutes les lettres sont passées en minuscule ****
	***********************************************************************************************************************/
	char * FICMinuscule(char* pcChaineMin);

	/******************************************************************************************************************
	**** Entrées : char* pcChaine																				   ****
	**** Nécessite :																		  					   ****
	**** Sorties :																								   ****
	**** Entraîne : Supprime un charactère c d'une chaine de caractère pcChaine passée en paramètre				   ****
	******************************************************************************************************************/
	void FICSupp_char(char* pcChaine, const char cCaractere);

	bool FICVerifBalise(char* pcToken, const char* pcNomBalise);
};


#endif