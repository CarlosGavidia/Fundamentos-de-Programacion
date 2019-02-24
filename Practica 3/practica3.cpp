/* 
*FUNDAMENTOS DE PROGRAMACION
*Practica 3 : "2048"
*Autores : Carlos Gavidia Ortiz y Pedro Garcia Marcos
*Grado Ingenieria Informatica 1 C 
*Universidad Complutense de Madrid
*Clase 9
*Grupo 10
*/

/*Biblioteca incluidas */
#include <iostream >
#include <windows.h> // para el color del tablero
#include <string >
#include <cstdlib> 
#include <ctime>
#include <iomanip >
#include <fstream >
#include <conio.h> // para leer las teclas especiales
#include <assert.h> //para asserciones evitar errores

/*Espacios de nombres usados*/
using namespace std;

/*Constantes utilizadas*/
const int N = 4 ;

/*Constantes utilizadas para dibujar el tablero */
const char ESQ_SUP_IZQ = char (218);
const char ESQ_INF_IZQ = char (192);
const char ESQ_SUP_DER = char (191);
const char ESQ_INF_DER = char (217);
const char RAYA_HOR = char (196);
const char RAYA_VER = char (179);
const char UNION_HOR_ARRIBA = char (194);
const char UNION_VER_IZQ = char (195);
const char UNION_HOR_ABAJO = char (193);
const char UNION_VER_DER = char (180);
const char UNIO_CUATRO = char (197);

/*Array multidimensional(tablero) */
typedef int tTablero[N][N];

/*Enumerado de movimientos(accion)*/
typedef enum { Arriba, Abajo, Derecha, Izquierda, Salir , Nada}tAccion;

/*Estructura(puntos) con las variables nombre y puntos totales.
Dentro de un array(ficha) de capacidad 100 (para evitar errores al almacenar los puntos).
Otra estructura (lista) con el entero contador para llevar la cuenta . */
typedef struct{
	string nombre;
	int totalPuntos;
}tPuntos;

typedef tPuntos tFicha[100];

typedef struct{
	tFicha ficha;
	int contador ;
}tLista;

/*Prototipos de las funciones defidas*/
void setBackgroundColor(int color);
void inicializa(tTablero tablero);
void visualiza(const tTablero tablero, int puntos, int totalPuntos);
int log2(int num);
void carga(tTablero tablero, int &totalPuntos, bool &ok);
tAccion leeAccion();
void mueveFichas(tTablero tablero, tAccion accion);
int mayor(const tTablero tablero);
bool lleno(const tTablero tablero);
void combinaFichas(tTablero tablero, tAccion accion, int &puntos);
void nuevaFicha(tTablero tablero);
void guarda(const tTablero tablero, int  totalPuntos);
void nuevoRecord(int totalPuntos, tLista &lista);
void actualizar (tLista &lista);
void muestraRecords();
void buscar (tTablero tablero,int &contF, int &contC  );

/*
*En la funcion main:
*Primero se preguntara al usuario si desea cargar un archivo de texto para ello el usuario debera introducir s o S, en ese caso llamara a la funcion carga(tablero,totalPuntos,ok).
*En caso negativo se pondran todas las casillas a 1 (ya que es el resultado de 2 elevado a 0 es 1 que se utilizara para el color), y se llamara a la funcion de inicializa( tablero).
*A continuacion se llamara a la funcion de visualiza(tablero,puntos,totalPuntos), para mostrar las casillas.
*Luego se pedira al usuario la accion que desea hacer llamando a la funcion de leeAccion().
*A partir de aqui se inciara un bucle que no llegara a su fin hasta que el usuario no le de al ESC (accion 4) , no se llege a la ficha 2048, o no este lleno.
*Dentro del bucle empezara llamando a la funcion de mueveFichas( tablero, accion), para mover las fichas segun la accion que haya dado el usuario antes.
*Llamara a la funcion de combinaFichas( tablero, accion, puntos) para combinar las fichas que esten juntas y sean iguales y dependiendo la accion del usuario de antes.
*Incluira una nueva ficha en el array llamando a la funcion de nuevaFicha( tablero).
*Luego borrara lo que haya en la panalla con system("cls") para dar un tono mas visual.
*Llamando otra vez a visualiza(tablero,puntos,totalPuntos) para volver a mostrar la tabla pero actualizando el totalPuntos y los puntos.
*Si el usuario llega a 2048 se llamara a nuevoRecord(totalPuntos, lista) y a muestraRecords() para mostrarlo por pantalla.
*Si el tablero esta lleno , y no se puede combinar ninguna ficha del tablero tambien se acabara el programa.
*Si el usuario pulsa ESC se le preguntara si quiere guardar partida, en caso afirmativo se llamara a la funcion de guarda( tablero,  totalPuntos) para guardar.
*/

