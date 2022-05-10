#pragma once
#include "CGraphe.h"
#include "CException.h"
class CArc {
private :

	//Attribut
	CSommet* pSOMARCDestination;
public :

	//Constructeurs & Destructeurs
	CArc();
	CArc(CArc &ARCParam);
	CArc(CSommet& pSOMParam);
	~CArc();

	//Accesseur
	CSommet* ARCLireDestination();

	//Modifieur
	void ARCChangerDestination(CSommet* pSOMDestination);

	//M�thodes
};