#include "sud.h"

using namespace std;

// Maintenant c'est avec Git !

int main(){
	sud S;

	S.init();
	S.affich();
	S.cherche(true);
	S.affich();
	cout << endl;
	S.affich_csv();

}
