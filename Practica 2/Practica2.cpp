/* 
*FUNDAMENTOS DE PROGRAMACION
*Autores : Carlos Gavidia Ortiz y Pedro Garcia Marcos
*Grado Ingenieria Informatica 
*Universidad Complutense de Madrid
*Clase 9
*Laboratorios 7
*Grupo 10
*/
/*Biblioteca incluidas */
#include <iostream> 
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <assert.h> //Para poder usar asserciones en el codigo y mostrar ERROR si el dato dado no es valido

/*Espacios de nombres usados*/
using namespace std;

/*Constntes utilizadas*/
const int CARTASPORPALO = 13;
const int CENTINELA = 52,  MAXCARTAS = 53;

/* Enumerados utilizados*/
typedef enum {picas, treboles, diamantes, corazones } tPalo;
typedef enum {as , dos, tres, cuatro , cinco, seis, siete, ocho , nueve, diez, jota, reina, rey } tNumero;

/* Tipos tCarta con sinonimos de "int "*/
typedef int tCarta;

/*Nuevos tipos definidos */
typedef tCarta tMazo [MAXCARTAS]; 

/*Prototipos de las funciones defidas*/
tPalo darPalo(tCarta carta);
tNumero darNumero(tCarta carta);
void escribirCarta(tCarta carta);
bool cargarMazo(tMazo mazo, string & nombre );// hemos añadido la variable  string & nombre a la funcion para que se pueda cargar un archivo (que contiene un mazo de cartas)
void escribirMazo(const tMazo mazo);
void crearMazoVacio(tMazo mazo);
int cuantasEnMazo(const tMazo mazo);
void barajarMazo(tMazo mazo);
bool unirMazos(tMazo mazoOriginal, const tMazo nuevoMazo);
bool partirMazo(tMazo mazoOrigen, int cuantasCoger, tMazo mazoDestino);
void cortarMazo(tMazo mazo, int cuantas);
void guardarMazo(const tMazo mazo );
int menu();
void repartirNegroRojo(const tMazo mazo, tMazo mazoNegro, tMazo mazoRojo);
void repartirBajaAlta(const tMazo mazo, tMazo mazoBajas, tMazo mazoAltas);
void repartirIntercalando(const tMazo mazo, int enCuantosMazos, int queMazoPido, tMazo mazoNuevo);
void trucoTresMontones(tMazo mazo, tMazo mazo1, tMazo mazo2, tMazo mazo3 );
void trucoPosada(tMazo mazo, tMazo mazo1, tMazo mazo2, tMazo mazo3, tMazo mazo4);
void repartirParImpar(const tMazo mazo, tMazo izq, tMazo der);
void repartirFiguraNoFigura(const tMazo mazo, tMazo izq1, tMazo der1);
void trucoJugadorDesconfiado(tMazo mazo, tMazo mazo1, tMazo mazo2, tMazo mazo3, tMazo mazo4, tMazo mazoNegro , tMazo mazoRojo , tMazo mazoAltas, tMazo mazoBajas);

/*
*En la funcion del main:
*Primero mostrara el menu y se creara un mazo vacio (principalmete para que cuando el usuario pulse una opcion sin  haber pulsado antes la opcion 1 para que se carge un archivo que contendra un mazo de cartas ). 
*Si el usuario pulsa la opcion 1 cargara el archivo que diga el usuario y mostrara las cartas que contenga.
*Si se pulsa la opcion 2 se baraja el mazo y se escribe todo el mazo. 
*Si se pulsa la opcion 3 se pedira el nombre del fichero que se quiere unir al mazo que ya se ha cargado anteriormente.
*Si la opcion que se ha pulsado es la 4 se preguntara porque carta se quiere cortar la baraja se llama a la funcion con con la variable que haya introducido el usuario (cuantas).
*Si la opcion es la 5 se guarda en un archivo con el nombre que indique el usuario. 
*En la opcion 6 se divide el mazo en dos mazos en negro y el rojo llamando a las funciones.7
*En la opcion 7 tambien se divide el mazo en dos mazos bajas y altas, tambien llamandolas.
*Si se elige la opcion 8 entonces preguntara en cuantos mazos se quiere dividir se llamara a la funcion con la variable que haya puesto el usuario y escribira el mazo que que haya elegido el usuario.
*La opcion 9 sera el truco de los tres montones que la llamara directamente.
*La opcion 10 sera el truco de la posada que tambien la llamara directamente 
*/