int main()
{

	tTablero tablero;
	tLista lista;
	tAccion accion;

	string adios; // para quitar el system("pause ")
	bool ok, encontrado = true;//inicializamos que encontrado sea true , es decir que hay combianciones posibles
	char respuesta, respuesta1;
	int puntos, totalPuntos, contF, contC;//las dos ultimas son variables pasadas por referecia de la funcion buscar , para saber si hay combianciones en filas y columnas  

	puntos =0;
	totalPuntos =0;

	srand(time(NULL)); //semilla para generar numero aleatorios
	
	//cargamos el archivo donde esta una partida guardada o si no existe se pone todo el tablero a 1 es decir nada , salvo dos baldosas.
	cout << "Desea cargar una partida (S/N)" << endl;
	cin >> respuesta1;

		if (respuesta1== 's'||respuesta1== 'S') // por si el usuario pulsa minuscula o mayuscula
		{
			carga(tablero,totalPuntos,ok);
		}

		else 
		{
			for (int i =0; i < N ; i++)
			{
				for (int j =0; j < N ; j++)
				{
					tablero[i][j]=1; // recorrido de todo el array se pone a 1 no a 0 (por que es el resultado de 2 elevado a 1)
				}
			}

			inicializa( tablero);
		}
	
	visualiza(tablero,puntos,totalPuntos);
	accion = leeAccion();

		while((accion !=4) && (mayor (tablero)!= 2048) && (encontrado) )
		{
			mueveFichas( tablero, accion);//primero se moveran en esa direcciom
			combinaFichas( tablero, accion, puntos);//leugo si hay dos iguales se combina
			mueveFichas( tablero, accion); //se vuleve a mover para que no queden huecos
			
			system("cls");

			totalPuntos = puntos + totalPuntos ;
				
				//si el tablero no esta lleno hay una nueva ficha 
				if (!lleno (tablero))
				{
					nuevaFicha( tablero);
				}


			visualiza(tablero,puntos,totalPuntos);
			
				//si el tablero no esta lleno o no se llega 2048 que pida la accion al usuario.
				if ((mayor (tablero)!= 2048) && (!lleno (tablero )))
				{
				
					accion = leeAccion();
				
				}
				
			//si esta lleno intentara encontrar una combiancion posible si es asi devuelve true
			if (lleno (tablero))
			{
				//llamara a la funcion de buscar para saber si hay combianciones en filas o columnas o las dos cosas cuando el tablero este lleno
				buscar ( tablero,contF, contC  );

				encontrado = false;
				int i =0;
				int j ;
				
				//En caso de que cuando este lleno el tablero haya combinaciones tanto en filas como en columnas el usuario podra pulsar cualquier tecla menos nada si no entrara en bucle
				if (contF >0 )//si el contador de filas es mayor que 0 quiere decir que hay combiancion en cualquier fila del tablero
				{

					if (contC >0)// lo mismo pasa con las columnas
					{

						accion= leeAccion();

							//cuando la accion sea nada entrara en bucle que no saldra hasta que no sea otro de los enumerados
							while (accion == 5 )
							{

								accion= leeAccion();

							}

							//si es una direccion de las anteriores devuelve true, ya que la ha encontrado
							if (accion == 0 )
							{

								encontrado = true;

							}
							else if (accion == 1)
							{

								encontrado = true;

							}

							else if (accion == 4)
							{
								encontrado = true;

							}
							else if (accion == 2)
							{

								encontrado = true;

							}
							else if (accion == 3)
							{

								encontrado = true;

							}
					}//fin del if del contador de columnas

				}//fin del if de contador de filas 
				
				//si se ha encontrado una combinacion entrara en bucle que no saldra de el hasta que no meta una direccion correcta
				while (  (i <N-1) && !encontrado )
				{
					j =0;
					while ( (j < N) && !encontrado )
					{
						//si la ficha es igual en la misma columna  y solo existe combinacion en las filas y no hay posibles combianciones en las filas 
						if (tablero[i][j]== tablero[i+1][j] && contF ==0)
						{

							accion= leeAccion();

							//no saldra del bucle hasta que sea arriba , abajo o salir
							while (accion != 0 && accion != 1 && accion != 4 )
							{

								accion= leeAccion();

							}

							//si es una direccion de las anteriores deuleve true, ya que la ha encontrado
							if (accion == 0 )
							{

								encontrado = true;

							}
							else if (accion == 1)
							{

								encontrado = true;

							}

							else if (accion == 4)
							{
								encontrado = true;

							}

						}//fin del if de igualdad
					
						else //en caso de no encontrar combiancion en la misma fila se aumenta 
						{
							j++;
						}

					}//fin del for de las filas
				 
					if (!encontrado) //si no se ha encontrado en la misma columna
					{
						i++;
					}

				}//fin del for de las columnas 
				
				//ahora recorrera las filas
				int h =0;
				int k ;

				while( (h <N) && !encontrado  )
				{
					k =0;
					while ( ( k < N-1) && !encontrado  )
					{
						
						//en caso de que sea iguales en la misma fila  y no hay combinaciones posibles en las columnas 
						if (tablero[h][k]== tablero[h][k+1] && contC ==0)
						{

							accion= leeAccion();

							//hasta que la accion no sea derecha , izquierda o salir que no salga del bucle 
							while (accion != 2 && accion != 3 && accion != 4 )
							{
								accion= leeAccion();
									
							}

							if (accion == 2 )
							{

								encontrado = true;

							}
							else if (accion == 3)
							{

								encontrado = true;

							}
							else if (accion == 4)
							{

								encontrado = true;

							}
				
						}//fin del if de igualdad
			
						else 
						{
							k++;
						}
					}//fin del for de filas
	
					if (!encontrado)
					{
						h++;
					}
				}//fin del for de las columnas 

			}//fin del if si esta lleno el tablero	
		
		}//fin del while (hasta que el mayor sea 2048, se pulse esc o no se pueda mover ninguna ficha)

		if ( mayor (tablero)== 2048)// si la casilla mas alta es 2048
		{
			cout << "Fin del juego has ganado !! " << endl;
			nuevoRecord(totalPuntos, lista);
			muestraRecords();
		}

		else if (!encontrado)// en caso de que no se haya encontrado posible combiancion terminara
		{
			cout <<"No puedes mover ninguna ficha mas . Has perdido " << endl;
		}

		else if (accion == 4 )// si el usuario pulsa ESC
		{
			cout << "Has abandonado.quieres guardar la partida (S/N)? " << endl;
			cin >> respuesta;

			if (respuesta == 's'||respuesta== 'S')
			{
				guarda( tablero,  totalPuntos);

				cout << "Has guardado la partida " << endl;
				cout << "Hasta la proxima !!" << endl;
			}

			else 
			{
				cout << "Hasta la proxima !!" << endl;
			}
		}

	cin.sync();//borra lo que haya en el bufer 
	cout << "Presiona Intro para salir..." ;
	getline (cin, adios);// por si el usuario mete espacios
	
}

