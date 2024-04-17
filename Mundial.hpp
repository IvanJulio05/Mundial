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
		
		//
		ListaEquipo equipos=ListaEquipo();
		
		ListaEquipo grupo1=ListaEquipo();
		ListaEquipo grupo2=ListaEquipo();
		ListaEquipo grupo3=ListaEquipo();
		ListaEquipo grupo4=ListaEquipo();
		
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
							agresividadTotal=grupo->equipo->getTotalAgresividad();
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
			
			
			
			//asignarGoles						
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
					if(contador<=3){
						equi->cargarJugadores(juga);
					}
					else{
						equi->cargarSuplentes(juga);
					}
					
					contador++;
					//cout<<"valor de separador = "<<separador<<endl;
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
		
		nodoPartido* getPartidos(){
			return partidos;
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
};
#endif
