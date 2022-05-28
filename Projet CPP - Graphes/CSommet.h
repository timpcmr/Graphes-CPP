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
	unsigned int SOMLireNbArcsSortants() const;
	const CArc * const* SOMLireArcsSortants() const;
	const CArc * const* SOMLireArcsEntrants() const;

	//Modifieurs
	void SOMModifierNumero(int iNumero);
	void SOMAjouterArcEntrant(CArc* pARCArc);
	void SOMSupprimerArcEntrant(CArc* pARCArc);
	void SOMAjouterArcSortant(CArc* pARCArc);
	void SOMSupprimerArcSortant(CArc* pARCArc);

	//Méthodes
	const CArc* SOMRechercheArc(int iDestination, int iParam) const;

	//Surcharge
	CSommet& operator=(const CSommet SOMSommet);

};

#endif