int main()
{
	string aux ; //es para quitar el system("pause ")
	tMazo mazo,mazo1,mazo2,mazo3,mazo4 ,  mazoNegro,mazoRojo,  mazoBajas,  mazoAltas, mazoNuevo;
	int opcion, cuantas, enCuantosMazos,queMazoPido;
	string nombre;
	
	
	opcion = menu();
	crearMazoVacio( mazo);//creara un mazo vacio por si el usuario pulsa la opcion 2 antes que la 1 (caragr mazo), y asi diremos que no hay cartas en ese mazo.
	
	while ( opcion !=0 )
	{
		//1)Llamara a las funciones cargarMazo y escribirMazo.
		if ( opcion == 1 )
		{
			if (cargarMazo(mazo, nombre ))
			{
				escribirMazo(mazo);	
			}	
		}

		//2) Llamara  a las funciones de barajarMazo y escribirMazo.
		else if (opcion == 2)
		{
			barajarMazo(mazo);
			escribirMazo(mazo);
		}
	
		//3) Llamara a la funcion cargarMazo(otro mazo para unir los dos. Ya se deberia haber seleccionado la opcion 1 para cargar un mazo) y escribirMazo
		else if (opcion == 3 )
		{
			if (cargarMazo(mazo2, nombre ))
			{
				unirMazos(mazo,mazo2);
				escribirMazo(mazo);
			}
		}

		//4)Llamara a la funcion de cortarMazo y escribirMazo . Tambien le preguntara al usuaro por cuantas (por cual la quiere cortar).
		else if (opcion == 4)
		{
			cout << "Por que carta desea cortar la baraja " ;
			cin >> cuantas;

				while (cuantas < 1 || cuantas > MAXCARTAS)
				{
					cout << "ERROR. No se puede cortar la baraja por la carta introducida. Inserte otra cifra ";
					cin >> cuantas;
				}

			assert (cuantas > 0 && cuantas <MAXCARTAS);//Aqui nos aseguramos que cuantas este entre 1 y 52.

			cortarMazo(mazo, cuantas);
			escribirMazo(mazo);	
		}

		//5)Llamara a la funcion de guardarMazo.
		else if (opcion == 5 )
		{
			guardarMazo(mazo);
		}

		//6)Llamara a la funcion de reaprtirNegroRojo y escribirMazo
		else if (opcion == 6 )
		{
			repartirNegroRojo( mazo,  mazoNegro,  mazoRojo);
			cout << "Cartas negras : " << endl;
			escribirMazo(mazoNegro);
			cout << "Cartas rojas : " << endl;
			escribirMazo(mazoRojo);
		}

		//7)Llamara  a la funcion de repartirBajaAlta y escribirMazo.
		else if (opcion == 7 )
		{
			repartirBajaAlta( mazo,  mazoBajas,  mazoAltas);
			cout << "Cartas bajas : " << endl;
			escribirMazo(mazoBajas);
			cout << "Cartas altas : " << endl;
			escribirMazo(mazoAltas);
		}

		//8)Llamara a la funcion de repartirIntercalando y escribirMazo. Tambien preguntara al usuario enCuantosMazos y queMazoPido.
		else if (opcion == 8)
		{
			cout << "En cuantas partes quiere dividir el mazo ";
			cin >> enCuantosMazos;

				while (enCuantosMazos < 1 || enCuantosMazos> MAXCARTAS)
				{
					cout << "ERROR. Solo se pueden dividir mazos por el numero introducido. Introduce otro numero ";
					cin >> enCuantosMazos;
				}

			assert (enCuantosMazos > 0 && enCuantosMazos < MAXCARTAS); // Asi nos aseguramos que el numero esta entre 0 y 52.
			
			cout << "Que mazo quiere quedarse ";
			cin >> queMazoPido;

				while (queMazoPido < 1 || queMazoPido> MAXCARTAS)
				{
					cout << "ERROR.  El numero introducido no es valido . Introduce otro numero ";
					cin >> queMazoPido;
				}

			assert (queMazoPido > 0 && queMazoPido < MAXCARTAS); // Asi nos aseguramos que el numero esta entre 0 y 52.

			repartirIntercalando(mazo, enCuantosMazos, queMazoPido,  mazoNuevo);
			cout << "El monton " << queMazoPido << " tiene las siguientes cartas: " << endl;
			escribirMazo(mazoNuevo);
		}

		//9)Llamara a la funcion cargarMazo y trucoTresMontones.
		else if (opcion == 9)
		{
			cargarMazo( mazo,  nombre );
			trucoTresMontones(mazo, mazo1, mazo2, mazo3);
		}

		//10) Llamara a la funcion cargarMazo y trucoPosada.
		else if (opcion == 10 )
		{
			cargarMazo( mazo,  nombre );
			trucoPosada(mazo, mazo1, mazo2, mazo3, mazo4);
		}

		//11)Llamara a la funcion cargarMazo y el trucoJugadorDesconfiado.
		else if (opcion == 11 )
		{
			cargarMazo(mazo, nombre);
			trucoJugadorDesconfiado( mazo,  mazo1, mazo2,  mazo3,  mazo4,  mazoNegro ,  mazoRojo ,  mazoAltas,  mazoBajas);
		}

	opcion = menu();
	
	}
	cout << "Hasta la proxima !! " << endl;
	

	cout << "Pulsa una tecla para continuar ..." ; //despedida 
	
	cin.sync(); //para evitar errores
	getline(cin,aux);
}

/*
*En esta funcion  calculara que el palo es  carta entre 13.
*lo que quiere decir que nos dira en que posicion del enumerado de tPalo esta esa carta.
*/

tPalo darPalo(tCarta carta)
{
	tPalo  palo;

	palo = tPalo(carta/CARTASPORPALO);
	 
	return palo ;
}

/*
*En esta funcion numero es el resto de  carta entre 13 .
*Por lo que sera un numero entre el 0 y el 12 y dira que posicion del enumerado de tNumero tiene esa carta.
*/

tNumero darNumero(tCarta carta)
{
	tNumero numero;

	numero = tNumero(carta%CARTASPORPALO);

	return numero;
}

/*
*En esta funcion juntara la funcionn de darNumero y darPalo para que muestre en nombre completo de la carta con el nombre del palo y del numero .
*Le dira a el programa que el 0 es el as y asi sucesivamente hasta 12 (del tNumero) y 0 es Picas y asi sucesivamente hast el 3 (del tPalo).
*Llamara a las funciones de darNumero y darPalo.
*/

void escribirCarta(tCarta carta)
{ 

	int palo, numero;

	numero = darNumero( carta);
	palo =  darPalo( carta );

		if (numero == 0)
		{
			cout << "As de ";
		}
		else if (numero == 1)
		{
			cout << "2 de ";
		}
		else if (numero == 2 )
		{
			cout << "3 de ";
		}
		else if (numero == 3 )
		{
			cout << "4 de ";
		}
		else if (numero == 4 )
		{
			cout << "5 de ";
		}
		else if (numero == 5)
		{
			cout << "6 de ";
		}
		else if (numero == 6 )
		{
			cout << "7 de ";
		}
		else if (numero == 7 )
		{
			cout << "8 de ";
		}
		else if (numero == 8 )
		{
			cout << "9 de ";
		}
		else if (numero == 9 )
		{
			cout << "10 de ";
		}
		else if (numero == 10 )
		{
			cout << "J de ";
		}
		else if (numero == 11 )
		{
			cout << "Q de ";
		}
		else if (numero == 12  )
		{
			cout << "K de ";
		}


		if (palo==0)
		{
			cout << " Picas " << endl;
		}
		else if (palo== 1)
		{
			cout << " Treboles " << endl;
		}
		else if (palo == 2)
		{
			cout << " Diamantes " << endl;
		}
		else if (palo == 3 )
		{
			cout << " Corazones " << endl;
		}
}

/*
*En esta funcion se basa en cargar un archivo de texto (ya creado) que leera (dentro del archivo estaran las cartas del mazo).
*Leera el nombre del archivo que ponga el usuario.
*Dentro del archivo leera primero la letra y luego el numero.
*A través de la acuacion propuesta en la funcion el programa sabrá en que palo esta.
*El usuario tendra tres oportunidades en caso de fallar en introducir el nombre del archivo luego volvera al menu.
*Al final del mazo se colocara el CENTINELA para cerrar el mazo.
*/

