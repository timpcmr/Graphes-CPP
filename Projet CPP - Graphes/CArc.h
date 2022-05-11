#ifndef ARC
#define ARC

class CSommet;

class CArc {
private :

	//Attribut
	CSommet* pSOMARCDestination;
public :

	//Constructeurs & Destructeurs
	CArc();
	CArc(CArc& ARCParam);
	CArc(CSommet* pSOMParam);
	~CArc();

	//Accesseur
	CSommet* ARCLireDestination();

	//Modifieur
	void ARCChangerDestination(CSommet* pSOMDestination);

	//Méthodes
};

#endif