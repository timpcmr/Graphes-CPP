#include "CFichier.h"
#pragma warning(disable : 4996)


Cfichier::Cfichier()
{
	pcFICLigne = new char[STR_LENGTH];
}

Cfichier::Cfichier(char * pcChemin)
{
	pcFICLigne = new char[STR_LENGTH];
	IFSFICFichier = ifstream(pcChemin);
	if (!IFSFICFichier.is_open()) {
		throw CException(EXCFichierNonOuvert);
	}
}

Cfichier::~Cfichier()
{
	delete[] pcFICLigne;
	IFSFICFichier.close();
}

void Cfichier::FICInitialiserFlot(char * pcChemin)
{
	IFSFICFichier = ifstream(pcChemin);
}

/******************************************************************************************************
**** Entrées : char* pcChemin																	   ****
**** Nécessite :																		  	       ****
**** Sorties :	CMatrice MATretour																   ****
**** Entraîne : Renvoie la matrice du fichier texte dont le chemin pcChemin est passé en paramètre ****
******************************************************************************************************/
int Cfichier::FICLireChiffre(char* pcTag)
{
	int iValeurRetournee = 0;

	if (IFSFICFichier.is_open()){
		FICLigneSuivante(pcFICLigne);
		char * pcToken = strtok(pcFICLigne, "=");

		while (FICVerifBalise(FICMinuscule(pcToken), FICMinuscule(pcTag)) == false) {
			FICLigneSuivante(pcFICLigne);
			pcToken = strtok(pcFICLigne, "=");
		}
		
		pcToken = strtok(NULL, "=");
		iValeurRetournee = atoi(pcToken);

		//Retour en haut du fichier pour les prochaines utilisations du flot
		IFSFICFichier.clear();
		IFSFICFichier.seekg(IFSFICFichier.beg);
	}
	else {
		throw CException(EXCFichierNonOuvert);
	}
	return iValeurRetournee;
}

int* Cfichier::FICLireTabSansVirgule(const int iNbLignes, char* pcTag1, char* pcTag2)
{
	int* piValeursRetour = new int[iNbLignes];
	unsigned int uiBoucle;

	if (IFSFICFichier.is_open()) {
		FICLigneSuivante(pcFICLigne);
		char* pcToken = strtok(pcFICLigne, "=");

		while (FICVerifBalise(FICMinuscule(pcToken), FICMinuscule(pcTag1)) == false) {
			FICLigneSuivante(pcFICLigne);
			pcToken = strtok(pcFICLigne, "=");
		}

		for (uiBoucle = 0; uiBoucle < iNbLignes; uiBoucle++) {
			FICLigneSuivante(pcFICLigne);
			pcToken = strtok(pcFICLigne, "=");
			if (FICVerifBalise(FICMinuscule(pcToken), FICMinuscule(pcTag2)) == true) {
				pcToken = strtok(NULL, "=");
				piValeursRetour[uiBoucle] = atoi(pcToken);
			}
			else {
				throw CException(EXCBaliseIncorrecte);
			}
		}

		//Retour en haut du fichier pour les prochaines utilisations du flot
		IFSFICFichier.clear();
		IFSFICFichier.seekg(IFSFICFichier.beg);
	}
	else {
		throw CException(EXCFichierNonOuvert);
	}
	return piValeursRetour;
}

int** Cfichier::FICLireTabAvecVirgule(const int iNbLignes, char* pcTag1, char* pcTag2, char* pcTag3)
{
	unsigned int uiBoucle1, uiBoucle2;

	int** ppiValeursRetour = new int * [iNbLignes];
	for (uiBoucle1 = 0; uiBoucle1 < iNbLignes; uiBoucle1++) {
		ppiValeursRetour[uiBoucle1] = new int[2];
	}
	
	if (IFSFICFichier.is_open()) {
		FICLigneSuivante(pcFICLigne);
		char* pcToken = strtok(pcFICLigne, "=");

		while (FICVerifBalise(FICMinuscule(pcToken), FICMinuscule(pcTag1)) == false) {
			FICLigneSuivante(pcFICLigne);
			pcToken = strtok(pcFICLigne, "=");
		}

		for (uiBoucle1 = 0; uiBoucle1 < iNbLignes; uiBoucle1++) {
			FICLigneSuivante(pcFICLigne);

			//Récupération des 2 elements de la ligne
			pcToken = strtok(pcFICLigne, ",");
			char* pcToken2 = strtok(NULL, ",");

			//Recuperation du numero de debut
			char* pcToken3 = strtok(pcToken, "=");
			if (FICVerifBalise(FICMinuscule(pcToken3), FICMinuscule(pcTag2)) == true) {
				pcToken3 = strtok(NULL, "=");
				ppiValeursRetour[uiBoucle1][0] = atoi(pcToken3);
			}
			else {
				throw CException(EXCBaliseIncorrecte);
			}

			//Recuperation numero de fin
			pcToken3 = strtok(pcToken2, "=");
			if (FICVerifBalise(FICMinuscule(pcToken3), FICMinuscule(pcTag3)) == true) {
				pcToken3 = strtok(NULL, "=");
				ppiValeursRetour[uiBoucle1][1] = atoi(pcToken3);
			}
			else {
				throw CException(EXCBaliseIncorrecte);
			}
			
		}

		//Retour en haut du fichier pour les prochaines utilisations du flot
		IFSFICFichier.clear();
		IFSFICFichier.seekg(IFSFICFichier.beg);
	}
	else {
		throw CException(EXCFichierNonOuvert);
	}
	return ppiValeursRetour;
}

void Cfichier::FICLigneSuivante(char* pcLigne)
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
char * Cfichier::FICMinuscule(char* pcChaine)
{
	if (pcChaine == nullptr) {
		throw CException(EXCTokenNulMinuscule);
	}
	unsigned int uiboucle;

	for (uiboucle = 0; pcChaine[uiboucle] != '\0'; uiboucle++) {
		pcChaine[uiboucle] = tolower(pcChaine[uiboucle]);
	}
	return pcChaine;
}


/******************************************************************************************************************
**** Entrées : char* pcChaine																				   ****
**** Nécessite :																		  					   ****
**** Sorties :																								   ****
**** Entraîne : Supprime un charactère c d'une chaine de caractère pcChaine passée en paramètre				   ****
******************************************************************************************************************/
void Cfichier::FICSupp_char(char* pcChaine, const char cCharactere)
{
	if (pcChaine == nullptr) {
		throw CException(EXCTokenNulSuppEspace);
	}
	unsigned int uiboucle1, uiboucle2;

	for (uiboucle1 = 0; pcChaine[uiboucle1] != '\0'; uiboucle1++) {
		if (pcChaine[uiboucle1] == cCharactere) {
			for (uiboucle2 = uiboucle1; pcChaine[uiboucle2] != '\0'; uiboucle2++) {
				pcChaine[uiboucle2] = pcChaine[uiboucle2 + 1];
			}
			uiboucle1--;
		}
	}
	pcChaine[uiboucle1] = '\0';
}

bool Cfichier::FICVerifBalise(char* pcToken,const char* pcNomBalise)
{
	if (strstr(FICMinuscule(pcToken), pcNomBalise) == nullptr) {
		return false;
	}
	else {
		return true;
	}
}
