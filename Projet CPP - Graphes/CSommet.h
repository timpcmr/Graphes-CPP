#ifndef SOMMET
#define SOMMET
#include "CArc.h"
#include <cstdlib>

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
	CSommet(int iNumero, unsigned int uiNbArcSommetEntrants, unsigned int uiNbArcSommetSortants);
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

	//Surcharges



};

#endif