bool cargarMazo(tMazo mazo, string & nombre )
{
	
	bool abrir;
	char a , valor;
	int numero, i = 1, contador = 0;
	
	ifstream archivo;
	cout << "Dime el nombre del archivo " ;
	
	cin.sync (); 
	getline(cin , nombre);
	
	archivo.open(nombre);

		while (!archivo.is_open() && i < 3 )//Para que cuando el usuario meta el nombre del archivo mal o no exista tenga hasta 2 opotunidades mas.Luego mostrara el menu
		{ 
			
			cout << "No ha podido abrir el fichero " << endl;
			cout << "Dime el nombre del archivo " ;
			cin.sync (); 
			getline(cin , nombre);
			i++;
			archivo.open(nombre);	
		}
	
		if (archivo.is_open())
		{
			archivo >> a;
			archivo >> numero;
			
			while ((a!= 'x')&&( contador <= MAXCARTAS))
			{
				
				if (a== 'p')
				{
					valor = 0*CARTASPORPALO + numero -1 ;
				}
				else if (a == 't')
				{
					valor = 1*CARTASPORPALO + numero -1 ;
				}
				else if (a=='d')
				{
					valor = 2*CARTASPORPALO + numero -1 ;
				}
				else if (a == 'c')
				{
					valor = 3*CARTASPORPALO + numero -1 ;
				}

				mazo[contador]=valor;
				contador++;
				archivo >> a;
				archivo >> numero;
				
			}

		mazo[contador]= CENTINELA;
		archivo.close();
		abrir= true;

		assert ( contador <= MAXCARTAS);//Nos aseguramos que no hay mas espacios en el array(contador) que sea mayor que MAXCARTAS.
		}
	

		else 
		{

		abrir= false;

		}

	return abrir;
}

/*
*En esta  funcion tiene la mision de mostrar las cartas del mazo.
*Utilizara un for para el recorrido del mazo siempre y cuando el mazo no supere a MAXCARTAS .
*Ni en primer lugar del mazo sea en CENTINELA en ese caso querria decir que el mazo esta vacio o que no se ha cargado un archivo de texto antes.
*Si no hay nada en el mazo no mostrara contenido.
*Si por el contrario si hay cartas la escribira hasta llegar el CENTINELA.
*Si no ha cargado un fichero mostrara ERROR.Por lo que no se podra escribir ninguna carta ya que no hay cartas en el mazo.
*/

void escribirMazo(const tMazo mazo)
{ 

	int i = 0 ;

	while ((i< MAXCARTAS)&&(mazo[i]!=CENTINELA))
	{
		escribirCarta(mazo[i]);
		i++;
	}	

	if (mazo[0]==CENTINELA)//para cuando el mazo este vacio porque no ha cargado ningun fichero de texto
	{
		cout << "Error. No ha cargado antes un mazo de cartas. " << endl;
	}

}

/*
*En esta funcion en la primera posico del array esta el CENTINELA.
*Su funcion principal es que no haya problemas a la hora de cargar un mazo.
*/

void crearMazoVacio(tMazo mazo)
{
	mazo[0]= CENTINELA;
}

/*
*En esta funcion se contaran las cartas que hay en el mazo.
*Se contaran las posiciones del array , apartir de un contador que sera igualdado a 0 para empezar.
*La funcion devolvera el valor del contador que sera en numero de cartas que hay en el mazo.
*/

int cuantasEnMazo(const tMazo mazo)
{
	int i =0;

		while ((i< MAXCARTAS)&&(mazo[i]!=CENTINELA))
		{
			i++;
		}

	return i;
}

/*
*En esta funcion se encogeran los posiciones de cartas del maazo al azar y se repetira cada tres veces por el numero de cartas que hay en el mazo.
*Utilizara numeros aleatorios para coger dos posiciones del array intercambiandolas de posicion.
*Llamara a la funcion de cuantas en el mazo para saber cuantas posiciones hay en el array .
*Hasta que no llege a la operacion de 3 por cuantas posicones que hay en el array.
*Llamara a la funcion de cuantasEnMazo.
*/

void barajarMazo(tMazo mazo)
{
	int pos1, pos2;
	tCarta aux;
	
	for (int i = 0; i < 3* cuantasEnMazo(mazo); i++ )
	{
		pos1 =rand() % (cuantasEnMazo(mazo)) ;
		pos2 =rand() % (cuantasEnMazo(mazo)) ;
		aux = mazo[pos1];//se utiliza un auxiliar para intercambiar las posiones del array.
		mazo[pos1 ] = mazo [pos2];
		mazo[pos2]= aux;
	}
	
}

/*
*En esta funcion se uniran dos mazos en uno solo.
*Utilizara los array que luego uniran en un array.
*Llamara a la funcion de cuantosEnMazo para un array y para otro.
*Al ser funcion booleana devolvera verdad flase si entre los dos mazos hay mas cartas que MAXCARTAS (las permitidas).
*Y devolvera true si no ha habido ningun error.
*Se añadira al final del mazo resultante un CENTINELA para evitar que las posiciones vacias del array no se corrompa.
*/

bool unirMazos(tMazo mazoOriginal, const tMazo nuevoMazo)
{
	int total, cuantas , i =0;
	bool verdad;

	total =cuantasEnMazo(mazoOriginal)+ cuantasEnMazo (nuevoMazo);

	if (total > CENTINELA)
	{
		verdad = false;
	}

	else
	{
		verdad = true;
		cuantas = cuantasEnMazo(mazoOriginal);
		
		while ((i< MAXCARTAS)&&(nuevoMazo[i]!=CENTINELA))
		{
			mazoOriginal[cuantas+i]= nuevoMazo[i];
			i++;
		}
	
		mazoOriginal [cuantas+i ]= CENTINELA;
	}
	
	return verdad;
}

/*
*Esta funcion constistira en partir un mazo en dos mazos.
*Al ser un afuncion booleana devolvera false si cuantasCoger es mayor que las cartas que haya en el mazo.
*En el menu le preguntara al usuario porque carta quiere partirlo, y lo enviara a la funcion para que lo parta por la posicion indicada.
*De un mazo lo dividira en dos un mazoDestino.
*Y un mazoOrigen que al a verle quitado el numero de cartas que indique el usuario.
*Las posiciones que se hayan quitado del mazo (principal)quedaran vacias y se les asignaran a el mazoOrigen desde la posicon 0.
*/

bool partirMazo(tMazo mazoOrigen, int cuantasCoger, tMazo mazoDestino)
{
	
	bool suficientes;
	int baraja, j = 0, i = 0;
	
	baraja =cuantasEnMazo( mazoOrigen) - cuantasCoger; //nos dria cuantas cartas hay en la baraja(final despues de quitarle las cartas que diga el usuario)
	
	if(cuantasCoger >= cuantasEnMazo( mazoOrigen))
	{
		suficientes = false;
	}

	else 
	{
		suficientes = true;
		
		for ( j = 0 ;j < cuantasCoger;j++ )//se tiene que sacar el int del int j =0; para luego poner un CENTINELA al final.
		{
			mazoDestino[j]= mazoOrigen[j];
		}
		mazoDestino[cuantasCoger ]= CENTINELA;
	
		for ( i = 0 ;i < baraja ;i++)//se tiene que sacar el int del int j =0; para luego poner un CENTINELA al final.
		{
			mazoOrigen[i] =mazoOrigen[cuantasCoger + i] ;
		}
		mazoOrigen [baraja ]= CENTINELA;

	}

	return  suficientes;
}

