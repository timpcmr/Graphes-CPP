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
	int iNbArcs, iNbSommets;
	unsigned int uiBoucle1, uiBoucle2;

	iNbArcs = FICParseur.FICLireChiffre((char*)"NBArcs");
	iNbSommets = FICParseur.FICLireChiffre((char*)"NBSommets");

	int* piSommets = FICParseur.FICLireTabSansVirgule(iNbSommets, (char*)"Sommets", (char*)"Numero");
	int** ppiArcs = FICParseur.FICLireTabAvecVirgule(iNbSommets, (char*)"Arcs", (char*)"Debut", (char*)"Fin");
	/*
	for (uiBoucle1 = 0; uiBoucle1 < iNbSommets; uiBoucle1++) {
		GRACONGraphe.GRAAjouterSommet()
	}
	*/
	//TBC
}
