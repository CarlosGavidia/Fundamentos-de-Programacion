/*Biblioteca incluidas */
#include <iostream >
#include <fstream >
#include <string >
#include "usuario.h" //esta el struct y el puntero ,los prototipos de las funciones

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

	return (usuario.contraseña == contrasenia);
}

/*
*En esta funcion modifica el usuario y rellena el id, y la contraseña.
*Las lista de entrada y salida se inicializan a 0 llamando a la funcion inicializar del registro
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
*primero se escribe nombre y contraseña
*luego el contador de los correos de entrada es decir, el numero de correos que tiene 
*luego ira recorriendo toda la lista y la escribiendo en el txt
*luego se pone el numero de correos que tiene la salida 
*y se hace lo mismo que con la entrada pero en salida 
*/

void guardar(const tUsuario& usuario,ofstream& archivo1)
{
	
	tListaRegCorreo listaReg;
	int cont=0;

	archivo1 << usuario.nombre << endl;
	archivo1 << usuario.contraseña << endl;
	
	archivo1 << usuario.entrada.contador<< endl;

	while (cont< usuario.entrada.contador)
	{
		archivo1 << usuario.entrada.registro[cont].id <<" "<<  usuario.entrada.registro[cont].leido << endl;
		cont++;
	}
	
	archivo1 << usuario.salida.contador << endl;

	cont =0;

	while(cont <usuario.salida.contador )
	{
		archivo1 << usuario.salida.registro[cont].id <<" "<<  usuario.salida.registro[cont].leido << endl;
		cont++;
	}
	
}

/*
*Funcion para cargar el  usuario , en cuanto a la lista de entrada y salida primero se pone a 0 y se empiezan a relleñar
*Hasta que se acabe la lista de salida .
*Terminara de leer cuando lea XXX
*pone la entrada y salida a 0
*Se hace un new de el usuario.entrada y salida *Tambien se hace new de la listaReg pero luego se elimnan, ya que sirven como auxiliares para cargar entrada y salida
*lee el numero de correos de entrada ,llama la funcion cargar de registro para relleñar el usuario.entrada y en salida lo mismo
*Si cuando este cargando los registros se llenan , llama a redimensionar para ampliar la capacidad de la entrada y salida 
*/

bool cargar(tUsuario & usuario, ifstream & archivo)
{
	bool ok = true;
	string aux;
	int contador, cont ;
	tListaRegCorreo listaReg;

	inicializar(listaReg);
	
	inicializar(usuario.entrada);
	inicializar(usuario.salida);
	usuario.entrada.registro = new tRegCorreo [MAX_REG];
	usuario.salida.registro = new tRegCorreo [MAX_REG];
	archivo >> aux;

	if (aux == "XXX")
	{
		ok = false;
	}

	if (ok == true)
	{
		usuario.nombre = aux;
		archivo >> usuario.contraseña;
		archivo >> contador;

		cont =0;	

		listaReg.capacidad=((contador/10)+1)*10;
		listaReg.registro= new tRegCorreo[listaReg.capacidad];
			
		while (cont < contador)
		{

			cargar(listaReg,  archivo);
			usuario.entrada.registro[usuario.entrada.contador] = listaReg.registro[listaReg.contador-1];
			usuario.entrada.contador++;

			if (usuario.entrada.contador>=MAX_REG  )
			{
				redimensionar (usuario.entrada,MAX_REG);
			}

			cont++;	

		}
			
		eliminar1(listaReg);
	
		archivo >> contador;

		cont =0;
			
		inicializar(listaReg);
		listaReg.capacidad=((contador/10)+1)*10;
		listaReg.registro= new tRegCorreo[listaReg.capacidad];
			
		while (cont < contador)
		{
			cargar(listaReg,  archivo);
			usuario.salida.registro[usuario.salida.contador] = listaReg.registro[listaReg.contador-1];
			usuario.salida.contador++;

			if (usuario.salida.contador>=MAX_REG)
			{
				redimensionar (usuario.salida,MAX_REG);
			}
			cont++;
				
		}

		eliminar1 (listaReg);
		
	}
		
	return ok;
}