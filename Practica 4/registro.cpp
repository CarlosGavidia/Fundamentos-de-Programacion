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
*Incializa la lista de lista registros a 0
*/

void inicializar(tListaRegCorreo &listaReg){
	listaReg.contador =0;
}

/*
*Carga el registro de un usuario, dandole un archivo ya abierto
*Primero lee el id y la contraseña del usuario, pedendiendo si es 0 o 1 sera falseo true respectivamente
*Los datos leidos se lo asigna a un registro y aumenta el contador
*/

void cargar(tListaRegCorreo &listaReg, ifstream& archivo)
{

	int  numero;
	tRegCorreo registro;
	
	archivo >> registro.id ;
	archivo >> numero;

		if (numero== 0)
			{
				registro.leido = false;
			}
		else 
			{
				registro.leido = true;
			}

		if (listaReg.contador < MAX_REG)// cuando la lista del contador sea mayor o igual no guardara en la lista esos registros
		{	
			listaReg.ficha1[listaReg.contador]= registro;
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
			archivo1 << listaReg.ficha1[i].id << " ";

			if ( listaReg.ficha1[i].leido == true)
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
*Inserta un registro en la lisat de registros
*Primero se asegura de que hay hueco , es decir de que no se ha llenado el numero maximo de registros
*Y lo inserta en la ultima posicion de la lista de registros , no se llama a la funcion de buscar , ya que la lisat no esta ordenada
*Por tanto se copian en la ultima posicion el id , y el bool y se aumenta el contador.
*/

bool insertar(tListaRegCorreo &listaReg, tRegCorreo registro)
{
	bool ok  =false;
	string emisor;
	tCorreo correo;

	correoNuevo(correo, emisor);

		if (listaReg.contador < MAX_REG )
		{
			listaReg.ficha1[listaReg.contador].id = correo.id;
			listaReg.ficha1[listaReg.contador].leido= false;
			listaReg.contador++;
			ok = true;
		}
	
	return ok;
}
/*
*Borra un registro de la lista de regsitros
*busca la posicon del id llamando a la funcion buscar y obtine la posicion.
*En dicha posicion se elimina ese registro.
*Se resta la lista contador del registro
*/

bool borrar(tListaRegCorreo &listaReg, string id)
{
	int pos;
	bool ok;
	
	pos = buscar(listaReg,  id);//busca la posicion a borrar

		if (pos !=-1)
		{
			ok= true;
			for (int i = pos; i < listaReg.contador - 1 ; i++) 
			{
				listaReg.ficha1[i] = listaReg.ficha1[i + 1];
			}

		listaReg.contador--;

		}
		else
		{
			ok= false;
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
			listaReg.ficha1[pos].leido = true;
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

int buscar(const tListaRegCorreo &listaReg, string id){
	int pos= -1 , i =0;
	bool encontrado = false;

	while ((i< listaReg.contador)&& !encontrado)
	{
		if (listaReg.ficha1[i].id == id)
		{
			encontrado = true;
			pos = i;
		}

		i++;
	}
	
	return pos;
}