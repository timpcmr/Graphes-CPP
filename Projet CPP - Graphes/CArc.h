#pragma once
#include "CGraphe.h"
#include "CException.h"
#include "CSommet.h"
class CSommet;
class CArc {
private :

	//Attribut
	CSommet* pSOMARCDestination;
public :

	//Constructeurs & Destructeurs
	CArc();
	CArc(CArc& ARCParam);
	CArc(CSommet& SOMParam);
	~CArc();

	//Accesseur
	CSommet* ARCLireDestination();

	//Modifieur
	void ARCChangerDestination(CSommet* pSOMDestination);

	//Méthodes
};