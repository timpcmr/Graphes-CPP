#include "CControleurParseur.h"

CControleurParseur::CControleurParseur()
{
	pcCONChemin = nullptr;
	GRACONGraphe = CGraphe();
}

CControleurParseur::CControleurParseur(char* pcChemin)
{
	pcCONChemin = pcChemin;
	GRACONGraphe = CGraphe();
}

CControleurParseur::~CControleurParseur()
{
	delete pcCONChemin;
	pcCONChemin = nullptr;
}

char* CControleurParseur::CONLireChemin()
{
	return pcCONChemin;
}

void CControleurParseur::CONModifierChemin(char* pcChemin)
{
	pcCONChemin = pcChemin;
}

void CControleurParseur::CONLireGraphe()
{
	Cfichier FICParseur(pcCONChemin);
	unsigned int uiNbArcs, uiNbSommets;
	unsigned int uiBoucle1, uiBoucle2;

	uiNbArcs = FICParseur.FICLireChiffre((char*)"NBArcs");
	uiNbSommets = FICParseur.FICLireChiffre((char*)"NBSommets");

	unsigned int* piSommets = FICParseur.FICLireTabSansVirgule(uiNbSommets, (char*)"Sommets", (char*)"Numero");
	unsigned int** ppiArcs = FICParseur.FICLireTabAvecVirgule(uiNbSommets, (char*)"Arcs", (char*)"Debut", (char*)"Fin");
	
	//Affectation Graphe
	//TBC
}
