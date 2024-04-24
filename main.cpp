#ifndef MAIN_CPP
#define MAIN_CPP	

#include <iostream>
#include<string>
#include<stdlib.h>
//#include "Equipo.hpp"
#include "Mundial.hpp"

using namespace std;

void mostrarEquipos(int);
void mostrarPartidos(nodoPartido*,bool);

Mundial mundial = Mundial();

int main() {
	srand(time(nullptr));
	int opcion,opcion2;	
	
	do{
		cout<<"\t.:MUNDIAL:."<<endl<<endl;
		cout<<"1.Comenzar Mundial"<<endl;
		cout<<"2.ver todos los equipos"<<endl;
		cout<<"3.ver grupos"<<endl;
		cout<<"4. salir"<<endl;
		cout<<"->";cin>>opcion;
		
		system("cls");
		switch(opcion){
			case 1:{
				mundial.JugarPartido();//face de grupo				
				mundial.JugarPartidoOctavos();//cuartos de finales
				mundial.JugarPartidosSemiFinal();//semi final
				mundial.jugarPartidoFinal();//final
				do{
					cout<<"\tOpciones del Mundial"<<endl<<endl;
					cout<<"1.Simulacion fragmentada del mundial"<<endl;
					cout<<"2.Simular partido a partido"<<endl;
					cout<<"3.Simular todo el Mundial"<<endl;
					cout<<"4.Regresar"<<endl;
					cout<<"->";cin>>opcion2;
					system("cls");
					switch(opcion2){
						case 1:{
							nodoPartido* partidos=mundial.getPartidos();
							mostrarPartidos(partidos,false);							
							system("pause");
							system("cls");
							cout<<"\n\tPUNTAJES DE LA FACE DE GRUPO"<<endl<<endl;
							mostrarEquipos(1);
							system("pause");
							cout<<"\n\tEQUIPOS CLASIFICADOS"<<endl<<endl;
							mostrarEquipos(2);
							system("pause");
							system("cls");		
							cout<<"\n\tCUARTOS DE FINALES"<<endl<<endl;					
							mostrarPartidos(mundial.getPartidosOctavos(),false);
							system("pause");
							cout<<"\n\tEQUIPOS CLASIFICADOS"<<endl<<endl;
							mostrarEquipos(3);							
							system("pause");
							system("cls");
							cout<<"\n\tSEMI FINAL"<<endl<<endl;
							mostrarPartidos(mundial.getPartidosSemiFinal(),false);							
							system("pause");
							cout<<"\n\tFINAL"<<endl<<endl;
							mostrarPartidos(mundial.getPartidoFinal(),false);
							system("pause");
							system("cls");
							cout<<"\n\tGANADOR DEL MUNDIAL"<<endl<<endl;
							for(int i=0;i<100;i++){
								cout<<mundial.getGanador()->getNombre()<<endl;
							}
							system("pause");
							break;
						}
						case 2:{
							nodoPartido* partidos=mundial.getPartidos();
							mostrarPartidos(partidos,true);							
							
							system("cls");
							cout<<"\n\tPUNTAJES DE LA FACE DE GRUPO"<<endl<<endl;
							mostrarEquipos(1);
							system("pause");
							cout<<"\n\tEQUIPOS CLASIFICADOS"<<endl<<endl;
							mostrarEquipos(2);
							system("pause");
							system("cls");		
							cout<<"\n\tCUARTOS DE FINALES"<<endl<<endl;					
							mostrarPartidos(mundial.getPartidosOctavos(),true);
						
							cout<<"\n\tEQUIPOS CLASIFICADOS"<<endl<<endl;
							mostrarEquipos(3);							
							system("pause");
							system("cls");
							cout<<"\n\tSEMI FINAL"<<endl<<endl;
							mostrarPartidos(mundial.getPartidosSemiFinal(),true);							
							
							cout<<"\n\tFINAL"<<endl<<endl;
							mostrarPartidos(mundial.getPartidoFinal(),true);
							
							system("cls");
							cout<<"\n\tGANADOR DEL MUNDIAL"<<endl<<endl;
							for(int i=0;i<100;i++){
								cout<<mundial.getGanador()->getNombre()<<endl;
							}
							system("pause");
							break;
						}
						case 3:{
							nodoPartido* partidos=mundial.getPartidos();
							mostrarPartidos(partidos,false);							
							//system("pause");
							//system("cls");
							cout<<"\n\tPUNTAJES DE LA FACE DE GRUPO"<<endl<<endl;
							mostrarEquipos(1);
							//system("pause");
							cout<<"\n\tEQUIPOS CLASIFICADOS"<<endl<<endl;
							mostrarEquipos(2);
							//system("pause");
							//system("cls");		
							cout<<"\n\tCUARTOS DE FINALES"<<endl<<endl;					
							mostrarPartidos(mundial.getPartidosOctavos(),false);
							//system("pause");
							cout<<"\n\tEQUIPOS CLASIFICADOS"<<endl<<endl;
							mostrarEquipos(3);							
							//system("pause");
							//system("cls");
							cout<<"\n\tSEMI FINAL"<<endl<<endl;
							mostrarPartidos(mundial.getPartidosSemiFinal(),false);							
							//system("pause");
							cout<<"\n\tFINAL"<<endl<<endl;
							mostrarPartidos(mundial.getPartidoFinal(),false);
							system("pause");
							system("cls");
							cout<<"\n\tGANADOR DEL MUNDIAL"<<endl<<endl;
							for(int i=0;i<100;i++){
								cout<<mundial.getGanador()->getNombre()<<endl;
							}
							system("pause");							
							break;
						}
					}
										
				}while(opcion2 != 4);

				break;
			}
			case 2:{
				
				cout<<"\tEQUIPOS\n"<<endl;
				NodoEquipo* x = mundial.getEquipos();
				Nodo* z =NULL;
				Nodo* suple =NULL;
				
				while(x != NULL){
					cout<<x->equipo->getNombre()<<"(Def:"<<x->equipo->getDefensa()
					<<", Ataq: "<<x->equipo->getAtaque()<<", Grupo: "<<x->equipo->getGrupo()
					<<") {"<<endl<<endl;
					z=x->equipo->getjugadores();
					suple=x->equipo->getSuplentes();
					while(z!=NULL){
						cout<<"-> "<<z->jugador->getNombre()<<"(Agresividdad:"<<z->jugador->getAgresividad()<<")."<<endl;
						z=z->siguiente;
					}
					cout<<endl<<"Suplentes:"<<endl;
					while(suple!=NULL){
						cout<<"-> "<<suple->jugador->getNombre()<<"(Agresividdad:"<<suple->jugador->getAgresividad()<<")."<<endl;
						suple=suple->siguiente;
					}
					cout<<endl<<"}"<<endl<<endl<<endl;
					x=x->siguiente;
				}
				system("pause");
				break;
			}
			
			case 3:{
				
				mostrarEquipos(1);			
											
				system("pause");
				break;
			}
		}
		
		system("cls");
	}while(opcion!=4);
		
	
	
	system("pause");
	return 0;
}

