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
	Partido partido;
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
		
		void setPartido(Partido p){
			
			nodoPartido *nuevoNodo = new nodoPartido();
			nuevoNodo->partido=p;
			nodoPartido *aux1= partidos;
			
			partidos=nuevoNodo;
			nuevoNodo->siguiente=aux1;
		}
		
		void JugarPartido(){
			
			
			
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
				
				/*cout<<"id: "<<idEquipo<<endl;
				cout<<"nombreEquipo: "<<nombreEquipo<<endl;
				cout<<"ataque: "<<ataque<<endl;
				cout<<"defensa: "<<defensa<<endl;
				cout<<"grupo: "<<grupo<<endl;*/
				
				Equipo* equi = new Equipo(convertir(idEquipo),nombreEquipo,convertir(ataque),convertir(defensa),convertir(grupo));
				//lectura de los jugadores
				while(separador != "-"){
					
					getline(archivo,numeroJugador);
					getline(archivo,nombreJugador);
					getline(archivo,agresividad);
					getline(archivo,separador);
					
					//cout<<"numero del jugador: "<<numeroJugador<<endl;
					//cout<<"nombre del jugador: "<<nombreJugador<<endl;
					//cout<<"agresividad del jugador: "<<agresividad<<endl;
					
					Jugador* juga = new Jugador(convertir(numeroJugador),nombreJugador,convertir(agresividad));
					equi->cargarJugadores(juga);
					
					//cout<<"valor de separador = "<<separador<<endl;
				}
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
		
		/*void asignarGoles(int fin,NodoEquipo&* equipo){
			
			int goles=0;
			random_device rd;
			mt19937 gen(rd());
			
			int min= 0;
			int max=fin;
			
			uniform_int_distribution<> distribucion(min,max);
			
			goles = distribucion(gen);
			
			equipo->equipo.setGoles(goles);
			
		}
		
		void asignarTarjetas(int max,NodoEquipo&* equipo){
			
			int tarjetas=0;
			
			int nAmarillas=0;
			int nRojas=0;
			random_device rd;
			mt19937 gen(rd());
			
			int min= 0;
			int max=max;
			
			
			uniform_int_distribution<> distribucion(min,max);
			
			for(int i=0;i<3;i++){
				tarjetas = distribucion(gen);	
				if(tarjetas == 0){
					nAmarrillas++;
				}
				else{
					nRojas++;
				}
			}
			
			//asignado las cartas a los jugadores
			
			int numeroJugador=0;
			int agresividad;
			
			while(nRojas!=0 || nAmarillas!=0){
				
				Nodo *aux=equipo->equipo->getjugadores();
				
				while(aux!=NULL){
					
					agresividad = aux->jugador->getAgresividad();
					bool noAsignada=true;
					int nMini=aux->jugador->getNumero()-1;
					int nMax=aux->jugador->getNumero()+1;
					for(int i=0;i<agresividad && noAsinada;i++){
						
						numeroJugador=generarNumeros(nMax,nMini);
						
						if(numeroJugador==aux->jugador->getNumero()){
							noAsinada=false;
							//definir que tarjeta sacerle
							int tarjeta;
							bool veri=true;
							while(veri){
								tarjeta = generarNumeros(1,0);
								
								if(tarjeta==0){
									if(nAmarillas!=0){
										nAmariilas--;
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
					aux=aux->siguiente;
				}				
				
			}
			

			
			
			//equipo->equipo.setGoles(goles);
		}
		
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
		
		int generarNumeros(int max,int min){
			
			int numero;
			
			numero = min + rand() % (max-min);
			
			return numero;
		}/*
		
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
};
#endif
