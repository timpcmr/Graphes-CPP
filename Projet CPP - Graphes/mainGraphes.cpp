#include "CGraphe.h"
#include "CException.h"
#include "CControleurParseur.h"
#include <cstdio>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
	
	CControleurParseur* pFichierLu = new CControleurParseur(argv[1]);
	pFichierLu->CONLireFichierGraphe();
	pFichierLu->CONLireGraphe().GRAAffichage();

	delete pFichierLu;
	return 0;
}