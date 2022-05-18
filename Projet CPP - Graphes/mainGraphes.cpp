#include "CGraphe.h"
#include "CException.h"
#include "CControleurParseur.h"
#include <cstdio>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
	
	CControleurParseur FichierLu(argv[1]);
	FichierLu.CONLireFichierGraphe();
	FichierLu.CONLireGraphe().GRAAffichage();

	
	return 0;
}