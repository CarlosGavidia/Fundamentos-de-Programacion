/*Autores: Carlos Gavidia Ortiz y Pedro Garcia Marcos
*Practica 4 : fdimail.com
*Grado ingenieria informatica
*Clase C
*Practica hecha e incluida la parte opcional de borrar el correo cuando el emisor y receptor ya lo han borrado de sus registros
*/

/*Bibliotecas incluidas*/
#include <iostream >
#include <string >
#include "gestor.h"

/*Espacios de nombre */
using namespace std;

/*
*Llamara al menu y recibe la opcion , hasta que no sea 0 no saldra del bucle, llama  a arrancar para cargar el gestor
*Si es 1 inica sesion muestra la bandeja y ejecuta la opcion de la bandeja elegida , y volvera al menu
*Si la opcion es 2 en vez de inciar sesion creara una cuenta y hara lo mismo que antes
*Si es 0 se despedira y saldra del bucle
*/

int main()
{

	bool entrada= true;//para saber si esta en la bandeja de entrada(false) o de salida(true)
	tGestor gestor;
	string adios;
	int numero;
	string nombre, id;
	bool ok= false ;
	string dominio= "fdimail.com";
	string dominio1= "fdimail.com";
	int opcion;

	numero= menu();
		while (numero!=0 )
		{
			if (!arrancar( gestor,  dominio)) //pone el gestor a 0, todo si no ha encontrado las listas de ficheros
			{
				inicializar(gestor, dominio);
				apagar (gestor);
			}

			cout <<"Bienvenido al correo de " << dominio <<  endl;
			if (numero ==1)
			{
				ok = iniciarSesion(gestor,  id);
				if (ok)// si ha podido inicar sesion correctamente
				{
					nombre = id;
					entrada = false;
					opcion= menuBandeja(gestor,  entrada, nombre);
					ejecutarMenuBandeja(gestor, opcion, entrada);

					numero= menu();// volvera al menu hasta que el numero sea 0
				}
				else 
				{
					cout << "No se ha podido iniciar la sesion el usuario/contrasenia no son correctos " << endl;
					system ("pause");
					system ("cls");
		
				}
				if (!ok)// si no se ha podido inciar sesion volvera al menu
				{
					numero= menu();
				}

			}
			
			else if (numero == 2 )// crear cuenta
			{
				if (crearCuenta(gestor, id))
				{
					ok = true;
					nombre = id;
					entrada = false;
					opcion = menuBandeja(gestor,  entrada, nombre);
					ejecutarMenuBandeja(gestor, opcion, entrada);
					numero= menu();
				}
				else // en caso de no crear un cuenta correctamnte
				{
					ok = false;
					system ("pause");
					cout << endl;
					cout << "No se ha podido crear una cuenta " << endl;
					system ("pause");
					system ("cls");
					numero= menu();
				}
			}

		}

		if (numero==0)// si es 0 compruba que si se puediese borrar algun correo de la lista de correos
		{
			borrar (gestor);
			cout << "Has pronto!!" << endl;
		}

	system ("pause");
}