void mostrarEquipos(int selection){
		
	NodoEquipo* a=NULL;
	NodoEquipo* b=NULL;
	NodoEquipo* c=NULL;
	NodoEquipo* d=NULL;			
		
	switch(selection){
		case 1:{
				a=mundial.getGrupoA();
				b=mundial.getGrupoB();
				c=mundial.getGrupoC();
				d=mundial.getGrupoD();			
			break;
		}
		case 2:{
				a=mundial.getGrupoOctavosA();
				b=mundial.getGrupoOctavosB();
				c=mundial.getGrupoOctavosC();
				d=mundial.getGrupoOctavosD();						
			break;
		}
		case 3:{
			NodoEquipo* semiFinal= mundial.getGrupoSemiFinal();
			ListaEquipo* _a = new ListaEquipo();
			ListaEquipo* _b = new ListaEquipo();
			ListaEquipo* _c = new ListaEquipo();
			ListaEquipo* _d = new ListaEquipo();
			int grupo;
			while(semiFinal!=NULL){
				grupo= semiFinal->equipo->getGrupo();
				
				switch(grupo){
					case 1:{
						_a->agregar(semiFinal->equipo);
						a=_a->mostrarList();
						break;
					}
					case 2:{
						_b->agregar(semiFinal->equipo);
						b=_b->mostrarList();						
						break;
					}
					case 3:{
						_c->agregar(semiFinal->equipo);
						c=_c->mostrarList();						
						break;
					}
					case 4:{
						_d->agregar(semiFinal->equipo);
						d=_d->mostrarList();						
						break;
					}
				}
				semiFinal=semiFinal->siguiente;
			}
			
			break;
		}


		
		
	}

	
	
	
	cout<<"\n\tGrupos"<<endl<<endl;
	cout<<" -------------"<<endl;
	cout<<"|   GRUPO A   |"<<endl;
	cout<<" -------------"<<endl;
	int largo;
	int mitad;
	while(a!=NULL){
		cout<<"|";
		largo= a->equipo->getNombre().length()+3;
		largo=13-largo;
		mitad = largo/2;
		for(int i=0;i<mitad;i++){
			cout<<" ";
		}
		cout<<a->equipo->getNombre()<<"["<<a->equipo->getPuntos()<<"]";
		for(int i=0;i<mitad;i++){
			cout<<" ";
		}
		cout<<"|"<<endl;
		a=a->siguiente;
	}
	cout<<" -------------"<<endl<<endl;
	
	cout<<"--------------"<<endl;
	cout<<"|   GRUPO B   |"<<endl;
	cout<<"--------------"<<endl;

	while(b!=NULL){
		cout<<"|";
		largo= b->equipo->getNombre().length()+3;
		largo=13-largo;
		mitad = largo/2;
		for(int i=0;i<mitad;i++){
			cout<<" ";
		}					
		cout<<b->equipo->getNombre()<<"["<<b->equipo->getPuntos()<<"]";
		for(int i=0;i<mitad;i++){
			cout<<" ";
		}
		cout<<"|"<<endl;
		b=b->siguiente;
	}
	cout<<" -------------"<<endl<<endl;	
	
	cout<<"--------------"<<endl;
	cout<<"|   GRUPO C   |"<<endl;
	cout<<"--------------"<<endl;
	while(c!=NULL){
		cout<<"|";
		largo= c->equipo->getNombre().length()+3;
		largo=13-largo;
		mitad = largo/2;
		for(int i=0;i<mitad;i++){
			cout<<" ";
		}					
		cout<<c->equipo->getNombre()<<"["<<c->equipo->getPuntos()<<"]";
		for(int i=0;i<mitad;i++){
			cout<<" ";
		}
		cout<<"|"<<endl;
		c=c->siguiente;
	}
	cout<<" -------------"<<endl<<endl;
	
	cout<<"--------------"<<endl;
	cout<<"|   GRUPO D   |"<<endl;
	cout<<"--------------"<<endl;
	while(d!=NULL){
		cout<<"|";
		largo= d->equipo->getNombre().length()+3;
		largo=13-largo;
		mitad = largo/2;
		for(int i=0;i<mitad;i++){
			cout<<" ";
		}					
		cout<<d->equipo->getNombre()<<"["<<d->equipo->getPuntos()<<"]";
		for(int i=0;i<mitad;i++){
			cout<<" ";
		}
		cout<<"|"<<endl;
		d=d->siguiente;
	}
	cout<<" -------------"<<endl<<endl;	
	
}




