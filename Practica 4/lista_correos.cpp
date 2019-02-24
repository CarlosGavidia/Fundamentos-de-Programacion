#include <iostream >
#include <ctime >
#include <string >
#include <fstream >
#include <sstream>
#include "lista_correo.h" //dentro del lista_correo.h esta la biblioteca correo.h

/*Espacios de nombres usados*/
using namespace std;

/*main(), probado de las funciones de este modulo*/
/*int main(){
	string dominio="arturo@fdimail.com";
	string dominio1="prueba@fdimail.com";
	ifstream archivo;
	tListaCorreos correos;
	tCorreo correo;
	string emisor ="prueba@fdimail.com";
	
	string id= "lancelot@fdimail.com_1428843792";
	int pos = -1;
	inicializar(correos);
	cargar(correos,  dominio);
	//string nombre = "prueba.txt";
	correoNuevo(correo,   emisor);
	insertar(correos, correo);
	//ordenar_AF(correos);
	guardar(correos, dominio1);
	//buscar(correos,  id, pos);

	system ("pause");
}*/

/*
*Devuleve el true si el asunto de la izq es mayor que el de la der
*En caso de que el asunto fuese el mismo se mirara la fecha
*Clave de ordenacion doble
*/

bool operator<(tCorreo opIzq, tCorreo opDer) 
{
	bool ok = false;

		if (opIzq.asunto < opDer.asunto)
		{
			ok = true;
		}
		else if (opIzq.asunto == opDer.asunto)
		{
			if (opIzq.fecha < opDer.fecha)
			{
				ok = true;
			}
		}

	return ok;

}

/*
*Esta funcion ordenara por primero asunto y si es igual por fecha
*Esta funcion sera llamada cuando el usuario haya pulsado la opcion 5 de lectura rapida
*Al final de la funcion la lista de correos estara ordenada
*Metodo utilizado , el metodo de la burbuja mejorada.
*Recibe una listade correos que la ordenara, como se ha dicho anteriormente
*/

void ordenar_AF(tListaCorreos &correos)
{

	bool inter = true;
	tListaCorreos tmp;//temporal para ordenar 
	int i = 0;

		while ((i < correos.contador - 1) && inter) 
		{
			inter = false;

			for (int j = correos.contador - 1; j > i; j--) 
			{
				if (correos.ficha[j] < correos.ficha[j - 1]) 
				{
					tmp.ficha[i] = correos.ficha[j];
					correos.ficha[j] = correos.ficha[j - 1];
					correos.ficha[j - 1] = tmp.ficha[i];
					inter = true;
				}
			}

			if (inter) 
			{
				i++;
			}
		}

}

/*
*Inicializara el contador a 0 de la lista de correos
*/

void inicializar(tListaCorreos &correos){
	correos.contador =0;
}

/*
*Como el archivo ya estara cargado en el modulo de correo solo se ira guardando en el contador el correo e ira aumentando
*Si hay algun fallo se hara saber al usuario
*Recibe el nombre del dominio para poder cargar el txt(suma del nombre y lo que esta entre "")
*/

bool cargar(tListaCorreos &correos, string dominio)
{
	tCorreo correo;
	bool ok = false;
	string aux;
	string nombre =dominio+ "_ListaCorreo.txt";
	ifstream archivo;
	archivo.open(nombre);

		if (archivo.is_open())
		{
			ok = true;
			inicializar(correos);//pone el contador a 0

			while ((cargar(correo,  archivo)) && correos.contador < MAX_CORREOS)//cuando cargar sea negativo querra decir que ha llegado al centinela,solo cargara los correos hasta que se llene el contador
			{ 
				correos.ficha[correos.contador]= correo;
				correos.contador++;
			}
		}
		else 
		{

			cout << "La aplicaion va a comenzar con las listas vacias  " << endl;
			
		}

	//devuelve si se ha cargado correctamente
	return ok;

}

/*
*Guarda en el mismo txt la lista de correos
*Lo guarda a partir del modulo correo
*Recibe el nombre del dominio que se le suma al nombre para poder guardar la lista de correos
*/

void guardar(const tListaCorreos &correos, string dominio1)
{

	ofstream archivo1 ;
	tCorreo correo;
	dominio1= dominio1+ "_ListaCorreo";
	string nombre = dominio1 +".txt";

	archivo1.open (nombre);

		if (archivo1.is_open())
		{
			for (int i =0; i< correos.contador;i++)
			{
				correo = correos.ficha[i] ;
				guardar(correo, archivo1);
				
			}

			archivo1 << "XXX" << endl;

		}
	
}

/*
*Funcion para insertar un correo en la lista ordenada de correos
*Se utiliza el algoritmo de inserccion ordenada , ya que la lista esta ordenada desde el inicio
*/

bool insertar(tListaCorreos &correos, const tCorreo &correo)
{
	
	bool colocar = false;
	string id;
	int pos;
	
		//siempre que no este lleno la lista de correos se aplica
		if ( correos.contador < MAX_CORREOS)
		{

			id = correo.id;
				if (!buscar(correos, id, pos)) 
				{
					colocar = true;
					for (int i = correos.contador; i > pos; i--)
					//{
						correos.ficha[i] = correos.ficha[i -1];
						correos.ficha[pos] = correo;
						correos.contador++;
					//}
				}
			else
			{
				cout << "Elemento repetido" << endl;
			}
		}

		else
		{
			cout << "La lista de correos esta llena"<< endl;
		}

		 
	return colocar;
}
/*
*Funcion de buscar un id y devuelve la posicion
*Si no exite devuleve la posicion en la que deberia de estar y false
*Algoritmo utilizado el de busqueda binaria , ya que esta ordenado por id
*/

bool buscar(const tListaCorreos &correos, string id, int &pos)
{

	bool encontrado = false;
	int  ini = 0, fin =correos.contador - 1, mitad;
	
		while ((ini <= fin) && !encontrado) 
		{
			mitad = (ini + fin) / 2; 

				if (id == correos.ficha[mitad].id) 
				{
					encontrado = true;
				}
				else if (id < correos.ficha[mitad].id) 
				{
					fin = mitad - 1;
				}
				else {
					ini = mitad + 1;
				}

		}

		
		if (encontrado) 
		{
			pos = mitad;
		}
		else 
		{
			pos = ini;
		}

	return encontrado;
}