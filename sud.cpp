#include "sud.h"

/*
 int sud::VO[N][N] = {  {0,0,0,0,0,0,0,1,0},
                        {4,0,0,0,0,0,0,0,0},
                        {0,2,0,0,0,0,0,0,0},
                        {0,0,0,0,5,0,4,0,7},
                        {0,0,8,0,0,0,3,0,0},
                        {0,0,1,0,9,0,0,0,0},
                        {3,0,0,4,0,0,2,0,0},
                        {0,5,0,1,0,0,0,0,0},
                        {0,0,0,8,0,6,0,0,0} };
*/

/*
 int sud::VO[N][N] = {  {0,0,0,7,0,0,8,9,1},
                        {0,0,0,0,8,0,6,0,0},
                        {0,6,0,0,0,0,3,0,5},
                        {4,0,0,8,0,3,0,5,0},
                        {9,0,0,0,0,0,0,0,8},
                        {0,5,0,9,0,4,0,0,2},
                        {3,9,2,0,0,0,0,6,0},
                        {5,0,0,0,3,0,0,0,0},
                        {6,0,0,2,0,0,0,0,0} };
 */

 int sud::VO[N][N] = {  {7,5,0,0,9,0,0,4,6},
                        {9,6,1,0,0,0,3,5,2},
                        {4,0,0,0,0,0,7,9,0},
                        {2,0,0,6,0,1,0,0,7},
                        {0,8,0,0,0,0,0,2,0},
                        {1,0,0,3,2,8,0,6,5},
                        {0,0,0,0,0,0,0,0,0},
                        {3,0,9,0,0,0,2,0,4},
                        {8,4,0,0,3,0,0,7,9} };


void sud::init(){
	int i, j, k;

	for (i = 0;i < N; i++)
		for (j = 0;j < N; j++){
			V[i][j] = VO[i][j];
			for (k = 0;k < N; k++)
				B[i][j][k] = true;
		}
	for (i = 0;i < N; i++)
		for (j = 0;j < N; j++)
			if (V[i][j] != 0)
				simplif(i,j);
}

int sud::nbval(int i, int j){
	int nb = 0, k;

	for (k = 0;k < N; k++)
		if (B[i][j][k])
			nb++;
	return nb;
}

void sud::affich(bool debug){
	int i, j, k;

	cout << "*************************************" << endl;
	for (i = 0;i < N; i++){
		cout << '*';
		for (j = 0;j < N; j++){
			cout << ' ';
			if (V[i][j] == 0)
				cout << ' ';
			else
				cout << V[i][j];
			if (debug){
				for (k = 0;k < N; k++)
					if (B[i][j][k])
						cout << k << ':';
				cout << ';';
			}
			if (j % rN == 2)
				cout << " *";
			else
				cout << " |";
		}
		cout << endl;
		if (i % rN == 2)
			cout << "*************************************" << endl;
		else
			cout << "* * * * * * * * * * * * * * * * * * *" << endl;
	}
}

// Supprime la valeur contenue dans la case (i,j) des lignes, colonnes
// et sous-carres correspondant
void sud::simplif(int i, int j, bool debug){
	int k, l;

	if (debug){
		affich();
		cerr << "simplif : " << i << ':' << j << endl;
	}
	for (k = 0;k < N; k++){
		B[i][k][V[i][j]-1] = false;
		B[k][j][V[i][j]-1] = false;
		B[i][j][k] = false;
	}
	for (k = (i / rN) * rN;k < (i / rN) * rN + rN; k++)
		for (l = (j / rN) * rN;l < (j / rN) * rN + rN; l++)
			B[k][l][V[i][j]-1] = false;
}

void sud::affich_csv(bool debug){
	int i, j, k;

	for (i = 0;i < N; i++){
		for (j = 0;j < N; j++){
			if (V[i][j] == 0){
				for (k = 0;k < N; k++)
					if (B[i][j][k])
						cout << k + 1 << ':';
				cout << ';';
			}
			else
				cout << V[i][j] << ';';
		}
		cout << endl;
	}
}

