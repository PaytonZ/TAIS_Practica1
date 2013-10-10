#include <iostream>
#include "TADs-EDA\AVL.h"


using namespace std;

int main()

{
	
	AVL <int,int>arbol;

	arbol.inserta(10,0);
arbol.inserta(100,0);
arbol.inserta(30,0);
arbol.inserta(80,0);
arbol.inserta(50,0);


Lista<int> z=arbol.inorden();
Lista<int>::Iterador it = z.principio();
while( it != z.final())
{
	int a=it.elem();
	cout << a << endl;
	it.avanza();
}





char a;
cin >> a;

return 0;
}

