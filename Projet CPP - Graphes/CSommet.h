#pragma once
#include "CArc.h"
#include "CException.h"
class CSommet {
private :

	//Attributs
	int iSOMNumero;
	unsigned int uiSOMNbArcsSommet;
	CArc** ppARCSOMEntrant;
	CArc** ppARCSOMSortant;
public :

	//Constructeurs & Destructeurs
	CSommet();
	CSommet(CSommet &SOMParam);
	CSommet(int iNumero, unsigned int uiNbArcSommet);
	~CSommet();

	//Accesseurs
	int SOMLireNumero();
	unsigned int SOMLireNbArcs();
	CArc ** SOMLireArcsSortants();
	CArc ** SOMLireArcsEntrants();

	//Modifieurs
	void SOMModifierNumero(int iNumero);
	void SOMAjouterArcEntrant(CArc* pARCArc);
	void SOMSupprimerArcEntrant(CArc* pARCArc);
	void SOMAjouterArcSortant(CArc* pARCArc);
	void SOMSupprimerArcSortant(CArc* pARCArc);

};