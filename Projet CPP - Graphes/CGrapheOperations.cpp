#include "CGrapheOperations.h"

/******************************************************************************************************
**** Entrées : pGRAParam : CGraphe*																   ****
**** Nécessite :																		  	       ****
**** Sorties : pGRARetour : CGraphe*															   ****
**** Entraîne : Crée un nouvel objet CGraphe inverse à pGRAParam								   ****
******************************************************************************************************/
CGraphe * CGrapheOperations::GRAInversion(const CGraphe* GRAParam) const
{
	CGraphe* pGRARetour = new CGraphe();
	unsigned int uiboucle, uiboucle2;
	for (uiboucle = 0; uiboucle < GRAParam->GRALireNbSommet(); uiboucle++) {
		pGRARetour->GRAAjouterSommet(GRAParam->GRALireSommets()[uiboucle]->SOMLireNumero());
	}

	for (uiboucle = 0; uiboucle < GRAParam->GRALireNbSommet(); uiboucle++) {
		for (uiboucle2 = 0; uiboucle2 < GRAParam->GRALireSommets()[uiboucle]->SOMLireNbArcsSortants(); uiboucle2++) {
			pGRARetour->GRAAjouterArc(GRAParam->GRALireSommets()[uiboucle]->SOMLireArcsSortants()[uiboucle2]->ARCLireDestination(), GRAParam->GRALireSommets()[uiboucle]->SOMLireNumero());
		}
	}
	return pGRARetour;
}

/******************************************************************************************************
**** Entrées : pGRAParam : CGraphe*																   ****
**** Nécessite :																		  	       ****
**** Sorties : pGRARetour : CGraphe*															   ****
**** Entraîne : Crée un nouvel objet CGraphe en copiant pGRAParam mais étant non-orienté		   ****
******************************************************************************************************/
CGraphe * CGrapheOperations::GRANonOriente(const CGraphe* pGRAParam) const
{
	CGraphe* pGRAGrapheRetour = new CGraphe(*pGRAParam);
	pGRAGrapheRetour->GRAModifierType(false);
	
	return pGRAGrapheRetour;
}
