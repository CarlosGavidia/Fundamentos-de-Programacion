/*
*Nota de la practica 4 :El modulo registro no lo hemos usado practicamente para nada (excepto para cargar el txt de usuarios), debido a que nos resultaba un poco lioso.
*Por lo que en este modulo habra difrencias con otros grupos 
*El programa funciona correctamente (por lo menos con las pruebas que nosotros hemos hecho), no hemos borrado la implementacion del registro.cpp para demostrar que sabiamos hacerla
*Esperamos que no resulte muy importante, ni muy prejudioso a la hora de poner la nota.
*/

/*Biblioteca incluidas */
#include <iostream >
#include <string >
#include "gestor.h"

/*Espacios de nombres usados*/
using namespace std;
void mensajesEntrada(const tGestor &gestor);
void mensajesSalida(const tGestor &gestor);
void leerMensajeEntrada ( tGestor &gestor,int &numero);
void leerMensajeSalida( tGestor &gestor,int &numero);
void correoConstestacion(tGestor &gestor, int &pos);
void borrarMensajeEntrada(tGestor &gestor, int &numero);
void borrarMensajeSalida(tGestor &gestor, int &numero);

/*main() utilizado para probar las funciones*/
/*int main(){
	bool entrada= true;
	tGestor gestor;
	string adios;
	int numero;
	string nombre, id;
	bool ok= false ;
	string dominio= "fdimail.com";
	int opcion;
	numero= menu();
	
	
	while ((numero!=0) ){

		
			cout << "Bienvenido al correo de fdimail.com " << endl;
			if (numero ==1){
				ok = iniciarSesion(gestor,  id);
				if (ok){
					nombre = id;
					entrada = false;
					opcion= menuBandeja(gestor,  entrada, nombre);
					ejecutarMenuBandeja(gestor, opcion, entrada);
					numero= menu();
				}
				else{
					cout << "No se ha podido iniciar la sesion el usuario/contrasenia no son correctos " << endl;
					system ("pause");
					system ("cls");
		
				}
				if (!ok){
				numero= menu();
			}

			}
			
			else if (numero == 2 ){
				if (crearCuenta(gestor, id)){
				ok = true;
				nombre = id;
				entrada = false;
				opcion = menuBandeja(gestor,  entrada, nombre);
				ejecutarMenuBandeja(gestor, opcion, entrada);
				numero= menu();

				}
				else {
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
	if (numero==0){
		cout << "Has pronto!!" << endl;
	}

	/*tListaRegCorreo listaReg;
	tCorreo correo;
	tListaUsuarios usuarios;
	int posicion;
	tGestor gestor;
	string aux;
	string dominio= "arturo@fdimail.com";

	iniciarSesion(gestor);

	//borrarCorreo(gestor,  listaReg);
	lecturaRapida( gestor,listaReg);

	/*string dominio1;
	string emisor= gestor.dominio;

	correoNuevo(correo,  emisor);
	string id = correo.destinatario;
	cargar(usuarios,  dominio);
	if (buscarUsuario( usuarios, id,  posicion)){
		enviarCorreo( gestor,correo);
		
		usuarios= gestor.usuarios;
		guardar(usuarios,  dominio1);
	}
	else {
		cout << "Error " << endl;
	}
	
	//leerCorreo( gestor,  listaReg);
	//arrancar( gestor,  dominio);
	//apagar(gestor);
	//crearCuenta(gestor);
	
	
	//system ("pause");
//}

*/

/*
*Menu de incio, mostrara las opciones al usuario y etsa funcion devolvera el numero que haya elegido el usuario , simepre que este entre 0 y 2
*/

int menu()
{
	int numero;

	cout << "Elija la opcion deseada: " << endl;
	cout << "1- Acceder a mi cuenta de correo " << endl;
	cout << "2- Crear cuenta de correo " << endl;
	cout << endl;
	cout << "0- Salir" << endl;

	cin >> numero;
	
	while (numero < 0 || numero > 2 )
	{
		cout << "Opcion no valida. Elije otra opcion " << endl;
		cin >> numero;
	}
	

	system ("cls");

	return numero;
}

/*
*Incializa el gestor, poniendo la lista de correos y usuarios a 0 y la posicion a -1 (para luego poder cambiarla al encontrar al usuario)
*/

