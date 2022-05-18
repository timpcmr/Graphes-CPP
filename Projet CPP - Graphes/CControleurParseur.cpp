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

CGraphe CControleurParseur::CONLireGraphe()
{
	return GRACONGraphe;
}

void CControleurParseur::CONLireFichierGraphe()
{
	Cfichier FICParseur(pcCONChemin);
	unsigned int uiNbArcs, uiNbSommets;
	unsigned int uiBoucle;

	uiNbArcs = FICParseur.FICLireChiffre((char*)"NBArcs");
	uiNbSommets = FICParseur.FICLireChiffre((char*)"NBSommets");

	unsigned int* piSommets = FICParseur.FICLireTabSansVirgule(uiNbSommets, (char*)"Sommets", (char*)"Numero");
	unsigned int** ppiArcs = FICParseur.FICLireTabAvecVirgule(uiNbSommets, (char*)"Arcs", (char*)"Debut", (char*)"Fin");
	
	//Affectation Graphe
		//Sommets
	for (uiBoucle = 0; uiBoucle < uiNbSommets; uiBoucle++) {
		GRACONGraphe.GRAAjouterSommet(piSommets[uiBoucle]);
	}

		//Arcs
	for (uiBoucle = 0; uiBoucle < uiNbArcs; uiBoucle++) {
		GRACONGraphe.GRAAjouterArc(ppiArcs[uiBoucle][0], ppiArcs[uiBoucle][1]);
	}

	GRACONGraphe.GRAAffichage();
	//TBC
}
