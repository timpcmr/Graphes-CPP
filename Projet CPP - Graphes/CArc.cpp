#include "CArc.h"

CArc::CArc()
{
	iARCNumeroSommet = -1;
}

CArc::CArc(const CArc& ARCParam)
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

int CArc::ARCLireDestination() const
{
	return iARCNumeroSommet;
}

void CArc::ARCChangerDestination(int iDestination)
{
	iARCNumeroSommet= iDestination;
}

CArc& CArc::operator=(const CArc ARCparam)
{
	iARCNumeroSommet = (int)ARCparam.ARCLireDestination();
	return *this;
}
