#ifndef MUNDIAL_HPP
#define MUNDIAL_HPP

#include<iostream>
#include "Partido.hpp"
#include "ListaEquipo.hpp"


#include <fstream>
#include <random>
#include <string>
#include<time.h>
#include <sstream>
using namespace std;

struct nodoPartido{
	Partido* partido;
	nodoPartido* siguiente;
};

class Mundial{
	
	private:
		
		nodoPartido *partidos=NULL;
		nodoPartido *partidosOctavos=NULL;
		
		//
		ListaEquipo equipos=ListaEquipo();
		
		//face de grupo
		ListaEquipo grupo1=ListaEquipo();
		ListaEquipo grupo2=ListaEquipo();
		ListaEquipo grupo3=ListaEquipo();
		ListaEquipo grupo4=ListaEquipo();
		
		//Octabos de finales
		ListaEquipo grupoOctavos1=ListaEquipo();//2equipos
		ListaEquipo grupoOctavos2=ListaEquipo();//2equipos
		ListaEquipo grupoOctavos3=ListaEquipo();//2equipos
		ListaEquipo grupoOctavos4=ListaEquipo();//2equipos
		
		//cuartos		
		ListaEquipo grupoCuartos=ListaEquipo();//4equipos
		
		//semifinal
		ListaEquipo grupoSemiFinal=ListaEquipo();//2equipos
		
		//ganador
		Equipo* equipo=NULL;
		
	private :
		void OrganizarGrupo(){
			NodoEquipo* equi=equipos.mostrarList();
			while(equi!=NULL){
				if(equi->equipo->getGrupo()==1){
					grupo1.agregar(equi->equipo);
				}
				else if(equi->equipo->getGrupo()==2){
					grupo2.agregar(equi->equipo);
				} 
				else if(equi->equipo->getGrupo()==3){
					grupo3.agregar(equi->equipo);
				}
				else if(equi->equipo->getGrupo()==4){
					grupo4.agregar(equi->equipo);
				}
				equi=equi->siguiente;
			}
		}		
				
	public:
		Mundial(){
			cargarEquipos();
			OrganizarGrupo();
		}		

