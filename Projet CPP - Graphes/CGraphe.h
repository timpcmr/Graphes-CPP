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
#define EXCPointeurSommetNul 23

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
	void GRAAjouterArc(CSommet* pSOMDepart, CSommet* pSOMArrivee);
	void GRAAjouterArc(int iDepart, int iArrivee);
	void GRASupprimerArc(int iDepart, int iArrivee);
	void GRAAjouterSommet(CSommet& pSOMSommet);
	void GRAAjouterSommet(int iNum);
	void GRASupprimerSommet(CSommet* pSOMParam);
	void GRAModifierType(bool bParam);

	//Méthodes
	CSommet* GRARechercheSommet(int iVal) const;
	int GRARechercheIndexSommet(int iSommet) const;
	bool GRANumeroSommetUnique(int iVal);
	void GRAAffichage() const;

	//Surcharge
	CGraphe& operator=(const CGraphe GRAparam);
};

#endif