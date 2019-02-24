/*Biblioteca incluidas */
#include <iostream >
#include <fstream >
#include <string >
#include "lista_usuario.h" // biblioteca en la que se incluye los prototipos de las funciones y el struct

/*Espacios de nombres usados*/
using namespace std;

/*main(), para pribar las funciones de este modulo*/
/*int main(){
	tListaUsuarios usuarios;
	int posicion;
	ifstream archivo;
	tUsuario usuario;
	string dominio="lancelot@fdimail.com";
	
	string id = "arturo@fsimail.com";
	
	
	cargar(usuarios,dominio );
	
	string contrasenia;
	inicializar( usuario,  id,contrasenia);


	aniadir( usuarios, usuario);

	string dominio1 ="zzz.txt";
	guardar( usuarios, dominio);
	system ("pause");
}*/

/*
*Incializa la lista de usuarios poniendo el contador de la lista a 0
*/

void inicializar(tListaUsuarios &usuarios)
{
	usuarios.contador=0;
}

/*
*Esta funcion se encarga de relleñar la lista de usuarios.
*Recibe el nombre del dominio para poder abrir el txt de a lista de usuarios
*Se abrira el archivo, y si existe y se ha podido abrir , llamara a la funcion de cargar usuario, para cargarlo de uno en uno controlando que no se pase del numero maximo
*En caso de que no se haya podido leer los usuarios bien se indicara por pantalla
*Se devolvera el reusltado en forma de bool , true si ha ido todo bien , false en caso contrario.
*/

bool cargar(tListaUsuarios& usuarios, string dominio)
{

	bool ok = false;
	string nombre = dominio+"_Usuarios.txt"; // nombre del txt
	tUsuario usuario;
	ifstream archivo;
	
	archivo.open(nombre);

		if (archivo.is_open())// si se ha podido abrir:
		{
			ok = true;
			inicializar(usuarios);// pone la lista a 0

				while ((cargar(usuario,  archivo)) && usuarios.contador < MAX_USUARIOS) //solo leera los usuarios hasta que se llene el max usuarios o haya terminado de leer todo, lo que venga despues en el txt no se guardara en la lista
				{
					usuarios.ficha2[usuarios.contador]=usuario;
					usuarios.contador++;
	
				}
		}

		else 
		{
				cout << "La aplicaion va a comenzar con las listas vacias  " << endl;
			ok = false;
		}

	return ok;

}

/*
*Se guarda en el mismo txt los cambio que se hayan producido en la lista de usuarios, para ello recibe como parametro el nombre del dominio
*Recorrera toda la lista de usuarios llamando a cargar usuario para que escriba lo que haya en cada contador
*Tambien recibe el nombre del txt , que sera el mismo que cuando lo ha cargado.
*/

void guardar(const tListaUsuarios& usuarios, string dominio1)
{

	ofstream archivo1 ;
	tUsuario usuario;
	dominio1 = dominio1+ "_Usuarios.txt";

	archivo1.open (dominio1);

		if (archivo1.is_open())
		{
			for (int i =0; i< usuarios.contador;i++)
			{
				usuario = usuarios.ficha2[i] ; // guarda en el usuario el usuario que esta en la posicion del contador
				guardar(usuario, archivo1);
				
			}

			archivo1 << "XXX" << endl;// cuando termine de cargar todo en txt se añade XXX (centinela final)
		}


}

/*
*Añade un usuario nuevo a la lista de usuarios
*Simepre que no haya pasado el tamaño maximo de usuarios, buscara el usuario , llamando a la funcion buscar usuario, si tampoco lo encuntra se produce a añadirlo
*Se ñade el usuario en la posicion que le corresponda , porque en la funcion de buscar si no lo encuentra nos devuelve la posicion en la que deberia de estar
*Las bandejas se pondran a 0 y se escribira el nombre y la contraseña , todo esto a partir de copiar el usuario que pase por referencia , que contendra toda esta informacion
*Por tanto la lista de usuarios que nos pasan por refrencia quedara modificada.
*/

bool aniadir(tListaUsuarios& usuarios, const tUsuario& usuario)
{

	bool colocar = false;
	string id= usuario.nombre;// el id, para pasarselo por refrencia a la funcion de buscar
	int posicion;

		if (usuarios.contador < MAX_USUARIOS)//cuando sea menor que el maximo
		{
	
			if (!buscarUsuario(usuarios, id, posicion)) //no se debe de encontrar ya que si no , significa que ya existe
			{
				colocar = true;

				for (int i = usuarios.contador; i > posicion; i--)// se añade en la posicion que le corresponda
				
					usuarios.ficha2[i] = usuarios.ficha2[i -1];
					usuarios.ficha2[posicion] = usuario;
					usuarios.contador++;
				
			}

			//si ha encontrado al usuario
			else
			cout << "Usuario repetido !!" << endl;
			
		}

		else
		{
			cout << "Lista de usuarios llena";
			colocar = false;
		}


	return colocar;

}

/*
*En esta funcion se buscara el usuario en una lista de usuarios
*Al estar ordenado por id, se utiliza el algoritmo de busqueda binaria
*Devulve un bool que sera true si lo ha encontrado , false en caso contrario
*Y se pasara por refrencia la posicion , que tambien la buscara , si no existe el usuario en la lista se pondra la posicion en a que deberia de estar.
*/

bool buscarUsuario(const tListaUsuarios& usuarios,string id, int& posicion)
{

	bool encontrado = false;
	int  ini = 0, fin =usuarios.contador - 1, mitad;
	
		while ((ini <= fin) && !encontrado) 
		{
			mitad = (ini + fin) / 2; 

			if (id == usuarios.ficha2[mitad].nombre) 
			{
				encontrado = true;
			}

			else if (id < usuarios.ficha2[mitad].nombre) 
			{
				fin = mitad - 1;
			}

			else {
				ini = mitad + 1;
			}
		}

		if (encontrado) 
		{
			posicion = mitad;
		}

		else 
		{
			posicion = ini;
		}

	return encontrado;

}