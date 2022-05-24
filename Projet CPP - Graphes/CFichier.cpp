#include "CFichier.h"
#pragma warning(disable : 4996)


CFichier::CFichier()
{
}

CFichier::CFichier(char * pcChemin)
{
	IFSFICFichier = ifstream(pcChemin);
	if (!IFSFICFichier.is_open()) {
		throw CException(EXCFichierNonOuvert);
	}
}

CFichier::~CFichier()
{
	IFSFICFichier.close();
}

void CFichier::FICInitialiserFlot(char * pcChemin)
{
	IFSFICFichier = ifstream(pcChemin);
}

/******************************************************************************************************
**** Entrées : char* pcChemin																	   ****
**** Nécessite :																		  	       ****
**** Sorties :	CMatrice MATretour																   ****
**** Entraîne : Renvoie la matrice du fichier texte dont le chemin pcChemin est passé en paramètre ****
******************************************************************************************************/
unsigned int CFichier::FICLireChiffre(char* pcTag)
{
	unsigned int uiValeurRetournee = 0;
	char* pcLigne = new char[STR_LENGTH];

	if (IFSFICFichier.is_open()){
		FICLigneSuivante(pcLigne);
		char * pcToken = strtok(pcLigne, "=");

		if (pcToken == nullptr) {
			delete[] pcLigne;
			throw CException(EXCParserPointeurNul);
		}

		while (FICVerifBalise(pcToken, pcTag) == false) {
			FICLigneSuivante(pcLigne);
			pcToken = strtok(pcLigne, "=");
		}
		
		pcToken = strtok(NULL, "=");
		if (pcToken == nullptr || pcToken[0] == '\0') {
			delete[] pcLigne;
			throw CException(EXCMiseEnFormeIncorecte);
		}
		int iValeurParsee = atoi(pcToken);
		if (iValeurParsee <= 0) {
			delete[] pcLigne;
			throw CException(EXCValeurNeg);
		}
		uiValeurRetournee = (unsigned int)iValeurParsee;

		//Retour en haut du fichier pour les prochaines utilisations du flot
		IFSFICFichier.clear();
		IFSFICFichier.seekg(IFSFICFichier.beg);
	}
	else {
		delete[] pcLigne;
		throw CException(EXCFichierNonOuvert);
	}
	delete[] pcLigne;
	return uiValeurRetournee;
}

unsigned int* CFichier::FICLireTabSansVirgule(const unsigned int uiNbLignes, char* pcTag1, char* pcTag2)
{
	char* pcLigne = new char[STR_LENGTH];
	unsigned int* puiValeursRetour = new unsigned int[uiNbLignes];
	unsigned int uiBoucle;

	if (IFSFICFichier.is_open()) {
		FICLigneSuivante(pcLigne);
		char* pcToken = strtok(pcLigne, "=");

		while (FICVerifBalise(pcToken, pcTag1) == false) {
			FICLigneSuivante(pcLigne);
			pcToken = strtok(pcLigne, "=");
		}

		for (uiBoucle = 0; uiBoucle < uiNbLignes; uiBoucle++) {
			FICLigneSuivante(pcLigne);
			pcToken = strtok(pcLigne, "=");
			if (FICVerifBalise(pcToken, pcTag2) == true) {
				pcToken = strtok(NULL, "=");
				if (pcToken == nullptr || pcToken[0] == '\0') {
					delete[] puiValeursRetour;
					delete[] pcLigne;
					throw CException(EXCMiseEnFormeIncorecte);
				}
				int iValeurParsee = atoi(pcToken);
				if (iValeurParsee <= 0) {
					delete[] puiValeursRetour;
					delete[] pcLigne;
					throw CException(EXCValeurNeg);
				}
				puiValeursRetour[uiBoucle] = (unsigned int)iValeurParsee;
			}
			else {
				delete[] pcLigne;
				delete[] puiValeursRetour;
				throw CException(EXCBaliseIncorrecte);
			}
		}

		//Retour en haut du fichier pour les prochaines utilisations du flot
		IFSFICFichier.clear();
		IFSFICFichier.seekg(IFSFICFichier.beg);
	}
	else {
		delete[] puiValeursRetour;
		delete[] pcLigne;
		throw CException(EXCFichierNonOuvert);
	}
	delete[] pcLigne;
	return puiValeursRetour;
}