void inicializar(tGestor &gestor, string dominio)
{

	gestor.dominio= dominio;

	inicializar(gestor.correos);
	inicializar(gestor.usuarios);

	gestor.posicion = -1;

}
/*
*Carga la lista de correos y usuarios llamando a dichas funciones y las guarda en el gestor, si todo ha ido bien devulve true, en caso contrario false
*Primero inicia el gestor a 0
*Luego carga los correos y usuarios
*/

bool arrancar(tGestor& gestor,  string dominio)
{
	bool ok = false;
	
	inicializar(gestor,  dominio);

	if (cargar(gestor.correos,  dominio))
	{
		
		if (cargar(gestor.usuarios,  dominio))
		{
				ok= true;
			
		}
	}

	return ok;
	
}

/*
*Guarda la lista de correos y usuarios del gestor (ya que han sido modificados durante la aplicacion) a los correos y usuarios.
*Llama a las funciones de guardado de dichos modulos y guardan los cambios en el txt
*Luego elimina los correos y los usuarios llamando a las funciones de destruccion para eliminar basura
*/

void apagar( tGestor &gestor)
{
	
	string dominio1 = gestor.dominio;

	guardar(gestor.correos, dominio1);
	guardar( gestor.usuarios,  dominio1);
	
	eliminar (gestor.correos);
	destruir (gestor.usuarios);
	
}

/*
*Funcion para crear una nueva cuenta
*Primero se pide el nombre, que se habra psado por refrencia , y la contraseña
*si el contador de los usuarios esta a 0 (se ha creado el fichero , ya que no existia)
*Se guarda en usuarios y correos lo que haya en el gestor correos y usuarios
*Se busca el usuario si ya existe devuleve false e informa al usuario
*Si no carga al usuario el id, y la contraseña y llama la funcion de añadir para añadir ese usuario a la lista
*Lo vuleve a buscar para cojer la posicion y ponersela al gestor
*/

bool crearCuenta(tGestor &gestor, string& id)
{

	bool crear=false;
	tUsuario usuario;
	string contrasenia, dominio= gestor.dominio, dominio1= gestor.dominio;
	int posicion;
	
	cout << "Introduzca su identificador correo: ";
	cin >> id;
	cout << "Introduzca su contrasenia: ";
	cin >> contrasenia;
	
	id = id +"@"+gestor.dominio ;
	
	if (gestor.usuarios.contador==0)
	{
		usuario.nombre = id;
		usuario.contraseña= contrasenia;
		inicializar( usuario,  id,  contrasenia);
		gestor.posicion = 0;
		crear = true;	
	}
	
		
	if (buscarUsuario( gestor.usuarios, id,  posicion))
	{
		cout << "El usuario introducido ya existe en " << gestor.dominio << endl;
		crear = false;
	}

	else 
	{
			
		usuario.nombre = id;
		usuario.contraseña= contrasenia;
		inicializar( usuario,  id,  contrasenia);

		if (aniadir( gestor.usuarios, usuario))
		{
				
			buscarUsuario( gestor.usuarios, id,  posicion);
			gestor.posicion = posicion;
			crear = true;		
		}
	}
	
	return crear;
}

/*
*Se inicia la sesion de un usuario que ya este en el archivo txt
*El usuario debera introducir el id y la contraseña
*Si el usuario esta en la lista validara la contraseña y pondra la posicion del usuario con la funcion de buscar usuario.
*En caso de que falle o el id o la contraseña dara error.
*/

bool iniciarSesion(tGestor &gestor, string& id)
{

	bool ok = false;
	string contrasenia;
	tUsuario usuario;
	string  dominio= "fdimail.com";
	int posicion;
	
	cout << "Introduzca su identificador correo: ";
	cin >> id;
	cout << "Introduzca su contrasenia : ";
	cin >> contrasenia;

	id = id +"@"+gestor.dominio ;
		
	if (!buscarUsuario( gestor.usuarios, id,  posicion))
	{
		gestor.posicion = -1;
		ok=false;
	}
	else 
	{
		usuario.contraseña = gestor.usuarios.ficha2[posicion]->contraseña ;
		usuario.entrada = gestor.usuarios.ficha2[posicion]->entrada ;
		usuario.salida = gestor.usuarios.ficha2[posicion]->salida ;
		usuario.nombre = gestor.usuarios.ficha2[posicion]->nombre ;
			
		if (validarContrasenia(usuario,contrasenia))
		{
			buscarUsuario( gestor.usuarios, id,  posicion);
			gestor.posicion = posicion;
			ok = true;
		}

		else 
		{
			gestor.posicion = -1;
			ok =false;
		}

	}
		
	return ok;
}

