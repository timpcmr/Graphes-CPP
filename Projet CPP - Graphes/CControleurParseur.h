#ifndef CONTROL_PARSER
#define CONTROL_PARSER

#include "CGraphe.h"
#include "CFichier.h"

#define EXCArretProgramme 50

#define EXCCheminVideCtrlParseur 30


class CControleurParseur {
private:
	char* pcCONChemin;
	CGraphe* pGRACONGraphe;
public:
	CControleurParseur();
	CControleurParseur(char* pcChemin);
	~CControleurParseur();

	char* CONLireChemin();
	void CONModifierChemin(char* pcChemin);

	CGraphe* CONLireGraphe();
	void CONLireFichierGraphe();
};










#endif // !CONTROL_PARSER
