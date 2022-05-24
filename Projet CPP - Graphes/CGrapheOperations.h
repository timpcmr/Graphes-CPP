#pragma once
#ifndef COPGRAPHES
#define COPGRAPHES

#include "CGraphe.h"

class CGrapheOperations {
public:
	CGraphe* GRAInversion(const CGraphe* GRAParam) const;
	CGraphe* GRANonOriente(const CGraphe* GRAParam) const;
};

#endif