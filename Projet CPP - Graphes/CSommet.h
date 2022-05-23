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

	//Surcharge
	CSommet& operator=(CSommet SOMSommet);

};

#endif