#pragma once
#ifndef COPGRAPHES
#define COPGRAPHES

#include "CGraphe.h"

class CGrapheOperations {
public:
	CGraphe* GRAInversion(const CGraphe* pGRAParam) const;
	CGraphe* GRANonOriente(const CGraphe* pGRAParam) const;
};

#endif