/*
*Esta funcion cortara el mazo  en dos como que carta diga el usuario y unira los dos mazos en uno.
*Utlizara el array de mazo y lo  cambiara de posiciones.
*Llamara a las funciones de cuantasMazos , partirMazo , y unirMazo.
*Solo cuando el numero que meta el usuario de por el que querra cortar el mazo sea menor  podra continuar.
*En este procedimiento unira la funcion de partirMazo(para partirlo) y la unir para modificar el array.
*/

void cortarMazo(tMazo mazo, int cuantas)
{
	int total;

	tMazo mazoDestino;

	total = cuantasEnMazo( mazo );//llamara a cuantas en el mazo y sera el total de cartas que haya

	if (cuantas < total )
	{
		partirMazo( mazo, cuantas, mazoDestino );
		unirMazos(mazo, mazoDestino); 
	}
	assert(cuantas < total );//Nos aseguramos que cuantas en menor que  el mazo.
}

/*
*En esta funcion guarda el mazo en un archivo de texto
*Le pedira a usuario que indique el nombre de coo lo quiere guardar.
*Llamara a la funcion cuantasEnMazo.
*Para escribir las cartas ne larchivo seguira la misma metodologia que para leerlo (con d , c (para los palos) y  1, 2 (para los numeros) ... ).
*/

void guardarMazo(const tMazo mazo  )
{

	int total , i= 0;
	string  nombre;

	ofstream archivo;
	cout << "Introduzca el nombre del fichero donde lo  quiere guardar " ;
	cin >> nombre;
	archivo.open(nombre);

	if (archivo.is_open())
	{
		total = cuantasEnMazo( mazo );//para saber cuantas hay en el mazo
		
		for ( i=0; i < total ; i++)//debera convertir los palos en d, c, p o t .
		{
			if (darPalo(mazo[i])== treboles )
			{
				archivo << "t ";
			}
			else if (darPalo(mazo[i])== picas  )
			{
				archivo << "p "; 
			}
			else if (darPalo(mazo[i])== corazones  )
			{
				archivo << "c "; 
			}
			else if (darPalo(mazo[i])== diamantes  )
			{
				archivo << "d "; 
			}

			archivo << darNumero(mazo[i])+1 << endl;//Apartir de la funcion de darNumero concocer el numero pero habra que sumarle 1, por el array.

		}
		
		archivo << "x" << endl;//el archivo acabra en x como centinela.
	}
}

/*
*En la funcion de menu mostrara las opciones que puede elegir el usuario.
*Devolvera la opcion que diga el usuario.
*Si la opcion no esta entre esos numero permitidos volvera a preguntar al usuario la opcion hasta que sea valida.
*/

int menu()
{

	int opcion;

	cout << "1 - Cargar un mazo de cartas de fichero " << endl;
	cout << "2 - Barajar mazo de cartas " << endl;
	cout << "3 - Aniadir mazo " << endl;
	cout << "4 - Cortar mazo " << endl;
	cout << "5 - Guardar mazo de cartas en fichero " << endl;
	cout << "6 - Separar en negras y rojas " << endl;
	cout << "7 - Separar en bajas y altas " << endl;
	cout << "8 - Repartir un mazo de manera alterna en  montones " << endl;
	cout << "9 - Truco de los tres montones "<< endl;
	cout << "10 - Truco de la posada " << endl;
	cout << "11 - Truco del jugador desconfiado " << endl;
	cout << "0 - Salir " << endl;

	cin >> opcion;
	
	while ( opcion < 0 || opcion > 11 ) //para cuando la opcion fuese  no valida.
	{
		cout << "Error . Opcion no valida "  ;
		cin >> opcion ;
	}

	//No hemos puesto un assert por si el usuario se ha equivado en la opcion pero no quiere cerrar el programa.

	return opcion ;
}

/*
*Version2.
*La mision de esta funcion sera repartir de un mazo en cartas negras(picas y treboles ) y las cartas rojas (corazones y diamnates)
*La funcion llamara a la funcion de cuantasEnMazo para dar el numero de cuantas cartas hay en el azmo.
*Atraves de la funcion darPalo sabra de que palo es cada carta del mazo.
*Utlizidara un contador a 0 para que a medida que se vayan leyendo las cartas del archivo se vayan apilando en negras o rojas 
*Cuando acabe de leer todas las cartas del archivo pondra un CENTINELA en ambas abrajas para cerrarlas y evitar errores.
*/

void repartirNegroRojo(const tMazo mazo, tMazo mazoNegro, tMazo mazoRojo)
{

	int total;
	int cuantasNegro=0, cuantasRojo=0;

	total = cuantasEnMazo( mazo );

	for ( int i=0; i < total ; i++)
	{

		if (darPalo(mazo[i])== picas|| darPalo(mazo[i])== treboles )//a aprtir de la funcion de darPalo sabra si la carta que lea es picas , treboles...
		{
			mazoNegro[cuantasNegro]= mazo[i];
			cuantasNegro++;
		}
			
		else 
		{
			mazoRojo[cuantasRojo]= mazo[i];
			cuantasRojo++;
		}
		
	}
	
	mazoNegro[cuantasNegro]=CENTINELA;
	mazoRojo[cuantasRojo]=CENTINELA;
	
}

/*
*Version2
*En esta funcion clasificara un mazo entre cartas altas y bajas.
*Esta funcion actua de la misma manera que repartirNegrasRojas, pero en vez de leer el palo leera el numero.
*Al igual que la anterior funcion comenzara llamando a cuantasEnMazo para saber el total.
*Empezara con un contador=0, para ir leyendo de una en una de archivo, clasificandolas, en altas(>7)o bajas (<=7).
*Al final tambien se colocara un CENTINELA para eviar fallos y asi cerrar el array.
*/