void mostrarPartidos(nodoPartido* partidos,bool automatico){

	Nodo* jugadoresTarjetas;
	int contador=1;
	cout<<"\tPARTIDOS"<<endl<<endl;
	//int contador
	while(partidos!=NULL){
		cout<<"partido numero: "<<contador<<endl;
		cout<<partidos->partido->getEquipo1()->getNombre();
		cout<<"["<<partidos->partido->getEquipo1()->getGoles();
		cout<<"] - ["<<partidos->partido->getEquipo2()->getGoles();
		cout<<"]";
		cout<<partidos->partido->getEquipo2()->getNombre()<<endl;
		cout<<"Fecha: "<<partidos->partido->getFecha()<<endl;
		cout<<"\nINFORMACION ADICIONAL"<<endl;
		cout<<"tarjetas "<<partidos->partido->getEquipo1()->getNombre()<<"["<<partidos->partido->getEquipo1()->getTotalTarjetas()<<"]."<<endl;
		cout<<"tarjetas rojas["<<partidos->partido->getEquipo1()->getTotalTarjetasRojas()<<"] {";
		jugadoresTarjetas = partidos->partido->getEquipo1()->getJugadoresConRojas();
		while(jugadoresTarjetas != NULL){
			cout<<jugadoresTarjetas->jugador->getNombre()<<", ";
			jugadoresTarjetas = jugadoresTarjetas->siguiente;
		}
		cout<<"}."<<endl;
		cout<<"tarjetas Amarillas["<<partidos->partido->getEquipo1()->getTotalTarjetasAmarillas()<<"] {";
		jugadoresTarjetas = partidos->partido->getEquipo1()->getJugadoresConAmarillas();
		while(jugadoresTarjetas != NULL){
			cout<<jugadoresTarjetas->jugador->getNombre()<<", ";
			jugadoresTarjetas = jugadoresTarjetas->siguiente;
		}
		cout<<"}"<<endl<<endl;
		
		
		cout<<"tarjetas "<<partidos->partido->getEquipo2()->getNombre()<<"["<<partidos->partido->getEquipo2()->getTotalTarjetas()<<"]."<<endl;
		cout<<"tarjetas rojas["<<partidos->partido->getEquipo2()->getTotalTarjetasRojas()<<"] {";
		jugadoresTarjetas = partidos->partido->getEquipo2()->getJugadoresConRojas();
		while(jugadoresTarjetas != NULL){
			cout<<jugadoresTarjetas->jugador->getNombre()<<", ";
			jugadoresTarjetas = jugadoresTarjetas->siguiente;
		}
		cout<<"}."<<endl;
		cout<<"tarjetas Amarillas["<<partidos->partido->getEquipo2()->getTotalTarjetasAmarillas()<<"] {";
		jugadoresTarjetas = partidos->partido->getEquipo2()->getJugadoresConAmarillas();
		while(jugadoresTarjetas != NULL){
			cout<<jugadoresTarjetas->jugador->getNombre()<<", ";
			jugadoresTarjetas = jugadoresTarjetas->siguiente;
		}
		cout<<"}"<<endl;								
		cout<<"----------------------------------------------"<<endl;
		contador++;
		partidos=partidos->siguiente;
		if(automatico){
			system("pause");
		}
		
	}	
	
}
#endif

