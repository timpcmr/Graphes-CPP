#include "CArc.h"

CArc::CArc()
{
	pSOMARCDestination = nullptr;
}

CArc::CArc(CArc& ARCParam)
{
	pSOMARCDestination = ARCParam.ARCLireDestination();
}

CArc::CArc(CSommet* pSOMParam)
{
	pSOMARCDestination = pSOMParam;
}

CArc::~CArc()
{
	pSOMARCDestination = nullptr;
}

CSommet* CArc::ARCLireDestination()
{
	return pSOMARCDestination;
}

void CArc::ARCChangerDestination(CSommet* pSOMDestination)
{
	pSOMARCDestination = pSOMDestination;
}