/*
*Mostrar la bandeja de entrada o de salida
*Se pasa por refrencia un bool de entrada , que si es false, es bandeja de entrada , true bandeja de salida
*En cuanto a los correos se muestran de abajo a arriba por lo que el bucle empieza desde el final
*Tambien se llamara la funcion de obtener cabecera para obterner la informacion de la bandeja de los mensajes
*Hemos separado la bandeja de entrada y salida con el booleano,lo unico que cambia a la hora de mostrar las bandejas es cambiar entrada por salida del gestor
*Para cada bandeja se llamara a la funcion de mensajesEntrada para mostrar los mensajes de entrada y los de salida en mensajesSalida
*/

int menuBandeja(tGestor &gestor, bool entrada, string& nombre)
{

	system ("cls");
	tCorreo correo;
	string dominio= gestor.dominio;
	string id;
	int opcion;

	cout << "Correo de " << gestor.usuarios.ficha2[gestor.posicion]->nombre << endl;

	if (entrada == false)// si es bandeja de entrada
	{
		cout << "----------------------------Bandeja de entrada----------------------------" << endl;
	}
	else //si es bandeja de salida
	{
		cout << "----------------------------Bandeja de salida----------------------------" << endl;
	}

	cout << "--------------------------------------------------------------------------" << endl;
	cout << "L N    EMISOR                ASUNTO                                FECHA " << endl; 
	cout << endl;
	cout << "--------------------------------------------------------------------------" << endl;

	if (entrada == false)
	{
		mensajesEntrada(gestor);
			
	}

	else 
	{
		mensajesSalida(gestor);
	}

	
	cout << "--------------------------------------------------------------------------" << endl;
	cout << "Elija una opcion: " << endl;
	cout << " 1- Leer correo " << endl;
	cout << " 2- Enviar correo "<< endl;
	cout << " 3- Borrar correo " << endl;

	if (entrada == false)
	{
		cout << " 4- Ver bandeja de salida " << endl;
	}
		
	else 
	{
		cout << " 4- Ver bandeja de entrada " << endl;
	}

	cout << " 5- Lectura rapida de correos sin leer " << endl;
	cout << " 0- Cerrar sesion " << endl;

	cin >> opcion;

	while(opcion < 0|| opcion > 5)
	{
		cout << "Opcion no valida. Introduce otra opcion " << endl;
		cin >> opcion;
	}

	return opcion;
}

/*
*En esta funcion se muestran los mensajes de entrada de un usuario al reves
*Recorre cada posicion empezando por el final y en cada posicion buscara buscara el correo en el gestor correos para mostrar la cabecera
*/

void mensajesEntrada(const tGestor &gestor)
{

	int numero=1,pos;
	string id;
	tCorreo correo;

	for (int i =gestor.usuarios.ficha2[gestor.posicion]->entrada.contador-1; i >=0; i--)
	{
		if (gestor.usuarios.ficha2[gestor.posicion]->entrada.registro[i].leido == false)
		{
			cout << "* " ;
		}
		else 
		{
			cout << "  ";
		}

		cout << numero << " - ";
		id = gestor.usuarios.ficha2[gestor.posicion]->entrada.registro[i].id;	
		buscar(gestor.correos, id, pos);
		correo = gestor.correos.ficha[pos];
		cout << obtenerCabecera(correo) << endl;
		numero++;
	}

}

/*
*En la de salida actua de la misma manera que la funcion de mensajesEntrada, pero en la salida
*/

