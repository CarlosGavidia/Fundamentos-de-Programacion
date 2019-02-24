//Practica1 "Pasa la calculadora" version 3
//Autores: Carlos Gavidia Ortiz y Pedro Garcia Marcos
//Clase: Grado de Ingenieria Informatica 1C Fundamentos de la Programacion Grupo 10 Laboratorio 4
//Añadido --> color y letras y en la version 3 al crear el archivo tambien escribe letras

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip> 
using namespace std ;
const int META = 31 ;
typedef enum { nadie, automata, persona } tJugador ;
tJugador pasaCalculadora() ; // declaracion de todas las funciones 
tJugador quienEmpieza () ;
bool mismaFila(int ultimo, int nuevo) ; 
bool mismaColumna(int ultimo, int nuevo) ;
bool digitoValido(int ultimo, int nuevo , int turno) ;  
int digitoAleatorio () ; 
int digitoAutomata(int ultimo, int turno) ;    
int digitoPersona () ;
int digitoPersona (int ultimo, int turno) ;
int menu() ;
bool mostrar(string nombArch) ;
bool actInforme(int jugadas, int ganadas, int abandonos);

int main () {

	tJugador jugador ; 
	
	int opcion ;
	int abandonos = 0 , ganadas= 0 , jugadas = 0 ; // version 3 para empezar la cuenta 
	string	nombre ; 

	system( " COLOR b0 " ) ; // para cambiar el color de la letra y el fondo al ejecutar en el cmd (decorativo)
	srand ( time ( NULL  ) ) ; // semilla para elegir numeros aleatorios
	
	cout << " Bienvenido a Pasa la calculadora! " << endl ; 
	cout << " Como te llamas ? " ; 
	getline(cin,nombre) ;
	cout << " Hola " << nombre << endl ;
	opcion = menu() ; // llama a la funcion menu para elegir las 3 posibles opciones
	
	while ( opcion !=0 ) {
	
		if ( opcion == 1 ) { // cuando la opcion sea 1 que inicie el juego
			jugador = pasaCalculadora() ;
			jugadas= jugadas + 1 ; // para la version 3 ir sumando al acabar el juego
			
				if ( jugador == automata ) { // para la version 3 si gana la maquina que sume uno a ganadas por la maquina
					ganadas = ganadas + 1 ;
				}
				
				else if ( jugador == nadie ) { // para la version 3  si abandona la persona que sume uno a abandonos
					abandonos = abandonos+1 ;
				}
				
			opcion = menu (); // llama a la funcion menu para poner las opciones que se pueden elegir
		}
		
		else if ( opcion == 2 ) { // si es opcion 2 que se abra el archvio txt y se muestre en pantalla
			mostrar( "versionPC.txt") ;
			opcion = menu(); // vuelve a llamar a la funcion para mostrar las tres opciones y volverlo a elegir
		}
		
	} // fin del while	
	
	actInforme( jugadas,  ganadas,  abandonos ) ; // version 3 llama a la funcion
	cout << " Hasta la proxima " << nombre << " ( pulsa una tecla ) " ;
	cin.get()  ;
	
	return 0 ;
}

int menu() { // unicamente muestra las opciones y puedes elegir las opciones mostrando error si no es 0,1,2

	int opcion ;
	
	cout << " Selecciona una opcion: " << endl ;
	cout << " 1 - Jugar " << endl ;
	cout << " 2 - Acerca de " << endl ;
	cout << " 0 - Salir " << endl ;
	cout << " Opcion: " ;
	cin >> opcion;
	
	while ( opcion < 0 || opcion > 2 ) {
		cout << " Error . Opcion no valida "  ;
		cin >> opcion ;
	}
	
	return opcion ;
}