		void JugarPartidoOctavos(){
			OrganizarGrupoOctavos(1);				
			OrganizarGrupoOctavos(2);
			OrganizarGrupoOctavos(3);
			OrganizarGrupoOctavos(4);
			int max;
			int defen1,defen2;
			int ataque1,ataque2;
			int total1,total2;
			int ventaja;
			NodoEquipo* grupo1=NULL;
			NodoEquipo* grupo2=NULL;						
			for(int i=0;i<2;i++){
				
				if(i==0){
					grupo1=grupoOctavos1.mostrarList();
					grupo2=grupoOctavos2.mostrarList();
				}
				else if(i==1){
					grupo1=grupoOctavos3.mostrarList();
					grupo2=grupoOctavos4.mostrarList();
				}			
				
				
				//primeros 2 grupos  A VS B
				
					
					//NodoEquipo* aux=grupo2;												
						
					while(grupo1!=NULL){
						
						//estadisticas del primer equipo						
						defen1=grupo1->equipo->getDefensa();
						ataque1=grupo1->equipo->getAtaque();
						total1=defen1+ataque1;
						
						//estadisticas del segundo equipo
						defen2=grupo2->equipo->getDefensa();
						ataque2=grupo2->equipo->getAtaque();							
						total2=defen2+ataque2;
						
						if(total1>=total2){
							ventaja= total1-total2;
							asignarGoles(5+ventaja,grupo1);
							asignarGoles(5,grupo2,grupo1);
							
						}
						else{
							ventaja= total2-total1;
							asignarGoles(5,grupo1);
							asignarGoles(5+ventaja,grupo2,grupo1);
						}
						
						//asignando las tarjetas
						
						//primer equipo						
						int agresividadTotal=grupo1->equipo->getTotalAgresividad();
						const int AGRESIVIDAD_MAXIMA_TOLERADA=150;
						const int AGRESIVIDAD_MEDIA_TOLERADA=100;
						int sobrante;							
						if(agresividadTotal > AGRESIVIDAD_MAXIMA_TOLERADA){
							
							sobrante= agresividadTotal - AGRESIVIDAD_MAXIMA_TOLERADA;
							sobrante = sobrante/10;
							sobrante*=2;
							if(sobrante>=1){
								if(sobrante<8){
									
									asignarTarjetas(10-sobrante,grupo1);
								}
								else{
									asignarTarjetas(2,grupo1);
								}
								
							}
							
						}else if(agresividadTotal > AGRESIVIDAD_MEDIA_TOLERADA){
							
							sobrante= agresividadTotal - AGRESIVIDAD_MEDIA_TOLERADA;
							sobrante = sobrante/10;
							
							if(sobrante>=1){
								asignarTarjetas(10-sobrante,grupo1);
							}
						}
						else{
							
							asignarTarjetas(10,grupo1);
							
						}
						
						//segundo equipo							
						agresividadTotal=grupo2->equipo->getTotalAgresividad();
						sobrante;							
						if(agresividadTotal > AGRESIVIDAD_MAXIMA_TOLERADA){
							
							sobrante= agresividadTotal - AGRESIVIDAD_MAXIMA_TOLERADA;
							sobrante = sobrante/10;
							sobrante*=2;
							if(sobrante>=1){
								if(sobrante<8){
									asignarTarjetas(10-sobrante,grupo2);
								}
								else{
									asignarTarjetas(2,grupo2);
								}
								
							}
							
						}else if(agresividadTotal > AGRESIVIDAD_MEDIA_TOLERADA){
							
							sobrante= agresividadTotal - AGRESIVIDAD_MEDIA_TOLERADA;
							sobrante = sobrante/10;
							
							if(sobrante>=1){
								asignarTarjetas(10-sobrante,grupo2);
							}
						}
						else{
							asignarTarjetas(10,grupo2);
							
						}							
						
						//asignando los puntos
						/*if(grupo->equipo->getGoles()>aux->equipo->getGoles()){
							grupo->equipo->setPuntos(grupo->equipo->getPuntos()+3);
						}
						else{
							aux->equipo->setPuntos(aux->equipo->getPuntos()+3);
						}*/
						
						//guardando el partido(copia de los equipos originales)
						
						//equipo 1
						Equipo* referencia = grupo1->equipo;
						Equipo* e1 = new Equipo(referencia->getId(),referencia->getNombre(),referencia->getAtaque(),referencia->getDefensa(),referencia->getGrupo());
						e1->setPuntos(referencia->getPuntos());
						e1->setGoles(referencia->getGoles());
						Nodo* jugaf= referencia->getjugadores();
						int nAmarillas,nRojas;
						
						while(jugaf!=NULL){
							Jugador* ref =jugaf->jugador; 
							Jugador* juga = new Jugador(ref->getNumero(),ref->getNombre(),ref->getAgresividad());
							nAmarillas= ref->getNumeroCartas(0);
							nRojas= ref->getNumeroCartas(1);
							//guardando las tarjetas del partido
							//amarillas
							for(int x=0;x<nAmarillas;x++){
								juga->setTarjeta(0);
							}
							//rojas
							for(int x=0;x<nRojas;x++){
								juga->setTarjeta(1);
							}
							
							e1->cargarJugadores(juga);
							
							jugaf=jugaf->siguiente;								
						}
						
						//equipo 2	
						referencia = grupo2->equipo;						
						Equipo* e2 = new Equipo(referencia->getId(),referencia->getNombre(),referencia->getAtaque(),referencia->getDefensa(),referencia->getGrupo());
						e2->setPuntos(referencia->getPuntos());
						e2->setGoles(referencia->getGoles());							
						jugaf= referencia->getjugadores();
						while(jugaf!=NULL){
							Jugador* ref =jugaf->jugador; 
							Jugador* juga = new Jugador(ref->getNumero(),ref->getNombre(),ref->getAgresividad());
							nAmarillas= ref->getNumeroCartas(0);
							nRojas= ref->getNumeroCartas(1);
							//guardando las tarjetas del partido
							//amarillas
							for(int x=0;x<nAmarillas;x++){
								juga->setTarjeta(0);
							}
							//rojas
							for(int x=0;x<nRojas;x++){
								juga->setTarjeta(1);
							}							
							e2->cargarJugadores(juga);
							
							jugaf=jugaf->siguiente;
						}							
						Partido* parti = new Partido(e1,e2,"01/02/2000");
						agregarPartidoOctavo(parti);
												
						grupo1=grupo1->siguiente;
						grupo2=grupo2->siguiente;
					}					
					

									
			}
								
		}	
		