/*
*En la funcion de carga pedira el nombre del archivo al usuario.
*En caso de que existeiese ese archivo, primero leera la dimension , seguira si la dimension del codigo y la del archivo sean distintas(el programa esta echo para visualizar cualquier dimension siempre que se cambien en ambos lados).
*Despues iniciara el array en la primera posicion e ira metiendo todos los numeros que se encuntre en el archivo.
*Cuando se llene querra decir que el numero que va a leer a continuacion son los puntos totales que llevaba el usuario en otra partida (hemos cambiado  el parametro por referencia puntos por totalPuntos por que nos liaba ).
*El ultimo numero lo guardara en totalPuntos (por referencia ).
*En caso de que no coincida la dimension del codigo con la del archivo saltara un error al tner un assert que regule la dimension.
*Tambien se utiliza el booleano ok para saber si true si se carga correctamnete o false en caso contrario.
*En caso de que el usuario introduzca un archivo que no existe se devuleve false y se iniacia un tablero a 1 llama a la funcion incializa para elegir dos casillas al azar para empezar la partida desde 0.
*/

void carga(tTablero tablero, int &totalPuntos, bool &ok)
{

	int numero;
	string nombre;

	ifstream archivo;

	cin.sync();//para borrar lo que haya en el bufer
	getline(cin, nombre);

	archivo.open(nombre );

		if (archivo.is_open())
		{
			archivo >> numero;
			assert (numero == N );//que salte error cuando la dimension del codigo y del archivo no coincida,

			while (!archivo.eof())
			{
				if (numero==N)
				{
					archivo >> numero; //seguira leyendo el siguinete numero

					for (int i =0; i < N ; i++)
					{
						for (int j =0; j < N ; j++)
						{
							tablero[i][j]= numero;//y lo guardara en todas las posiciones del array
							archivo >> numero;
						}
					}

					archivo >> numero; //despues de llenarse el array leera los puntos y los guarda en totalPuntos
					totalPuntos = numero;
					ok = true; // si se ha podido abrir y leer bien el archivo 
				}
				
			}

			archivo.close();
		
		}
	
		else //en caso de no existir ese archivo o no poder cargarse
		{
			ok = false ;
		
			cout << "No se ha podido cargar el archivo " << endl;
			cout << "Se iniciara una nueva partida " << endl;

			//se pondra todas las casillas del array a 1.Y se llamara a incializa para situar dos fichas al azar en el tablero (lapartida empezara desde el principio)
			for (int i =0; i < N ; i++)
			{
				for (int j =0; j < N ; j++)
				{
					tablero[i][j]=1;
				}
			}

			inicializa( tablero);

		}

}

/*
*En esta funcion se cogeran dos casillas del array al azar y se pondran a 2 (85% de posibilidad )o 4 (el resto).
*No pueden coincidir dos 4.
*Y solo se ejecutara esta funcion si no se ha podido cargar el archivo o el usuario no quiere entones empezara una partida nueva.
*Pimero se cogen fila y columna al azar , este proceso se repite otra vez para la otra ficha pero si coinciden la posicion volvera a hacer otras dos posiciones al azar.
*Se coge otro numero entre 1 y 100, que si es mayor que 95 sera cuatro y si no 2 (esto se hace por el porcentaje).
*Si el numero que sale es el 4 el siguiente tendra que ser el 2 .
*/

