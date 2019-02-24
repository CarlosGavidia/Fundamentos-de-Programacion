#include <iostream >
#include <string>
#include <ctime >
#include <cstdlib>
using namespace std;
const int N =5;
typedef enum {nada, puente, agua,pirata, tesoro }tJugador;
typedef int tTablero[N][N];
int colocarFicha(tTablero tablero);
int direccionPirata(tTablero tablero);
bool buscar (tTablero tablero);
tJugador jugador;
int main(){
	srand(time(NULL));
	tTablero tablero = {nada};
	colocarFicha(tablero);
	 buscar ( tablero);
	system ("pause");
}
bool  buscar (tTablero tablero){
	int contador =0, aux ;
	int pirata, pirata1, tesoro, tesoro1;
	bool encontrado = false;

		for (int i =0; i < N ; i++){
			for (int j =0; j <N; j++){
				if (tablero[i][j]== pirata){
					pirata = i;
					pirata1 = j;
				}
				else if (tablero[i][j]==tesoro){
					tesoro= i;
					tesoro1 = j;
				}
			}
		}
		while (contador < 50 || !encontrado ){
		aux =  direccionPirata( tablero);
		if (aux ==1 ){
			pirata++;
		}
		else if (aux == 2 ){
			pirata--;
		}
		else if (aux == 3 ){
			pirata1++;
		}
		else if (aux == 4 ){
			pirata1--;
		}
		contador++;
		if (tablero[pirata][pirata1]== tablero[tesoro][tesoro1]){
			encontrado = true;
			cout <<"Lo ha encontrado" << endl;

		}
		else if (contador >=50)  {
			encontrado = false;
			cout << "Ha hecho mas de 50 posibilidades " << endl;
		}
		else if (tablero[pirata][pirata1]= agua){
			encontrado = false;
			cout << "Se ha caido al agua " << endl;
		}
		}

return 0;

}
int direccionPirata(tTablero tablero){

	int dirreccion ;
	dirreccion = rand() %  5;


	return dirreccion ;


}
int colocarFicha(tTablero tablero){
	 
		
	tablero[0][N-1]=puente;
	tablero[N-1][0]= puente;

	for (int i =0; i < N-1 ; i++){
		tablero[0][i]= agua;
	}
	for (int i =0; i < N-1;i++){
		tablero[i][0]= agua;
	}
	for (int i =1; i < N; i++ ){
		tablero[N-1][i]= agua;
	}
	for (int i =1; i < N; i++ ){
		tablero[i][N-1]= agua;
	}
	int fila, columna , fila1, columna1;
	fila = rand() % (N-2) + 1;
	columna = rand() % (N-2) + 1;
	

	fila1 = rand() % (N-2) + 1;
	columna1 = rand() % (N-2) + 1;

	while ((fila = fila1) && (columna= columna1) ){

		fila1 = rand() % (N-2) + 1;
		columna1 = rand() % (N-2) + 1;
	}
	tablero[fila][columna]= pirata;
	tablero[fila1][columna1]= tesoro;
	return 0;
}