		void JugarPartido(){
			
			int max;
			int defen1,defen2;
			int ataque1,ataque2;
			int total1,total2;
			int ventaja;
			NodoEquipo* grupo=NULL;						
			for(int i=0;i<4;i++){
				
				if(i==0){
					grupo=grupo1.mostrarList();
					
				}
				else if(i==1){
					grupo=grupo2.mostrarList();
					
				}
				else if(i==2){
					grupo=grupo3.mostrarList();
					
				}
				else if(i==3){
					grupo=grupo4.mostrarList();
					
				}
				
				
				
				
				//primer grupo
				
					
					NodoEquipo* aux=grupo;
					for(int h=0;h<4;h++){						
						grupo=grupo->siguiente;
						
						while(grupo!=NULL){
							//estadisticas del primer equipo
							
							defen1=grupo->equipo->getDefensa();
							ataque1=grupo->equipo->getAtaque();
							total1=defen1+ataque1;
							
							//estadisticas del segundo equipo
							defen2=aux->equipo->getDefensa();
							ataque2=aux->equipo->getAtaque();							
							total2=defen2+ataque2;
							
							if(total1>=total2){
								ventaja= total1-total2;
								asignarGoles(5+ventaja,grupo);
								asignarGoles(5,aux,grupo);
								
							}
							else{
								ventaja= total2-total1;
								asignarGoles(5,grupo);
								asignarGoles(5+ventaja,aux,grupo);
							}
							
							//asignando las tarjetas
							
							//primer equipo
							
							int agresividadTotal=grupo->equipo->getTotalAgresividad();
							const int AGRESIVIDAD_MAXIMA_TOLERADA=150;
							const int AGRESIVIDAD_MEDIA_TOLERADA=100;
							int sobrante;							
							if(agresividadTotal > AGRESIVIDAD_MAXIMA_TOLERADA){
								
								sobrante= agresividadTotal - AGRESIVIDAD_MAXIMA_TOLERADA;
								sobrante = sobrante/10;
								sobrante*=2;
								if(sobrante>=1){
									if(sobrante<8){
										
										asignarTarjetas(10-sobrante,grupo);
									}
									else{
										asignarTarjetas(2,grupo);
									}
									
								}
								
							}else if(agresividadTotal > AGRESIVIDAD_MEDIA_TOLERADA){
								
								sobrante= agresividadTotal - AGRESIVIDAD_MEDIA_TOLERADA;
								sobrante = sobrante/10;
								
								if(sobrante>=1){
									asignarTarjetas(10-sobrante,grupo);
								}
							}
							else{
								
								asignarTarjetas(10,grupo);
								
							}
							
							//segundo equipo							
							agresividadTotal=aux->equipo->getTotalAgresividad();
							sobrante;							
							if(agresividadTotal > AGRESIVIDAD_MAXIMA_TOLERADA){
								
								sobrante= agresividadTotal - AGRESIVIDAD_MAXIMA_TOLERADA;
								sobrante = sobrante/10;
								sobrante*=2;
								if(sobrante>=1){
									if(sobrante<8){
										asignarTarjetas(10-sobrante,aux);
									}
									else{
										asignarTarjetas(2,aux);
									}
									
								}
								
							}else if(agresividadTotal > AGRESIVIDAD_MEDIA_TOLERADA){
								
								sobrante= agresividadTotal - AGRESIVIDAD_MEDIA_TOLERADA;
								sobrante = sobrante/10;
								
								if(sobrante>=1){
									asignarTarjetas(10-sobrante,aux);
								}
							}
							else{
								asignarTarjetas(10,aux);
								
							}							
							
							//asignando los puntos
							if(grupo->equipo->getGoles()>aux->equipo->getGoles()){
								grupo->equipo->setPuntos(grupo->equipo->getPuntos()+3);
							}
							else{
								aux->equipo->setPuntos(aux->equipo->getPuntos()+3);
							}
							
							//guardando el partido(copia de los equipos originales)
							
							//equipo 1
							Equipo* referencia = grupo->equipo;
							Equipo* e1 = new Equipo(referencia->getId(),referencia->getNombre(),referencia->getAtaque(),referencia->getDefensa(),referencia->getGrupo());
							e1->setPuntos(referencia->getPuntos());
							e1->setGoles(referencia->getGoles());
							Nodo* jugaf= referencia->getjugadores();
							int nAmarillas,nRojas;
							
							while(jugaf!=NULL){
								Jugador* ref =jugaf->jugador; 
								Jugador* juga = new Jugador(ref->getNumero(),ref->getNombre(),ref->getAgresividad());
								nAmarillas= ref->getNumeroCartas(0);
								nRojas= ref->getNumeroCartas(1);
								//guardando las tarjetas del partido
								//amarillas
								for(int x=0;x<nAmarillas;x++){
									juga->setTarjeta(0);
								}
								//rojas
								for(int x=0;x<nRojas;x++){
									juga->setTarjeta(1);
								}
								
								e1->cargarJugadores(juga);
								
								jugaf=jugaf->siguiente;								
							}
							
							//equipo 2	
							referencia = aux->equipo;						
							Equipo* e2 = new Equipo(referencia->getId(),referencia->getNombre(),referencia->getAtaque(),referencia->getDefensa(),referencia->getGrupo());
							e2->setPuntos(referencia->getPuntos());
							e2->setGoles(referencia->getGoles());							
							jugaf= referencia->getjugadores();
							while(jugaf!=NULL){
								Jugador* ref =jugaf->jugador; 
								Jugador* juga = new Jugador(ref->getNumero(),ref->getNombre(),ref->getAgresividad());
								nAmarillas= ref->getNumeroCartas(0);
								nRojas= ref->getNumeroCartas(1);
								//guardando las tarjetas del partido
								//amarillas
								for(int x=0;x<nAmarillas;x++){
									juga->setTarjeta(0);
								}
								//rojas
								for(int x=0;x<nRojas;x++){
									juga->setTarjeta(1);
								}							
								e2->cargarJugadores(juga);
								
								jugaf=jugaf->siguiente;
							}							
							Partido* parti = new Partido(e1,e2,"01/02/2000");
							agregarPartido(parti);
							grupo=grupo->siguiente;
						}					
						aux=aux->siguiente;
						grupo=aux;	
						//grupo=grupo->siguiente;
					}

									
			}
			
			
			
								
		}
		
