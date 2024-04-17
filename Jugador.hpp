#ifndef JUGADOR_HPP
#define JUGADOR_HPP


#include<iostream>
#include<string>
#include <sstream>

using namespace std;

//0=amarilla
//1=roja
struct NodoTarjeta{
	
	int carta;
	NodoTarjeta* siguiente;
};

class Jugador{
	private:
		int numero;
		string nombre;
		int agresividad;
		NodoTarjeta *tarjetas=NULL;
		
	public:
		Jugador(){
			
		}
		
		Jugador(int _numero,string _nombre,int _agresividad){
			numero = _numero;
			nombre=_nombre;
			agresividad=_agresividad;			
		}
		
		//0=amarilla
		//1=roja
		int getNumeroCartas(int tipoCarta){
			int contador=0;
			NodoTarjeta *aux=tarjetas;
			while(aux!=NULL){
				if(aux->carta==tipoCarta){
					contador++;
				}
				aux=aux->siguiente;				
			}
			return contador;
		}
		
		int getTotalCartas(){
			int total=getNumeroCartas(0);
			total+=getNumeroCartas(1);
			return total;
		}
		
		
		
		string toString(){
			std::stringstream ss;
			ss << "{Jugador " << nombre << ", Numero: " << numero << ", Agresividad: " << agresividad << "}";
			return ss.str();			
		}
		
		//metodos getters
		string getNombre(){
			return nombre;
		}
		int getNumero(){
			return numero;
		}
		int getAgresividad(){
			return agresividad;
		}		
		NodoTarjeta* getTarjetas(){
			return tarjetas;
		}
		
		//metodos setters
		void setNombre(string _nombre){
			nombre=_nombre;
		}
		void setNumero(int _numero){
			numero=_numero;
		}
		void setAgresividad(int agre){
			agresividad=agre;
		}
		void setTarjeta(int n){
			NodoTarjeta *nuevoNodo = new NodoTarjeta();
			nuevoNodo->carta=n;
			NodoTarjeta *aux1= tarjetas;
			
			tarjetas=nuevoNodo;
			nuevoNodo->siguiente=aux1;						
		}
		
		
};

#endif

