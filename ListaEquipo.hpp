#ifndef LISTAEQUIPO_HPP
#define LISTAEQUIPO_HPP

#include<iostream>
#include "Equipo.hpp"

using namespace std;

struct NodoEquipo{
	Equipo* equipo;
	NodoEquipo *siguiente;
};

class ListaEquipo{
	
	private:
		NodoEquipo *lista=NULL;
	
	public:
		ListaEquipo(){
			
		}
		Equipo* buscarEquipo(int);
		void agregar(Equipo*);
		bool eliminar(int);
		NodoEquipo* mostrarList();
		void setLista(NodoEquipo *_lista){
			lista=_lista;
		}
		bool isEmpty(){
			if(lista==NULL){
				return true;
			}
			else{
				return false;
			}
		}
			
};

void ListaEquipo::agregar(Equipo* j){
	NodoEquipo *nuevoNodo = new NodoEquipo();
	nuevoNodo->equipo=j;
	NodoEquipo *aux1=lista;
	
	lista=nuevoNodo;
	nuevoNodo->siguiente=aux1;
}

Equipo* ListaEquipo::buscarEquipo(int numero){
	NodoEquipo *aux = lista;
	bool noEncontrado = true;
	NodoEquipo *EquipoBuscado=NULL;
	
	while(aux!=NULL && noEncontrado){
		
		if(aux->equipo->getId() == numero){
			noEncontrado = false;
			EquipoBuscado=aux;
		}
	}
	
	if(noEncontrado){		
		return NULL;
	}
	else{
		return EquipoBuscado->equipo;
	}		
}

bool ListaEquipo::eliminar(int id){
	
	NodoEquipo *aux1 = lista;
	NodoEquipo *aux2; 

	while(aux1!=NULL && aux1->equipo->getId() != id){
		aux2=aux1;
		aux1=aux1->siguiente;
	}
	
	if(aux1!=NULL){
		aux2->siguiente=aux1->siguiente;
		return true;
	}
	else{
		delete aux1;
		return false;
	}
	
}

NodoEquipo* ListaEquipo::mostrarList(){
	return lista;
} 

#endif
