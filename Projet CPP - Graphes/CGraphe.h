#pragma once
#include "CSommet.h"
#include "CArc.h"
#include "CException.h"
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
	void GRAModifierNbArcs(unsigned int uiNombre);
	void GRAModifierType(bool bType);
	void GRAAjouterSommet(CSommet SOMSommet);
	void GRASupprimerSommet(CSommet SOMSommet);

	//Méthodes
	void GRAAffichage();
	void GRAInversion();
	
};