unsigned int** CFichier::FICLireTabAvecVirgule(const unsigned int uiNbLignes, char* pcTag1, char* pcTag2, char* pcTag3)
{
	unsigned int uiBoucle1;

	char* pcLigne = new char[STR_LENGTH];
	unsigned int** ppuiValeursRetour = new unsigned int* [uiNbLignes];
	for (uiBoucle1 = 0; uiBoucle1 < uiNbLignes; uiBoucle1++) {
		ppuiValeursRetour[uiBoucle1] = new unsigned int[2];
	}
	
	if (IFSFICFichier.is_open()) {
		FICLigneSuivante(pcLigne);
		char* pcToken = strtok(pcLigne, "=");

		while (FICVerifBalise(pcToken, pcTag1) == false) {
			FICLigneSuivante(pcLigne);
			pcToken = strtok(pcLigne, "=");
		}

		for (uiBoucle1 = 0; uiBoucle1 < uiNbLignes; uiBoucle1++) {
			FICLigneSuivante(pcLigne);

			//Récupération des 2 elements de la ligne
			pcToken = strtok(pcLigne, ",");
			char* pcToken2 = strtok(NULL, ",");

			//Recuperation du numero de debut
			char* pcToken3 = strtok(pcToken, "=");
			if (FICVerifBalise(pcToken3, pcTag2) == true) {
				pcToken3 = strtok(NULL, "=");
				if (pcToken3 == nullptr || pcToken3[0] == '\0') {
					delete[] pcLigne;
					delete[] ppuiValeursRetour;
					throw CException(EXCMiseEnFormeIncorecte);
				}
				int iValeurParsee = atoi(pcToken3);
				if (iValeurParsee <= 0) {
					delete[] pcLigne;
					delete[] ppuiValeursRetour;
					throw CException(EXCValeurNeg);
				}
				ppuiValeursRetour[uiBoucle1][0] = (unsigned int)iValeurParsee;
			}
			else {
				delete[] pcLigne;
				delete[] ppuiValeursRetour;
				throw CException(EXCBaliseIncorrecte);
			}

			//Recuperation numero de fin
			pcToken3 = strtok(pcToken2, "=");
			if (FICVerifBalise(pcToken3, pcTag3) == true) {
				pcToken3 = strtok(NULL, "=");
				if (pcToken3 == nullptr || pcToken3[0] == '\0') {
					delete[] pcLigne;
					delete[] ppuiValeursRetour;
					throw CException(EXCMiseEnFormeIncorecte);
				}
				int iValeurParsee = atoi(pcToken3);
				if (iValeurParsee <= 0) {
					delete[] pcLigne;
					delete[] ppuiValeursRetour;
					throw CException(EXCValeurNeg);
				}
				ppuiValeursRetour[uiBoucle1][1] = (unsigned int)iValeurParsee;
			}
			else {
				delete[] pcLigne;
				delete[] ppuiValeursRetour;
				throw CException(EXCBaliseIncorrecte);
			}
			
		}

		//Retour en haut du fichier pour les prochaines utilisations du flot
		IFSFICFichier.clear();
		IFSFICFichier.seekg(IFSFICFichier.beg);
	}
	else {
		delete[] pcLigne;
		delete[] ppuiValeursRetour;
		throw CException(EXCFichierNonOuvert);
	}

	delete[] pcLigne;
	return ppuiValeursRetour;
}

void CFichier::FICLigneSuivante(char* pcLigne)
{
	unsigned int uiBoucle = 0;

	if (pcLigne == nullptr) {
		throw CException(EXCLigneNulle);
	}
	if (!IFSFICFichier) {
		throw CException(EXCFichierNonOuvert);
	}

	do
	{
		IFSFICFichier.getline(pcLigne, STR_LENGTH);
		FICSupp_char(pcLigne, ' ');
		FICSupp_char(pcLigne, '\t');
		uiBoucle++;
		if (uiBoucle == MAX_LOOPING) {
			throw CException(EXCBoucleInfinie);
		}
	} while (pcLigne[0] == '\n' || pcLigne[0] == '\0' || pcLigne[0] == '\r');
}



/***********************************************************************************************************************
**** Entrées : char* pcChaine																					    ****
**** Nécessite :																		  							****
**** Sorties :	char* pcChaine																						****
**** Entraîne : Renvoie la chaine pcChaine passée en paramètre et dont toutes les lettres sont passées en minuscule ****
***********************************************************************************************************************/
char * CFichier::FICMinuscule(char* pcChaineMin)
{
	if (pcChaineMin == nullptr) {
		throw CException(EXCTokenNulMinuscule);
	}
	unsigned int uiboucle;

	for (uiboucle = 0; pcChaineMin[uiboucle] != '\0'; uiboucle++) {
		pcChaineMin[uiboucle] = tolower(pcChaineMin[uiboucle]);
	}
	return pcChaineMin;
}


/******************************************************************************************************************
**** Entrées : char* pcChaine																				   ****
**** Nécessite :																		  					   ****
**** Sorties :																								   ****
**** Entraîne : Supprime un charactère c d'une chaine de caractère pcChaine passée en paramètre				   ****
******************************************************************************************************************/
void CFichier::FICSupp_char(char* pcChaine, const char cCaractere)
{
	if (pcChaine == nullptr) {
		throw CException(EXCTokenNulSuppChar);
	}
	unsigned int uiboucle1, uiboucle2;

	for (uiboucle1 = 0; pcChaine[uiboucle1] != '\0'; uiboucle1++) {
		if (pcChaine[uiboucle1] == cCaractere) {
			for (uiboucle2 = uiboucle1; pcChaine[uiboucle2] != '\0'; uiboucle2++) {
				pcChaine[uiboucle2] = pcChaine[uiboucle2 + 1];
			}
			uiboucle1--;
		}
	}
	pcChaine[uiboucle1] = '\0';
}

bool CFichier::FICVerifBalise(char* pcToken,const char* pcNomBalise)
{
	if (strcmp(FICMinuscule(pcToken), pcNomBalise) != 0) {
		return false;
	}
	else {
		return true;
	}
}
