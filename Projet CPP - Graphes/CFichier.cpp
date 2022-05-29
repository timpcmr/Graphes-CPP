#include "CFichier.h"
#pragma warning(disable : 4996)

/******************************************************************************************************
**** Entrées : 																					   ****
**** Nécessite :																		  	       ****
**** Sorties :																					   ****
**** Entraîne : Construction d'un object Cfichier par défaut									   ****
******************************************************************************************************/
CFichier::CFichier()
{
}

/******************************************************************************************************
**** Entrées : 	char * pcChemin																	   ****
**** Nécessite : pcChemin non nul comme chemin du fichier à lire						  	       ****
**** Sorties :																					   ****
**** Entraîne : Construction d'un object Cfichier par défaut									   ****
******************************************************************************************************/
CFichier::CFichier(char * pcChemin)
{
	IFSFICFichier = ifstream(pcChemin);
	
	//Si echec de l'ouverture du fichier
	if (!IFSFICFichier.is_open()) {
		throw CException(EXCFichierNonOuvert);
	}
}

/******************************************************************************************************
**** Entrées : 																					   ****
**** Nécessite :																		  	       ****
**** Sorties :																					   ****
**** Entraîne : Destruction de l'objet CFichier par défaut										   ****
******************************************************************************************************/
CFichier::~CFichier()
{
	IFSFICFichier.close();
}

/******************************************************************************************************
**** Entrées : pcChemin : char*																	   ****
**** Nécessite :																		  	       ****
**** Sorties :																					   ****
**** Entraîne : Initialise le flot de lecture du fichier										   ****
******************************************************************************************************/
void CFichier::FICInitialiserFlot(char * pcChemin)
{
	IFSFICFichier = ifstream(pcChemin);
}

/******************************************************************************************************
**** Entrées : pcTag : char*																	   ****
**** Nécessite :																		  	       ****
**** Sorties :	uiValeurRetournee : unsigned int												   ****
**** Entraîne : Renvoie le chiffre lu dans le fichier											   ****
******************************************************************************************************/
unsigned int CFichier::FICLireChiffre(char* pcTag)
{
	unsigned int uiValeurRetournee = 0;
	char* pcLigne = new char[STR_LENGTH];

	if (IFSFICFichier.is_open()){
		
		//Récupération de la ligne
		FICLigneSuivante(pcLigne);

		//On récupère la valeur du tag
		char * pcToken = strtok(pcLigne, "=");

		if (pcToken == nullptr) {
			delete[] pcLigne;
			throw CException(EXCParserPointeurNul);
		}

		// On compare le tag jusqu'a trouver le bon
		while (FICVerifBalise(pcToken, pcTag) == false) {
			FICLigneSuivante(pcLigne);
			pcToken = strtok(pcLigne, "=");
		}
		
		// On récupère la valeur associée
		pcToken = strtok(NULL, "=");
		
		if (pcToken == nullptr || pcToken[0] == '\0') {
			delete[] pcLigne;
			throw CException(EXCMiseEnFormeIncorecte);
		}
		
		// On convertit la valeur en entier
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
		//Récupération de la ligne
		FICLigneSuivante(pcLigne);
		// On récupère la valeur du tag
		char* pcToken = strtok(pcLigne, "=");

		// On compare le tag jusqu'a trouver le bon
		while (FICVerifBalise(pcToken, pcTag1) == false) {
			FICLigneSuivante(pcLigne);
			pcToken = strtok(pcLigne, "=");
		}

		// On récupère les valeurs associées en cherchant le tag2
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

				// On convertit la valeur en entier
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
		//Récupération de la ligne
		FICLigneSuivante(pcLigne);
		// On récupère la valeur du tag
		char* pcToken = strtok(pcLigne, "=");

		// On compare le tag jusqu'a trouver le bon
		while (FICVerifBalise(pcToken, pcTag1) == false) {
			FICLigneSuivante(pcLigne);
			pcToken = strtok(pcLigne, "=");
		}

		// On récupère les valeurs associées
		for (uiBoucle1 = 0; uiBoucle1 < uiNbLignes; uiBoucle1++) {
			FICLigneSuivante(pcLigne);

			//Récupération des 2 elements de la ligne
			pcToken = strtok(pcLigne, ",");
			char* pcToken2 = strtok(NULL, ",");

			//Recuperation du numero de debut
			char* pcToken3 = strtok(pcToken, "=");

			//On vérifier que le tag est correct (tag2)
			if (FICVerifBalise(pcToken3, pcTag2) == true) {
				pcToken3 = strtok(NULL, "=");
				if (pcToken3 == nullptr || pcToken3[0] == '\0') {
					delete[] pcLigne;
					delete[] ppuiValeursRetour;
					throw CException(EXCMiseEnFormeIncorecte);
				}
				// On convertit la valeur en entier
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
			//On vérifie que le tag est correct (tag3)
			if (FICVerifBalise(pcToken3, pcTag3) == true) {
				pcToken3 = strtok(NULL, "=");
				if (pcToken3 == nullptr || pcToken3[0] == '\0') {
					delete[] pcLigne;
					delete[] ppuiValeursRetour;
					throw CException(EXCMiseEnFormeIncorecte);
				}
				// On convertit la valeur en entier
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

	// Tant que la ligne n'est pas vide
	do
	{
		// On récupère la ligne
		IFSFICFichier.getline(pcLigne, STR_LENGTH);
		
		// On supprime les epsaces et les tabulations de la ligne
		FICSupp_char(pcLigne, ' ');
		FICSupp_char(pcLigne, '\t');

		//On met à jour un compteur pour ne pas déclencher de boucle infinie
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

	// Mise en minuscule de la chaine
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

	// Suppression du caratère passé en paramètre de la chaine
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