		void cargarEquipos(){
			
			string idEquipo;
			string nombreEquipo;
			string ataque;
			string defensa;
			string grupo;
			string numeroJugador;
			string nombreJugador;
			string agresividad;			
			int contador=1;
			
			string separador="0";
			
			ifstream archivo;
			archivo.open("infor.txt",ios::in);
			
			if(archivo.fail()){
				cout<<"No se pudo abrir el archivo";
				exit(1);
			}
			
			while(!archivo.eof()){
				
				getline(archivo,idEquipo);
				getline(archivo,nombreEquipo);
				getline(archivo,ataque);
				getline(archivo,defensa);
				getline(archivo,grupo);		
				
				
				Equipo* equi = new Equipo(convertir(idEquipo),nombreEquipo,convertir(ataque),convertir(defensa),convertir(grupo));
				//lectura de los jugadores
				while(separador != "-"){
					
					getline(archivo,numeroJugador);
					getline(archivo,nombreJugador);
					getline(archivo,agresividad);
					getline(archivo,separador);

					
					Jugador* juga = new Jugador(convertir(numeroJugador),nombreJugador,convertir(agresividad));
					
					//aqui se determina el numero de jugadores
					if(contador<=11){
						equi->cargarJugadores(juga);
					}
					else{
						equi->cargarSuplentes(juga);
					}
					
					contador++;
					//system("pause");
				}
				
				contador=1;
				separador="0";
				//agregar equipo al mundial
				equipos.agregar(equi);
			}
			
			archivo.close();
		}
		