void mensajesSalida(const tGestor &gestor)
{

	int numero=1,pos;
	string id;
	tCorreo correo;
	
	for (int i =gestor.usuarios.ficha2[gestor.posicion]->salida.contador-1; i >=0; i--)
	{
		if (gestor.usuarios.ficha2[gestor.posicion]->salida.registro[i].leido == false)
		{
			cout << "* " ;
		}

		else 
		{
			cout << "  ";
		}

		cout << numero << " - ";
		id = gestor.usuarios.ficha2[gestor.posicion]->salida.registro[i].id;
		buscar(gestor.correos, id, pos);
		correo = gestor.correos.ficha[pos];
		cout << obtenerCabecera(correo) << endl;
		numero++;
	}

}

/*
*A partir de la opcion que haya elegido llamara a diferentes funciones (explicado en cada opcion)
*/

void ejecutarMenuBandeja(tGestor &gestor,int opcion, bool &entrada)
{
	tCorreo correo;
	tListaRegCorreo listaReg;
	string nombre;
	
	while (opcion !=0)
	{
		if (opcion == 1 )
		{
			leerCorreo( gestor,  listaReg, entrada);
			system ("cls");
		}
		else if (opcion == 2 )
		{
			system ("cls");
			string emisor = gestor.usuarios.ficha2[gestor.posicion]->nombre;
			correoNuevo(correo, emisor);
			enviarCorreo( gestor, correo);
			system ("cls");
		}
		else if (opcion == 3 )
		{
			borrarCorreo(gestor,  listaReg,  entrada);
			system ("cls");
		}
		else if (opcion ==4 )
		{
			if (entrada == true)
			{
				entrada = !entrada;
			}
			else 
			{
				entrada = !entrada;
			}
		}
		else if (opcion == 5)
		{
			system ("cls");
			lecturaRapida( gestor,  listaReg, entrada);
			system ("cls");
		}

		opcion =menuBandeja(gestor, entrada,  nombre);
	}

	if (opcion ==0)
	{
		cout << "Cerrando la sesion... Hasta pronto !!" << endl;
		system ("cls");
	}
			
}
/*
*Funcion de leer correo , se ejecutara cuando la opcion sea 1
*Pedira al usuario el numero a leer , y como la lista esta al reves (de orden de prodecencia) se ira recorriendo la lista de abajo a arriba hasta llegar a esa posicion
*Se pasar a correo ese correo de la lista de correos y se mostrara por pantalla 
*Se pregunta al usuario la opcion de contestar o volver bandeja 
*En caso de contestar se llamara a la funcion de constestar del modulo de correo
*Volvera a la bandeja 
*/

void leerCorreo(tGestor& gestor, tListaRegCorreo& listaReg, bool entrada)
{
	tCorreo correo;
	bool leer = true;
	int numero;
	string id, aux;
	string nombre;

	cout << "Numero del correo a leer: ";
	cin >> numero;

	if (entrada == false)
	{
		leerMensajeEntrada ( gestor,numero);

	}

	else 
	{
		leerMensajeSalida( gestor,numero);
	}

}

/*
*Si el contador es 0 se avisa al usuario de que no hay mensajes
*Tambien se vigila el numero de correo a leer, se informara si eso ocurre
*Si no ocurre esto dicho anteriormente se leera el correo buscando el id, en la lista de correos y se mostrara al usuario las dos opciones
*/

void leerMensajeEntrada ( tGestor &gestor,int &numero)
{

	bool leer=true;
	string id;
	int pos,opcion;
	tCorreo correo;

	if (gestor.usuarios.ficha2[gestor.posicion]->entrada.contador==0)
	{
		cout << "Ya has leido todos tus mensajes !!. Espera a que te manden mas " << endl;
	}
	if (numero > gestor.usuarios.ficha2[gestor.posicion]->entrada.contador || numero <= 0)
	{
		cout << "Error , has seleccionado un numero de correo no valido " << endl;
		leer = false;
		system("pause");
	}

	system ("cls");

	if (leer)
	{
		int posicion =gestor.usuarios.ficha2[gestor.posicion]->entrada.contador-numero;

		gestor.usuarios.ficha2[gestor.posicion]->entrada.registro[posicion].leido= true;
		id = gestor.usuarios.ficha2[gestor.posicion]->entrada.registro[posicion].id;
		buscar(gestor.correos, id, pos);
		correo = gestor.correos.ficha[pos];

		cout << aCadena(correo) << endl;
		cout << endl;
		cout << "--------------------------------------------------------------------------" << endl;

		cout << "Elija una opcion: "<< endl;
		cout << "  1- Contestar correo " << endl;
		cout << "  0- Volver a la bandeja " << endl;
		cout << "--------------------------------------------------------------------------" << endl;

		cout << "Introduzca una opcion: ";
		cin >> opcion;

		while (opcion < 0 || opcion > 1)
		{
			cout << "Opcion no valida. Elija otra opcion de nuevo " << endl;
			cin >> opcion;
		}

		if (opcion ==1 )//llamara al correo contestacion 
		{
			correoConstestacion(gestor,pos);
		}

		else 
		{
			cout << "Volviendo a la bandeja de entrada" << endl;
			system ("cls");
		}
	}
}

