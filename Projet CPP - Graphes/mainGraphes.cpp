#include "CGraphe.h"
#include "CException.h"
#include "CControleurParseur.h"
#include <cstdio>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {

	cout << "1\n";
	CControleurParseur* pFichierLu = new CControleurParseur(argv[1]);
	cout << "2\n";
	pFichierLu->CONLireFichierGraphe();
	cout << "3\n";
	CGraphe* pGRAGraphe = pFichierLu->CONLireGraphe();
	pGRAGraphe->GRAAffichage();
	cout << "inversion" << endl;
	CGraphe* pGRAGrapheInverse = pGRAGraphe->GRAInversion();
	pGRAGrapheInverse->GRAAffichage();

	CGraphe* pGRAGrapheNonOriente = pGRAGraphe->GRANonOriente();
	pGRAGrapheNonOriente->GRAAffichage();
	cout << "Avant destruct\n";
	//delete pGRAGraphe;
	//delete pGRAGrapheInverse;
	delete pFichierLu;
	cout << "Apres destruct\n";
	return 0;
}