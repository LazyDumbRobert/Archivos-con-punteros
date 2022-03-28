#include <iostream>
#include <stdio.h>  
#include <string.h> 
#include <conio.h>
using namespace std;

const char *nombre_archivo = "archivo.dat";
const char *nombre_archivo_temp = "archivo_temp.dat";

struct estudiante{
	int codigo;
	char nombre[50];
	char direccion[100];
	char apellido[50];
	int telefono;
}Estudiante, *p_estudiante=&Estudiante;//declaracion de puntero que apunta a la estructura estudiante

void crear();
void leer();
void actualizar();
void eliminar();

int main(){
	
	int op;
	int *p_op = &op; //Utilizamos punteros para el menú principal
	
	do{
		system("cls");
		cout<<"1.Agregar estudiante"<<endl;
		cout<<"2.Actualizar estudiante datos de estudiante"<<endl;
		cout<<"3.Leer datos de estudiante"<<endl;
		cout<<"4.Eliminar estudiante"<<endl;
		cout<<"0.Salir"<<endl;
		cout<<"Ingrese la opcion que desea realizar: ";
		cin>>*p_op;
		
		switch(*p_op){ //Utilizamos punteros para el switch
			case 1: crear(); break;
			case 2: actualizar(); break;
			case 3: leer(); break;
			case 4: eliminar(); break;
			case 0: break;
		}
	}while(op!=0);
	
	return 0;
	getch();
}

void actualizar(){
	system("cls");
	FILE* archivo = fopen(nombre_archivo,"r+b");
	int id;
	string nombre, apellido,direccion;
	string *p_n = &nombre, *p_lastn = &apellido, *p_adress = &direccion; //Declaramos los punteros de los datos que vamos a actualizar
	cout<<"Ingrese el id para modificar: ";
	cin>>id;
	
	fseek(archivo,id *sizeof(struct estudiante),SEEK_SET);
	
		cout<<"Ingrese el codigo: ";
		cin>>p_estudiante->codigo; //Utilizamos el puntero que apunta a la estructura
		cin.ignore();
		
		cout<<"Ingrese el nombre de estudiante: ";
		getline(cin,*p_n); //Utilizamos el puntero de nombre
		strcpy(p_estudiante->nombre,nombre.c_str()); //Utilizamos el puntero que apunta a la estructura
		
		cout<<"Ingrese el apellido de estudiante: ";
		getline(cin,*p_lastn); //Utilizamos el puntero de apellidos
		strcpy(p_estudiante->apellido,apellido.c_str());//Utilizamos el puntero que apunta a la estructura
		
		cout<<"Ingrese el numero de telefono: ";
		cin>>p_estudiante->telefono;
		
		cout<<"Ingrese la direccion del estudiante: ";
		fflush(stdin);
		getline(cin,*p_adress); //Utilizamos el puntero de direccion
		strcpy(p_estudiante->direccion,direccion.c_str());//Utilizamos el puntero que apunta a la estructura
		
		
		getch();
		fwrite(&Estudiante,sizeof(struct estudiante),1,archivo);
		fclose(archivo);
}

void leer(){
	system("cls");
	FILE* archivo = fopen(nombre_archivo,"rb");
	
	if(!archivo){
		archivo = fopen(nombre_archivo,"w+b");
	}
	int id=0;
	
	fread(&Estudiante,sizeof(struct estudiante),1,archivo);
	
	do{
			//Utilizamos punteros para imprimir todos los datos de la estructura
			cout<<"__________________________"<<endl;
			cout<<"Id: "<<id<<endl;
			cout<<"Codigo: "<<p_estudiante->codigo<<endl;
			cout<<"Nombres: "<<p_estudiante->nombre<<endl;
			cout<<"Apellidos: "<<p_estudiante->apellido<<endl;
			cout<<"Telefono: "<<p_estudiante->telefono<<endl;
			cout<<"Direccion: "<<p_estudiante->direccion<<endl;
			fread(&Estudiante,sizeof(struct estudiante),1,archivo);
			id++;
		
	}while(feof(archivo)==0);
	getch();
	fclose(archivo);
}

void crear(){
	system("cls");
	FILE* archivo = fopen(nombre_archivo,"ab");
	char continuar;
	string nombre, apellido,direccion;
	string *p_n = &nombre, *p_lastn = &apellido, *p_adress = &direccion; //Declaramos los punteros de los datos que vamos a crear
	do{
		fflush(stdin);
		cout<<"Ingrese el codigo: ";
		cin>>p_estudiante->codigo;//Utilizamos el puntero que apunta a la estructura
		cin.ignore();
		
		cout<<"Ingrese el nombre de estudiante: ";
		getline(cin,*p_n);
		strcpy(p_estudiante->nombre,nombre.c_str());//Utilizamos el puntero que apunta a la estructura
		
		cout<<"Ingrese el apellido de estudiante: ";
		getline(cin,*p_lastn);
		strcpy(p_estudiante->apellido,apellido.c_str());//Utilizamos el puntero que apunta a la estructura
		
		cout<<"Ingrese el numero de telefono: ";
		cin>>p_estudiante->telefono;
		cin.ignore();
		
		cout<<"Ingrese la direccion del estudiante: ";
		getline(cin,*p_adress);
		strcpy(p_estudiante->direccion,direccion.c_str());//Utilizamos el puntero que apunta a la estructura
		
		
		fwrite(&Estudiante,sizeof(struct estudiante),1,archivo);
		
		cout<<"Desea agregar otro esutidiante (s/n): ";
		cin>>continuar;
	}while(continuar=='s' or continuar=='S');
	getch();
	fclose(archivo);
}

void eliminar(){
	system("cls");
	FILE *archivo, *archivo_temp; 
	int n; 
	int *p_n = &n; //Declaramos un puntero para el ingreso del codigo a eliminar
	archivo_temp=fopen(nombre_archivo_temp,"w+b"); 
	archivo=fopen(nombre_archivo,"rb"); 
	                      				                
	cout<<"Ingrese el codigo del estudiante que desea eliminar: "; 
	cin>>*p_n; //Usamos el puntero para el ingreso
		                                                                                
		while(fread(&Estudiante,sizeof(estudiante),1,archivo)){ 
			if (p_estudiante->codigo != n) //utilizamos el puntero para comparar el codigo del estudiante
			fwrite(&Estudiante,sizeof(estudiante),1,archivo_temp); 
			}
	                
		fclose(archivo_temp); 
		fclose(archivo); 
	                
		archivo_temp=fopen(nombre_archivo_temp,"rb"); 
		archivo=fopen(nombre_archivo,"wb"); 
	 
		while(fread(&Estudiante,sizeof(estudiante),1, archivo_temp)){ 
			fwrite(&Estudiante,sizeof(estudiante),1, archivo); 
		}
	 cout<<"El estudiante ha sido eliminado exitosamente, presione una tecla para continuar...";
	 getch();              
	fclose(archivo_temp); 
	fclose(archivo); 
}
