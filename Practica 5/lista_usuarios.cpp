/*Biblioteca incluidas */
#include <iostream >
#include <fstream >
#include <string >
#include "lista_usuario.h" // biblioteca en la que se incluye los prototipos de las funciones y el structy el array estatico de datos dinamicos

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
*Incializa la lista de usuarios poniendo el contador de la lista a 0 y va recorriendo todas las posiciones y poniendolas a NULL
*/

void inicializar(tListaUsuarios &usuarios)
{
	usuarios.contador=0;
	for (int i=0; i < usuarios.contador;i++)
	{
		usuarios.ficha2[i]=NULL;
	}

}

/*
*Esta funcion se encarga de relleñar la lista de usuarios.
*Recibe el nombre del dominio para poder abrir el txt de a lista de usuarios
*Se abrira el archivo, y si existe y se ha podido abrir , llamara a la funcion de cargar usuario, para cargarlo de uno en uno controlando que no se pase del numero maximo
*En caso de que no se haya podido leer los usuarios bien se indicara por pantalla
*Se devolvera el reusltado en forma de bool , true si ha ido todo bien , false en caso contrario.
*Solo leera los usuarios que entren en el maximo , a partir de superar el maximo no se seguira leyendo ningun usuario
*Al final se elimina usuario.entrada y salida ya que ya se ha copiado en la lista de usuarios
*/

bool cargar(tListaUsuarios& usuarios, string dominio)
{
	
	bool ok = false;
	string nombre = dominio+"_Usuarios.txt";
	tUsuario usuario;
	ifstream archivo;
	
	archivo.open(nombre);

	if (archivo.is_open())
	{
		ok = true;
		inicializar(usuarios);
			
		while ((cargar(usuario,  archivo)) && usuarios.contador < MAX_USUARIOS) 
		{	
			usuarios.ficha2[usuarios.contador]=new tUsuario (usuario);
			usuarios.contador++;
					
		}
				
		eliminar1 (usuario.entrada);
		eliminar1 (usuario.salida);

		if (usuarios.contador==MAX_USUARIOS)
		{
			cout << "Se han cargado solo los usuarios hasta que se ha llegado al maximo de usuarios " << endl;
		}
			
	}

	else 
	{
		cout << "La aplicaion va a comenzar con las listas vacias  " << endl;
		ok = false;
		usuario.entrada.capacidad=10;
		usuario.salida.capacidad=10;
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
			usuario.contraseña = usuarios.ficha2[i]->contraseña ;
			usuario.entrada = usuarios.ficha2[i]->entrada ;
			usuario.salida = usuarios.ficha2[i]->salida ;
			usuario.nombre = usuarios.ficha2[i]->nombre ;
			guardar(usuario, archivo1);
				
		}
		archivo1 << "XXX" << endl;
	}

}

/*
*Añade un usuario nuevo a la lista de usuarios
*Simepre que no haya pasado el tamaño maximo de usuarios, buscara el usuario , llamando a la funcion buscar usuario, si tampoco lo encuntra se produce a añadirlo
*Se ñade el usuario en la posicion que le corresponda , porque en la funcion de buscar si no lo encuentra nos devuelve la posicion en la que deberia de estar
*Las bandejas se pondran a 0 y se escribira el nombre y la contraseña , todo esto a partir de copiar el usuario que pase por referencia , que contendra toda esta informacion
*Por tanto la lista de usuarios que nos pasan por refrencia quedara modificada.
*Se crean un new en la lista de usuarios para poder añadir el nuevo usuario, y por tantotambien el de la entrada y salida
*/

bool aniadir(tListaUsuarios& usuarios, const tUsuario& usuario)
{
	
	bool colocar = false;
	string id= usuario.nombre;
	int posicion;

	if (usuarios.contador < MAX_USUARIOS)
	{
	
		if (!buscarUsuario(usuarios, id, posicion)) 
		{
			colocar = true;
				
			for (int i = usuarios.contador; i > posicion; i--)
			{
				usuarios.ficha2[i] = usuarios.ficha2[i -1];
			}
			usuarios.contador++;

			usuarios.ficha2[posicion] = new tUsuario(usuario);
			usuarios.ficha2[posicion]->entrada.registro= new tRegCorreo[MAX_REG];
			usuarios.ficha2[posicion]->salida.registro= new tRegCorreo[MAX_REG];
		}
				
		else
			cout << "Usuario repetido !!" << endl;
			
	}

	else
	{
		cout << "Lista de usuarios llena" << endl;
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

		if (id == usuarios.ficha2[mitad]->nombre) 
		{
			encontrado = true;
		}

		else if (id < usuarios.ficha2[mitad]->nombre) 
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
		posicion = mitad;
	}

	else 
	{
		posicion = ini;
	}

	return encontrado;

}

/*
*Esta funcion se utilizara cuando se apage el gestor y se salga de la aplicacion 
*En ella se ira recorriendo la lista de usuarios y se ira podiendo a null tambien la de entrada y salida llamando a la funcion de registro y s epondra el contador a 0
*/

void destruir (tListaUsuarios & usuarios)
{
	
	for (int i = 0; i < usuarios.contador; i++) 
	{
		eliminar1(usuarios.ficha2[i]->entrada);
		eliminar1(usuarios.ficha2[i]->salida);

	delete usuarios.ficha2[i];
	usuarios.ficha2[i]=nullptr;

	}

	usuarios.contador = 0;
	
}