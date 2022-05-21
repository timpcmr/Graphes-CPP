#ifndef GRAPHE
#define GRAPHE


#include "CSommet.h"
#include "CException.h"

#include <cstdio>
#include <iostream>
#include <cstdlib>

#define EXCAucunParamRecherche 20
#define EXCValeurSommetIntrouvable 21
#define EXCListeSommetInexistante 22

class CSommet;
class CArc;

class CGraphe {
private :

	//Attributs
	CSommet** ppSOMGRAListeSommet;
	unsigned int uiGRANbSommet;
	unsigned int uiGRANbArcs;
	bool bGRAOriente;

public :

	//Constructeur & Destructeur
	CGraphe();
	~CGraphe();

	//Accesseurs
	CSommet** GRALireSommets();
	unsigned int GRALireNbSommet();
	unsigned int GRALireNbArcs();
	bool GRALireType();

	//Modifieurs
	void GRAAjouterArc(CSommet* SOMDepart, CSommet* SOMArrivee);
	void GRAAjouterArc(int iDepart, int iArrivee);
	void GRASupprimerArc(CArc* pARCParam);
	void GRAAjouterSommet(CSommet* pSOMSommet);
	void GRAAjouterSommet(int iNum);
	void GRASupprimerSommet(int iNumSommet);

	//Méthodes
	CSommet* GRARechercheSommetAvecArc(CArc * pARCParam, int iParam);
	CSommet* GRARechercheSommet(int iVal);
	int GRARechercheIndexSommet(int iSommet);
	bool GRANumeroSommetUnique(int iVal);
	void GRAAffichage();
	CGraphe* GRAInversion();
	CGraphe* GRANonOriente();
	

};

#endif