/*
*Esta funcion se ejecutara cuando se introduzca la opcion 1 de la funcion anterior
*Llamara a la funcion de contestar correo
*Si supera la capacidad se llamara a redimensionar
*Tambien se tendra que añadir el id en la salida y entrada de los respectivos emisor y destinatario, vigilando que no sobrepase la capacidad maxima de los registros
*/

void correoConstestacion(tGestor &gestor, int &pos)
{
	string id;
	int posicion;
	system ("cls");
	string emisor = gestor.usuarios.ficha2[gestor.posicion]->nombre;

	tCorreo correo;
	tCorreo correoOriginal;
	correoOriginal =  gestor.correos.ficha[pos];
	correoContestacion(correoOriginal, correo, emisor);

	if (gestor.usuarios.ficha2[gestor.posicion]->salida.contador==gestor.usuarios.ficha2[gestor.posicion]->salida.capacidad)
	{
		redimensionar (gestor.usuarios.ficha2[gestor.posicion]->salida, MAX_REG);
	}

	gestor.usuarios.ficha2[gestor.posicion]->salida.registro[gestor.usuarios.ficha2[gestor.posicion]->salida.contador].id= correo.id;
	gestor.usuarios.ficha2[gestor.posicion]->salida.registro[gestor.usuarios.ficha2[gestor.posicion]->salida.contador].leido= true;
	gestor.usuarios.ficha2[gestor.posicion]->salida.contador++;
		
	id = correo.destinatario;
	buscarUsuario( gestor.usuarios, id,  posicion);

	if (gestor.usuarios.ficha2[gestor.posicion]->entrada.contador==gestor.usuarios.ficha2[gestor.posicion]->entrada.capacidad)
	{
		redimensionar (gestor.usuarios.ficha2[gestor.posicion]->entrada, MAX_REG);
	}
					
	gestor.usuarios.ficha2[posicion]->entrada.registro[gestor.usuarios.ficha2[posicion]->entrada.contador].id= correo.id;
	gestor.usuarios.ficha2[posicion]->entrada.registro[gestor.usuarios.ficha2[posicion]->entrada.contador].leido = false;
	gestor.usuarios.ficha2[posicion]->entrada.contador++;

	insertar(gestor.correos,correo);

}

/*
*En esta funcion se implementa igual que la de leerMensajes de entrada pero cambiando la entrada por salida 
*Pero ya no se mostrara las opciones debido a aque es salida
*/

void leerMensajeSalida( tGestor &gestor,int &numero)
{
	bool leer=true;
	string id;
	int pos;
	tCorreo correo;

	if (gestor.usuarios.ficha2[gestor.posicion]->salida.contador==0)
	{
		cout << "No tienes ningun mensaje que hayas enviado que puedas leer . " << endl;
		cout << "Puedes enviar un correo nuevo para leerlo " << endl;
	}

	if (numero > gestor.usuarios.ficha2[gestor.posicion]->salida.contador || numero <= 0)
	{
		cout << "Error , has seleccionado un numero de correo no valido " << endl;
		system ("pause");
		leer = false;
	}
	if (leer)
	{
		system ("cls");
		int posicion =gestor.usuarios.ficha2[gestor.posicion]->salida.contador-numero;
		gestor.usuarios.ficha2[gestor.posicion]->salida.registro[posicion].leido= true;
		id = gestor.usuarios.ficha2[gestor.posicion]->salida.registro[posicion].id;
		buscar(gestor.correos, id, pos);
		correo = gestor.correos.ficha[pos];
		cout << aCadena(correo) << endl;
		cout << endl;
		cout << "--------------------------------------------------------------------------" << endl;
		cout << "Volviendo a la bandeja de salida " << endl;
		system ("pause");
		system ("cls");
	}

}

