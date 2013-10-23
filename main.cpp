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
arbol.inserta(20,0);
cout << arbol;

cout << arbol.kesimaMenorClave(1) << endl;
cout << arbol.kesimaMenorClave(2)  << endl;
cout << arbol.kesimaMenorClave(3)  << endl;
cout << arbol.kesimaMenorClave(4)  << endl;
cout << arbol.kesimaMenorClave(5)  << endl;



/*
Lista<int> z=arbol.inorden();

Lista<int>::Iterador it = z.principio();
while( it != z.final())
{
	int a=it.elem();
	cout << a << endl;
	it.avanza();
}
*/





char a;
cin >> a;

return 0;
}

