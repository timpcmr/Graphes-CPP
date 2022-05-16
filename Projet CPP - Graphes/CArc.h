#ifndef ARC
#define ARC

class CArc {
private :

	//Attribut
	int iARCNumeroSommet;
public :

	//Constructeurs & Destructeurs
	CArc();
	CArc(CArc& ARCParam);
	CArc(int iParam);
	~CArc();

	//Accesseur
	int ARCLireDestination();

	//Modifieur
	void ARCChangerDestination(int iDestination);

	//Méthodes
};

#endif