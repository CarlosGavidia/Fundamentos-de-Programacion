/*Bibliotecas incluidas */
#include <iostream >
#include <ctime >
#include <string >
#include <fstream >

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

bool operator<(const tCorreo opIzq,const tCorreo opDer) 
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
*Primero inicaliza a 0 el contador y capacidad y a NULL el correo.ficha, luego se hace un new para borrarlo al final y no generar restos
*Al final se llamara a eliminar para eliminar el array dinamico temporal que habiamos creado y no dejar basura
*/

void ordenar_AF(tListaCorreos &correos)
{

	bool inter = true;
	tListaCorreos tmp;//temporal para ordenar 
	int i = 0;

	inicializar (tmp);
	tmp.ficha=new tCorreo [correos.contador];

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

	eliminar (tmp);

}

/*
*Inicializara el contador a 0 de la lista de correos, la capacidad a MAX y la ficha a NULL
*/

void inicializar(tListaCorreos &correos){
	
	correos.contador =0;
	correos.ficha=NULL;
	correos.capacidad = MAX_CORREOS;
}

/*
*Como el archivo ya estara cargado en el modulo de correo solo se ira guardando en el contador el correo e ira aumentando
*Recibe el nombre del dominio para poder cargar el txt(suma del nombre y lo que esta entre "")
*Para empezar incializa la lista de correos.
*Lee el numero al principio de la lista que indica el numero de correos y pone la capacidad a la siguiente decena
*Crea un array dinamico de la dimension de numero de correos.capacidad que tenga.
*Y empieza el bucle que llamara a la funcion de cargar correos tantas veces como el numero de correos que haya en el txt
*Se ira asignando a cada posicion de la lista el correo.
*En caso de no haber detectado el txt, informara que empieza con las listas vaciasy la capacidad sera de 10
*/

bool cargar(tListaCorreos &correos, string dominio)
{
	tCorreo correo;
	bool ok = false;
	string aux;
	int numero, cont=0;
	
	string nombre =dominio+ "_ListaCorreo.txt";
	ifstream archivo;
	archivo.open(nombre);

	if (archivo.is_open())
	{
		ok = true;
		inicializar(correos);
		archivo >> numero;
		correos.capacidad= ((numero/10)+1)*10;
		correos.ficha= new tCorreo [correos.capacidad];
			
		while (( cont < numero) && cargar(correo,  archivo))
		{ 
			correos.ficha[correos.contador]= correo;
			correos.contador++;
			cont++;
		}
	}

	else 
	{

		cout << "La aplicaion va a comenzar con las listas vacias  " << endl;
		correos.capacidad=10;
			
	}

	return ok;

}

/*
*Guarda en el mismo txt la lista de correos
*Lo guarda a partir del modulo correo
*Recibe el nombre del dominio que se le suma al nombre para poder guardar la lista de correos
*Primero se pone el numero de correos que hay (correos.contador), por lo que no hara falta poner el centinela
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
		archivo1 << correos.contador << endl;

		for (int i =0; i< correos.contador;i++)
		{
			correo = correos.ficha[i] ;
			guardar(correo, archivo1);
				
		}

	}
	
}

/*
*Funcion para insertar un correo en la lista ordenada de correos
*Se utiliza el algoritmo de inserccion ordenada , ya que la lista esta ordenada desde el inicio
*No hace falta redimensionar porque ya lo hago en el gestor
*/

bool insertar(tListaCorreos &correos, const tCorreo &correo)
{
	
	bool colocar = false;
	string id;
	int pos;

	id = correo.id;

	if (!buscar(correos, id, pos)) 
	{
		colocar = true;
		for (int i = correos.contador; i > pos; i--)
					
			correos.ficha[i] = correos.ficha[i -1];
			correos.ficha[pos] = correo;
			correos.contador++;
					
	}
	else
	{
		cout << "Elemento repetido" << endl;
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
		else 
		{
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

/*
*Se utilizara cuando el la capacidad de los correos sea la misma que la del contador y asi ampliar su capacidad de poder tener mas correos
*Se nombra un puntero auxiliar con la nueva capacidad y se va copiando cada posicion de correos a la auxiliar
*Luego se borrar la lista anterior
*Se copia todo a la lista de correos y tambien se amplia la capacidad 
*/

void redimensionar(tListaCorreos &correos, int incremento)
{

	tPtrCorreo aux = new tCorreo[(correos.capacidad*3)/2+1];

	for (int i = 0; i < correos.contador; i++) 
	{
		aux[i] = correos.ficha[i];
    }

	delete [] correos.ficha;
	correos.ficha = aux;
	correos.capacidad = (correos.capacidad*3)/2+1;

}

/*
*Se utilizara cuando se apage el gestor y por tanto se cierre la aplicacion 
*En esta funcion se borra la lista de correos, se pone a NULL y tambien el contador y la capacidad se ponen a 0
*/

void eliminar (tListaCorreos &correos)
{

	
	delete [] correos.ficha;
	correos.ficha=nullptr;
	correos.contador = 0;
	correos.capacidad = 0;

}