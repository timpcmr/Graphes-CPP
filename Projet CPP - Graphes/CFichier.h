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
#define EXCErrTypeMat 3
#define EXCNbSommetsNeg 4
#define EXCNbArcsNeg 5
#define EXCParserPointeurNul 6
#define EXCTokenNulMinuscule 7
#define EXCTokenNulSuppEspace 8
#define EXCColonneDimSup 9
#define EXCColonneDimInf 10
#define EXCLigneDimSup 11
#define EXCLigneDimInf 12
#define EXCBoucleInfinie 13
#define EXCLigneNulle 14
#define EXCBaliseIncorrecte 15

using namespace std;

class Cfichier {
private:
	char * pcFICLigne;
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
	char * FICMinuscule(char* pcChaine);

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