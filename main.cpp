#include <iostream>
#include "TADs-EDA\AVL.h"


using namespace std;

int main()

{
	
	AVL <int,int>arbol;

	arbol.inserta(10,0);
		arbol.inserta(40,0);
arbol.inserta(100,0);
arbol.inserta(30,0);
arbol.inserta(80,0);
arbol.inserta(50,0);
//arbol.inserta(20,0);
cout << "inicio TODO EL ARBOL" << endl;
Lista<int> clave = arbol.rango(INT_MIN,INT_MAX);
for(Lista<int>::Iterador it=clave.principio() ; it != clave.final() ; it.avanza())
{
	cout << it.elem() << endl;
}
cout << "FIN TODO EL ARBOL" << endl;

cout << "------10---20-----" << endl;

clave = arbol.rango(10,20);

for(Lista<int>::Iterador it=clave.principio() ; it != clave.final() ; it.avanza())
{
	cout << it.elem() << endl;
}
cout << "------15------20--" << endl;
clave = arbol.rango(15,20);


clave = arbol.rango(20,20);
clave = arbol.rango(30,20);
clave = arbol.rango(10,100);

/*
cout << "--10---------100---" << endl;
for(Lista<int>::Iterador it=clave.principio() ; it != clave.final() ; it.avanza())
{
	cout << it.elem() << endl;
}
*/






char a;
cin >> a;

return 0;
}

