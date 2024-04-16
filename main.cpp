#include <iostream>
#include<string>
#include<stdlib.h>
//#include "Equipo.hpp"
#include "Mundial.hpp"

using namespace std;


int main() {
	
	int opcion,opcion2;	
	Mundial mundial = Mundial();
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
				mundial.JugarPartido();
				do{
					cout<<"\tOpciones del Mundial"<<endl<<endl;
					cout<<"1.Simular todos el mundial"<<endl;
					cout<<"2.Simular partido a partido"<<endl;
					cout<<"3.Regresar"<<endl;
					cout<<"->";cin>>opcion2;
					
					switch(opcion2){
						case 1:{
							
							break;
						}
						case 2:{
							nodoPartido* partidos=mundial.getPartidos();
							int contador=1;
							cout<<"PARTIDOS"<<endl<<endl;
							while(partidos!=NULL){
								cout<<"partido numero: "<<contador<<endl;
								cout<<partidos->partido->getEquipo1()->getNombre();
								cout<<"["<<partidos->partido->getEquipo1()->getGoles();
								cout<<"] - ["<<partidos->partido->getEquipo2()->getGoles();
								cout<<"]";
								cout<<partidos->partido->getEquipo2()->getNombre()<<endl;
								cout<<"Fecha: "<<partidos->partido->getFecha()<<endl;
								
								cout<<"----------------------------------------------"<<endl;
								contador++;
								partidos=partidos->siguiente;
								system("pause");
							}
							break;
						}
					}
										
				}while(opcion2 != 3);

				break;
			}
			case 2:{
				
				cout<<"\tEQUIPOS\n"<<endl;
				NodoEquipo* x = mundial.getEquipos();
				Nodo* z =NULL;
				
				while(x != NULL){
					cout<<x->equipo->getNombre()<<"(Def:"<<x->equipo->getDefensa()
					<<", Ataq: "<<x->equipo->getAtaque()<<", Grupo: "<<x->equipo->getGrupo()
					<<") {"<<endl<<endl;
					z=x->equipo->getjugadores();
					while(z!=NULL){
						cout<<"-> "<<z->jugador->getNombre()<<"(Agresividdad:"<<z->jugador->getAgresividad()<<")."<<endl;
						z=z->siguiente;
					}
					cout<<endl<<"}"<<endl<<endl;
					x=x->siguiente;
				}
				system("pause");
				break;
			}
			
			case 3:{
				
				
				NodoEquipo* a=mundial.getGrupoA();
				NodoEquipo* b=mundial.getGrupoB();
				NodoEquipo* c=mundial.getGrupoC();
				NodoEquipo* d=mundial.getGrupoD();
				
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
											
				system("pause");
				break;
			}
		}
		
		system("cls");
	}while(opcion!=4);
		
	
	
	system("pause");
	return 0;
}
