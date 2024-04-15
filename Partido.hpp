#ifndef PARTIDO_HPP
#define PARTIDO_HPP

#include<iostream>
#include "Equipo.hpp"

using namespace std;

class Partido{

	private:
		Equipo equipo1;
		Equipo equipo2;
		ListaJugadores expulsiones = ListaJugadores();
		string fecha;
		
	public:
		Partido(Equipo e1,Equipo e2,string _fecha){
			equipo1=e1;
			equipo2=e2;
			fecha = _fecha;
		}
		Partido(){
		}
		
		Equipo getGanador(){
			
			if(equipo1.getGoles()>equipo2.getGoles()){
				return equipo1;
			}
			else{
				return equipo2;
			}			
		}
		
		//metodos getters
		Equipo getEquipo1(){
			return equipo1;
		}
		Equipo getEquipo2(){
			return equipo2;
		}
		
		string getFecha(){
			return fecha;
		}
		
		Nodo* getExpulsiones(){
			return expulsiones.mostrarList();
		}
		
		//metodos setters
		void setJugadorExpulsado(Jugador* j){		
			expulsiones.agregar(j);
		}
		
};
#endif
