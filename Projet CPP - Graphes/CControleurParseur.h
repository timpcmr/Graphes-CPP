#ifndef CONTROL_PARSER
#define CONTROL_PARSER

#include "CGraphe.h"
#include "Cfichier.h"

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