void inicializa(tTablero tablero)
{

	int fila , columna, fila1 , columna1 , numero , numero1;

	// se coge al azar la fila y columna de numero estre el 0 y el 3 
	fila = rand() % (4);
	columna = rand() % (4);

		//esta condicion no suele darse ,pero si hay un numero mayor  que 1 es decir una ficha volvera a repetir el proceso anterior, hasta que sea diferente posicion.
		while (tablero[fila][columna]> 1)
		{
			fila = rand() % (4);
			columna = rand() % (4);
		}
	
	//se volvera a hacer con la otra ficha (eligiendo tambien fila y columna al azar).
	fila1 = rand() % (4);
	columna1 = rand() % (4);

		//si coinciden fila y columna volvera a repetir los numero hasta que las posiciones sean diferentes.
		while ((fila1 == fila) && (columna1 == columna))
		{
		
			fila1 = rand() % (4);
			columna1 = rand() % (4);
		}
	
		//en este bucle pasa lo mismo que lo dicho anteriormente , si ocurre que hay una ficha en la posicion elgeida volvera a elegir otros numeros.
		while  (tablero[fila1][columna1]> 1)
		{
			fila1 = rand() % (4);
			columna1 = rand() % (4);
		}
	
	//Una vez elegida la posicion queda elegir si es 2 o 4.
	//Primero se cogera un numero entre 1 y 100
	numero = (rand() % 100) + 1;

		//si es menor que 95 es 2 
		if (numero <= 95)
		{
			tablero[fila][columna]=2;

			numero1 = (rand() % 100) + 1;// se cogera un numero para la otra ficha

			//pondremos la misma condicion
			if (numero1 <= 95 )
			{
				tablero[fila1][columna1]=2;
			}

			// En caso de que sea mayor de 95 es 4
			else
			{
				tablero[fila1][columna1 ]=4;
			}

		}

		//por el contrario si ha salido en la primera vez un 4 la siguinte dentra que ser un 2 (ya que no se pude repetir el numero)
		else 
		{
			tablero[fila][columna]= 4;
			tablero[fila1][columna1]=2;
		}

}

/*
*Esta funcion calculara el exponente de un numero, para que el resultado que sera el exponente servira a la funcion de color para colorear las casillas.
*Primero la suma (lo que se va a devolver ) sera 1 para que sea un color difrente de negro.
*En caso de que el numero sea 1 es decir que 2 elevado a 0 es 1 (no hay nada en la casilla) se devuelve 0 para que se pinte de negro.
*Si es mayor que dos se cogera el cociente de el numero entre dos y se aumenta el contador (lo que querra decir es que si el numero de la casilla es 4 se divide entre 2 , la suma ya sera 2 y 2 se divide otra vez entre dos , la suma sera 3 que es el color verde ).
*Al final se devolvera el contador que indicara el color de la casilla.
*/

int log2(int  num)
{
	int suma =1;

		if (num == 1 )
		{
			suma =0;
		}

		while (num >2 )
		{
			num = num/2;
			suma++;
		}
	
	return suma;
}

/*
*Esta funcion sera la encargada de poner color en las casillas.
*Usara la funcion log2 para coger el exponente de cada numero con el cual generara un color diferente, sera negro para las casillas en las que no haya nada.
*/

void setBackgroundColor(int color) 
{
	
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));

}

/*
*Esta funcion dibujara el tablero en la dimension que haya elegido el usuario.
*Al principio dibujara la parte superior del tablero(la primera raya).
*Luego entrara en un bucle para dibujar N-1 casillas horizontales tenga en tablero.
*Y las ultimas casillas horizontales (no podran meterse en el anterior bucle ya que la raya del final no coincide con las del medio).
*Al final se dibujara la raya horizontal de abajo.
*Dentro de cada casilla se debera comprobar si hay un numero (mayor que 1 ) para pintar y que se muestre por pantalla.
*En caso de no haberlo saltara a la siguinte casilla.
*Tambien arriba pondran los puntos echos en ese turno y los totales.
*/

