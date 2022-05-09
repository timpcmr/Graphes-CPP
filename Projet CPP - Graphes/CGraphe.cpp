#pragma once

#include "CGraphe.h"
#include "CSommet.h"
CGraphe::CGraphe()
{
	pSOMGRAListeSommet = new CSommet();
	uiGRANbArcs = 0;
	uiGRANbSommet = 0;
	bGRAOriente = true;
}

CGraphe::CGraphe(unsigned int uiNbSommet)
{
	uiGRANbArcs = uiNbSommet;
	uiGRANbSommet = 0;
	bGRAOriente = true;

	pSOMGRAListeSommet = new CSommet[uiGRANbSommet];
}


CSommet* CGraphe::GRALireSommets()
{
	return pSOMGRAListeSommet;
}

unsigned int CGraphe::GRALireNbSommet()
{
	return uiGRANbSommet;
}

unsigned int CGraphe::GRALireNbArcs()
{
	return uiGRANbArcs;
}

bool CGraphe::GRALireType()
{
	return bGRAOriente;
}
