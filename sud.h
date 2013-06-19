#ifndef ___BTZ___SUD_H___
#define ___BTZ___SUD_H___

#include <iostream>

using namespace std;

class sud{
	const static int N = 9, rN = 3, N2 = 81;
	static int VO[N][N] ;

	int V[N][N] ;
	bool B[N][N][N];
	
	public:
		void init();
		void affich(bool = false);
		void affich_csv(bool = false);
		void simplif(int, int, bool = false);
		int affecte(int &, bool = false);
		void cherche(bool = false);
		int nbval(int, int);
		void copier(sud &);
};


#endif
