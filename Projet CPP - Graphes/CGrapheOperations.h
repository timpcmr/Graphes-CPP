#pragma once
#ifndef COPGRAPHES
#define COPGRAPHES

#include "CGraphe.h"

class CGrapheOperations {
public:

	/******************************************************************************************************
	**** Entrées : pGRAParam : CGraphe*																   ****
	**** Nécessite :																		  	       ****
	**** Sorties : pGRARetour : CGraphe*															   ****
	**** Entraîne : Crée un nouvel objet CGraphe inverse à pGRAParam								   ****
	******************************************************************************************************/
	CGraphe* GRAInversion(const CGraphe* pGRAParam) const;

	/******************************************************************************************************
	**** Entrées : pGRAParam : CGraphe*																   ****
	**** Nécessite :																		  	       ****
	**** Sorties : pGRARetour : CGraphe*															   ****
	**** Entraîne : Crée un nouvel objet CGraphe en copiant pGRAParam mais étant non-orienté		   ****
	******************************************************************************************************/
	CGraphe* GRANonOriente(const CGraphe* pGRAParam) const;
};

#endif