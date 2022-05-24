#include "CArc.h"

/******************************************************************************************************
**** Entrées :																					   ****
**** Nécessite :																		  	       ****
**** Sorties :																					   ****
**** Entraîne : Construction d'un objet CArc par défaut											   ****
******************************************************************************************************/
CArc::CArc()
{
	iARCNumeroSommet = -1;
}

/******************************************************************************************************
**** Entrées :																					   ****
**** Nécessite :																		  	       ****
**** Sorties :																					   ****
**** Entraîne : Construction d'un objet CArc par recopie										   ****
******************************************************************************************************/
CArc::CArc(const CArc& ARCParam)
{
	iARCNumeroSommet = ARCParam.ARCLireDestination();
}

/******************************************************************************************************
**** Entrées :																					   ****
**** Nécessite :																		  	       ****
**** Sorties :																					   ****
**** Entraîne : Construction d'un objet CArc par valeur de destination							   ****
******************************************************************************************************/
CArc::CArc(int iParam)
{
	iARCNumeroSommet = iParam;
}

/******************************************************************************************************
**** Entrées :																					   ****
**** Nécessite :																		  	       ****
**** Sorties :																					   ****
**** Entraîne : Destruction d'un objet CArc par défaut											   ****
******************************************************************************************************/
CArc::~CArc()
{

}

/******************************************************************************************************
**** Entrées :																					   ****
**** Nécessite :																		  	       ****
**** Sorties :	int iARCNumeroSommet : Destination de l'arc										   ****
**** Entraîne :	Lecture de valeur de destination de l'arc	 									   ****
******************************************************************************************************/
int CArc::ARCLireDestination() const
{
	return iARCNumeroSommet;
}

/******************************************************************************************************
**** Entrées :	int iDestination : Nouvelle destination de l'arc								   ****
**** Nécessite :																		  	       ****
**** Sorties :																					   ****
**** Entraîne :	Changement de valeur de destination de l'arc									   ****
******************************************************************************************************/
void CArc::ARCChangerDestination(int iDestination)
{
	iARCNumeroSommet= iDestination;
}

/******************************************************************************************************
**** Entrées : const CArc ARCparam : CArc à copier												   ****
**** Nécessite : ARCparam non nul														  	       ****
**** Sorties :	CArc & this : Objet modifié selon le paramètre									   ****
**** Entraîne : La copie de l'objet CArc en paramètre											   ****
******************************************************************************************************/
CArc& CArc::operator=(const CArc ARCparam)
{
	iARCNumeroSommet = (int)ARCparam.ARCLireDestination();
	return *this;
}
