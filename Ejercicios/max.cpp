#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std; // BUSCAR EL NUMERO MAYOR DE TODOS
int main() {
	int aux=0, a;
	ifstream archivo;
	archivo.open("nuevo.txt");
	if (archivo.is_open()){
	archivo >> a;
		while ( a!=-1){
		if((a > aux)){
		aux = a;
		archivo >> a;
		}
		else {
		aux = aux  ;
		archivo >> a;
		}
		}
	
	cout << " el max es " << aux << endl;
	archivo.close();
	}
	}
	