void repartirBajaAlta(const tMazo mazo, tMazo mazoBajas, tMazo mazoAltas)
{ 

	int total;
	int cuantasBajas=0, cuantasAltas=0;

	total = cuantasEnMazo( mazo );

	for ( int i=0; i < total ; i++)
	{
		if ((darNumero(mazo[i]) <=7))
		{ 
			mazoBajas[cuantasBajas]= mazo[i];
			cuantasBajas++;
		}

		else 
		{
			mazoAltas[cuantasAltas]= mazo[i];
			cuantasAltas++;
		}	
	}

	mazoBajas[cuantasBajas]=CENTINELA;
	mazoAltas[cuantasAltas]=CENTINELA;

}

/*
Version2.
*En esta funcion repartira alternamente la baraja de cartas en los montones que eliga en usuario y mostrara por pantalla el mazo que tambien lo eligira el usuario.
*Utlizamos un contador del mazo que vamos a crear a 0, y otro que sera el del mazo anterior.
*Apartir de una  operacion podremos averiguar cada cuantas cartas esa carta que leera se copiara e ra al mazo que se crear(el mazo nuevo)
*Al final  se colocara el centinela en la ultima posicion del array que se cree.
*Para saber todas las posiciones que nos haran falta en el array se llamara a la funcion de cuanatsEnMazo.
*/

void repartirIntercalando(const tMazo mazo, int enCuantosMazos, int queMazoPido, tMazo mazoNuevo)
{

	int contadorMazoNuevo = 0,  contadorMazoGrande =queMazoPido -1;

		while ( contadorMazoGrande< cuantasEnMazo(mazo))
		{
			mazoNuevo[contadorMazoNuevo] = mazo[contadorMazoGrande];
			contadorMazoNuevo++;
			contadorMazoGrande = contadorMazoGrande + enCuantosMazos;
		}

	mazoNuevo[contadorMazoNuevo]=CENTINELA;
	
}

/*
*Version 3.
*En la siguinte funcion se ejecutara el truco de los tres montones .
*El usuario dara el nombre del mazo que quiere cargar.
*Luego se barajean las cartas del mazo y se repartira de manera alterna al usuario.
*Se pedira que escoja un carta mentalamente y se indique en que monton esta. Apartir del monton que diga este se pondra en medio de los otros dos.
*Los tres mazos se uniran en uno solo y se volveran a repartirse en tres montones y el usuario tendra que decir donde esta la crtas otra vez.
*El proceso de prguntar al usuario y repartir los montones se hara dos veces mas.
*Al final del truco se mostrara la carta que eligio el usuario.
*Para su implemetacion se llamaran a las siguientes funciones repartirIntercalando , escribirMazo, unirMazo y la de barajarMazo.
*/

void trucoTresMontones(tMazo mazo, tMazo mazo1, tMazo mazo2 , tMazo mazo3)
{
	
	int  enCuantosMazos=3,queMazoPido,  queMazoPido1 = 1, queMazoPido2 = 2, queMazoPido3 = 3;
				
	cout << "Barajamos el mazo. " << endl;
	barajarMazo(mazo);

	//ahora el mazo se reparira en tres mazos llamando a la funcion de repartir intercalado.
	repartirIntercalando(mazo, enCuantosMazos, queMazoPido1,  mazo1);
	cout << "El primer monton contiene las siguientes cartas: " << endl;
	escribirMazo(mazo1);
				
	repartirIntercalando(mazo, enCuantosMazos, queMazoPido2,  mazo2);
	cout << "El segundo monton contiene las siguientes cartas: " << endl;
	escribirMazo(mazo2);
				
	repartirIntercalando(mazo, enCuantosMazos, queMazoPido3,  mazo3);
	cout << "El tercer monton contiene las siguientes cartas: " << endl;
	escribirMazo(mazo3);
				
	cout << "Escoja mentalmente una carta y diga en que mazo esta su carta elegida ";
	cin >> queMazoPido;

	int i =1;

		while (i < 3 )
		{
			if (queMazoPido == 1 )//1)si el usuario dice que eat en el monton 1 
			{
				unirMazos(mazo2,mazo1);
				unirMazos(mazo2, mazo3);
				escribirMazo(mazo2);

				int j = 0, i=0;

					while (j < 21)// este while es para recomponer el mazo.
					{
						mazo[j]= mazo2[i];
						i++;
						j++;
					}
					
				cout << "Repatirmos las cartas en tres montones de nuevo "<< endl;//2 vez que vamos a repartir en tres montones.

				repartirIntercalando(mazo, enCuantosMazos, queMazoPido1,  mazo1);
				cout << "El primer monton contiene las siguientes cartas: " << endl;
				escribirMazo(mazo1);
				
				repartirIntercalando(mazo, enCuantosMazos, queMazoPido2,  mazo2);
				cout << "El segundo monton contiene las siguientes cartas: " << endl;
				escribirMazo(mazo2);
				
				repartirIntercalando(mazo, enCuantosMazos, queMazoPido3,  mazo3);
				cout << "El tercer monton contiene las siguientes cartas: " << endl;
				escribirMazo(mazo3);

				}

				else if (queMazoPido == 2)// 2) si el usuario dice que esta en el monton 2 
				{
					unirMazos(mazo1,mazo2);
					unirMazos(mazo1, mazo3);
					escribirMazo(mazo1);

					int w = 0, e=0;

						while (w < 21)//para recomponer el mazo.
						{
							mazo[w]= mazo1[e];
							w++;
							e++;
						}

					cout << "Repatirmos las cartas en tres montones de nuevo "<< endl;//segunda vez que repartimos

					repartirIntercalando(mazo, enCuantosMazos, queMazoPido1,  mazo1);
					cout << "El primer monton contiene las siguientes cartas: " << endl;
					escribirMazo(mazo1);
				
					repartirIntercalando(mazo, enCuantosMazos, queMazoPido2,  mazo2);
					cout << "El segundo monton contiene las siguientes cartas: " << endl;
					escribirMazo(mazo2);
				
					repartirIntercalando(mazo, enCuantosMazos, queMazoPido3,  mazo3);
					cout << "El tercer monton contiene las siguientes cartas: " << endl;
					escribirMazo(mazo3);

				}

				else if (queMazoPido== 3 )// 3)si el usuario dice que su carta esta en el trecer monton.
				{
					unirMazos(mazo1,mazo3);
					unirMazos(mazo1, mazo2);
					escribirMazo(mazo1);

					int q = 0, r=0;

						while (q < 21)//para recomponer el mazo.
						{
							mazo[q]= mazo1[r];
							r++;
							q++;
						}

					cout << "Repatirmos las cartas en tres montones de nuevo "<< endl;//segunda vez que repartimos.

					repartirIntercalando(mazo, enCuantosMazos, queMazoPido1,  mazo1);
					cout << "El primer monton contiene las siguientes cartas: " << endl;
					escribirMazo(mazo1);
				
					repartirIntercalando(mazo, enCuantosMazos, queMazoPido2,  mazo2);
					cout << "El segundo monton contiene las siguientes cartas: " << endl;
					escribirMazo(mazo2);
				
					repartirIntercalando(mazo, enCuantosMazos, queMazoPido3,  mazo3);
					cout << "El tercer monton contiene las siguientes cartas: " << endl;
					escribirMazo(mazo3);
				}

				cout << "Asegurese de que esta su carta y vuelva a decir en que monton esta ";
				cin >> queMazoPido;
				i++;//para que se repita dos veces mas (lo de repartir en montones)

		}//cierre del while
				//a partir de aqui ya se a repartido tres veces el mazo.
				if (queMazoPido == 1 )//si el usuario dice que esta en el monton 1
				{
					unirMazos(mazo2,mazo1);
					unirMazos(mazo2, mazo3);
					escribirMazo(mazo2);

					int o = 0, p=0;

						while (o < 21)//recompone el mazo.
						{
							mazo[o]= mazo2[p];
							p++;
							o++;
						}
				}

				else if (queMazoPido == 2)// si el usuario dice que esta en el 2 monton 
				{
					unirMazos(mazo1,mazo2);
					unirMazos(mazo1, mazo3);
					escribirMazo(mazo1);

					int u = 0, y=0;

						while (u < 21)//para recomponer el mazo.
						{
							mazo[u]= mazo1[y];
							u++;
							y++;
						}
				}

				else if (queMazoPido == 3 )//por si el usuario dice que la carta esta en le 3 monton.
				{
					unirMazos(mazo1,mazo3);
					unirMazos(mazo1, mazo2);
					escribirMazo(mazo1);

					int g = 0, f=0;

					while (g < 21)//para recomponer el mazo.
					{
						mazo[g]= mazo1[f];
						f++;
						g++;
					}	
				}
				
	cout << "Su carta es " ;
	escribirCarta(mazo[10]);//llamamos a escribir carta para que nos muestre el contendo del mazo en la posicion 10.
	cout << "El truco ha finalizado " << endl;

}