bool mostrar(string nombArch) { // version2 para mostrar en pantalla el archivo txt 

	char a;
	bool x;
	 
	ifstream archivo;
	archivo.open( nombArch.c_str() ) ; 
	
	if ( archivo.is_open() ) {
		archivo.get(a) ; 
		cout << a ; 
		
		while (!archivo.eof()) {
			archivo.get(a) ; 
			cout << a ; 
		}
		archivo.close() ;
		x = true ;
		
	}
	
	else {
		cout << " ERROR: No se ha podido abrir el archivo " << endl; // muestra error si no puede mostrar el txt
		x = false;
	}

	return x ; 
}

bool actInforme(int jugadas, int ganadas, int abandonos) { // version 3 
	
	int jugadas2 = 0, ganadas2 = 0 , abandonos2 = 0 ;
	bool x;
	int ejecuciones2 = 1 ;
	
	ifstream archivo ; // para leer lo que esta escrito en el txt si no esta lo crea
	archivo.open ("informePC.txt") ;
	
	if (archivo.is_open()) {
		archivo >> ejecuciones2;
		ejecuciones2 = ejecuciones2 + 1 ;
		archivo >> jugadas2 ;
		archivo >> ganadas2 ;
		archivo >> abandonos2 ;
		x = true;
	}
	
	else {
		
		x = false;
	}
	
	ofstream archivo1 ; // escribe en el txt abandonos, jugadas... Va sumando dependiendo si abandona, gana la maquina etc
	
	archivo1.open("informePC.txt") ;
	jugadas2 = jugadas2 + jugadas ; 
	abandonos2 = abandonos2 + abandonos;
	ganadas2 = ganadas2 + ganadas ;
	archivo1 << "\t" << ejecuciones2 <<  "\t";
	archivo1 << "\t" << jugadas2  << "\t" ;
	archivo1 << "\t" << ganadas2  << "\t" ;
	archivo1 << "\t" << abandonos2  << "\t"  << endl;
	archivo1 << " utilizadas " << "\t" ;
	archivo1 << " jugadas " << "\t" ;
	archivo1 << " perdidas " << "\t" ;
	archivo1 << " abandonos " << "\t" ;

	archivo.close();
	
	return x;
}
	
tJugador quienEmpieza () {	// elige aleatoriamente entre 0 y 1 si sale el primero empieza la maquina y sino la persona
	
	tJugador jugador = nadie ;
	int aleatorio = 0 ; 
	      
	aleatorio = rand() % 2 ; 
	
	if ( aleatorio == 0 ) {
		jugador = automata ;
	}
	
	else {
		jugador = persona ;
	}
	
	return jugador;
}

bool mismaFila (int ultimo, int nuevo) { // restriction a partir del segundo turno  
 
	bool digito; 
	
	if (( nuevo - 1) / 3 == (ultimo - 1) / 3) { // mira si esta en la misma fila
		digito = true ;
		
	}
	else { 
		digito = false ;
	}
	
	return digito;
}

bool mismaColumna (int ultimo , int nuevo) { // restriction a partir del segundo turno 

	bool digito ; 
	
	if (( nuevo - 1) % 3 == (ultimo - 1) % 3) { // mira si esta en la misma columna
		digito = true ;
	}
	
	else { 
		digito = false ;
	}
	
	return digito ;
}

bool digitoValido (int ultimo, int nuevo, int turno) {  // restriction a partir del segundo turno 

	bool digito ;
	
	if (turno == 0 ) {
		digito = true;
	}
	else if ((( ultimo != nuevo) && (mismaFila(ultimo, nuevo) || mismaColumna (ultimo,nuevo))) || (nuevo ==0))  {
		digito= true; // mira si este la misma fila y columna y que sea distinto al ultimo puesto si cumple estos requisitos devulve true 
	}
	
	else {
		digito = false ; 
	}
	
	return digito ;
}
	
int digitoAleatorio () { // devulve un digito y elige un numero aleatorio enre 0 y 9

	int digito ;
   
	digito = (rand() % 9) + 1 ;
	
	return digito;
}

