
#ifndef AVL_H_
#define AVL_H_

int max(int a,int b){if(a>=b)return a;else return b;}

#include "Excepciones.h"
#include <iostream>
#include <fstream>
#include "Lista.h"
#include <cassert>
#include "DCola.h"

using namespace std;


template <class Clave, class Valor>
class AVL {
private:
   /**
    Clase nodo que almacena internamente la pareja (clave, valor),
    los punteros al hijo izquierdo y al hijo derecho, y la altura.
    */
   class Nodo {
   public:
      Clave clave;
      Valor valor;
      Nodo *iz;
      Nodo *dr;
      int altura;
	  int tam_i;
      Nodo(const Clave& c, const Valor& v, Nodo* i=NULL, Nodo* d=NULL, int alt=1, int tam=1)
      : clave(c), valor(v), iz(i), dr(d), altura(alt), tam_i(tam) {}
   };


public:
   /** constructor */
   AVL() : raiz(NULL) {};

   /** destructor */
   ~AVL(){
      libera();
      raiz = NULL;
   };

   void inserta(const Clave &c, const Valor &v) {
      inserta(c, v, raiz);
	  assert(es_avl_correcto(raiz));
   }

   bool esVacio() const {
      return raiz == NULL;
   }

   bool esta(const Clave& c) const {
      return busca(c, raiz) != NULL;
   }

   const Valor& consulta(const Clave &clave) {
      Nodo* p = busca(clave, raiz);
      if (p == NULL)
         throw EClaveErronea("La clave no se puede consultar");
      return p->valor;
   }

   void mostrar(ostream& o, int indent) const {
      mostrar(o,indent,raiz);
   }


   /** Constructor copia */
   AVL(const AVL<Clave, Valor>& other) : raiz(NULL) {
      copia(other);
   }


   /** Operador de asignacion */
   AVL<Clave, Valor>& operator=(const AVL<Clave, Valor> &other) {
      if (this != &other) {
         libera();
         copia(other);
      }
      return *this;
   }

   Lista<Clave> inorden() const {
		Lista<Clave> ret;
		inordenAcu(raiz, ret);
		return ret;
	}

   static void inordenAcu(Nodo *ra, Lista<Clave> &acu) {
		if (ra == NULL)
			return;

		inordenAcu(ra->iz, acu);
		acu.ponDr(ra->clave);
		inordenAcu(ra->dr, acu);
	}

    

   Clave kesimaMenorClave(int i)
 {
		
		Nodo *ra = raiz;
        int cuenta=i;
		    
        while(ra != NULL)
        {
            if (tam_i(ra->iz)+1 == cuenta)      return ra->clave;
            else if (tam_i(ra->iz) < cuenta)
            {
               ra = ra->dr;
                cuenta = cuenta - (tam_i(ra->iz)+1);
            }
            else
            {
                ra= ra->iz;
            }

	 }
}

protected:

   void libera(){
      libera(raiz);
   }

   void copia(const AVL<Clave, Valor>& a){
      copia(raiz,a.raiz);
   }

  

private:
	  /**
    Puntero a la raiz de la estructura jerarquica de nodos.
    */
   Nodo* raiz;

  

	bool es_avl_correcto(Nodo *ra) {

	   if(ra==NULL) return true;
	   
	   return (es_avl_correcto(ra->dr) && es_avl_correcto(ra->iz) && ( abs(altura(ra->iz) - altura(ra->dr)) <=1 ) && (altura(ra) == calculaAltura(ra)) );
	   }


	 int calculaAltura(Nodo *ra)
	{
		int altizq=0, altder=0;
		if (ra==NULL) return 0;
		if (ra->iz!=NULL) altizq= calculaAltura(ra->iz);
		if (ra->dr != NULL) altizq= calculaAltura(ra->dr);

		return int(max(altizq,altder)+1);
	}
		   static void libera(Nodo* a){
      if (a != NULL){
         libera(a->iz);
         libera(a->dr);
         delete a;
      }
   }

   static void copia(Nodo*& a,Nodo* b){
      if(b==NULL) a = NULL;
      else{
         Nodo* iz, *dr;
         copia(iz,b->iz);
         copia(dr,b->dr);
         a = new Nodo(b->clave,b->valor,iz,dr,max(altura(iz),altura(dr))+1,tam_i(iz)+1);
      }
   }

   static Nodo* busca(const Clave& c, Nodo* a) {
      if (a == NULL)
         return NULL;
      else if (a->clave == c)
         return a;
      else if (c < a->clave)
         return busca(c, a->iz);
      else // c > a->clave
         return busca(c, a->dr);
   }

   static int altura(Nodo* a){
      if (a==NULL) return 0;
      else return a->altura;
   }

     static int tam_i(Nodo* a){
      if (a==NULL) return 0;
      else return a->tam_i;
   }

   static void inserta(const Clave& c, const Valor& v, Nodo*& a){
      if (a == NULL) {
         a = new Nodo(c,v);
      } else if (c == a->clave) {
         a->valor = v;
      } else if (c < a->clave) {
         inserta(c, v, a->iz);
		 a->tam_i++;
         reequilibraDer(a);
      } else { // c > a->clave
         inserta(c, v, a->dr);
         reequilibraIzq(a);
      }
   }


   static void rotaDer(Nodo*& k2){
      Nodo* k1 = k2->iz;

	   k2->iz = k1->dr;
	

      k1->dr = k2;
      k2->altura = max(altura(k2->iz),altura(k2->dr))+1;
      k1->altura = max(altura(k1->iz),altura(k1->dr))+1;
      k2 = k1;
   }

   static void rotaIzq(Nodo*& k1){
      Nodo* k2 = k1->dr;


      k1->dr = k2->iz;
	 

      k2->iz = k1;
      k1->altura = max(altura(k1->iz),altura(k1->dr))+1;
      k2->altura = max(altura(k2->iz),altura(k2->dr))+1;


      k1=k2;
   }

   static void rotaIzqDer(Nodo*& k3){
      rotaIzq(k3->iz);
      rotaDer(k3);
   }

   static void rotaDerIzq(Nodo*& k1){
      rotaDer(k1->dr);
      rotaIzq(k1);
   }

   static void reequilibraIzq(Nodo*& a){
      if (altura(a->dr)-altura(a->iz) > 1) {
         if (altura(a->dr->iz) > altura(a->dr->dr))
            rotaDerIzq(a);
         else rotaIzq(a);
      }
      else a->altura = max(altura(a->iz),altura(a->dr))+1;
   }

   static void reequilibraDer(Nodo*& a){
      if (altura(a->iz)-altura(a->dr) > 1) {
         if (altura(a->iz->dr) > altura(a->iz->iz))
            rotaIzqDer(a);
         else rotaDer(a);
      }
      else a->altura = max(altura(a->iz),altura(a->dr))+1;
   }

    void mostrar(ostream& o,int indent, Nodo* r) const {
      if(r!=NULL){
         mostrar(o,indent+2,r->dr);
         for(int i=0;i<indent;i++) o << " ";
         o << "(" << r->clave << "," << r-> valor << ")" << endl;
         mostrar(o,indent+2,r->iz);
      }
   }

};

template <class Clave, class Valor>
ostream& operator<<(ostream& o,const AVL<Clave, Valor>& a){
   a.mostrar(o, 0);
   return o;
}




#endif /* AVL_H_ */