/*
*Version4.
*Este truco consiste en coger un a baraja que contendra los cuatros ases, cuatros jotas, cuatro reyes y cuatro reinas.
*Repartira esa baraja a apartir de la funcion repartir intercalado en cautro montones.
*Y los volvera a unir en un unico mazo con la funcion unirMazo.
*Pedira al usuario por que carta quiere partir el mazo.
*Luego volvera a repartirlo en cuatro montones,mostrando que en cada mazo estan las cuatro jotas, en otra los cuatro reyes, en otro los ases y en otro las reinas.
*/

void trucoPosada(tMazo mazo, tMazo mazo1, tMazo mazo2, tMazo mazo3, tMazo mazo4)
{
	int enCuantosMazos  = 4 ;
	int queMazoPido1 = 1, queMazoPido2 = 2, queMazoPido3 = 3, queMazoPido4 = 4;
	int o = 0, p=0, cuantas;

	cout << "Para hacer el siguiente truco primero tenemos que contar una historia : " << endl;
	cout << "" << endl;
	cout << "Llegaron cuatro caballeros (las cuatro J) y cada uno se puso en " << endl;
	cout << "una habitacion diferente (cada carta se pone en un sitio de la mesa)." << endl;
	cout << "" << endl;
	cout << "Luego llegaron cuatro senioras (Q) y, " << endl;
	cout << "para no dejarlas sin habitacion, ubicaron a cada" << endl;
	cout << "una en una de dichas habitaciones, con los caballeros " << endl;
	cout << "(cada Q se pone sobre cada J)." << endl;
	cout << "" << endl;
	cout << "Luego llegaron cuatro reyes (K) con sus cuatro peones (A), " << endl;
	cout << "y pusieron cada rey y cada peon en alguna de dichas cuatro habitaciones." << endl;
	cout << "" << endl;
	cout << "Asi que en cada habitacion quedo una J, una Q, una K y una A " << endl;
	cout << "(es decir, tenemos cuatro mazos, cada uno con una J, una Q, una K y una A). " << endl;
	cout << "" << endl;
	cout << "Entonces se fueron todos a dormir. " << endl;
	cout << "" << endl;

	//ahora repartira el mazo en cuatro montones y los muestra en pantalla.
	repartirIntercalando( mazo,  enCuantosMazos,  queMazoPido1,mazo1);
	cout << "El primer monton contiene estas cartas " << endl;
	escribirMazo (mazo1);

	repartirIntercalando( mazo,  enCuantosMazos,  queMazoPido2,mazo2);
	cout << "El segundo  monton contiene estas cartas " << endl;
	escribirMazo (mazo2);

	repartirIntercalando( mazo,  enCuantosMazos,  queMazoPido3,mazo3);
	cout << "El tercer monton contiene estas cartas " << endl;
	escribirMazo (mazo3);

	repartirIntercalando( mazo,  enCuantosMazos,  queMazoPido4,mazo4);
	cout << "El cuarto monton contiene estas cartas " << endl;
	escribirMazo (mazo4);

	//los une los cuatro mazos en uno.
	unirMazos(mazo1, mazo2);
	unirMazos(mazo1, mazo3);
	unirMazos(mazo1, mazo4);

	cout << "Ahora juntamos los cuatros mazos en uno solo " << endl;
		
		while (o < 16) //para organizar el array.
		{
			mazo[o]= mazo1[p];
			p++;
			o++;
		}

	//pedira al usuario por que carta quiere corar la baraja 
	cout << "En que numero de carta quiere cortar el nuevo mazo ";
	cin >> cuantas;
	assert(cuantas >0 && cuantas < 16);//para asegurarnos que el usuario mete un numero menor o igual que el mazo.
	cortarMazo( mazo,  cuantas);
	
	//ahora volvera a repartir el  mazo en cuatro montones(donde estaran las mismas cartas )
	repartirIntercalando( mazo,  enCuantosMazos,  queMazoPido1,mazo1);
	cout << "El primer monton contiene estas cartas " << endl;
	escribirMazo (mazo1);

	repartirIntercalando( mazo,  enCuantosMazos,  queMazoPido2,mazo2);
	cout << "El segundo  monton contiene estas cartas " << endl;
	escribirMazo (mazo2);

	repartirIntercalando( mazo,  enCuantosMazos,  queMazoPido3,mazo3);
	cout << "El tercer monton contiene estas cartas " << endl;
	escribirMazo (mazo3);

	repartirIntercalando( mazo,  enCuantosMazos,  queMazoPido4,mazo4);
	cout << "El cuarto monton contiene estas cartas " << endl;
	escribirMazo (mazo4);

	cout << "Y en cada mazo estan las cuatro cartas del mismo palo !! " << endl;
	cout << "El truco ha finalizado " << endl;

}

