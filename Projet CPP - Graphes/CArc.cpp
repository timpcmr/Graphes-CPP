#include "CArc.h"

CArc::CArc()
{
	iARCNumeroSommet = -1;
}

CArc::CArc(CArc& ARCParam)
{
	iARCNumeroSommet = ARCParam.ARCLireDestination();
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

CArc& CArc::operator=(CArc ARCparam)
{
	iARCNumeroSommet = ARCparam.ARCLireDestination();
	return *this;
}