void visualiza(const tTablero tablero, int puntos, int totalPuntos)
{
	
	int color, num , bucle =0;
	
	cout << setw(7)<< puntos << setw(12) << " Total   " << totalPuntos << endl;

	//Apartir de aqui se dibuja la raya de arriba
	cout << ESQ_SUP_IZQ ;
		
		//se hara un bucle para que se escriba 6 veces la raya en horizontal
		for (int i =0 ; i < N-1; i++)
		{
			for (int j =0; j< 6; j++)
			{
				cout << RAYA_HOR;
			}

			cout << UNION_HOR_ARRIBA ;// union de dos casillas
		}

		//este se deja fuera del bucle ya que el final no es igual este el la esquina.
		for (int q =0; q < 6 ; q ++)
		{
			cout << RAYA_HOR;
		}

		cout << ESQ_SUP_DER << endl;
		
		//Apartir de aqui se dibujan las casillas horizontales N-1(expecto la ultima).
		while (bucle < N-1)
		{
			cout << RAYA_VER;
			
			//se dibuja la primera parte de la casilla (donde todavia no este el numero).
			for (int r =0; r < N ; r++)
			{

				//cuando en la casilla sean mayores que 1 llama a la funcion de log para sacar el numero, luego para el color para dibujar el color.
				//este color se dibujara hasta 6 espacios y luego se pondra en negro y la raya para separar las casillas.
				if (tablero[bucle][r]>1)
				{
					num = tablero[bucle][r];
					color= log2(num);
					setBackgroundColor(color);	
					cout << setw(6) <<  " ";
					setBackgroundColor(0);
					cout << RAYA_VER;
				}

				//en caso de que el numero sea 1 no se pinta y se corre 7 espacios y se dibuja la raya vertical.
				else 
				{
					cout << setw(7) << RAYA_VER ;
				}

			}

			cout << endl;
			
			//empezamos a dibujar la mitad de la casilla donde esta el numero.
			cout << RAYA_VER ;
		
			for (int r =0; r < N ; r++)
			{
				//tendra la misma estructura que el anterior solo que añadiendo el numero que haya en el arrya si es mayor que 1.
				//Se debera dejar un espacio menos ya que el numero ocupa un espacio.
				if (tablero[bucle][r]>1)
				{
					num = tablero[bucle][r]; 
					color= log2(num);
					setBackgroundColor(color);
					cout << setw(5) << tablero[bucle][r]  << " " ;
					setBackgroundColor(0);
					cout << RAYA_VER;
				}

				else 
				{
					cout << setw(7) << RAYA_VER ;
				}

			}

			cout <<  endl;
			
			//empezamos a dibujar la parte baja de la casilla (igual que la primera , tambien sin el numero)
			cout << RAYA_VER ;
			
			//esta parte se haria igual que la primera.
			for (int r =0; r < N ; r++)
			{

				if (tablero[bucle][r]>1)
				{
					num = tablero[bucle][r];
					color= log2(num);
					setBackgroundColor(color);	
					cout << setw(6) << " ";
					setBackgroundColor(0);
					cout << RAYA_VER;
				}

				else 
				{
					cout << setw(7) << RAYA_VER;
				}

			}

			cout << endl; 

			//por ultimo el borde que las separa 
			cout << UNION_VER_IZQ;

			for (int i =0 ; i < N-1; i++)
			{
				for (int j =0; j< 6; j++)
				{
					cout << RAYA_HOR;
				}

				cout << UNIO_CUATRO;
			}

			for (int q =0; q < 6 ; q ++)
			{
				cout << RAYA_HOR;
			}

			cout << UNION_VER_DER << endl;


			bucle++;

		}

	//La ultima fila 
	cout << RAYA_VER ;
	
	//los tres for que estan a continuacion son iguales que los del bucle pero al ser el final de las filas de la ultima y las de en medio diferente se saca fuera.
		for (int r =0; r < N ; r++)
		{

			if (tablero[N-1][r]>1)
			{
				num = tablero[N-1][r];
				color= log2(num);
				setBackgroundColor(color);	
				cout << setw(6) << " ";
				setBackgroundColor(0);
				cout << RAYA_VER ;
			}

			else 
			{
				cout << setw(7) << RAYA_VER ;
			}

		}

	cout << endl;

	cout << RAYA_VER ;
		
		for (int r =0; r < N ; r++)
		{

			if (tablero[N-1][r]>1)
			{
				num = tablero[N-1][r];
				color= log2(num);
				setBackgroundColor(color);
				cout << setw(5) << tablero[N-1][r] << " " ;
				setBackgroundColor(0);
				cout << RAYA_VER ;
			}

			else 
			{
				cout << setw(7) << RAYA_VER ;
			}

		}

	cout <<  endl;

	cout << RAYA_VER ;
	
		for (int r =0; r < N ; r++)
		{

			if (tablero[N-1][r]>1)
			{
				num = tablero[N-1][r];
				color= log2(num);
				setBackgroundColor(color);	
				cout << setw(6) << " " ;
				setBackgroundColor(0);
				cout <<  RAYA_VER ;
			}

			else
			{
				cout << setw(7) << RAYA_VER ;
			}

		}

	cout << endl;

	cout << ESQ_INF_IZQ ;

		for (int i =0 ; i < N-1; i++)
		{

			for (int j =0; j< 6; j++)
			{
				cout << RAYA_HOR;
			}

			cout << UNION_HOR_ABAJO ;
		}

		for (int q =0; q < 6 ; q ++)
		{
			cout << RAYA_HOR;
		}

	cout << ESQ_INF_DER << endl;

	cout << "Usa las teclas de flecha (Esc para salir) " << endl;
	
}

/*
*En la funcion leeAccion , devolvera la accion que haya metido el usuario siempre que no sea Nada (es decir teclas que no sean las fecjas o Esc).
*Primero inicializamos accion a Nada, para que no salga del bucle hasta que no introduzca un valor distinto de tal.
*Dependiendo de la direccion el programa adjudicara accion a un valor.
*Si el 27 sera salir .
*En caso de no ser ninguna direccion de las dadas se considera como letra distinta de estas y no saldra del bucle hasta introducir flechas o esc.
*/

