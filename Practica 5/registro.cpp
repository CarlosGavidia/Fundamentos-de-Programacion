/*Bibliotecas incluidas*/
#include <iostream >
#include "registro.h"
#include "correo.h"
#include <string >
#include <fstream >

/*Espacios de nombres usados*/
using namespace std;


/*main(), probado las funciones de este modulo*/
/*int main(){
	tListaRegCorreo listaReg;
	tRegCorreo registro;
	ifstream archivo;
	archivo.open("lancelot@fdimail.com_usuarios.txt");
	if (archivo.is_open()){
		inicializar(listaReg);
		cargar(listaReg,  archivo);
	}
	
	string id = "lanceot@fimail.com_323432324";
	//inicializar(listaReg);
	//insertar(listaReg,  registro);
	//borrar(listaReg, id);
	correoLeido(listaReg, id);
	//buscar(listaReg,  id);
	ofstream archivo1;
	archivo1.open("zzz.txt");

	guardar(listaReg, archivo1);

	system ("pause");
}*/

/*
*Incializa la lista de lista registros a 0 y se pone a null Y la capacidad al maximo
*/

void inicializar(tListaRegCorreo &listaReg){

	listaReg.contador =0;
	listaReg.registro=NULL;
	listaReg.capacidad = MAX_REG;

}

/*
*Carga el registro de un usuario, dandole un archivo ya abierto
*Primero lee el id y la contraseña del usuario, pedendiendo si es 0 o 1 sera falseo true respectivamente
*Los datos leidos se lo asigna a un registro y aumenta el contador
*cuando la lista del contador sea mayor o igual no guardara en la lista esos registros
*/

void cargar(tListaRegCorreo &listaReg, ifstream& archivo)
{
	tRegCorreo reg;
	int  numero;

	archivo >> reg.id ;
	archivo >> numero;
	
	if (numero== 0)
	{
		reg.leido = false;
	}
	else 
	{
		reg.leido = true;
	}

	if (listaReg.contador < listaReg.capacidad)
	{	
		listaReg.registro[listaReg.contador]= reg;
		listaReg.contador++;
	}
			

}

/*
* Guarda en el txt primero el numero de registro que hay por usuario y luego recorre toda la lista y va poniendo el el id y el numero 1 o 0  leido o no
*/
			
void guardar(const tListaRegCorreo &listaReg, ofstream& archivo1)
{
	
	archivo1 << listaReg.contador << endl;
		
	for (int i =0; i < listaReg.contador; i++)
	{
		archivo1 << listaReg.registro[i].id << " ";

		if ( listaReg.registro[i].leido == true)
		{
			archivo1 << 1 << endl;
		}
		else 
		{
			archivo1 << 0 << endl;
		}

	}
	
}

/*
*Para redimensionar se hace al igual que en la lista de correos, se iguala a un auxiliar , la luego copiarlo en el registro original
*Se borrar el auxiliar y se modifica la capacidad a la nueva 
*/

void redimensionar (tListaRegCorreo &listaReg, int incremento)
{

	tPtrRegistro aux = new tRegCorreo[(listaReg.capacidad*3)/2+1];

	for (int i = 0; i < listaReg.contador; i++) 
	{
		aux[i] = listaReg.registro[i];
    }

	delete [] listaReg.registro;
	listaReg.registro = aux;
	listaReg.capacidad = (listaReg.capacidad*3)/2+1;

}

/*
*Inserta un registro en la lisat de registros
*Primero se asegura de que hay hueco , es decir de que no se ha llenado el numero maximo de registros
*Y lo inserta en la ultima posicion de la lista de registros , no se llama a la funcion de buscar , ya que la lisat no esta ordenada
*Por tanto se copian en la ultima posicion el id , y el bool y se aumenta el contador.
*Cuando se el contador llega a la capacidad maxima de la lista llamara a redimensionar 
*/

bool insertar(tListaRegCorreo &listaReg, tRegCorreo registro)
{
	bool ok  =false;
	string emisor;
	
	if (listaReg.contador ==listaReg.capacidad )
	{
		redimensionar (listaReg, MAX_REG);
	}
		
	listaReg.registro[listaReg.contador].id = registro.id;
	listaReg.registro[listaReg.contador].leido= false;
	listaReg.contador++;
	ok = true;
		
	return ok;
}
/*
*Borra un registro de la lista de regsitros
*busca la posicon del id llamando a la funcion buscar y obtine la posicion.
*En dicha posicion se elimina ese registro.
*Se resta la lista contador del registro
*Se rediemnsionara al borrar un registro
*/

bool borrar(tListaRegCorreo &listaReg, string id)
{
	int pos;
	bool ok;
	
	pos = buscar(listaReg,  id);

	if (pos !=-1)
	{
		ok= true;
		for (int i = pos; i < listaReg.contador - 1 ; i++) 
		{
			listaReg.registro[i] = listaReg.registro[i + 1];
		}

	listaReg.contador--;

	}
	else
	{
		ok= false;
	}

	if (listaReg.contador < listaReg.capacidad - 2 * MAX_REG)
	{
      redimensionar(listaReg, -MAX_REG);
    }

	return ok;
}
/*
*Marca un correo de false a true , es decir de no leido a leido
*Primero obtienen la posicion del id que quieren cabiar llmando a la funcion de buscar
*Y en esa posicion se pone a true
*Devuelve un bool si se ha encontrad dicha posicion y se ha podido marcar
*/

bool correoLeido(tListaRegCorreo &listaReg, string id)
{
	bool encontrado;
	int pos= buscar(listaReg,  id);
	
	if (pos !=-1)
	{
		encontrado = true;
		listaReg.registro[pos].leido = true;
	}

	else
	{
		encontrado = false;
	}

	return encontrado;
}

/*
*Busca la posicon donde esta el id , que lleva por refrencia la funcion
*Empieza en pos = -1 , por si no encontrase la posicion
*Hace una busqueda normal ya que la lista no esta ordenada.
*Enmpieza a recorrer la lista y cuando lo encuentre para y devulve dicha posicion , en caso de no encontrarlo devolvera -1
*/

int buscar(const tListaRegCorreo &listaReg, string id)
{
	int pos= -1 , i =0;
	bool encontrado = false;

	while ((i< listaReg.contador)&& !encontrado)
	{
		if (listaReg.registro[i].id == id)
		{
			encontrado = true;
			pos = i;
		}

		i++;
	}
	
	return pos;
}

/*
*Al eliminar la lista de registro se hara de una misma manera a la de los correos.
*Se borra la lista y se pone el contador y la capacidad a 0
*/

void eliminar1 (tListaRegCorreo &listaReg){

	delete [] listaReg.registro;
	listaReg.registro=nullptr;
	listaReg.contador = 0;
	listaReg.capacidad = 0;
}