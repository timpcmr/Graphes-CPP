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
	CGraphe Graphe = pFichierLu->CONLireGraphe();
	Graphe.GRAAffichage();
	cout << "inversion" << endl;
	CGraphe GrapheInverse = Graphe.GRAInversion();
	GrapheInverse.GRAAffichage();
	cout << "Avant destruct\n";
	delete pFichierLu;
	cout << "Apres destruct\n";
	return 0;
}