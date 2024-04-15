#ifndef LISTAJUGADORES_HPP
#define LISTAJUGADORES_HPP

#include<iostream>
#include "Jugador.hpp"

using namespace std;

struct Nodo{
	Jugador* jugador;
	Nodo *siguiente;
};

class ListaJugadores{
	
	private:
		Nodo *lista=NULL;
	
	public:
		ListaJugadores(){
			
		}
		Jugador* buscarJugador(int);
		void agregar(Jugador*);
		bool eliminar(int);
		Nodo* mostrarList();
		void setLista(Nodo *_lista){
			lista=_lista;
		}
			
};

void ListaJugadores::agregar(Jugador* j){
	Nodo *nuevoNodo = new Nodo();
	nuevoNodo->jugador=j;
	Nodo *aux1=lista;
	
	lista=nuevoNodo;
	nuevoNodo->siguiente=aux1;
}

Jugador* ListaJugadores::buscarJugador(int numero){
	Nodo *aux = lista;
	bool noEncontrado = true;
	Nodo *jugadorBuscado=NULL;
	
	while(aux!=NULL && noEncontrado){
		
		if(aux->jugador->getNumero() == numero){
			noEncontrado = false;
			jugadorBuscado=aux;
		}
	}
	
	if(noEncontrado){		
		return NULL;
	}
	else{
		return jugadorBuscado->jugador;
	}		
}

bool ListaJugadores::eliminar(int numero){
	
	Nodo *aux1 = lista;
	Nodo *aux2; 

	while(aux1!=NULL && aux1->jugador->getNumero() != numero){
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

Nodo* ListaJugadores::mostrarList(){
	return lista;
} 

#endif
