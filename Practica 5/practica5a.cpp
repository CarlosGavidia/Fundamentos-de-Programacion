/*Autores: Carlos Gavidia Ortiz y Pedro Garcia Marcos
*Practica 5 : fdimail.com 2.0
*Grado ingenieria informatica
*Clase C
*Practica hecha e incluida la parte opcional de borrar el correo cuando el emisor y receptor ya lo han borrado de sus registros(de la practica 4 )
*/

/*Bibliotecas incluidas*/
#include <iostream >
#include <string >
#include <vld.h>
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
	bool entrada= true;
	tGestor gestor;
	string adios;
	int numero;
	string nombre, id;
	bool ok= false ;
	string dominio= "fdimail.com";
	
	int opcion, turno=0;

	numero= menu();
	
	if (!arrancar( gestor,  dominio)) 
	{
		inicializar(gestor, dominio);
	}

	while (numero!=0 )
	{
		cout <<"Bienvenido al correo de " << dominio <<  endl;
		if (numero ==1)
		{
			ok = iniciarSesion(gestor,  id);
			if (ok)
			{
				nombre = id;
				entrada = false;
				opcion= menuBandeja(gestor,  entrada, nombre);
				ejecutarMenuBandeja(gestor, opcion, entrada);
				
				numero= menu();
			}
			else 
			{
				cout << "No se ha podido iniciar la sesion el usuario/contrasenia no son correctos " << endl;
				system ("pause");
				system ("cls");
		
			}
			if (!ok)
			{
				numero= menu();
			}

		}
		else if (numero == 2 )
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
			else 
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

	if (numero==0)
	{
		borrar (gestor);
		cout << "Has pronto!!" << endl;
	}
	
	system ("pause");
}
