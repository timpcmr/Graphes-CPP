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
	CSommet(const CSommet &SOMParam);
	CSommet(int iNumero);
	~CSommet();

	//Accesseurs
	int SOMLireNumero() const;
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