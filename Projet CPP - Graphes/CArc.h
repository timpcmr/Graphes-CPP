#ifndef ARC
#define ARC

#define entrant 0
#define sortant 1
#define EXCArretProgramme 50

class CArc {
private :

	//Attribut
	int iARCNumeroSommet;
public :

	//Constructeurs & Destructeurs

	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Construction d'un objet CArc par défaut											   ****
	******************************************************************************************************/
	CArc();

	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Construction d'un objet CArc par recopie										   ****
	******************************************************************************************************/
	CArc(const CArc& ARCParam);

	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Construction d'un objet CArc par valeur de destination							   ****
	******************************************************************************************************/
	CArc(int iParam);

	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Destruction d'un objet CArc par défaut											   ****
	******************************************************************************************************/
	~CArc();

	//Accesseur

	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties :	int iARCNumeroSommet : Destination de l'arc										   ****
	**** Entraîne :	Lecture de valeur de destination de l'arc	 									   ****
	******************************************************************************************************/
	int ARCLireDestination() const;

	//Modifieur

	/******************************************************************************************************
	**** Entrées :	int iDestination : Nouvelle destination de l'arc								   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne :	Changement de valeur de destination de l'arc									   ****
	******************************************************************************************************/
	void ARCChangerDestination(int iDestination);

	//Surcharge

	/******************************************************************************************************
	**** Entrées : const CArc ARCparam : CArc à copier												   ****
	**** Nécessite : ARCparam non nul														  	       ****
	**** Sorties :	CArc & this : Objet modifié selon le paramètre									   ****
	**** Entraîne : La copie de l'objet CArc en paramètre											   ****
	******************************************************************************************************/
	CArc& operator=(const CArc ARCparam);
};

#endif