		int convertir(string x){
			int numero;
			istringstream(x)>>numero;			
			return numero;
		}
		
		void asignarGoles(int fin,NodoEquipo* &equipo){
			
			int goles=0;
			
			int min= 0;
			int max=fin;
			
			
			
			goles = generarNumeros(max,min);
			
			equipo->equipo->setGoles(goles);
			
		}
		void asignarGoles(int fin,NodoEquipo* &equipo,NodoEquipo* comprobar){
			int goles=0;
			
			int min= 0;
			int max=fin;
			bool iguales= true;
			
			while(iguales){
				goles = generarNumeros(max,min);
				
				if(goles != comprobar->equipo->getGoles()){
					iguales=false;
				}
				
			}
			
			
			equipo->equipo->setGoles(goles);
		}
		
		void asignarTarjetas(int max,NodoEquipo* equipo){
			

			
			int tarjetas=0;
			
			int nAmarillas=0;
			int nRojas=0;
			
			
			
			
			//cout<<"valor de max: "<<max<<endl;
			for(int i=0;i<3;i++){
				tarjetas = generarNumeros(max,0);	
				//cout<<"miraaaaaaaaa veeeee: "<<tarjetas<<endl;
				if(tarjetas == 0){
					nAmarillas++;
				}
				else{
					if(nRojas<2){
						if(tarjetas==1){
							nRojas++;
						}
						
					}
					
					
				}
			}
			

			
			//asignado las cartas a los jugadores
			
			int numeroJugador=0;
			int agresividad;
			bool noSalir=true;
			Nodo* aux=NULL;
			while(nRojas!=0 || nAmarillas!=0){
				aux=equipo->equipo->getjugadores();
				
				while(aux!=NULL && noSalir){
					agresividad = aux->jugador->getAgresividad();
					bool noAsignada=true;					
					int nMini=aux->jugador->getNumero()-2;					
					int nMax=aux->jugador->getNumero()+3;
					
					for(int i=0;i<agresividad && noAsignada;i++){
						
						numeroJugador=generarNumeros(nMax,nMini);					
						if(numeroJugador==aux->jugador->getNumero()){
							noAsignada=false;							
							
							//definir que tarjeta sacerle
							int tarjeta;
							bool veri=true;							
							while(veri){
								
								if(nAmarillas>0 && nRojas>0){
									tarjeta = generarNumeros(1,0);
								}
								else if(nAmarillas==0){
									tarjeta = 1;																									
								}
								else if(nRojas == 0){
									tarjeta=0;
								}													
								if(tarjeta==0){
									
									if(nAmarillas!=0){
										nAmarillas--;
										veri=false;
										
									}
								}
								else if(tarjeta==1){
									
									if(nRojas != 0){
										nRojas--;
										veri=false;
										
									}
								}
								
							}						
							
							//sacandole tarjeta al jugador
							aux->jugador->setTarjeta(tarjeta);
						}
						
					}
					//verificando si todavia hay parejeta para seguir repartiendo
					if(nRojas==0 && nAmarillas==0){
						noSalir=false;
					}
					
					aux=aux->siguiente;
					
					
				}				
			}
		

			
			
		}
		
		
		void OrganizarGrupoOctavos(int group){
			NodoEquipo* g1 = NULL;
			switch(group){
				case 1:{
					g1 = grupo1.mostrarList();
					break;
				}
				case 2:{
					g1 = grupo2.mostrarList();
					break;
				}
				case 3:{
					g1 = grupo3.mostrarList();
					break;
				}
				case 4:{
					g1 = grupo4.mostrarList();
					break;
				}
			}
			
			NodoEquipo* aux=g1;
			Equipo* equipo1=NULL;
			Equipo* equipo2=NULL;
			
			
			
			equipo1= g1->equipo;
			g1=g1->siguiente;
			bool comprobar= true;
			
			while(g1!=NULL){
				
				//en el caso de que existe otro con mayor puntaje, se hace cambio
				if(equipo1->getPuntos() < g1->equipo->getPuntos()){
					equipo2=equipo1;
					equipo1=g1->equipo;
					comprobar = false;
				}
				//en el caso de que existe otro con el mismo punte,se toman los goles
				else if(equipo1->getPuntos() == g1->equipo->getPuntos()){
					
					if(equipo1->getGoles() < g1->equipo->getGoles()){
						
						equipo2 = equipo1;						
						equipo1 = g1->equipo;
						comprobar = false;
					}
					else if(equipo2!=NULL){
						if(equipo2->getGoles()<g1->equipo->getGoles()){
							equipo2= g1->equipo;
							comprobar = false;
						}
						
					}
					else{
						equipo2= g1->equipo;
						comprobar = false;
					}
					
					
				}
				g1=g1->siguiente;
			}
			//buscando el segundo puesto
			//en el caso de que el primero sea el mayor			
			if(comprobar){
				//cout<<"entro aca,osea el primero es el mayor"<<endl;
				//NodoEquipo* aux=grupo1.mostrarList();
				int puntaje= equipo1->getPuntos();//
				
				puntaje-=3;
				int contador=0;
				bool noEntro = true;
				while(noEntro){			
					//cout<<"bucle Grande"<<endl;
					while(aux!=NULL){
						//cout<<"bucle pequenio"<<endl;
						//buscando uno de referencia
						if(aux->equipo->getPuntos() == puntaje && noEntro){
							equipo2=aux->equipo;
							noEntro = false;
							aux=aux->siguiente;						
						}
						if(aux!=NULL){
							
							if(!noEntro && equipo2->getPuntos() == aux->equipo->getPuntos()){
								if(equipo2->getGoles() < aux->equipo->getGoles()){
									equipo2=aux->equipo;
								}
							}						
						}
						
						if(aux!=NULL){
							aux=aux->siguiente;
						}
						
					}	
					puntaje-=3;	
					
					
				}
																				
			}
			//primer equipo
			Equipo* e1 = new Equipo(equipo1->getId(),equipo1->getNombre(),equipo1->getAtaque(),equipo1->getDefensa(),equipo1->getGrupo());
			Nodo* j = equipo1->getjugadores();
			while(j!=NULL){
				Jugador* juga= new Jugador(j->jugador->getNumero(),j->jugador->getNombre(),j->jugador->getAgresividad());
				e1->cargarJugadores(juga);
				j=j->siguiente;
			}
			//suplentes
			j=equipo1->getSuplentes();
			while(j!=NULL){
				Jugador* suple= new Jugador(j->jugador->getNumero(),j->jugador->getNombre(),j->jugador->getAgresividad());
				e1->cargarSuplentes(suple);
				j=j->siguiente;
			}
			
			//segundo equipo
			Equipo* e2 = new Equipo(equipo2->getId(),equipo2->getNombre(),equipo2->getAtaque(),equipo2->getDefensa(),equipo2->getGrupo());
			j = equipo2->getjugadores();
			while(j!=NULL){
				Jugador* juga= new Jugador(j->jugador->getNumero(),j->jugador->getNombre(),j->jugador->getAgresividad());
				e2->cargarJugadores(juga);
				j=j->siguiente;
			}
			
			//suplentes
			j=equipo2->getSuplentes();
			while(j!=NULL){
				Jugador* suple= new Jugador(j->jugador->getNumero(),j->jugador->getNombre(),j->jugador->getAgresividad());
				e2->cargarSuplentes(suple);
				j=j->siguiente;
			}						
			
			switch(group){
				case 1:{
					grupoOctavos1.agregar(e1);
					grupoOctavos1.agregar(e2);
					break;
				}
				case 2:{
					grupoOctavos2.agregar(e1);
					grupoOctavos2.agregar(e2);
					break;
				}
				case 3:{
					grupoOctavos3.agregar(e1);
					grupoOctavos3.agregar(e2);
					break;
				}
				case 4:{
					grupoOctavos4.agregar(e1);
					grupoOctavos4.agregar(e2);
					break;
				}
			}			

			
			
		}
		
