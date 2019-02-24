/*Biblioteca incluidas */
#include <iostream >
#include <fstream >
#include <string >
#include "usuario.h" //esta el struct y los prototipos de las funciones

/*Espacios de nombres usados*/
using namespace std;

/*main(), usado para probar las funciones de este modulo*/
/*int main(){
	tUsuario usuario;
	string id ;
	string contrasenia;
	tListaRegCorreo listaReg;
	
	ifstream archivo; 
	ofstream archivo1;
	
	archivo1.open("zzz.txt");
	
	archivo.open ("lancelot@fdimail.com_usuarios.txt" );
	if (archivo.is_open()){
	
	cargar(usuario,  archivo);
	guardar(usuario, archivo1);
	cargar(usuario,  archivo);
	guardar(usuario, archivo1);
	cargar(usuario,  archivo);
	guardar(usuario, archivo1);
	archivo1 << "XXX" << endl;
	}
	
	

	/*inicializar( usuario, id, contrasenia);

	validarContrasenia(usuario, contrasenia);
	system ("pause");
}*/

/*
*Funcion para verificar la contraseña que haya metido el usuario, sera usada en el gestor, para cuando incie sesion el usuario
*Recibe una contraseña (string ) y comprueba que sea igual a la del usuario y si lo es devuelve true, si no false.
*/

bool validarContrasenia(const tUsuario &usuario, string contrasenia)
{

	bool ok= false;
	
		if (usuario.contraseña == contrasenia)
		{
		
			ok = true;

		}

	return ok;

}

/*
*En esta funcion modifica el usuario y rellena el id, y la contraseña.
*Las lista de entrada y salida se inicializan a 0 llamando a la funcion inicializar
*/

void inicializar(tUsuario& usuario, string id, string contrasenia)
{

	
	usuario.nombre = id;
	usuario.contraseña = contrasenia;

	inicializar(usuario.entrada);
	inicializar(usuario.salida);

}

/*
*Dado un archivo ya abierto , escribira en el txt, primero escribira  el nombre , luego la contraseña.
*Y en cuanto a las lista de entrada y de salida se hara un contador e ira escribiendo los datos de el id del que lo ha enviado y si lo a lido o no
*/

void guardar(const tUsuario& usuario,ofstream& archivo1)
{
	
	tListaRegCorreo listaReg;
	int cont=0;

	//primero se escribe nombre y contraseña
	archivo1 << usuario.nombre << endl;
	archivo1 << usuario.contraseña << endl;
	
	//luego el contador de los correos de entrada es decir, el numero de correos que tiene 
	archivo1 << usuario.entrada.contador<< endl;

		//luego ira recorriendo toda la lista y la escribiendo en el txt
		while (cont< usuario.entrada.contador)
		{
			archivo1 << usuario.entrada.ficha1[cont].id <<" "<<  usuario.entrada.ficha1[cont].leido << endl;
			cont++;
		}
	//luego se pone el numero de correos que tiene la salida 
	archivo1 << usuario.salida.contador << endl;

	//y se hace lo mismo que con la entrada pero en salida 
	cont =0;

		while(cont <usuario.salida.contador )
		{
			archivo1 << usuario.salida.ficha1[cont].id <<" "<<  usuario.salida.ficha1[cont].leido << endl;
			cont++;
		}
	
}

/*
*Funcion para cargar el  usuario , en cuanto a la lista de entrada y salida primero se pone a 0 y se empiezan a relleñar
*Hasta que se acabe la lista de salida .
*Terminara de leer cuando lea XXX
*/

bool cargar(tUsuario & usuario, ifstream & archivo)
{
	bool ok = true;
	string aux;
	int contador, cont ;
	tListaRegCorreo listaReg;

	//pone la entrada y salida a 0
	inicializar(listaReg);
	inicializar(usuario.entrada);
	inicializar(usuario.salida);

	archivo >> aux;

		if (aux == "XXX")
		{
			ok = false;
		}

		if (ok == true)// si no ha leido XXX
		{
			usuario.nombre = aux;
			archivo >> usuario.contraseña;
			archivo >> contador;

			cont =0;	
		
			while (cont < contador)
			{

				cargar(listaReg,  archivo);// se carga la entrada del usuario
				usuario.entrada.ficha1[usuario.entrada.contador] = listaReg.ficha1[listaReg.contador-1];// listaReg.contador-1 porque al acabar la funcion suma listaReg
				usuario.entrada.contador++;
				cont++;

			}

			archivo >> contador;//lee el numero de correos de salida

			cont =0;
			
			//se hace lo mismo que con la entrada 
			while (cont < contador)
			{

				cargar(listaReg,  archivo);
				usuario.salida.ficha1[usuario.salida.contador] = listaReg.ficha1[listaReg.contador-1];
				usuario.salida.contador++;
				cont++;

			}
		
	
		}

	return ok;
}