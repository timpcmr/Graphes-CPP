#ifndef GRAPHE
#define GRAPHE

#pragma warning(disable : 6386)

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
	CGraphe(const CGraphe& GRAGraphe);
	~CGraphe();

	//Accesseurs
	const CSommet* const* GRALireSommets() const;
	unsigned int GRALireNbSommet() const;
	unsigned int GRALireNbArcs() const;
	bool GRALireType() const;

	//Modifieurs
	void GRAAjouterArc(CSommet* SOMDepart, CSommet* SOMArrivee);
	void GRAAjouterArc(int iDepart, int iArrivee);
	void GRASupprimerArc(CArc* pARCParam);
	void GRAAjouterSommet(CSommet& pSOMSommet);
	void GRAAjouterSommet(int iNum);
	void GRASupprimerSommet(int iNumSommet);
	void GRAModifierType(bool bParam);

	//Méthodes
	CSommet* GRARechercheSommetAvecArc(CArc * pARCParam, int iParam) const;
	CSommet* GRARechercheSommet(int iVal) const;
	int GRARechercheIndexSommet(int iSommet) const;
	bool GRANumeroSommetUnique(int iVal);
	void GRAAffichage() const;
	CGraphe* GRAInversion() const;
	CGraphe* GRANonOriente() const;
	

};

#endif