#include "CGrapheOperations.h"

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

CGraphe * CGrapheOperations::GRANonOriente(const CGraphe* pGRAParam) const
{
	CGraphe* pGRAGrapheRetour = new CGraphe(*pGRAParam);
	//unsigned int uiboucle, uiboucle2;
	pGRAGrapheRetour->GRAModifierType(false);
	/*
	for (uiboucle = 0; uiboucle < GRAParam->GRALireNbSommet(); uiboucle++) {
		pGRAGrapheRetour->GRAAjouterSommet(GRAParam->GRALireSommets()[uiboucle]->SOMLireNumero());
	}
	for (uiboucle = 0; uiboucle < GRAParam->GRALireNbSommet(); uiboucle++) {
		for (uiboucle2 = 0; uiboucle2 < GRAParam->GRALireSommets()[uiboucle]->SOMLireNbArcsSortants(); uiboucle2++) {
			pGRAGrapheRetour->GRAAjouterArc(GRAParam->GRALireSommets()[uiboucle]->SOMLireNumero(), GRAParam->GRALireSommets()[uiboucle]->SOMLireArcsSortants()[uiboucle2]->ARCLireDestination());
			pGRAGrapheRetour->GRAAjouterArc(GRAParam->GRALireSommets()[uiboucle]->SOMLireArcsSortants()[uiboucle2]->ARCLireDestination(), GRAParam->GRALireSommets()[uiboucle]->SOMLireNumero());
		}
	}
	*/
	return pGRAGrapheRetour;
}
