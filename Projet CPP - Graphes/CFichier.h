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
	**** Entr�es : char* pcChemin																	   ****
	**** N�cessite :																		  	       ****
	**** Sorties :	CMatrice MATretour																   ****
	**** Entra�ne : Renvoie la matrice du fichier texte dont le chemin pcChemin est pass� en param�tre ****
	******************************************************************************************************/
	unsigned int FICLireChiffre(char* pcTag);

	unsigned int* FICLireTabSansVirgule(const unsigned int iNbLignes, char* pcTag1, char* pcTag2);

	unsigned int** FICLireTabAvecVirgule(const unsigned int iNbLignes, char* pcTag1, char* pcTag2, char* pcTag3);
	/***********************************************************************************************************************
	**** Entr�es : char* pcChaine, ifstream& fichier																    ****
	**** N�cessite : Un fichier ouvert et une chaine non nulle								  							****
	**** Sorties :																										****
	**** Entra�ne : Renvoie la chaine pcChaine pass�e en param�tre et dont tous les tabh et espaces sont supprim�s	    ****
	***********************************************************************************************************************/
	void FICLigneSuivante(char* pcLigne);

	//Fonctions de handle mauvaise mise en forme

	/***********************************************************************************************************************
	**** Entr�es : char* pcChaine																					    ****
	**** N�cessite :																		  							****
	**** Sorties :	char* pcChaine																						****
	**** Entra�ne : Renvoie la chaine pcChaine pass�e en param�tre et dont toutes les lettres sont pass�es en minuscule ****
	***********************************************************************************************************************/
	char * FICMinuscule(char* pcChaineMin);

	/******************************************************************************************************************
	**** Entr�es : char* pcChaine																				   ****
	**** N�cessite :																		  					   ****
	**** Sorties :																								   ****
	**** Entra�ne : Supprime un charact�re c d'une chaine de caract�re pcChaine pass�e en param�tre				   ****
	******************************************************************************************************************/
	void FICSupp_char(char* pcChaine, const char cCharactere);

	bool FICVerifBalise(char* pcToken, const char* pcNomBalise);
};


#endif