/*
*Se ejecuta al pulsar la opcion 2 
*Se busca el destinatario.
*En caso de haber llegado al limite de capacidad se redimensionara la capacidad de correos, y de los registros
*Se añade el registro de salida y entrada en el usuario de destinatario y emisor respectivamente y en el gestor correos
*/

void enviarCorreo(tGestor& gestor, const tCorreo &correo)
{
	
	int posicion;
	bool  buscar = false;
	string id = correo.destinatario;

	if (buscarUsuario( gestor.usuarios, id,  posicion))
	{
		buscar = true;
	}

	else 
	{
		cout << "Error. El destinatario introducido no esta registrado en fdimail.com" << endl;
		cout << "Volviendo a la bandeja de entrada " << endl;
		system ("pause");
	}

	if (gestor.correos.contador >= gestor.correos.capacidad)
	{
		redimensionar( gestor.correos, MAX_CORREOS);
			
	}

	if (gestor.usuarios.ficha2[gestor.posicion]->salida.contador >= gestor.usuarios.ficha2[gestor.posicion]->salida.capacidad)
	{
		redimensionar (gestor.usuarios.ficha2[gestor.posicion]->salida, MAX_REG);	
	}
		
	if (gestor.usuarios.ficha2[posicion]->entrada.contador >=gestor.usuarios.ficha2[posicion]->entrada.capacidad)
	{
		redimensionar (gestor.usuarios.ficha2[posicion]->entrada, MAX_REG);
			
	}
		
	if (buscar == true)
	{
		insertar(gestor.correos,correo);
		
		gestor.usuarios.ficha2[gestor.posicion]->salida.registro[gestor.usuarios.ficha2[gestor.posicion]->salida.contador].id = correo.id ;
		gestor.usuarios.ficha2[gestor.posicion]->salida.registro[gestor.usuarios.ficha2[gestor.posicion]->salida.contador].leido = true;
		gestor.usuarios.ficha2[gestor.posicion]->salida.contador++;
		
		gestor.usuarios.ficha2[posicion]->entrada.registro[gestor.usuarios.ficha2[posicion]->entrada.contador].id=correo.id;
		gestor.usuarios.ficha2[posicion]->entrada.registro[gestor.usuarios.ficha2[posicion]->entrada.contador].leido=false;
		gestor.usuarios.ficha2[posicion]->entrada.contador++;
		
	}

}

/*
*Esta funcion se ejecutara cuando se pulse la opcion 3 del menu
*Se preguntara al usuario que correo quiere borrar, y se ira recorriendo al reves (al estar ordenado)y se eliminara del gestor de ese usuario
*Se comprobara que la lista de registro del usuario que etsa el id y se elimara, en la posicion que la que se haya encontrado.
*Dependiendo si es entrada o salida llamara a dicha funcion 
*/

void borrarCorreo(tGestor& gestor, tListaRegCorreo& listaReg, bool entrada)
{
	int numero;
	string id;
	bool borrar= true;
	
	cout << "Numero de correo que desea borrar: " ;
	cin >> numero;

	if (entrada == false)//bandeja de entrada
	{
		if (gestor.usuarios.ficha2[gestor.posicion]->entrada.contador==0)
		{
			cout << "Ya has borrado todos los correos de la bandeja de entrada!!" << endl;
			cout << "Espera a que te manden mas correos para poder borrarlos " << endl;
			cout << "Volviendo a la bandeja de entrada " << endl;
			borrar = false;
			system ("pause");
		}
		else
		{
			if (numero > gestor.usuarios.ficha2[gestor.posicion]->entrada.contador || numero <= 0)
			{
				cout << "Error , has seleccionado un numero de correo no valido " << endl;
				borrar = false;
				cout << "Volviendo a la bandeja  " << endl;
				system("pause");
			}
		}
	}
		
	else// bandeja de salida
	{
		if (gestor.usuarios.ficha2[gestor.posicion]->salida.contador==0)
		{
			cout << "Ya has borrado todos los correos de la bandeja de salida!!" << endl;
			cout << "Puedes mandar mas correos y borrarlos " << endl;
			cout << "Volviendo a la bandeja de salida" << endl;
			borrar = false;
			system ("pause");
		}
		else
		{
			if (numero > gestor.usuarios.ficha2[gestor.posicion]->salida.contador || numero <= 0)
			{
				cout << "Error , has seleccionado un numero de correo no valido " << endl;
				borrar = false;
				cout << "Volviendo a la bandeja  " << endl;
				system("pause");
			}
		}
	}

	if (borrar)
	{
		if (entrada == false)
		{
			borrarMensajeEntrada(gestor, numero);

		}
	
		else
		{
			borrarMensajeSalida(gestor, numero);
		}

	}
	
}

