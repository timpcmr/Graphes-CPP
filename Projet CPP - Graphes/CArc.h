#ifndef ARC
#define ARC

#define entrant 0
#define sortant 1
#define EXCArretProgramme 50

class CArc {
private :

	//Attribut
	int iARCNumeroSommet;
public :

	//Constructeurs & Destructeurs
	CArc();
	CArc(const CArc& ARCParam);
	CArc(int iParam);
	~CArc();

	//Accesseur
	int ARCLireDestination() const;

	//Modifieur
	void ARCChangerDestination(int iDestination);

	//Surcharge
	CArc& operator=(const CArc ARCparam);
};

#endif