/*
*Version5 
*En esta funcion primero se baraja un mazo que tendra 20 cartas especificas (para que le truco salga bien con otra baraja puede tenr otros efectos).
*Repartira en cuatro montones(para cuatro jugadores).
*Y cada mazo se dividira en dos cada uno( en total ocho).
*Segun el siguiente criterio:
 -El primer mazo se dividira entre negras y rojas.
 -El segundo entre altas y bajas
 -El tercero entre pares e impares
 -El cuarto entre figras o no figuras.
*Los mazo resultantes se llamaran izquierdo y dercho y los jugadores se repartiran de la siguiente manera:
 -El mazo derecho de cada jugador se le dara al jugador derecho(en la practica el jugador derecho es el de abajo. Ej si el jugador 1 le tiene que dar su mazo derecho al jugador de la drecha se lo dara a el jugador2 y asi sucesivamente).
 -El mazo izuierdo se le dara al jugador que este en la izquierda(en la practica seguira el mismo criterio que el anterior pero alreves, es decir que por ejemplo el jugador 1 le dara su mazo izquierdo al jugador4 ...).
*Los mazos se volveran a juntar y se escriben en pantalla.
*Luego se hara el porceso anterior desde repartir en 8 partes otra vez.
*Y por ultimo se reparira otra ves en 8 mazos pero esta vez solo se psara el mazo izquierdo(siguiendo lo descrito anteriormete) y se quedan con el derecho.
*Al final el jugador 1 gana por tener escalera de color , el segundo full el tercero poker y el ultimo color.
*En esta funcion llamara a las funciones de repartirNegroRojo, barajarMazo, escribirMazo, repartirIntercalado, repartirParImpar , repartirAltasBjas, repartirFigurasNoFiguras.
*Se utilizaran hasta 8 arrays para luego ir uniendolos a lo largo del truco e ir jugando con ellos.
*/

void trucoJugadorDesconfiado(tMazo mazo, tMazo mazo1, tMazo mazo2, tMazo mazo3, tMazo mazo4, tMazo mazoNegro , tMazo mazoRojo , tMazo mazoAltas, tMazo mazoBajas)
{

	int enCuantosMazos = 4 , enCuantosMazos1 = 2 , queMazoPido1 = 1, queMazoPido2 = 2, queMazoPido3 = 3, queMazoPido4 = 4;
	
	tMazo izq, der, izq1 , der1; //mazos del tercer y cuarto jugador.
	string tecla;//solo sirve para que cuando se haga el truco no caiga en cascada y permita que el usuario visualize lo que hace.

	cout << "Un jugador de poker, llamado Jugador 1, dice que desconfoa de que los demas" << endl;
	cout << "jugadores sentados con el en la mesa (llamados Jugador 2, Jugador 3 y Jugador 4" << endl;
	cout << "yendo en sentido contrario a las agujas del reloj desde Jugador 1)" << endl;
	cout << "le hagan trampas. Por ello, propone que las 20 cartas que se van a repartir  " << endl;
	cout << "sean visibles para todos antes de repartirse (A, Q, K de picas; "<< endl;
	cout << "2, 4, 5, 6, 9, Q, K de tréboles; c2, 3, 4, 5, 6, 10, K de diamantes; " << endl;
	cout << "y 10, Q, K de corazones). " << endl;
	cout << "" << endl;
	cout << "Barajamos el mazo " << endl;

	barajarMazo(mazo);
	escribirMazo(mazo);

	//repartimos el mazo a los cuatro jugadores llamando a la funciond e repartirIntercalado.

	repartirIntercalando( mazo,  enCuantosMazos,  queMazoPido1,mazo1);
	cout << "El primer jugador tiene las siguientes cartas " << endl;
	escribirMazo (mazo1);

	repartirIntercalando( mazo,  enCuantosMazos,  queMazoPido2,mazo2);
	cout << "El segundo jugador tiene las siguientes cartas " << endl;
	escribirMazo (mazo2);

	repartirIntercalando( mazo,  enCuantosMazos,  queMazoPido3,mazo3);
	cout << "El tercer jugador tiene las siguientes cartas " << endl;
	escribirMazo (mazo3);

	repartirIntercalando( mazo,  enCuantosMazos,  queMazoPido4,mazo4);
	cout << "El cuarto jugador tiene las siguientes cartas " << endl;
	escribirMazo (mazo4);

	cout << "Pulsa una tecla para continuar con el truco " << endl;//Unicamnte para que el programa se vaya parando en el truco poco a poco.
	getline(cin, tecla);

	// ahora dividir cada mazo en dos el izquierdo y el derecho
	//Hemos puesto un contador que empieza en 0 para que lo divida tres veces 

	int contador =0;
		while (contador < 3)
		{
			//repartimos el mazo del jugador 1 en dos
			repartirNegroRojo( mazo1,  mazoNegro,  mazoRojo);
			repartirNegroRojo( mazo1, mazoNegro,  mazoRojo);

			//repartimos el mazo del jugador2 en dos
			repartirBajaAlta( mazo2, mazoBajas,  mazoAltas);
			repartirBajaAlta( mazo2, mazoBajas,  mazoAltas);
			
			//pasamos todos los valores del mazo3 al mazo y ponemos un centinela para evitar errores y llamamos a funcion repartirParImpar para dividirlo entre par e impar.
			int g = 0, f=0;
			int total6= cuantasEnMazo(mazo3);

				while (g < total6)
				{
					mazo[g]= mazo3[f];
					f++;
					g++;
				}

			mazo[total6]=CENTINELA;
	
			//repartimos el mazo3 del jugador 3 en dos
			repartirParImpar( mazo,  izq1,  der1);

			//hacemos lo mismo que hemos hecho antes pero con el mazo4
			int s = 0, w=0;
			int total7 = cuantasEnMazo(mazo4);

				while (s < total7)
				{
					mazo[s]= mazo4[w];
					w++;
					s++;
				}

			mazo[total7]=CENTINELA;

			//repartimos el mazo4 del jugador 4 en dos .
			repartirFiguraNoFigura( mazo,  izq,  der);

			//Ya hemos hecho los ocho montones ahora hay repartirlo segun los criterios ya explicados arriba
			//Si el contador es quiere decir que ya se ha repartido dos veces antes por lo que esta es la ultima vez en la que solo se reparte el  mazo izquierdo.
	
			if (contador ==2)
			{

				cout << "El primer jugador tendra estas cartas" << endl;
				unirMazos(mazoBajas,mazoRojo); // el mazo derecho no se mueve el izquierdo es el de jugador 2

				int total10;
				int contador11 =0;
				total10 =cuantasEnMazo(mazoBajas);

					for (int i =0; i < total10; i++)
					{
						mazo1[i]=mazoBajas[i];
						contador11++;
					}

				mazo1[contador11]=CENTINELA;

				escribirMazo(mazo1);

				cout << "El segundo jugador tendra estas cartas" << endl;
				unirMazos(izq1, mazoAltas);//el mazo izquierdo le viene del jugador 3.

				int total12;
				int contador13 =0;
				total12 =cuantasEnMazo(izq1);

					for (int i =0; i < total12; i++)
					{
						mazo2[i]=izq1[i];
						contador13++;
					}

				mazo2[contador13]=CENTINELA;

				escribirMazo(mazo2);

				cout << "El tercer jugador tendra esta cartas" << endl;
				unirMazos(izq, der1);//el mazo izquierdo le viene del jugador 4
	
				int total14;
				int contador15=0;
				total14 =cuantasEnMazo(izq);

					for (int i =0; i < total14; i++)
					{
						mazo3[i]=izq[i];
						contador15++;
					}

				mazo3[contador15]=CENTINELA;

				escribirMazo(mazo3);

				cout << "El cuarto jugador tendra estas cartas " << endl;
				unirMazos(mazoNegro,der);//el mazo izquierdo le viene del jugador 1

				int total16;
				int contador17=0;
				total16 =cuantasEnMazo(mazoNegro);

					for (int i =0; i < total16; i++)
					{
						mazo4[i]=mazoNegro[i];
						contador17++;
					}

				mazo4[contador17]=CENTINELA;

				escribirMazo(mazo4);

			}//cierre del if si contador el 2

		//esta opcion se leva a cabo si el contador es 0 o 1 es decir que es la primera o segunda vez que dividen cada mazo en dos.
		else 
		{

			cout << "El primer jugador tendra estas cartas" << endl;
			unirMazos(mazoBajas,der);//mazo izquierdo del jugador 2 y el mazo derecho con el jugador 4

			int total;
			int contador1 =0;
			total =cuantasEnMazo(mazoBajas);

				for (int i =0; i < total; i++)
				{
					mazo1[i]=mazoBajas[i];
					contador1++;
				}

			mazo1[contador1]=CENTINELA;

			escribirMazo(mazo1);

			cout << "El segundo jugador tendra estas cartas" << endl;
			unirMazos(izq1, mazoRojo);//mazo derecho del jugador 1 y el mazo izquierdo del jugador 3.
	
			int total1;
			int contador2 =0;
			total1 =cuantasEnMazo(izq1);

				for (int i =0; i < total1; i++)
				{
					mazo2[i]=izq1[i];
					contador2++;
				}

			mazo2[contador2]=CENTINELA;

			escribirMazo(mazo2);

			cout << "El tercer jugador tendra esta cartas" << endl;
			unirMazos(izq, mazoAltas);//mazo derecho del jugador 2  y el mazo izquerdo del jugador 4  
	
			int total2;
			int contador3=0;
			total2 =cuantasEnMazo(izq);

				for (int i =0; i < total2; i++)
				{
					mazo3[i]=izq[i];
					contador3++;
				}

			mazo3[contador3]=CENTINELA;

			escribirMazo(mazo3);

			cout << "El cuarto jugador tendra estas cartas " << endl;
			unirMazos(mazoNegro,der1);//el mazo derecho del jugador 3 y el mazo izquierdo del jugador 1 
	
			int total3;
			int contador4=0;
			total3 =cuantasEnMazo(mazoNegro);

				for (int i =0; i < total3; i++)
				{
					mazo4[i]=mazoNegro[i];
					contador4++;
				}

			mazo4[contador4]=CENTINELA;

			escribirMazo(mazo4);

			cout << "Pulsa una tecla para continuar con el truco " << endl;//Unicamnte para que el programa se vaya parando en el truco poco a poco.
			getline(cin, tecla);

		}//cierre del else 

	contador++;

	}//cierre del while 

	cout << "El ganador es el jugador 1 , tiene escalera de color !! " << endl;
	
}

