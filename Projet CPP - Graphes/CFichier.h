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

class Cfichier {
private:
	ifstream IFSFICFichier;

public:
	//Constructeurs et Destructeur
	Cfichier();

	Cfichier(char* pcChemin);

	~Cfichier();

	//Modifieur

	void FICInitialiserFlot(char* pcChemin);

	//Parseur

	/******************************************************************************************************
	**** Entrées : char* pcChemin																	   ****
	**** Nécessite :																		  	       ****
	**** Sorties :	CMatrice MATretour																   ****
	**** Entraîne : Renvoie la matrice du fichier texte dont le chemin pcChemin est passé en paramètre ****
	******************************************************************************************************/
	unsigned int FICLireChiffre(char* pcTag);

	unsigned int* FICLireTabSansVirgule(const unsigned int iNbLignes, char* pcTag1, char* pcTag2);

	unsigned int** FICLireTabAvecVirgule(const unsigned int iNbLignes, char* pcTag1, char* pcTag2, char* pcTag3);
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
	void FICSupp_char(char* pcChaine, const char cCharactere);

	bool FICVerifBalise(char* pcToken, const char* pcNomBalise);
};


#endif