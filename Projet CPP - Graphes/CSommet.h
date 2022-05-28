#ifndef SOMMET
#define SOMMET

#pragma warning(disable : 6385)
#pragma warning(disable : 6386)

#include "CArc.h"
#include "CException.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>

#define EXCSuppImpossible 40
#define EXCPointeurArcNul 41
#define EXCValeurArcIntrouvable 424222

class CSommet {
private :

	//Attributs
	int iSOMNumero;
	unsigned int uiSOMNbArcsSommetSortants;
	unsigned int uiSOMNbArcsSommetEntrants;
	CArc** ppARCSOMEntrant;
	CArc** ppARCSOMSortant;
public :

	//Constructeurs & Destructeurs

	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties : CSommet																			   ****
	**** Entraîne : Crée un nouvel objet CSommet par défaut											   ****
	******************************************************************************************************/
	CSommet() = delete;

	/******************************************************************************************************
	**** Entrées :	SOMParam : CSommet&																   ****
	**** Nécessite :																		  	       ****
	**** Sorties : CSommet																			   ****
	**** Entraîne : Crée un nouvel objet CSommet par copie de SOMParam								   ****
	******************************************************************************************************/
	CSommet(const CSommet &SOMParam);

	/******************************************************************************************************
	**** Entrées : iNumero : int																	   ****
	**** Nécessite :																		  	       ****
	**** Sorties : CSommet																			   ****
	**** Entraîne : Crée un nouvel objet CSommet possédant le numéro iNumero						   ****
	******************************************************************************************************/
	CSommet(int iNumero);

	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties : 																					   ****
	**** Entraîne : Destruction de l'objet CSommet par défaut										   ****
	******************************************************************************************************/
	~CSommet();

	//Accesseurs

	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties : iSOMNumero : int																	   ****
	**** Entraîne : Renvoie le numéro du sommet														   ****
	******************************************************************************************************/
	int SOMLireNumero() const;

	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties : uiSOMNbArcsSommetEntrants : unsigned int											   ****
	**** Entraîne : Renvoie le nombre d'arcs entrants du sommet										   ****
	******************************************************************************************************/
	unsigned int SOMLireNbArcsEntrants() const;

	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties : uiSOMNbArcsSommetSortants : unsigned int											   ****
	**** Entraîne : Renvoie le nombre d'arcs sortants du sommet										   ****
	******************************************************************************************************/
	unsigned int SOMLireNbArcsSortants() const;

	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties : ppARCSOMSortants : CArc**														   ****
	**** Entraîne : Renvoie la liste des arcs sortants												   ****
	******************************************************************************************************/
	const CArc * const* SOMLireArcsSortants() const;

	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties : ppARCSOMEntrants : CArc**														   ****
	**** Entraîne : Renvoie la liste des arcs entrants												   ****
	******************************************************************************************************/
	const CArc * const* SOMLireArcsEntrants() const;

	//Modifieurs

	/******************************************************************************************************
	**** Entrées : iNumero : int																	   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Modifie le numéro du sommet														   ****
	******************************************************************************************************/
	void SOMModifierNumero(int iNumero);

	/******************************************************************************************************
	**** Entrées : pARCArc : CArc*																	   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Ajoute CArc dans la liste des arcs entrants du sommet							   ****
	******************************************************************************************************/
	void SOMAjouterArcEntrant(CArc* pARCArc);

	/******************************************************************************************************
	**** Entrées : pARCArc : CArc*																	   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Supprime CArc dans la liste des arcs entrants du sommet							   ****
	******************************************************************************************************/
	void SOMSupprimerArcEntrant(CArc* pARCArc);

	/******************************************************************************************************
	**** Entrées : pARCArc : CArc*																	   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Ajoute CArc dans la liste des arcs sortants du sommet							   ****
	******************************************************************************************************/
	void SOMAjouterArcSortant(CArc* pARCArc);

	/******************************************************************************************************
	**** Entrées : pARCArc : CArc*																	   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Supprime CArc dans la liste des arcs sortants du sommet							   ****
	******************************************************************************************************/
	void SOMSupprimerArcSortant(CArc* pARCArc);

	//Méthodes

	/***************************************************************************************************************************
	**** Entrées : iDestination : int, iParam : int																			****
	**** Nécessite :																		  								****
	**** Sorties :																											****
	**** Entraîne : Recherche et renvoie l'arc désiré à partir de sa destination et du fait qu'il soit entrant ou sortant	****
	***************************************************************************************************************************/
	const CArc* SOMRechercheArc(int iDestination, int iParam) const;

	//Surcharge

	/******************************************************************************************************
	**** Entrées : SOMSommet : CSommet																   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Crée un nouvel objet CSommet par copie de SOMSommet								   ****
	******************************************************************************************************/
	CSommet& operator=(const CSommet SOMSommet);

};

#endif