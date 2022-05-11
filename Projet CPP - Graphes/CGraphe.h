#pragma once
#include "CSommet.h"
#include "CArc.h"
#include "CException.h"

#include <cstdio>
#include <iostream>
#include <cstdlib>

#define entrant 0
#define sortant 1
#define EXCAucunParamRecherche 20
#define EXCValeurSommetIntrouvable 21
#define EXCListeSommetInexistante 22
class CSommet;
class CArc;
class CGraphe {
private :

	//Attributs
	CSommet* pSOMGRAListeSommet;
	unsigned int uiGRANbSommet;
	unsigned int uiGRANbArcs;
	bool bGRAOriente;

public :

	//Constructeur & Destructeur
	CGraphe();
	CGraphe(unsigned int uiNbSommet);
	~CGraphe();

	//Accesseurs
	CSommet* GRALireSommets();
	unsigned int GRALireNbSommet();
	unsigned int GRALireNbArcs();
	bool GRALireType();

	//Modifieurs
	void GRAAjouterArc(CSommet& SOMDepart, CSommet& SOMArrivee);
	void GRASupprimerArc(CArc* pARCParam);
	void GRAAjouterSommet(CSommet& SOMSommet);
	void GRASupprimerSommet(CSommet& SOMSommet);

	//Méthodes
	CSommet& GRARechercheArc(CArc * pARCParam, int iParam);
	CSommet& GRARechercheSommet(int iVal);
	void GRAAffichage();
	void GRAInversion();
	void GRANonOriente();
	
};