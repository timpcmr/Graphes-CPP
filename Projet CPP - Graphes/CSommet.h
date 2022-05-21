#ifndef SOMMET
#define SOMMET
#include "CArc.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>

//class CArc;

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
	CSommet() = delete;
	CSommet(CSommet &SOMParam);
	CSommet(int iNumero);
	~CSommet();

	//Accesseurs
	int SOMLireNumero();
	unsigned int SOMLireNbArcsEntrants();
	unsigned int SOMLireNbArcsSortants();
	CArc ** SOMLireArcsSortants();
	CArc ** SOMLireArcsEntrants();

	//Modifieurs
	void SOMModifierNumero(int iNumero);
	void SOMAjouterArcEntrant(CArc* pARCArc);
	void SOMSupprimerArcEntrant(CArc* pARCArc);
	void SOMAjouterArcSortant(CArc* pARCArc);
	void SOMSupprimerArcSortant(CArc* pARCArc);

	//Méthodes
	CArc* SOMRechercheArc(int iDestination, int iParam);



};

#endif