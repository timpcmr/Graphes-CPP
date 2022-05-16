#include "CArc.h"

CArc::CArc()
{
	iARCNumeroSommet = -1;
}

CArc::CArc(CArc& ARCParam)
{
	iARCNumeroSommet = ARCParam.iARCNumeroSommet;
}

CArc::CArc(int iParam)
{
	iARCNumeroSommet = iParam;
}

CArc::~CArc()
{
	
}

int CArc::ARCLireDestination()
{
	return iARCNumeroSommet;
}

void CArc::ARCChangerDestination(int iDestination)
{
	iARCNumeroSommet= iDestination;
}