tAccion leeAccion()
{

	tAccion accion;
	int dir;

	accion = Nada;
	cin.sync();

		while (accion == Nada )
		{
				dir =_getch();

				if (dir == 0xe0) 
				{
					dir = _getch();
		
					if (dir == 72)
					{
						accion = Arriba;
					}

					else if (dir ==80)
					{
						accion = Abajo;
					}

					else if (dir == 77)
					{
						accion = Derecha ;
					}

					else if (dir == 75)
					{
						accion = Izquierda;
					}
	
				}

				else if (dir == 27)
				{
					accion =Salir;
				}

				//en caso de no ser nada de lo anterior se considera como Nada.
				else 
				{
					accion = Nada;
				}
	
		}
	
	return accion;
}

/*
*En esta funcion se moveran las fichas en la dirrecion que haya indicado el usuario en la funcion anterior.
*Dependiendo de la accion , se inciariara un recorrido por todo el array, en el que si la sicha es menor que 2, es decir no hay ficha se correra un espacio en tal direccion.
*Y la posicion anterior donde etsaba la ficha antes de cambiar su posicion sera 1 , es decir no habra ficha.
*Aunque se podria haber generalizado con el bucle y dentro de este poner la accion ,hemos preferido este metodo ya que nos resultaba menos lioso.
*/

void mueveFichas(tTablero tablero, tAccion accion)
{
	
	int o =0, j =0, g=0, k =0;
		
		//hacia arriba
		if (accion == 0)
		{
			while (o < N-1)//repetira el bucle N-1 veces para juntar todas las fichas en esa dimension
			{
				for (int i =0; i < N-1 ;i++)//empezara de la posicion 0,0 hasta N-1 àra no salirse del array.
				{
					for (int j =0; j < N ;j++)// las filas si llegaran a todas ya que lo que se va a cambiar seran las columnas 
					{
						if (tablero[i][j]< 2 ) 
						{

							tablero[i][j]= tablero[i+1][j];//al ser hacia arriba si no habia nada en i esa posicion sera ocupada por i+1
							tablero[i+1][j]= 1;	//i+1 sera 1 no habra ninguna ficha
						}
				
					}

				}
			o++;
			}
		}

		//hacia abajo
		else if (accion == 1 )
		{
			while (j < N-1)
			{
				for (int i =N-1; i > 0 ;i--)//al ser para abajo lo hara al reves desde 3,3 pero no llegara la la primera para no salirse del array
				{
					for (int j =N-1; j >=0 ;j--)
					{
						if (tablero[i][j]< 2 )
						{

							tablero[i][j]= tablero[i-1][j];//si no hay una ficha en i entonces ocupara su lugar en i-1
							tablero[i-1][j]= 1;// e i-1, j sera 1 , no habria ficha
						}

					}

				}
			j++;
			}

		}

		//hacia la derecha
		else if (accion == 2 )
		{
			while (g < N-1)
			{
				for (int i =N-1; i >= 0 ;i--) //empezara desde 3,3 
				{
					for (int j =N-1; j >0 ;j--)// no llegara a la primera ya que si no se saldria del array
					{
						if (tablero[i][j]< 2 )
						{

							tablero[i][j]= tablero[i][j-1];//en caso de que que no hubiera nada  se pasaria j-1 a el lugar de j
							tablero[i][j-1]= 1;	// y j-1 a 1 para no haber ficha
						}
				
					}

				}
			g++;
			}
		}

		//hacia la izquierda
		else if (accion == 3 )
		{
			while (k < N-1)
			{
				for (int i =0; i < N ;i++) // empezara desde 0,0
				{
					for (int j =0; j < N-1 ;j++)// hasta N-1 para no salirse del array
					{
						if (tablero[i][j]< 2 )
						{

							tablero[i][j]= tablero[i][j+1];// si no hay nada  se pasa j+1 a j
							tablero[i][j+1]= 1;	// y j+1 se deja sin niguna ficha
						}
				
					}

				}
			k++;
			}

		}
	
}

/*
*Esta funcion combina las fichas que esten juntas dependiendo de la accion que haya dado el usuario.
*Dependiendo de la accion se sumaran las fichas se guardara en puntos el resultado y la casilla anterior se pondra a 1.
*Simpre que en esa casilla sea mayor que 1 y sean igual empezara la condicion.
*/

