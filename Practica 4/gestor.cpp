/*
*Nota:El modulo registro no lo hemos usado practicamente para nada (excepto para cargar el txt de usuarios), debido a que nos resultaba un poco lioso.
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

	tListaCorreos correos;
	tListaUsuarios usuarios;

	gestor.dominio= dominio;

	inicializar(correos);
	inicializar(usuarios);

	gestor.correos = correos;
	gestor.usuarios= usuarios;

	gestor.posicion = -1;

}
/*
*Carga la lista de correos y usuarios llamando a dichas funciones y las guarda en el gestor, si todo ha ido bien devulve true, en caso contrario false
*/

bool arrancar(tGestor& gestor,  string dominio)
{

	tListaCorreos correos;
	tListaUsuarios usuarios;
	bool ok = false;

	inicializar(gestor,  dominio);//llama a la funcion enla que pondra el gestor a 0

		//carga los correos y los usuarios
		if (cargar(correos,  dominio))
		{
		
			if (cargar(usuarios,  dominio))
			{

				ok = true;
				gestor.correos= correos;
				gestor.usuarios= usuarios;
			}
		}

	return ok;
	
}

/*
*Guarda la lista de correos y usuarios del gestor (ya que han sido modificados durante la aplicacion) a los correos y usuarios.
*Llama a las funciones de guardado de dichos modulos y guardan los cambios en el txt
*/

void apagar(const tGestor &gestor)
{

	tListaCorreos correos;
	tListaUsuarios usuarios;
	string dominio1 = gestor.dominio;

	usuarios = gestor.usuarios;
	correos = gestor.correos;

	guardar(correos, dominio1);
	guardar( usuarios,  dominio1);

}

/*
*Funcion para crear una nueva cuenta
*Primero se pide el nombre, que se habra psado por refrencia , y la contraseña
*Se guarda en usuarios y correos lo que haya en el gestor correos y usuarios
*Se busca el usuario si ya existe devuleve false e iforma al usuario
*Si no carga al usuario el id, y la contraseña y llama la funcion de añadir para añadir ese usuario a la lista
*Lo vuleve a buscar para cojer la posicion y ponersela al gestor
*Guarda la lista de usuarios en txt , con la funcion guardar usuarios y arranca de nuevo el gestor para cargar lo que habia en el archivo txt de usuarios que hemos escrito al pulsar esta opcion
*/

bool crearCuenta(tGestor &gestor, string& id)
{

	bool crear=false;
	tListaUsuarios usuarios;
	tListaCorreos correos;
	tUsuario usuario;
	string contrasenia, dominio= gestor.dominio, dominio1= gestor.dominio;
	int posicion;
	
	cout << "Introduzca su identificador correo: ";
	cin >> id;
	cout << "Introduzca su contrasenia: ";
	cin >> contrasenia;

	//se guarda en usuarios lo que hay en el gestor
	usuarios = gestor.usuarios;
	correos = gestor.correos;
	
	id = id +"@"+gestor.dominio ;
	
		if (gestor.usuarios.contador==0)// si el contador de los usuarios esta a 0 (se ha creado el fichero , ya que no existia)
		{
			usuario.nombre = id;
			usuario.contraseña= contrasenia;
			inicializar( usuario,  id,  contrasenia);//para incializar la lista de entrada y salida a 0
			gestor.posicion = 0;
			crear = true;	
		}
	
		//si encunetra al usuario , ya estaba por lo que devulve false
		if (buscarUsuario( usuarios, id,  posicion))
		{
			cout << "El usuario introducido ya existe en " << gestor.dominio << endl;
			crear = false;
		}

		else 
		{
			//copia todos los campos de un usuario para añadirlo en el siguinte paso
			usuario.nombre = id;
			usuario.contraseña= contrasenia;
			inicializar( usuario,  id,  contrasenia);

			if (aniadir( usuarios, usuario))
			{
				//busca el usuario para poner la posicion en el gestor
				buscarUsuario( usuarios, id,  posicion);
				gestor.posicion = posicion;
				crear = true;
				guardar(usuarios,  dominio1);//guarda en le txt la nueva lista de usuarios
				gestor.usuarios = usuarios;
			}

		}
	
	return crear;
}

/*
*Se inicia la sesion de un usuario que ya este en el archivo txt
*Carga los usuarios del gestor usuarios, para buscar el usuario
*El usuario debera introducir el id y la contraseña
*Si el usuario esta en la lista validara la contraseña y pondra la posicion del usuario con la funcion de buscar usuario.
*/

