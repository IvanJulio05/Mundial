#ifndef EQUIPO_HPP
#define EQUIPO_HPP

#include<iostream>
#include<string>
#include <sstream>

#include "ListaJugadores.hpp"

using namespace std;

class Equipo{
	private:
		int id;
		int goles=0;
		string nombre;
		int ataque;
		int defensa;
		int puntos;
		int grupo;
		ListaJugadores jugadores = ListaJugadores();	
		ListaJugadores suplentes = ListaJugadores();
			
	public:
		Equipo(int _id,string _nombre,int _ataque,int _defensa,int _grupo){
			id=_id;
			nombre=_nombre;
			ataque=_ataque;
			defensa=_defensa;
			grupo = _grupo;
		}
		Equipo(){
			
		}
		
		void hacerCambio(Jugador* jugador){
			Nodo* j=jugadores.mostrarList();
			Nodo* suplente=NULL;
			bool noEncontrado=true;
			bool cambio=false;
			while(j!=NULL && !cambio){
				if(j->jugador->getNumero() == jugador->getNumero()){
					
					//buscando suplente
					for(int i=1;i<31 && noEncontrado;i++){
						suplente = BuscarSuplenteNumero(i);
						
						if(suplente->jugador->getNumeroCartas(0)==0 && suplente->jugador->getNumeroCartas(1)==0){
							noEncontrado=false;
						}
					}
					
					//realizando cambio
					Jugador* aux= new Jugador(j->jugador->getNumero(),j->jugador->getNombre(),j->jugador->getAgresividad());
					NodoTarjeta* tar=j->jugador->getTarjetas();
					while(tar!=NULL){
						aux->setTarjeta(tar->carta);
					}
					
					j->jugador=suplente->jugador;
					
					suplente->jugador=aux;
					
					cambio=true;
				}
				j=j->siguiente;
			}
			
			
		}
		
		string toString(){
			
			Nodo* x=jugadores.mostrarList();
			std::stringstream descripcion;
			descripcion << "{EQUIPO " << nombre << ", Id: " << id << ", Ataque: " << ataque<<", Defensa" <<defensa<<"}"<<endl;
			while(x!=NULL){
				descripcion<<x->jugador->toString()<<endl;
				x=x->siguiente;
			}
			return descripcion.str();			
		}
		
		void cargarJugadores(Jugador* jugador){			
			jugadores.agregar(jugador);			
		}
		void cargarSuplentes(Jugador* suplente){			
			suplentes.agregar(suplente);			
		}
		
		
		
		
		//metodos getters
		int getId(){
			return id;
		}
		int getGoles(){
			return goles;
		}
		string getNombre(){
			return nombre;
		}
		int getAtaque(){
			return ataque;			
		}
		int getDefensa(){
			return defensa;
		}
		int getPuntos(){
			return puntos;
		}
		int getGrupo(){
			return grupo;
		}
		Nodo* getjugadores(){
			return jugadores.mostrarList();
		}
		Nodo* getSuplentes(){
			return suplentes.mostrarList();
		}
		
		Nodo* BuscarSuplenteNumero(int numero){
			Nodo* s=jugadores.mostrarList();
			Nodo* j=NULL;
			while(s!=NULL){
				if(s->jugador->getNumero() == numero){
					j=s;
				}				
			}
			return j;
		}
		
		//metodo setters
		void setId(int _id){
			id=_id;
		}
		void setGrupo(int _grupo){
			grupo=_grupo;
		}
		void setGoles(int _goles){
			goles=_goles;
		}
		void setNombre(string _nombre){
			nombre=_nombre;
		}
		void setAtaque(int _ataque){
			ataque=_ataque;
		}
		void setDefensa(int _defensa){
			defensa=_defensa;
		}
		void setPuntos(int _puntos){
			puntos=_puntos;
		}
		
};

#endif