/*
*En esta funcion el mazo se repartira entre par e impar(tambien la Q que sera par y el K y el As que sean impares).
*Esta funcion llamara a cuantasEnMazo que sera el total del mazo.
*Luego llamara a darNumero que si su resto es divible entre dos es impar(al reves que lo normal ya que en darNumero por ejemplo el 2 sera el uno en la baraja).
*Al final se colocara un CENTINELA en cada mazo resultante para cerrar esos mazos y que no tengan errores.
*/

void repartirParImpar(const tMazo mazo, tMazo izq1, tMazo der1)
{

	int  contadorIzq=0,  contadorDer=0;
	int total = cuantasEnMazo(mazo);

		for (int i= 0; i < total; i++)
		{
		 
			 if (darNumero(mazo[i]) % 2 ==0)
			 {
				der1 [contadorDer]=mazo [i];
				 contadorDer++;
			}

			else 
			{
				izq1[contadorIzq]=mazo[i];
				contadorIzq++;
			}
			
		}
	
	izq1[ contadorIzq]= CENTINELA;
	der1[ contadorDer]= CENTINELA;

}

/*
*Esta funcion tendra la mision de separar en dos mazos, el mazo con figuras(Aa, K ...) y sin figuras (del 2 al 10).
*Tambien llamara a cuantasEnMazo para saber cuantas hay en el mazo.
*Y funcionara de la misma manera quela anterior pero en vez de dividirlo en dos para saber su resto, le pondremos la condion que si esta entre el 1 al 9(seria de la carta 2 a la 10) sea Nofiguras.
*Al final se cierra con una centinela para cerrar el mazo y evitar errores.
*Se utilizara un contador igual a 0 al principio para contar cuantas cartas hay en el array de cada uno.
*/

void repartirFiguraNoFigura(const tMazo mazo, tMazo izq, tMazo der)
{

	int  contadorIzq=0,  contadorDer=0;
	int total = cuantasEnMazo(mazo);

		for (int i= 0; i < total; i++)
		{
		 
			if (darNumero(mazo[i])>= 1 && darNumero(mazo[i]) <= 9)
			{
				der [contadorDer]=mazo [i];
				contadorDer++;
			}

			else 
			{
				izq[contadorIzq]=mazo[i];
				contadorIzq++;
			}
		
		}
	
	izq[ contadorIzq]= CENTINELA;
	der[ contadorDer]= CENTINELA;

}