bool iniciarSesion(tGestor &gestor, string& id)
{

	bool ok = false;
	string contrasenia;
	tUsuario usuario;
	tListaUsuarios usuarios;
	string  dominio= "fdimail.com";
	int posicion;
	
	usuarios = gestor.usuarios;

	cout << "Introduzca su identificador correo: ";
	cin >> id;
	cout << "Introduzca su contrasenia : ";
	cin >> contrasenia;

	id = id +"@"+gestor.dominio ;
		
		//si no esta devulve false
		if (!buscarUsuario( usuarios, id,  posicion))
		{
			gestor.posicion = -1;
			ok=false;
		}

		// si esta se pasa a usuario el usuario en la posicion en la que haya inciado la sesion el usuario
		else 
		{
			usuario= usuarios.ficha2[posicion];

			if (validarContrasenia(usuario,contrasenia))
			{
				buscarUsuario( usuarios, id,  posicion);
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
*/

int menuBandeja(tGestor &gestor, bool entrada, string& nombre)
{

	system ("cls");
	tCorreo correo;
	string dominio= gestor.dominio;
	tListaCorreos correos;
	string id;
	int pos, numero=1, opcion;// el numero es una variable para poner el numero del correo

	cout << "Correo de " << gestor.usuarios.ficha2[gestor.posicion].nombre << endl;//muestra el nombre que lo ha inciado 

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
			
			for (int i =gestor.usuarios.ficha2[gestor.posicion].entrada.contador-1; i >=0; i--)//se muestran al reves
			{
				if (gestor.usuarios.ficha2[gestor.posicion].entrada.ficha1[i].leido == false)
				{
					cout << "* " ;
				}
				else 
				{
					cout << "  ";
				}

				cout << numero << " - ";
				id = gestor.usuarios.ficha2[gestor.posicion].entrada.ficha1[i].id;
				cargar(correos, dominio);
				buscar(correos, id, pos);// busca el id de un correos para cojer la posicion y con ella se le añade a un correo y obtener la cabecera
				correo = correos.ficha[pos];
				cout << obtenerCabecera(correo) << endl;
				numero++;
			}
		}
		

		else //para la bandeja de salida lo mismo que la entrada
		{
			
			for (int i =gestor.usuarios.ficha2[gestor.posicion].salida.contador-1; i >=0; i--)
			{
				if (gestor.usuarios.ficha2[gestor.posicion].salida.ficha1[i].leido == false)
				{
					cout << "* " ;
				}

				else 
				{
					cout << "  ";
				}
				cout << numero << " - ";
				id = gestor.usuarios.ficha2[gestor.posicion].salida.ficha1[i].id;
				cargar(correos, dominio);
				buscar(correos, id, pos);
				correo = correos.ficha[pos];
				cout << obtenerCabecera(correo) << endl;
				numero++;
		
			}
		
		}
	// para cualquier bandeja
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
*A partir de la opcion que haya elegido llamara a diferentes funciones (explicado en cada opcion)
*/

void ejecutarMenuBandeja(tGestor &gestor,int opcion, bool &entrada)
{
	tCorreo correo;
	tListaRegCorreo listaReg;
	string nombre;
	
		while (opcion !=0)
		{

			if (opcion == 1 )//lee el correo llamando a la funcion de leer correo
			{
				leerCorreo( gestor,  listaReg, entrada);
				system ("cls");
			}
			else if (opcion == 2 )//al enviar un correo , primero pone en el emisor el usuario que este en la sesion, hara un corre nuevo y lo enviara ,llama la funcion de enviar
			{
				system ("cls");
				string emisor = gestor.usuarios.ficha2[gestor.posicion].nombre;
				correoNuevo(correo, emisor);
				enviarCorreo( gestor, correo);
				system ("cls");
			}
			else if (opcion == 3 )//borra el correo solo de este usuario , llmando a la funcion de borrar correo
			{
				borrarCorreo(gestor,  listaReg,  entrada);
				system ("cls");
			}
			else if (opcion ==4 )//cambia de bandeja
			{
				if (entrada == true)//si esta en la de salida , cambia a la entrada , cambiando el bool , y viceversa
				{
					entrada = false;
				}
				else 
				{
					entrada = true;
				}
			}
			else if (opcion == 5)//la lectura rapida, llamara a la funcion de lectura rapida
			{
				system ("cls");
				lecturaRapida( gestor,  listaReg, entrada);
				system ("cls");
			}

		opcion =menuBandeja(gestor, entrada,  nombre);// volvera a la bandeja y pedira de nuevo otra opcion
		}

		if (opcion ==0)//no terminara hasta que no sea 0
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
	tListaCorreos correos;
	tListaUsuarios usuarios;
	int numero, pos, opcion;
	string id, aux;
	string nombre;

	cout << "Numero del correo a leer: ";
	cin >> numero;

	if (entrada == false)// si es bandeja de entrada
	{
		if (gestor.usuarios.ficha2[gestor.posicion].entrada.contador==0)// en caso de que la lista de correos sea 0
		{
			cout << "Ya has leido todos tus mensajes !!. Espera a que te manden mas " << endl;
		}
		if (numero > gestor.usuarios.ficha2[gestor.posicion].entrada.contador || numero <= 0)
		{
			cout << "Error , has seleccionado un numero de correo no valido " << endl;
			leer = false;
			system("pause");
		}

		system ("cls");

		if (leer)// bool creado para cuando se pueda leer algun correo
		{
			int posicion =gestor.usuarios.ficha2[gestor.posicion].entrada.contador-numero;

			gestor.usuarios.ficha2[gestor.posicion].entrada.ficha1[posicion].leido= true;// se pone a true
			id = gestor.usuarios.ficha2[gestor.posicion].entrada.ficha1[posicion].id;
			correos = gestor.correos;//s eguarda en correo los datos de la lista en esa posicion
			buscar(correos, id, pos);
			correo = gestor.correos.ficha[pos];

			cout << aCadena(correo) << endl;// se escribe la cabecera
			cout << endl;
			cout << "--------------------------------------------------------------------------" << endl;

			cout << "Elija una opcion: "<< endl;//opcion de contestar
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
					system ("cls");
					string emisor = gestor.usuarios.ficha2[gestor.posicion].nombre;
					tCorreo correo;
					tCorreo correoOriginal;
					correoOriginal =  gestor.correos.ficha[pos];
					correoContestacion(correoOriginal, correo, emisor);

					//en la salida de destinatario se guarda
					gestor.usuarios.ficha2[gestor.posicion].salida.ficha1[gestor.usuarios.ficha2[gestor.posicion].salida.contador].id= correo.id;
					gestor.usuarios.ficha2[gestor.posicion].salida.ficha1[gestor.usuarios.ficha2[gestor.posicion].salida.contador].leido= true;
					gestor.usuarios.ficha2[gestor.posicion].salida.contador++;
		
					id = correo.destinatario;
					usuarios= gestor.usuarios;
					buscarUsuario( usuarios, id,  posicion);

					//y en la de entrada del emisor
					gestor.usuarios.ficha2[posicion].entrada.ficha1[gestor.usuarios.ficha2[posicion].entrada.contador].id= correo.id;
					gestor.usuarios.ficha2[posicion].entrada.ficha1[gestor.usuarios.ficha2[posicion].entrada.contador].leido = false;
					gestor.usuarios.ficha2[posicion].entrada.contador++;

					insertar(correos,correo);// se inserta en la lista de correos
					gestor.correos= correos;
					apagar(gestor);// se apaga para guardar todo en el txt
				}
		else 
		{
			cout << "Volviendo a la bandeja de entrada" << endl;
			system ("cls");
		}
		}
	}//fin de la bandeja de entrada

	else // la bandeja de salida es igual que la de entrada pero cambiando entrada por salida 
	{
		if (gestor.usuarios.ficha2[gestor.posicion].salida.contador==0)
		{
			cout << "No tienes ningun mensaje que hayas enviado que puedas leer . " << endl;
			cout << "Puedes enviar un correo nuevo para leerlo " << endl;
		}
		if (numero > gestor.usuarios.ficha2[gestor.posicion].salida.contador || numero <= 0)
		{
			cout << "Error , has seleccionado un numero de correo no valido " << endl;
			system ("pause");
			leer = false;
		}

		if (leer)
		{
			system ("cls");
			int posicion =gestor.usuarios.ficha2[gestor.posicion].salida.contador-numero;

			gestor.usuarios.ficha2[gestor.posicion].salida.ficha1[posicion].leido= true;
			id = gestor.usuarios.ficha2[gestor.posicion].salida.ficha1[posicion].id;
			correos = gestor.correos;
			buscar(correos, id, pos);
			correo = gestor.correos.ficha[pos];
			cout << aCadena(correo) << endl;
			cout << endl;
			cout << "--------------------------------------------------------------------------" << endl;
			cout << "Volviendo a la bandeja de salida " << endl;
			system ("pause");
			system ("cls");
		}
	}

}

/*
*Se ejecuta al pulsar la opcion 2 
*Se busca el destinatario, si es menor la lista de correos que el maximo, y la lista de registros
*Dependiendo de todo esto dicho se le hara saber al usuario , dependiendo de la causa
*Si se puede se añade el correo , se añade el registro de salida y entrada en el usuario de destinatario y emisor respectivamente
*/

void enviarCorreo(tGestor& gestor, const tCorreo &correo)
{
	tListaUsuarios usuarios;
	int posicion;
	tListaCorreos correos;
	bool enviar = false, buscar = false, entrada= false, salida= false, max_correos= false;

	usuarios= gestor.usuarios;
	correos= gestor.correos;

	string id = correo.destinatario;

		if (buscarUsuario( usuarios, id,  posicion))
		{
			buscar = true;
		}
		else // si no encuentra el destinatario
		{
			cout << "Error. El destinatario introducido no esta registrado en fdimail.com" << endl;
			cout << "Volviendo a la bandeja de entrada " << endl;
			system ("pause");
		}
		if (gestor.correos.contador < MAX_CORREOS)
		{
			 max_correos= true;
		}
		else // si se ha llenado la lista de correos
		{
			cout << "La lista de correos del destinatario esta llena, por lo que no figura en su bandeja de entrada " << endl;
			cout << "Pero si en tu bandeja de salida " << endl;
			cout << "Volviendo a la bandeja de entrada " << endl;
			system("pause");
		}
		if (gestor.usuarios.ficha2[gestor.posicion].salida.contador <MAX_REG )
		{
			salida = true;
		}
		else // si se ha llenado el registro de salida del emisor
		{
			cout << "Tu lista de salida esta llena,por lo que no figura el correo en ella" << endl;
			cout << "Pero se ha enviado correctamente el correo " << endl;
			cout << "Volviendo a la bandeja de entrada " << endl;
			system("pause");
		}

		if (gestor.usuarios.ficha2[posicion].entrada.contador <MAX_REG )
		{
			entrada= true;
		}
		else // si se ha llenado el registro de entrada del destinatario
		{
			cout << "La lista de entrada del destinatario esta llena " << endl;
			cout << "Volviendo a la bandeja de entrada " << endl;
			system("pause");
		}
				
		if (buscar /*&& entrada && salida*/ && max_correos)// si se cumplen todos estos factores entonces se puede enviar el correo
		{
			enviar = true;
		}	
	
		if (enviar == true)
		{
			insertar(correos,correo);// se inserta el correo en la lista 
			gestor.correos= correos;// se guarda en el gestor la lista de correos , que ya ha sido modificada

			if (salida){
			// en el registro de salida se pone el mensaje a true y el emisor sera el mismo que el que lo ha enviado, pero añadiendo la fecha
			gestor.usuarios.ficha2[gestor.posicion].salida.ficha1[gestor.usuarios.ficha2[gestor.posicion].salida.contador].id = correo.id ;
			gestor.usuarios.ficha2[gestor.posicion].salida.ficha1[gestor.usuarios.ficha2[gestor.posicion].salida.contador].leido = true;
			gestor.usuarios.ficha2[gestor.posicion].salida.contador++;
			}
			if (entrada){
			//en el salida sera el mismo que el de arriba 
			gestor.usuarios.ficha2[posicion].entrada.ficha1[gestor.usuarios.ficha2[posicion].entrada.contador].id=correo.id;
			gestor.usuarios.ficha2[posicion].entrada.ficha1[gestor.usuarios.ficha2[posicion].entrada.contador].leido=false;
			gestor.usuarios.ficha2[posicion].entrada.contador++;
			}
		
		}
	
	
	apagar(gestor);// se guardan todos los cambios producidos en el txt

}

/*
*Esta funcion se ejecutara cuando se pulse la opcion 3 del menu
*Se preguntara al usuario que correo quiere borrar, y se ira recorriendo al reves (al estar ordenado)y se eliminara del gestor de ese usuario
*Se comprobara que la lista de registro del usuario que etsa el id y se elimara.
*/

void borrarCorreo(tGestor& gestor, tListaRegCorreo& listaReg, bool entrada)
{
	int numero;
	string id;
	bool borrar= true;
	tListaUsuarios usuarios;

	cout << "Numero de correo que desea borrar: " ;
	cin >> numero;

		if (entrada == false)// si es bandeja de entrada
		{
			if (gestor.usuarios.ficha2[gestor.posicion].entrada.contador==0)// si no hay correos
			{
				cout << "Ya has borrado todos los correos de la bandeja de entrada!!" << endl;
				cout << "Espera a que te manden mas correos para poder borrarlos " << endl;
				cout << "Volviendo a la bandeja de entrada " << endl;
				borrar = false;
				system ("pause");
			}
			else
			{
				if (numero > gestor.usuarios.ficha2[gestor.posicion].entrada.contador || numero <= 0)
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
			if (gestor.usuarios.ficha2[gestor.posicion].salida.contador==0)
			{
				cout << "Ya has borrado todos los correos de la bandeja de salida!!" << endl;
				cout << "Puedes mandar mas correos y borrarlos " << endl;
				cout << "Volviendo a la bandeja de salida" << endl;
				borrar = false;
				system ("pause");
			}
			else
			{
				if (numero > gestor.usuarios.ficha2[gestor.posicion].salida.contador || numero <= 0)
				{
					cout << "Error , has seleccionado un numero de correo no valido " << endl;
					borrar = false;
					cout << "Volviendo a la bandeja  " << endl;
					system("pause");
				}
			}
		}

		if (borrar)// si hay correos en la bandeja de entrada o salida se procedera a borrarlos
		{
			if (entrada == false)
			{
				int i =gestor.usuarios.ficha2[gestor.posicion].entrada.contador; //numeros de correos que hay en la bandeja de entrada
				int posicion, cont=0; 

					while (cont < numero)//al estar al reves los correosque se muestran se hace una busqueda hasta que se llege al numero marcado, es decir se ira restando el numero marcado , y el total de correos
					{
						i--;
						cont++;
					}

				posicion = i;//se obtiene la posicion y el id en esa posicion encontrada
				id = gestor.usuarios.ficha2[gestor.posicion].entrada.ficha1[posicion].id;

				usuarios = gestor.usuarios;//se le asignan a la lista de usuarios la lista de usuarios que hay en el gestor 
				
					if (posicion !=-1)//siempre que sea la posicion -1 se porcedera a borrar ese correo del gestor, en el usuario que haya inciado sesion 
					{
						for (int i = posicion; i < gestor.usuarios.ficha2[gestor.posicion].entrada.contador  ; i++) 
						{
							gestor.usuarios.ficha2[gestor.posicion].entrada.ficha1[i] = gestor.usuarios.ficha2[gestor.posicion].entrada.ficha1[i + 1];
						}

						//se reduce la lista de correos de entradadel usuario , se guarda en usuarios los cambios y se llama a apagar para que guarde las modificaciones producidas hasta este momneto
						gestor.usuarios.ficha2[gestor.posicion].entrada.contador--;
						usuarios = gestor.usuarios;
						apagar(gestor);
				
					}
					else 
					{
						cout << "No se ha encontrado el correo para borrar " << endl;
					}
			}//fin del borrado de la bandeja de entrada
	
			else//en la bandeja de salida , se aplica lo mismo que en la de entrada pero se borrara el correo de la bandeja de salida del emisor, cuando inicie sesion
			{
				 
				int i =gestor.usuarios.ficha2[gestor.posicion].salida.contador;
				int posicion, cont=0; 
					while (cont < numero)
					{
						i--;
						cont++;
					}

				posicion = i;
				id = gestor.usuarios.ficha2[gestor.posicion].salida.ficha1[posicion].id;

				usuarios = gestor.usuarios;

					if (posicion !=-1)
					{
			
							for (int i = posicion; i < gestor.usuarios.ficha2[gestor.posicion].salida.contador  ; i++) 
							{
								 gestor.usuarios.ficha2[gestor.posicion].salida.ficha1[i] = gestor.usuarios.ficha2[gestor.posicion].salida.ficha1[i + 1];
							}
						gestor.usuarios.ficha2[gestor.posicion].salida.contador--;
						usuarios = gestor.usuarios;
						apagar(gestor);
				
					}
					else 
					{
						cout << "No se ha encontrado el correo para borrar " << endl;
					}
			}

		}//fin del borrado de la bandeja de salida
	
}

/*
*Mostrara todos los mensajes no leidos de la bandeja de entrada, si esta en la bandeja de salida se le hara saber al usuario que esta en dicha bandeja y al haberlos enviado el estaran ya leidos
*Siempre que el contador de la bandeja de entrada sea mayor que 0 y que haya como minimo 1 no leido se podran mostrar , en caso contrario volvera a bandeja de entrada
*Recorrera toda la lista de entrada y guardara en una lista auxiliar aquellos correos no leidos (los que esten a false)
*Tambien se mira las tres primeras letras si son "Re:", se eliman de la lista auxiliar
*Despues de haberlo recorrido y guardado en la lista auxiliar , se prdenan por asunto y fecha , llmando a la funcion de ordenarAF.
*Se muestra al usuario
*/

void lecturaRapida(tGestor& gestor, tListaRegCorreo& listaReg,  bool entrada)
{
	string id;
	tCorreo correo;
	tListaCorreos correos;
	tListaCorreos aux;
	int pos;
	bool seguir = true;// booleano para que cuando el contador de entrada sea 0 devuleva false y aabe
	
		if (seguir)
		{
			if (entrada == false)
			{
				inicializar(aux);// se inicaliza la lista a 0
				if (gestor.usuarios.ficha2[gestor.posicion].entrada.contador==0)// se informa al usuario de que no tiene mensajes y sale del bucle
				{
					cout << "Ya has leido todos tus mensajes espera a que te manden mas !!" << endl;
					seguir = false;
					cout << "Volviendo a la bandeja de entrada " << endl;
				}
				else
				{
					for (int i =0; i < gestor.usuarios.ficha2[gestor.posicion].entrada.contador;i++)
					{
						if (gestor.usuarios.ficha2[gestor.posicion].entrada.ficha1[i].leido== false)// cunado este no leido
						{
							gestor.usuarios.ficha2[gestor.posicion].entrada.ficha1[i].leido= true; // se pone ledio
							correos = gestor.correos;
							id = gestor.usuarios.ficha2[gestor.posicion].entrada.ficha1[i].id;// se busca ese id y la posicion
							buscar(correos, id, pos);
							aux.ficha[aux.contador]= gestor.correos.ficha[pos];// se guarda en la lista auxiliar
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
								palabra = palabra+letra; // Inserta car al principio
								posi++;
							}
							if (palabra=="Re:")// se comprueba esta palabra
							{
								aux.ficha[j].asunto.erase(0,3);// se elimina del asunto
							}
					}
	
				ordenar_AF(aux);// se ordena la lista auxiliar

					for (int i =0; i < aux.contador; i++)// se muestran todos los correos de la lista auxiliar , ya ordenados
					{
						correo = aux.ficha[i];
						cout << aCadena(correo)<< endl;
						cout << "--------------------------------------------------------------------------" << endl;
						cout << "Pulsa una tecla para continuar con el siguiente mensaje " << endl;
						system ("pause");
						cout << "--------------------------------------------------------------------------" << endl;
					}
				}
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

	tListaCorreos correos;
	string nombre;
	correos = gestor.correos;
	bool borrar = false;// de momento no ha encontrado el id
	int cont=0;//las veces que no ha encontrado el correo
	
		for (int i =0; i< correos.contador; i++)
		{
			nombre = correos.ficha[i].id;// el id para buscarlo
		
			for(int j =0; j < gestor.usuarios.contador ;j++) // en la bandeja de entrada
			{
				int w =0;
				while (w < gestor.usuarios.ficha2[j].entrada.contador && !borrar )// cuando termine el bucle o si encuntra el id
				{
					if (gestor.usuarios.ficha2[j].entrada.ficha1[w].id== nombre )
					{
						cont++;// si lo ha encontrado el contador aumenta
						borrar= true;
					}
					w++;
				}
			
			}
		
			for(int t =0; t < gestor.usuarios.contador;t++ ) // en la bandeja de salida
			{
				int q =0;
				borrar = false;
				while (q < gestor.usuarios.ficha2[t].salida.contador && !borrar)
				{
					if (gestor.usuarios.ficha2[t].salida.ficha1[q].id== nombre )
					{
						cont++;
						borrar= true;
					}
					q++;
				}
			
			}
			if (cont== 0 )// sino ha encontrado el correo el contador es 0 y se borra de la lista de correos
			{
			
				for (int e=i; e < correos.contador  ; e++) 
				{
					 correos.ficha[e] = correos.ficha[e + 1];
				}
			correos.contador--;
			}
		
			gestor.correos = correos;// se guarda el gestor de correos, debido a que ha sido modificado
			cont=0;
		}

	apagar(gestor);// se guarda el txt, los cambios

}




