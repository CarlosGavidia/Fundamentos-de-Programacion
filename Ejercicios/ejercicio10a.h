#include <iostream >
#include <cstdlib> 
#include <ctime>
using namespace std;

const int N = 5;
typedef int tVector[N][N];
int inicializarTablero(tVector vector);
int main(){
	srand(time(NULL));
	tVector vector;
	inicializarTablero( vector);

system ("pause ");
}
int inicializarTablero(tVector vector){
	int  nada=0 , agua =1, puente=2, pirata=3, tesoro=4;
	int fila, columna, fila1 , columna1;
	int aux =0, aux1=0;
	for (int i =0; i < N ; i++){
		for (int j =0; j < N ; j++){
			vector [i][j]=0;
		}
	}



	vector [0][N-1] = puente ;
	vector [N -1][0]= puente ;
	while(aux < N -1) {
	vector [0][aux]= agua ;
	aux++;
	}
	while (aux1 < N -1){
		vector [aux1][0]= agua ;
		aux1++;
	}
	
	fila =  rand() % ( 4 );
	columna  =  rand() % ( 4);
	vector [fila][columna] = pirata ;

	fila1 =  rand() % ( 4 );
	columna1  =  rand() % ( 4);

	while (fila1== fila && columna1 == columna ){
		fila1 =  rand() % ( 4 );
		columna1  =  rand() % ( 4);
	}
	vector [fila1][columna1] = tesoro ;
	

	for (int i =0; i < N ; i++){
		for (int j =0; j < N ; j++){
			cout << vector [i][j] << endl;
		}
	}
	
	return 0;
}