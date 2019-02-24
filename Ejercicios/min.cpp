#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
int main() {
	int a , aux1=0, aux2 =100;
	ifstream archivo;
	archivo.open("nuevo.txt");
	if(archivo.is_open()){
	archivo >> a;
		while (a!=-1 ){
			if (a > aux1){
			aux1 = a;
			archivo >> a;
			}
			else {
			aux1 = aux1;
			archivo >> a;
			}
			if (a< aux2){
			aux2= a;
			archivo >> a;
			}
			else {
			aux2 = aux2;
			archivo >> a;
			}
			}
		
	archivo.close();
	cout << aux1  << endl;
	cout << aux2;
	}
	}
			