		/*
		void HacerCambios(NodoEquipo &*equipo){
			Nodo* jugadores=equipo->equipo->getjugadores();
			int tarjetaRoja=0;
			int tarjetaAmarilla=0;
			while(jugadores!=NULL){
				tarjetaRoja=jugadores->jugador->getNumeroCartas(1);
				tarjetaAmarilla=jugadores->jugador->getNumeroCartas(0);
				
				if(tarjetaAmarilla>=2 || tarjetaRoja==1){
					equipo->equipo->hacerCambio(jugadores->jugador);
					
				}
				
				jugadores=jugadores->siguiente;
			}
		}
		
		*/int generarNumeros(int max,int min){
			
			int numero;
			
			numero = min + rand() % (max-min);
			
			return numero;
		}
		
		/*void exportarResultados(){
			
			ofstream archivo;
			NodoEquipo* listaEquipo = equipos.mostrarList();
			Nodo* listaJugadores=NULL;
			
			archivo.open("Resultados.txt",ios::out);//abriendo el archivo
			
			if(archivo.fail()){
				cout<<"ERROR al exportar, no eres tu, soy yo";
				exit(1);
			}
			
			archivo<<"PARTICIPANTES:"<<end;
			while(listaEquipo!=NULL){
				archivo<<endl<<listaEquipo->equipo->getNombre()<<"{"<<endl;
				listaJugadores=listaEquipo->equipo->getjugadores();
				
				//exportando participantes con su informacion
				while(listaJugadores!=NULL){
					archivo<<endl;
					archivo<<listaJugadores->jugador.getNombre()<<"[";
					archivo<<listaJugadores->jugador.getNumero()<<"]"<<endl;
					listaJugadores=listaJugadores->siguiente;
				}
				archivo<<endl<<"}";
				listaEquipo=listaEquipo->siguiente;
				
				//partidos
				archivo<<endl;
				archivo<<"Partidos"<<endl<<endl;
				if(partidos==NULL){
					archivo<<"NO HAY PARTIDOS REGISTRADOS";
				}
				else{
					while(partidos!=NULL){												
						archivo<<"Fecha: "<<partidos->partido->getFecha()<<endl;
						archivo<<partidos->partido->getEquipo1.getNombre()<<"[";
						archivo<<partidos->partido->getEquipo1.getGoles()<<"] - ";
						archivo<<partidos->partido->getEquipo2.getNombre()<<"[";
						archivo<<partidos->partido->getEquipo2.getGoles()<<"]"<<endl;
						archivo<<"Ganador: "partidos->partido->getGanador().getNombre()<<endl;
						
						//tarjetas amarillas
						archivo<<"Tarjetas Amarillas [";
						//primer equipo						
						archivo<<partidos->partido->getEquipo1.getNombre<<": ";
						Nodo* x=partidos->partido->getEquipo1.getjugadores();
						while(x!=NULL){
							if(x.jugador.getNumeroCartas(0)!=0){
								archivo<<x.jugador.getNombre()<<",";
							}
							x=x->siguiente;
						}						
						//segundo equipo
						archivo<<" | "<<partidos->partido->getEquipo1.getNombre<<": ";
						x=partidos->partido->getEquipo2.getjugadores();
						while(x!=NULL){
							if(x.jugador.getNumeroCartas(0)!=0){
								archivo<<x.jugador.getNombre()<<",";
							}
							x=x->siguiente;
						}
						archivo<<"]"<<endl;
						
						//tarjetas rojas
						archivo<<"Tarjetas Rojas [";
						//primer equipo						
						archivo<<partidos->partido->getEquipo1.getNombre<<": ";
						Nodo* x=partidos->partido->getEquipo1.getjugadores();
						while(x!=NULL){
							if(x.jugador.getNumeroCartas(1)!=0){
								archivo<<x.jugador.getNombre()<<",";
							}
							x=x->siguiente;
						}						
						//segundo equipo
						archivo<<" | "<<partidos->partido->getEquipo1.getNombre<<": ";
						x=partidos->partido.getEquipo2.getjugadores();
						while(x!=NULL){
							if(x->jugador->getNumeroCartas(1)!=0){
								archivo<<x->jugador->getNombre()<<",";
							}
							x=x->siguiente;
						}				
						archivo<<"]"<<endl;
						
						archivo<<"---------------------------------------------"<<endl<<endl;
						partidos=partidos->siguiente;
					}	
				}
				
				
			}
		}*/
		
