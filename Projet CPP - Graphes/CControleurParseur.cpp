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

CGraphe CControleurParseur::CONLireGraphe()
{
	return GRACONGraphe;
}

void CControleurParseur::CONLireFichierGraphe()
{
	Cfichier FICParseur(pcCONChemin);
	unsigned int uiNbArcs, uiNbSommets;
	unsigned int uiBoucle;

	uiNbArcs = FICParseur.FICLireChiffre((char*)"nbarcs");
	uiNbSommets = FICParseur.FICLireChiffre((char*)"nbsommets");

	unsigned int* piSommets = FICParseur.FICLireTabSansVirgule(uiNbSommets, (char*)"sommets", (char*)"numero");
	unsigned int** ppiArcs = FICParseur.FICLireTabAvecVirgule(uiNbSommets, (char*)"arcs", (char*)"debut", (char*)"fin");
	
	//Affectation Graphe
		//Sommets
	for (uiBoucle = 0; uiBoucle < uiNbSommets; uiBoucle++) {
		GRACONGraphe.GRAAjouterSommet(piSommets[uiBoucle]);
	}

		//Arcs
	for (uiBoucle = 0; uiBoucle < uiNbArcs; uiBoucle++) {
		GRACONGraphe.GRAAjouterArc(ppiArcs[uiBoucle][0], ppiArcs[uiBoucle][1]);
	}
	
	delete[] piSommets;
	for (uiBoucle = 0; uiBoucle < uiNbArcs; uiBoucle++) {
		delete[] ppiArcs[uiBoucle];
	}
	delete[] ppiArcs;
	
}
