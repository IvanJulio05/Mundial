#ifndef ARBOLEQUIPO_HPP
#define ARBOLEQUIPO_HPP

#include<iostream>

using namespace std;

struct nodoEquipo{
	Equipo* equipo;
	nodoEquipo* der;
	nodoEquipo* izq;
};


class ArbolEquipo{
	
	private:
		nodoEquipo* arbolEquipo=NULL;
	
	public:
		
		ArbolEquipo(){
			
		}
		
		void insertarEquipos(){
			
		}
		
		
	
	
};


#endif