/*
*Llamara a dicha funcion para borrar un corrreo de la lista de correos del gestor si es la entrada
*Al estar al reves los correos segun se ven en la bandeja se hara al reves
*/

void borrarMensajeEntrada(tGestor &gestor, int &numero)
{
	string id;
	int i =gestor.usuarios.ficha2[gestor.posicion]->entrada.contador,posicion,cont=0; 

	while (cont < numero)
	{
		i--;
		cont++;
	}

	posicion = i;
	id = gestor.usuarios.ficha2[gestor.posicion]->entrada.registro[posicion].id;

	if (posicion !=-1)
	{
						
		for (int i = posicion; i < gestor.usuarios.ficha2[gestor.posicion]->entrada.contador  ; i++) 
		{
			gestor.usuarios.ficha2[gestor.posicion]->entrada.registro[i] = gestor.usuarios.ficha2[gestor.posicion]->entrada.registro[i + 1];
		}	

	gestor.usuarios.ficha2[gestor.posicion]->entrada.contador--;

	}
	else 
	{
		cout << "No se ha encontrado el correo para borrar " << endl;
	}

}

/*
*Se implemeta igual que en la bandeja de entrada pero en la salida
*/

void borrarMensajeSalida(tGestor &gestor, int &numero)
{
	string id;
	int i =gestor.usuarios.ficha2[gestor.posicion]->salida.contador;
	int posicion, cont=0; 

	while (cont < numero)
	{
		i--;
		cont++;
	}

	posicion = i;
	id = gestor.usuarios.ficha2[gestor.posicion]->salida.registro[posicion].id;

	if (posicion !=-1)
	{
			
		for (int i = posicion; i < gestor.usuarios.ficha2[gestor.posicion]->salida.contador  ; i++) 
		{
			gestor.usuarios.ficha2[gestor.posicion]->salida.registro[i] = gestor.usuarios.ficha2[gestor.posicion]->salida.registro[i + 1];
		}

		gestor.usuarios.ficha2[gestor.posicion]->salida.contador--;
	
	}

	else 
	{
		cout << "No se ha encontrado el correo para borrar " << endl;
	}

}

/*
*Mostrara todos los mensajes no leidos de la bandeja de entrada, si esta en la bandeja de salida se le hara saber al usuario que esta en dicha bandeja y al haberlos enviado el estaran ya leidos
*Siempre que el contador de la bandeja de entrada sea mayor que 0 y que haya como minimo 1 no leido se podran mostrar , en caso contrario volvera a bandeja de entrada
*Recorrera toda la lista de entrada y guardara en una lista auxiliar aquellos correos no leidos (los que esten a false)
*Tambien se mira las tres primeras letras si son "Re:", se eliman de la lista auxiliar
*Despues de haberlo recorrido y guardado en la lista auxiliar , se prdenan por asunto y fecha , llmando a la funcion de ordenarAF.
*Se muestra al usuario
*Se elimina la lista auxiliar
*/

