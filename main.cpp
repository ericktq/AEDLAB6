#include<iostream>

#include<stdlib.h>

using namespace std;
template <typename T>
class Nodo
{
    public:
        T dato;
        Nodo<T> *der;
        Nodo<T> *izq;
        Nodo<T> *padre;
        Nodo();

        ~Nodo();
};
template <typename T>
Nodo<T>::Nodo(){
    this->dato=0;
    this->der=NULL;
    this->izq=NULL;
    this->padre=NULL;
}

template <typename T>
Nodo<T>::~Nodo()
{
}

template <typename T>
class ABB
{
    public:
        Nodo<T> *raiz;
        ABB();
        Nodo<T> *crearNodo(T n,Nodo<T> *padre);
       void insertar(Nodo<T> *&raiz_,T n,Nodo<T> *padre);
        void mostrar(Nodo<T>* raiz,T cont);
        bool buscar(Nodo<T>* raiz,T n);
        void preOrden(Nodo<T> *raiz);
        void inOrden(Nodo<T> *raiz);
        void postOrden(Nodo<T> *raiz);
        Nodo<T> *minimo(Nodo<T>* raiz);
        void reemplazar(Nodo<T>* raiz,Nodo<T> *nuevoNodo);
        void destruirNodo(Nodo<T> *nodo);
        void eliminarNodo(Nodo<T> *nodoEliminar);
        void eliminar(Nodo<T> *raiz,T n);
        ~ABB();

        void clear(){
            clearPri(raiz->izq);
            clearPri(raiz->der);
            raiz=NULL;
				}

        void eliminar2(Nodo<T>*& nodo){
            if(nodo!=NULL){
            eliminar2(nodo->der);
            eliminar2(nodo->izq);
                delete nodo;
					}
            nodo=NULL;
				}

		private:
            void clearPri(Nodo<T>*& nodo){
                if(nodo!=NULL){
                    eliminar2(nodo->der);
                    eliminar2(nodo->izq);
                    delete nodo;
					}
                nodo=NULL;
				}


};
template <typename T>
ABB<T>::ABB(){
    raiz=NULL;
}
template <typename T>
Nodo<T> *ABB<T>::crearNodo(T n,Nodo<T> *padre){
    Nodo<T> *nuevo_nodo=new Nodo<T>();
    nuevo_nodo->dato=n;
    nuevo_nodo->der=NULL;
    nuevo_nodo->izq=NULL;
    nuevo_nodo->padre=padre;

    return nuevo_nodo;
}
template <typename T>
void ABB<T>::insertar(Nodo<T> *&raiz,T n,Nodo<T> *padre){
    if(raiz==NULL){
        Nodo<T> *nuevo_nodo=crearNodo(n,padre);
        raiz=nuevo_nodo;
    }
    else{

        int valorRaiz=raiz->dato;
        if(n<valorRaiz){
            this->insertar(raiz->izq,n,raiz);
        }
        else{
            this->insertar(raiz->der,n,raiz);
        }
    }
}
template <typename T>
void ABB<T>::mostrar(Nodo<T>* raiz,T cont){
    if(raiz==NULL){
        return;
    }
    else{
        mostrar(raiz->der,cont+1);
        for(int i=0;i<cont;i++){
            cout<<"   ";
        }
        cout<<raiz->dato<<endl;
        mostrar(raiz->izq,cont+1);
    }
}
template <typename T>
bool ABB<T>::buscar(Nodo<T>* raiz,T n){
    if(raiz==NULL){
        return false;
    }
    else if(raiz->dato==n){
        return true;
    }
    else if(n<raiz->dato){
        return buscar(raiz->izq,n);
    }
    else{
        return buscar(raiz->der,n);
    }
}
template <typename T>
void ABB<T>::preOrden(Nodo<T> *raiz){
    if(raiz==NULL){
        return;
    }
    else{
        cout<<raiz->dato<<"  ";
        preOrden(raiz->izq);
        preOrden(raiz->der);
    }
}
template <typename T>
void ABB<T>::inOrden(Nodo<T> *raiz){
    if(raiz==NULL){
        return;
    }
    else{
        inOrden(raiz->izq);
        cout<<raiz->dato<<"  ";
        inOrden(raiz->der);
    }
}
template <typename T>
void ABB<T>::postOrden(Nodo<T> *raiz){
    if(raiz==NULL){
        return;
    }
    else{
        postOrden(raiz->izq);
        postOrden(raiz->der);
        cout<<raiz->dato<<"  ";

    }
}

