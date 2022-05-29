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
#define EXCNumeroIndisponible 24

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
	
	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Construction d'un objet CGraphe par défaut										   ****
	******************************************************************************************************/
	CGraphe();

	/******************************************************************************************************
	**** Entrées : GRAGraphe : CGraphe&																   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Construction d'un objet CGraphe par recopie de GRAGraphe						   ****
	******************************************************************************************************/
	CGraphe(const CGraphe& GRAGraphe);
	
	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Destruction de l'objet CGraphe													   ****
	******************************************************************************************************/
	~CGraphe();

	//Accesseurs
	
	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties : ppSOMGRAListeSommet : CSommet**													   ****
	**** Entraîne : Renvoie la liste des sommets de l'objet CGraphe									   ****
	******************************************************************************************************/
	const CSommet* const* GRALireSommets() const;
	
	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties : uiGRANbSommet : unsigned int														   ****
	**** Entraîne : Renvoie le nombre de sommet de l'objet CGraphe									   ****
	******************************************************************************************************/
	unsigned int GRALireNbSommet() const;

	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties : uiGRANbArcs : unsigned int														   ****
	**** Entraîne : Renvoie le nombre d'arcs de l'objet CGraphe										   ****
	******************************************************************************************************/
	unsigned int GRALireNbArcs() const;

	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties : bGRAOriente : bool																   ****
	**** Entraîne : Renvoie le type de l'objet CGraphe (1 si oriente, 0 si non-oriente)				   ****
	******************************************************************************************************/
	bool GRALireType() const;

	//Modifieurs
	
	/******************************************************************************************************
	**** Entrées : pSomDepart : CSommet*, pSOMArrivee : CSommet*									   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Crée un arc partant du sommet pSOMDepart allant vers le sommet pSOMArrivee		   ****
	******************************************************************************************************/
	void GRAAjouterArc(CSommet* pSOMDepart, CSommet* pSOMArrivee);

	/*****************************************************************************************************************
	**** Entrées : iDepart : int, iArrivee : int															      ****
	**** Nécessite :																		  				      ****
	**** Sorties :																								  ****
	**** Entraîne : Crée un arc partant du sommet ayant le numero iDepart vers le sommet ayant le numéro iArrivee ****
	*****************************************************************************************************************/
	void GRAAjouterArc(int iDepart, int iArrivee);

	/*********************************************************************************************************
	**** Entrées : iDepart : int, iArrivee : int														  ****
	**** Nécessite :																		  			  ****
	**** Sorties :																						  ****
	**** Entraîne : Supprime l'arc partant du sommet numéro iDepart allant vers le sommet numéro iArrivee ****
	*********************************************************************************************************/
	void GRASupprimerArc(int iDepart, int iArrivee);

	/******************************************************************************************************
	**** Entrées : SOMSommet CSommet&																   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Ajoute le sommet SOMSommet au graphe											   ****
	******************************************************************************************************/
	void GRAAjouterSommet(CSommet& SOMSommet);

	/******************************************************************************************************
	**** Entrées : iNum : int																		   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Ajoute le sommet numero iNum au graphe											   ****
	******************************************************************************************************/
	void GRAAjouterSommet(int iNum);
	
	/******************************************************************************************************
	**** Entrées : pSOMParam : CSommet*																   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Supprime le sommet pSOMParam du graphe											   ****
	******************************************************************************************************/
	void GRASupprimerSommet(CSommet* pSOMParam);

	/******************************************************************************************************
	**** Entrées : pSOMParam : CSommet*, iNum : int													   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Modifie le numéro du sommet pSOMParam par le numero iNum						   ****
	******************************************************************************************************/
	void GRAModifierNumSommet(CSommet* pSOMParam, int iNum);
	
	/******************************************************************************************************
	**** Entrées : bParam : bool																	   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Modifie le type du graphe (0 = non-orienté, 1 = orienté)						   ****
	******************************************************************************************************/
	void GRAModifierType(bool bParam);

	//Méthodes

	/*************************************************************************************************************
	**** Entrées : iVal : int																				  ****
	**** Nécessite :																		  				  ****
	**** Sorties : CSommet*																					  ****
	**** Entraîne : Renvoie un pointeur sur le sommet numéro iVal s'il existe, renvoie un pointeur null sinon ****
	*************************************************************************************************************/
	CSommet* GRARechercheSommet(int iVal) const;

	/******************************************************************************************************
	**** Entrées : iSommet : int																	   ****
	**** Nécessite :																		  	       ****
	**** Sorties : int																				   ****
	**** Entraîne : Renvoie la position du sommet numéro iSommet s'il existe, -1 sinon				   ****
	******************************************************************************************************/
	int GRARechercheIndexSommet(int iSommet) const;

	/******************************************************************************************************
	**** Entrées : iVal	: int																		   ****
	**** Nécessite :																		  	       ****
	**** Sorties : bool																				   ****
	**** Entraîne : Renvoie true si le sommet numéro iVal n'existe pas, false sinon					   ****
	******************************************************************************************************/
	bool GRANumeroSommetUnique(int iVal);

	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Fonction d'affichage du graphe													   ****
	******************************************************************************************************/
	void GRAAffichage() const;

	//Surcharge
	
	/******************************************************************************************************
	**** Entrées : GRAParam : CGraphe&																   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : La copie de l'objet CGraphe en paramètre										   ****
	******************************************************************************************************/
	CGraphe& operator=(const CGraphe &GRAParam);
};

#endif