// Affecte les valeurs sures (une seule possibilite) et detecte les
// impossibilites :
// Retour : -1 impossibilite (pas de valeurs possibles)
//           0 au moins une affectation
//           1 pas d'affectation
//           2 fini
int sud::affecte(int & nb_bon, bool debug){
	int ret = 1;
	int i, j, k, o, p;
	int nb, nbc, nbl, kv, kc, kl;

	nb_bon = N2;
	for (i = 0;i < N; i++)
		for (j = 0;j < N; j++)
			if (V[i][j] == 0)
				nb_bon--;
	//cout << "bon deb : " << nb_bon << endl;
	for (i = 0;i < N; i++)
		for (j = 0;j < N; j++){
			if (V[i][j] == 0){
				nb = 0;
				for (k = 0;k < N; k++) // nb valeurs possibles
					if (B[i][j][k]){
						nb++;
						kv = k+1;
					}
				if (nb == 0){
					if (debug)
						cerr << "PB 1 : " << i << ':' << j << endl;
					return -1;
				}
				if (nb == 1){
					ret = 0;
					V[i][j] = kv;
					nb_bon++;
					if (debug){
						cerr << "trouve 1 : ";
						cerr << "V[" << i << "][" << j<< "] = " << kv << endl;
						affich();
					}
					if (nb_bon == N2)
						return 2;
					simplif(i, j);
				}
				for (k = 0;k < N; k++){ // nb possibilites pour une valeur
					nbl = nbc = 0;
					for (o = 0;o < N; o++){
						if (V[o][j] == k + 1) // Ignorer les cas ou la valeur est deja rangee !
							nbc = 2;
						if (B[o][j][k]){
							kc = o;
							nbc++;
						}
						if (V[i][o] == k + 1)
							nbl = 2;
						if (B[i][o][k]){
							kl = o;
							nbl++;
						}
					}
					if (debug)
						cerr << i << ':' << j << ':' << k << ':' << nbc << ':' << nbl << endl;
					if (nbc == 0){
						if (debug)
							cerr << "PB 2 : " << i << ':' << j << ':' << kc + 1 << endl;
						return -1;
					}
					if (nbc == 1 && V[kc][j] == 0){
						ret = 0;
						V[kc][j] = k + 1;
						nb_bon++;
						if (debug){
							cerr << "trouve 2 : ";
							cerr << "V[" << kc << "][" << j<< "] = " << k + 1 << endl;
							affich();
						}
						if (nb_bon == N2)
							return 2;
						simplif(kc, j);
					}
					if (nbl == 0){
						if (debug)
							cerr << "PB 3 : " << i << ':' << j << ':' << k + 1 << endl;
						return -1;
					}
					if (nbl == 1 && V[i][kl] == 0){
						ret = 0;
						V[i][kl] = k + 1;
						nb_bon++;
						if (debug){
							cerr << "trouve 3 : ";
							cerr << "V[" << i << "][" << kl<< "] = " << k + 1 << endl;
							affich();
						}
						if (nb_bon == N2)
							return 2;
						simplif(i, kl);
					}
					nb = 0;
					for (o = (i / rN) * rN;o < (i / rN) * rN + rN; o++)
						for (p = (j / rN) * rN;p < (j / rN) * rN + rN; p++){
							if (B[o][p][k]){
								kc = o;
								kl = p;
								nb++;
							}
							if (V[o][p] == k + 1)
								nb = 2;
						}
					if (nb == 0){
						if (debug)
							cerr << "PB 4 : " << i << ':' << j << ':' << kv + 1 << endl;
						return -1;
					}
					if (nb == 1 && V[kc][kl] == 0){
						ret = 0;
						V[kc][kl] = k + 1;
						nb_bon++;
						if (debug){
							cerr << "trouve 4 : ";
							cerr << "V[" << i << "][" << j<< "] = " << kv + 1 << endl;
							affich();
						}
						if (nb_bon == N2)
							return 2;
						simplif(kc, kl);
					}
				}
			}
		}
	return ret;
}

void sud::cherche(bool debug){
	int ret, bon;
	int i, j, k;
	sud C;
	bool fini;

	while (!(ret = affecte(bon, debug))){
		if (debug){
			cerr << "bon : " << bon << endl;
			//affich();
		}
	}
	switch (ret){
		case -1 :
			if (debug){
				cerr << "Argh !" << endl;
			}
			break;
		case 1 :
			if (debug){
				cerr << "Ok pas fini" << endl;
			}
			fini = false;
			for (i = 0;i < N && !fini; i++)
				for (j = 0;j < N; j++){
					cerr << i << ':' << j << ':' << V[i][j] << " ! ";
					if (V[i][j] == 0){
						fini = true;
						break;
					}
				}
			for (k = 0;k < N; k++)
				if (B[i][j][k]){
					copier(C);
					C.V[i][j] = k + 1;
					C.simplif(i,j);
					if (debug){
						cerr << "trouve 5 : ";
						cerr << "V[" << i << "][" << j<< "] = " << k + 1 << endl;
						affich();
						C.affich();
					}
					//C.affich();
					C.cherche(debug);
				}
			break;
		case 2 :
			if (debug){
				cerr << "Ok fini" << endl;
				cerr << "bon : " << bon << endl;
				affich();
			}
			break;
		default :
			cerr << "???" << endl;
	}
	cerr << endl;
}

void sud::copier(sud & C){
	int i, j, k;

	for (i = 0;i < N; i++)
		for (j = 0;j < N; j++){
			C.V[i][j] = V[i][j];
			for (k = 0;k < N; k++)
				C.B[i][j][k] = B[i][j][k];
		}

}