template <typename T>
Nodo<T> *ABB<T>::minimo(Nodo<T>* raiz){
    if(raiz==NULL){
        return NULL;
    }
    if(raiz->izq){
        return minimo(raiz->izq);
    }
    else{
        return raiz;
    }
}

template <typename T>
void ABB<T>::reemplazar(Nodo<T>* raiz,Nodo<T> *nuevoNodo){
    if(raiz->padre){
        if(raiz->dato==raiz->padre->izq->dato){
            raiz->padre->izq=nuevoNodo;
        }
        else if(raiz->dato == raiz->padre->der->dato){
                raiz->padre->der=nuevoNodo;
        }
    }
    if(nuevoNodo){
            nuevoNodo->padre=raiz->padre;

    }
}
template <typename T>
void ABB<T>::destruirNodo(Nodo<T> *nodo){
    nodo->izq=NULL;
    nodo->der=NULL;
    delete nodo;

}
template <typename T>
void ABB<T>::eliminarNodo(Nodo<T> *nodoEliminar){
    if(nodoEliminar->izq&&nodoEliminar->der){
        Nodo<T> *menor=minimo(nodoEliminar->der);
        nodoEliminar->dato=menor->dato;
        eliminarNodo(menor);
    }
    else if(nodoEliminar->izq){
        reemplazar(nodoEliminar,nodoEliminar->izq);
        destruirNodo(nodoEliminar);
    }
    else if(nodoEliminar->der){
        reemplazar(nodoEliminar,nodoEliminar->der);
        destruirNodo(nodoEliminar);
    }
    else{
        reemplazar(nodoEliminar,NULL);
        destruirNodo(nodoEliminar);

    }
}

template <typename T>
void ABB<T>::eliminar(Nodo<T>* raiz,T n){
    if(raiz==NULL){
        return;
    }
    else if(n<raiz->dato){
        eliminar(raiz->izq,n);
    }
    else if(n>raiz->dato){
        eliminar(raiz->der,n);
    }
    else{
        eliminarNodo(raiz);
    }


}

template <typename T>
ABB<T>::~ABB(){


}

int main(){
    ABB<int> raiz;
   int contador =0;
   raiz.insertar(raiz.raiz,10,NULL);
   raiz.insertar(raiz.raiz,6,NULL);
   raiz.insertar(raiz.raiz,15,NULL);
   raiz.insertar(raiz.raiz,3,NULL);
   raiz.insertar(raiz.raiz,8,NULL);
   raiz.insertar(raiz.raiz,12,NULL);
   raiz.insertar(raiz.raiz,20,NULL);
   raiz.insertar(raiz.raiz,7,NULL);
   raiz.insertar(raiz.raiz,9,NULL);
   raiz.insertar(raiz.raiz,30,NULL);
   cout<<"=======Insertando Elementos========"<<endl;
   raiz.mostrar(raiz.raiz,contador);
   cout<<"=======Buscando un Numero=========="<<endl;
   int dato_=3;
   if(raiz.buscar(raiz.raiz,dato_)==true){
    cout<<"\nEl elemento "<<dato_<<" ha sido encontrado!"<<endl;
   }
   else{
    cout<<"\nEl elemento "<<dato_<<" no ha sido encontrado!"<<endl;
   }
    cout<<"=================================="<<endl;
    raiz.eliminar(raiz.raiz,20);
    cout<<"Eliminamos 20"<<endl;
    cout<<"=================================="<<endl;
    raiz.mostrar(raiz.raiz,contador);
    cout<<"=================================="<<endl;
    raiz.postOrden(raiz.raiz);
    cout<<"\n===================================\n";
    raiz.inOrden(raiz.raiz);
    cout<<"\n===================================\n  ";
    raiz.preOrden(raiz.raiz);
    cout<<"\n===================================";

		raiz.clear();
		cout<<"Se borro todo debe salir vacio"<<endl;
    cout<<"\n===================================\n  ";
    raiz.inOrden(raiz.raiz);
    cout<<"\n===================================\n  ";
    raiz.preOrden(raiz.raiz);
    cout<<"\n===================================";


    return 0;
}



