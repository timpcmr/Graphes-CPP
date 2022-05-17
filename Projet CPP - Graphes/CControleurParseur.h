#ifndef CONTROL_PARSER
#define CONTROL_PARSER

#include "CGraphe.h"
#include "Cfichier.h"

class CControleurParseur {
private:
	char* pcCONChemin;
	CGraphe GRACONGraphe;
public:
	CControleurParseur();
	CControleurParseur(char* pcChemin);
	~CControleurParseur();

	char* CONLireChemin();
	void CONModifierChemin(char* pcChemin);

	void CONLireGraphe();
};










#endif // !CONTROL_PARSER