void combinaFichas(tTablero tablero, tAccion accion, int &puntos)
{
	
	puntos =0;//empezara en 0 luego se pasar por parametro de referencia
		
		//hacia arriba
		if (accion ==0)
		{
			for (int i =0; i < N-1 ; i++)// N-1 para no salirse del array
			{
				for (int j =0; j < N ; j++)
				{

					if ((tablero[i][j]> 1 && tablero[i+1][j]> 1)&& (tablero[i][j]== tablero[i+1][j])) // siempre que sea iguales y mayores que 1
					{

						tablero[i][j]= tablero[i][j]+tablero[i+1][j]; // se sumaran las casilla de abajo con la de arriba 
						tablero[i+1][j]= 1; // la anterior se pondra a 1
						puntos =tablero[i][j]; //se guarda los puntos obtenidos

					}
				}
			}
		}

		//hacia abajo
		else if (accion ==1 )
		{
			for (int i =N-1; i >0; i--) // empezara desde abajoy no llegara a todos para no salirse del array
			{
				for (int j =N-1; j  >= 0 ; j--)
				{
					if ((tablero[i][j]> 1 && tablero[i-1][j]> 1)&& (tablero[i][j]== tablero[i-1][j]))// cuando se cumpla esta condicion
					{

						tablero[i][j]= tablero[i][j]+tablero[i-1][j];// se suma la casilla con el de arriba 
						tablero[i-1][j]= 1;// el de arriba se deja a 1 
						puntos = tablero[i][j];// se guarda el resultado
					
					}
				}
			}
		}

		//hacia la derecha
		else if (accion == 2 )
		{
			for (int i =N-1; i >=0 ; i--)//empeiza por el final
			{
				for (int j =N-1; j >0 ; j--)// solo igual a 0  para no salirse del array
				{
					if ((tablero[i][j]> 1 && tablero[i][j-1]> 1)&& (tablero[i][j]== tablero[i][j-1]))
					{

						tablero[i][j]= tablero[i][j]+tablero[i][j-1]; // la casilla actual se suma con la de la izquierda
						tablero[i][j-1]= 1;// la actual se deja a 1 
						puntos = tablero[i][j];// se guarda el resultado
					
					}
				}
			}
		}

		//para la izquierda
		else if (accion ==3)
		{
			for (int i =0; i < N ; i++)
			{
				for (int j =0; j < N-1 ; j++)// N-1 para no salirse del array
				{
					if ((tablero[i][j]> 1 && tablero[i][j+1]> 1)&& (tablero[i][j]== tablero[i][j+1]))
					{

						tablero[i][j]= tablero[i][j]+tablero[i][j+1];// se suma la casilla de la derecha con la actual
						tablero[i][j+1]= 1;// la  de la derecha se deja a 1 
						puntos = tablero[i][j];// se guarda el resultado
					
					}
				}
			}
		}
	
}

/*
*En esta funcion generara una nueva ficha 2 (95%)o 4 (el resto).
*Esta funcion se llamara despues de combinar las fichas.
*Primero se elige una fila y columna al azar pero si coincide con una casilla donde ya hay un numero se metera en bucle que no saldra  hasta que sean diferentes
*Se coge un numero entre 1 y 100 si es menor que 95 es 2 sino 4.
*/

void nuevaFicha(tTablero tablero)
{
	int fila, columna, numero;

	fila = rand() % (4);
	columna = rand() % (4);

		while  (tablero[fila][columna]> 1 )// en caso de que coincidad con una casilla que haya un numero
		{
			fila = rand() % (4);
			columna = rand() % (4);
		}
	
	numero = (rand() % 100) + 1;

		if (numero <= 95)
		{
			tablero[fila][columna]=2;
		}

		else 
		{
			tablero[fila][columna]= 4;
		}

}

/*
*Esta funcion se encargara de devolver un bool si esta lleno el tablero o no.
*Emperzara llamando bool como true, y recorriendo todo el array si hay una casilla que sea menor que 2 es decir si esta vacia devuelve false que querra decir que no esta lleno.
*Es una busqueda cuando encuentre un valor menor que 1 completo es false , es decir no es lleno se sale del bucle y devuelve el valor completo.
*/

bool lleno(const tTablero tablero )
{
	bool completo= true;
	int i =0, j;
	
		while ( (i <N) && completo )
		{
			j =0;

			while ( (j <N)  && completo )
			{
				if (tablero[i][j]< 2 )
				{
					completo = false;// si hay una casilla que sea 1 , no esta completo y devuelve false y se sale
				}

				else 
				{
					j++; // si no lo encuntra que siga buscando en la misma fila
				}

			}

			if (completo)
			{
				i++; // pasa a la otra columna si no lo encuentra
			}
			
		}
	
	return completo;
}
/*
*En esta funcion sirve para buscar las combinaciones que haya en filas, columnas o las dos.
*Utiliza dos parametros por referencia, una contF , que cuenta las posiblidades en las filas, que haya y contC que cuenta las posiblidades en las columnas
*Esta funcion solo se llamara cuando este lleno el tablero
*Primero recorrera todo el tablero y contatara las combinaciones posibles tanto de columnas , colo filas sin salirse del array y pasando los resultado como parametros de refrencia .
*/

void  buscar (tTablero tablero,int &contF, int &contC )
{
	contF=0, contC =0;
	
	for (int i =0; i <N -1; i++)
	{
		for (int j =0; j <N ; j++)
		{
			if (tablero[i][j]== tablero[i+1][j])
			{

				contC++;

			}
		}
	}

	for (int i =0; i <N ; i++)
	{
		for (int j =0; j <N -1; j++)
		{
			if (tablero[i][j]== tablero[i][j+1])
			{

				contF++;

			}
		}
	}

}