int digitoPersona () { // funcion para saber si el numero esta entre el 0 y 9 
   
	int resultado ; 
	
	cout << " Introduce un digito (0 para abandonar): " ; 
	cin >> resultado ;
	
	while  ((9< resultado) || (resultado <0) == true) { // si el digito es mayor que 9 o menor que 0 sevolvera a pedir otro numero	
		cout << " Digito no valido . Introduce un digito del 1 al 9 (0 para abandonar): " ; 
		cin >> resultado ;
	}
	
	return resultado ;
} 

int digitoAutomata (int ultimo, int turno) { // funcion para cuando le toque a la maquina poner un  numero con restricciones
	                                         // he añadido una variable turno a esta funcion para que el juego funcione a traves de turnos
	int digito2 ;
	
	digito2 = digitoAleatorio (); // el digito que coja sera a partir de llamar la funcion de digitoAleatorio()
	
	while (digitoValido(digito2, ultimo, turno ) == false) { // para cuando la maquina de un numero que no cumpla los requisitos volvera a hacer otro numero aleatorio
		
		digito2 = digitoAleatorio ();
	}
	
	cout << " Yo pulso: " << digito2 << endl ;

	return digito2 ;
}	
		
int digitoPersona (int ultimo, int turno) { // para cuando sea el turno de la persona 
	                                        // he añadido una variable turno a esta funcion para que el juego funcione a traves de turnos
	int resultado ;
	
	cout << " 7  8  9 " << endl ;
	cout << " 4  5  6 " << endl ;
	cout << " 1  2  3 " << endl ;
	resultado = digitoPersona (); // la persona pone un numero que se comprueba que este entre 0 y 9 la funcion de digitoPersona()
	
	while (digitoValido(ultimo, resultado, turno )== false) { // devolvera false si el numero no respeta las condiciones
		cout << " Error: tiene que ser distinto de " << resultado << " y estar en la misma fila o columna " << endl;
		resultado = digitoPersona() ;
	}
	
	return resultado;
} 
	
tJugador pasaCalculadora ()	{ // funcion por la que se desarrollara la mayor parte del proceso y la mas importante ( une a la mayoria de las funciones )
	int turno = 0; // turno empieza en cero y a medida que vaya avanzando van aumentando los turnos
	int nuevo = -1 ;
	int ultimo = -1  ;
	int suma= 0 ;
	tJugador jugador = quienEmpieza() ; // llama a la funcion quienEmpieza para saber quien empieza

	if (jugador == automata) {
		cout << " Empiezo yo " << endl ;
	}
	
	else {
		cout << " Empiezas tu " << endl ;
		}
	
	while (suma < META && nuevo !=0 ) { // termina cuando la suma de los digito iguale o sumere 31
	
		if (jugador == persona) { // cuando sea turno de la persona que llame a esa funcion y que sume los digitos anteriores
			ultimo = nuevo ;
			nuevo = digitoPersona(ultimo, turno) ;
			turno++; // sumador de turnos
				if (nuevo !=0) {
					suma = suma + nuevo;
					cout << " Suma : " << suma << endl ;
					jugador = automata ;
				}
				
				else { // si pulsas 0 para abandonar
					cout << " Has abandonado . Hasta la proxima ! " << endl ;
					jugador = nadie ;
				}
				
		} 
		
		else { // cuando el turno sea de la maquina que tambien sume los digitos anteriores 
	
			ultimo = nuevo ;
			turno++;// sumador de turnos
			nuevo = digitoAutomata(ultimo, turno) ;
			suma = suma + nuevo ;
			cout << " Suma : " << suma << endl ;
			jugador = persona ;
		}
		
	} // fin del while
	
	if (suma >= META) { // cuando sea igual o mayor que 31 la suma de todos los digitos anteriores 
	
		if (jugador == automata) {
			cout << " Has perdido , la maquina ha ganado ! " << endl ;
		}
		
		else {
			cout << " Enhorabuena has ganado! " << endl ;
		}
		
	} 
	
	return jugador ;
}