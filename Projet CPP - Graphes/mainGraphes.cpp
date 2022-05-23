#include "CGraphe.h"
#include "CException.h"
#include "CControleurParseur.h"
#include <cstdio>
#include <cstdlib>

#define EXCArretProgramme 50

using namespace std;

int main(int argc, char* argv[]) {

	if (argc > 1) {

		//D�claration des variables du main
		CControleurParseur* pCONFichierLu = nullptr;
		CGraphe* pGRAGraphe = nullptr, * pGRAGrapheInverse = nullptr;

		//Lecture du fichier pass� en param�tre
		try {
			pCONFichierLu = new CControleurParseur(argv[1]);
			pCONFichierLu->CONLireFichierGraphe();
		}
		catch (CException EXCException) {
			if (EXCException.EXCLireErreur() == EXCArretProgramme) {
				return 1;
			}
			else if (EXCException.EXCLireErreur() == EXCCheminVideCtrlParseur) {
				cout << "Erreur : Chemin de fichier pass� en param�tre vide ou nul !" << endl;
				return 1;
			}
		}

		//R�cup�ration du graphe lu et affichage
		try {
			cout << endl << "-----Graphe lu depuis le fichier :-----" << endl << endl;
			pGRAGraphe = new CGraphe(*pCONFichierLu->CONLireGraphe());
			pGRAGraphe->GRAAffichage();
		}
		catch (CException EXCException) {
			if (EXCException.EXCLireErreur() == EXCArretProgramme) {
				return 1;
			}
			else if (EXCException.EXCLireErreur() == EXCArretProgramme) {

			}
		
		
		}

		//R�cup�ration du graphe invers� puis affichage
		try{
			cout << endl << "-----Graphe Inverse-----" << endl << endl;
			pGRAGrapheInverse = pGRAGraphe->GRAInversion();
			pGRAGrapheInverse->GRAAffichage();

		
			delete pGRAGraphe;
			delete pGRAGrapheInverse;
			delete pCONFichierLu;
		}
		catch (CException EXCException) {
			if (EXCException.EXCLireErreur() == EXCArretProgramme) {
				return 1;
			}
			else if (EXCException.EXCLireErreur() == EXCListeSommetInexistante) {
				cout << "Erreur Affichage : La liste des sommets du graphe a afficher est vide !" << endl;
				return 1;
			}
			else {
				cout << "Erreur non-specifiee !" << endl;
			}
		}
	}
	else {
		cout << "Erreur : Aucun chemin de fichier passe en argument !" << endl;
		return 1;
	}

	return 0;
}