		NodoEquipo* getEquipos(){
			return equipos.mostrarList();
		}
		
		NodoEquipo* getGrupoA(){
			return grupo1.mostrarList();
		}
		NodoEquipo* getGrupoB(){
			return grupo2.mostrarList();
		}
		NodoEquipo* getGrupoC(){
			return grupo3.mostrarList();
		}
		NodoEquipo* getGrupoD(){
			return grupo4.mostrarList();
		}
		
		NodoEquipo* getGrupoOctavosA(){
			return grupoOctavos1.mostrarList();
		}
		NodoEquipo* getGrupoOctavosB(){
			return grupoOctavos2.mostrarList();
		}
		NodoEquipo* getGrupoOctavosC(){
			return grupoOctavos3.mostrarList();
		}
		NodoEquipo* getGrupoOctavosD(){
			return grupoOctavos4.mostrarList();
		}						
		
		nodoPartido* getPartidos(){
			return partidos;
		}
		
		nodoPartido* getPartidosOctavos(){
			return partidosOctavos;
		}
		
		void agregarPartido(Partido* &p){
			nodoPartido *nuevoNodo = new nodoPartido();
			nuevoNodo->partido=p;
			nodoPartido *aux1= partidos;
			nodoPartido *aux2;
			while(aux1!=NULL){
				aux2=aux1;
				aux1=aux1->siguiente;
			}
			if(aux1==partidos){
				partidos=nuevoNodo;
			}
			else{
				aux2->siguiente=nuevoNodo;
			}
			
			nuevoNodo->siguiente=aux1;
		}
		
		void agregarPartidoOctavo(Partido* &p){
			nodoPartido *nuevoNodo = new nodoPartido();
			nuevoNodo->partido=p;
			nodoPartido *aux1= partidosOctavos;
			nodoPartido *aux2;
			while(aux1!=NULL){
				aux2=aux1;
				aux1=aux1->siguiente;
			}
			if(aux1==partidosOctavos){
				partidosOctavos=nuevoNodo;
			}
			else{
				aux2->siguiente=nuevoNodo;
			}
			
			nuevoNodo->siguiente=aux1;
		}		
		
		
		
};
#endif
