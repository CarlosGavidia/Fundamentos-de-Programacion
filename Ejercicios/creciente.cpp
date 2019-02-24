#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
int main () {
	bool creciente;
	int a , b= 0;
	ifstream archivo;
	archivo.open("nuevo.txt");
	if (archivo.is_open()){
	archivo >> a;
		while ((a !=-1)&& (a > b) ){
		b=a;
		archivo >> a;
		}
	if (a == -1){
	creciente = true;
	cout << " es creciente" << endl;
	}
	else{
	creciente= false;
	cout << "no es creciente por que el  " << a  << " ya que el anterior era mayor que " << b << endl;
	}
	archivo.close(); // lo acabo de poner quitar sinio
	}
	
	return creciente;
	}
	
	
		