void lecturaRapida(tGestor& gestor, tListaRegCorreo& listaReg,  bool entrada)
{
	string id;
	tCorreo correo;
	tListaCorreos aux;
	int pos;
	bool seguir = true;
	
	if (seguir)
	{
		if (entrada == false)
		{
			inicializar(aux);
			aux.ficha = new tCorreo[gestor.correos.contador];
			if (gestor.usuarios.ficha2[gestor.posicion]->entrada.contador==0)
			{
				cout << "Ya has leido todos tus mensajes espera a que te manden mas !!" << endl;
				seguir = false;
				cout << "Volviendo a la bandeja de entrada " << endl;
			}
			else
			{
				for (int i =0; i < gestor.usuarios.ficha2[gestor.posicion]->entrada.contador;i++)
				{
					if (gestor.usuarios.ficha2[gestor.posicion]->entrada.registro[i].leido== false)
					{
						gestor.usuarios.ficha2[gestor.posicion]->entrada.registro[i].leido= true; 
						id = gestor.usuarios.ficha2[gestor.posicion]->entrada.registro[i].id;
						buscar(gestor.correos, id, pos);
						aux.ficha[aux.contador]= gestor.correos.ficha[pos];
						aux.contador++;
					}
				}
				//Para quitar el Re:
				for (int j =0;j < aux.contador;j++)
				{
					string  palabra = "";
					int posi;
					char letra;	
					posi = 0;

					while (posi < 3) 
					{
						letra = aux.ficha[j].asunto.at(posi);
						palabra = palabra+letra; 
						posi++;
					}

					if (palabra=="Re:")// se comprueba esta palabra
					{
						aux.ficha[j].asunto.erase(0,3);// se elimina del asunto
					}
				}
	
				ordenar_AF(aux);

				for (int i =0; i < aux.contador; i++)
				{
					correo = aux.ficha[i];
					cout << aCadena(correo)<< endl;
					cout << "--------------------------------------------------------------------------" << endl;
					cout << "Pulsa una tecla para continuar con el siguiente mensaje " << endl;
					system ("pause");
					cout << "--------------------------------------------------------------------------" << endl;
				}
			}

			eliminar (aux);	
		}
			else// en caso de estar en la bandeja de salida 
		{
			cout << "Esta usted en la bandeja de salida, por lo que no hay correos que no haya leido." << endl;
		}

	system ("pause");

	}

}

/*
*Funcion de la parte opcional
*Cuando tanto el emisor, como el destinatario hayan borrado el mensaje se borrara de la lista de correos
*Se hace un recorrido primero en la bandeja de entrada de los usuarios y se busca el id del primero correo que haya en la lista de correos
*Si lo encuentra devulve false y pasa al siguiente correo de la lista de correos
*En caso de no encontrar el correo querra decir que el usuario ya lo ha borrado de su bandeja de entrada ,por lo que se mirara en la bandeja de salida si esta el id(mismo proceso que antes)
*Cuando no se encuentre el correo el cont sumara +1 si no llega a 0 quiere decir que no lo ha encontrado ni en la bandeja de entrada ni salida porque ya han borrado el mensaje ambos usuarios 
*Si llega el cont =0 , se borra de la lista de correos , y se apaga el gestor para guardar los cambios en el txt
*/

void borrar (tGestor &gestor)
{
	string nombre;
	bool borrar = false;
	int cont=0;

	for (int i =0; i< gestor.correos.contador; i++)
	{
		nombre = gestor.correos.ficha[i].id;
		for(int j =0; j < gestor.usuarios.contador ;j++)
		{
			int w =0;
			while (w < gestor.usuarios.ficha2[j]->entrada.contador && !borrar )
			{
				if (gestor.usuarios.ficha2[j]->entrada.registro[w].id== nombre )
				{
					cont++;// si lo ha encontrado el contador aumenta
					borrar= true;
				}

				w++;
			}
			
		}
		for(int t =0; t < gestor.usuarios.contador;t++ )
		{
			int q =0;
			borrar = false;

			while (q < gestor.usuarios.ficha2[t]->salida.contador && !borrar)
			{
				if (gestor.usuarios.ficha2[t]->salida.registro[q].id== nombre )
				{
					cont++;
					borrar= true;
				}
				q++;
			}
			
		}
		if (cont== 0 )
		{
			for (int e=i; e < gestor.correos.contador  ; e++) 
			{
				gestor.correos.ficha[e] = gestor.correos.ficha[e + 1];
			}

		gestor.correos.contador--;

		}

	cont=0;
	}

	apagar(gestor);
}




