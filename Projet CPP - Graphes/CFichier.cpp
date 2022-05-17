#include "CFichier.h"
#pragma warning(disable : 4996)


Cfichier::Cfichier()
{
	pcLigne = new char[STR_LENGTH];
}

Cfichier::Cfichier(char * pcChemin)
{
	pcLigne = new char[STR_LENGTH];
	IFSFichier = ifstream(pcChemin);
	if (!IFSFichier.is_open()) {
		throw CException(EXCFichierNonOuvert);
	}
}

Cfichier::~Cfichier()
{
	delete[] pcLigne;
	IFSFichier.close();
}

void Cfichier::FICInitialiserFlot(char * pcChemin)
{
	IFSFichier = ifstream(pcChemin);
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

	if (IFSFichier.is_open()){
		FICLigneSuivante(pcLigne);
		char * pcToken = strtok(pcLigne, "=");

		while (FICVerifBalise(FICMinuscule(pcToken), FICMinuscule(pcTag)) == false) {
			FICLigneSuivante(pcLigne);
			pcToken = strtok(pcLigne, "=");
		}
		
		pcToken = strtok(NULL, "=");
		iValeurRetournee = atoi(pcToken);

		//Retour en haut du fichier pour les prochaines utilisations du flot
		IFSFichier.clear();
		IFSFichier.seekg(IFSFichier.beg);
	}
	else {
		throw CException(EXCFichierNonOuvert);
	}
	return iValeurRetournee;
}

void Cfichier::FICLigneSuivante(char* pcLigne)
{
	unsigned int uiBoucle = 0;

	if (pcLigne == nullptr) {
		throw CException(EXCLigneNulle);
	}
	if (!IFSFichier) {
		throw CException(EXCFichierNonOuvert);
	}

	do
	{
		IFSFichier.getline(pcLigne, STR_LENGTH);
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