/*
*En esta funcion devolvera el numero mayor encontrado en el array.
*Primero se inicia a 0 , para que recorriendo el array si hay algun valor mayor que ese se cambiara por ese valor.
*Esta funcion servira para que cuando llege a 2048 se acabe.
*/

int mayor(const tTablero tablero)
{
	int maximo=0;

		for (int i =0; i <N ; i++)
		{
			for (int j =0;  j< N; j++)
			{
				if (tablero[i][j] > maximo)
				{
					maximo = tablero[i][j];
				}
			}
		}
	
	return maximo;
}

/*
*Esta funcion servira para guardar una partida a medias (version 4) si el usuario pulsa Esc.
*Pedira el nombre de archivo al usuario, y recorriendo el array ira poniendo en el archivo primero la dimension, luego las fichas que haya en cada poscion y por ultimo el totalPuntos
*/

void guarda(const tTablero tablero, int totalPuntos)
{

	string nombre;
	ofstream archivo;

	cin >> nombre ;
	archivo.open (nombre);

		if (archivo.is_open ())
		{
			archivo <<N << endl;

			for (int i =0; i < N ; i++)
			{
				for (int j =0; j <N ; j++)
				{
					archivo << tablero[i][j] << endl;
				}
			}

			archivo << totalPuntos << endl;

			archivo.close();
		}

		else
		{
			cout << "No se ha encontrado ese archivo"<< endl;
		}

}

/*
*Esta funcion solo se ejecutura si se llega a 2048
*Para esta funcion primero se leera el archivo de records en caso de poder o no haber dicho archivo no lo leera y no habra ningun record guardado.
*Si se puede leer se guarda en la lista (una estructura).
*Luego le pedira su nombre y  se guardara tambien la puntuacion total.
*Luego se ordenara la lista de mayor a menor con el algoritmo de inserccion con  intercambios.
*Luego llamara a actualiza , para actualizar el archivo o crearlo en su defecto.
*/

void nuevoRecord(int totalPuntos, tLista &lista)
{
	tPuntos puntos;
	lista.contador =0;
	int pos;
	string aux;
	tPuntos tmp;//para poder copiar todos los elementos de los tPuntos que son el nombre y el totalPuntos sin tener que ir cambiandolo de posicion de cada elemento de uno en uno
	
	ifstream archivo;
	archivo.open ("records.txt");

		if (archivo.is_open ())
		{
			archivo >> puntos.nombre;

			while (puntos.nombre !="???")//acabra cuando leea esto
			{

				archivo >> puntos.totalPuntos; // se leera los puntos y se guardara
				lista.ficha[lista.contador]= puntos; 
				lista.contador++;
				archivo >> puntos.nombre;// luego se llamara otra vez al nombre

			}

			archivo.close();
		}

	
	//le pedira el nombre al usuario y se guardara el nombre y los puntos
	cout << "Dime tu nombre ";
	cin >> lista.ficha[lista.contador].nombre;
	lista.ficha[lista.contador].totalPuntos= totalPuntos;
	lista.contador++;// se amplia el contador

	//se ordenara la lista de mayor a menor 
	for (int i=1 ; i < lista.contador;i++)
	{
		pos =i;
		
		while ((pos > 0) && (lista.ficha[pos-1].totalPuntos < lista.ficha[pos].totalPuntos))// si es menor se cambian las posiciones 
		{
			tmp = lista.ficha[pos];
			lista.ficha[pos] = lista.ficha[pos- 1];
			lista.ficha[pos - 1] = tmp;
			pos--;
		}
	}
	
	actualizar (lista);

}

/*
*En esta funcion reescribira el archivo o creara uno nuevo.
*Al final se escribira ??? como centinela
*/

void actualizar (tLista &lista)
{
	tPuntos puntos;
	ofstream archivo;

	archivo.open ("records.txt");

		if (archivo.is_open ())
		{
			if (lista.contador <=9)//solo se escribira hasta 10 puntuaciones
			{
				for (int i =0; i < lista.contador; i++)
				{
					archivo << lista.ficha[i].nombre << " " << lista.ficha[i].totalPuntos << endl;
				}
			}

			else {
				for (int i =0; i < 10; i++)
				{
					archivo << lista.ficha[i].nombre << " " << lista.ficha[i].totalPuntos << endl;
				}
			}

			archivo << "???" << endl;
			archivo.close();
		}

		else 
		{
			cout << "No se ha podido abir el archivo " << endl;
		}

}

/*
*En esta funcion se imprimira por pantalla lo que haya en el archivo.
*/

void muestraRecords()
{

	string nombre;
	int puntos;

	ifstream archivo ;
	archivo.open ("records.txt");

	cout << setw (10) <<  "RECORDS" << endl;

		if (archivo.is_open ())
		{
			archivo >> nombre ;

			while (nombre!= "???" )
			{

				archivo >> puntos; // leera los puntos
				cout << nombre << " " << puntos  << endl; //mostrara por pantalla el nombre y la puntuacion
				archivo >> nombre ; // volvera a leer el nombre

			}

			archivo.close();

		}

		else 
		{
			cout <<"No se ha podido leer el archivo " << endl;
		}

}




