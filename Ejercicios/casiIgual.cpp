#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
int main() { 
	int numero, a, aux=0;
	cout << "dame un numero" ;
	cin >> numero;
	ifstream archivo;
	archivo.open("nuevo.txt");
	if (archivo.is_open()){
	archivo >> a;
		while (a !=-1  ){
		
			if ((numero -2 == a) || (a == numero+2)){
			cout << a <<  " es casi igual " << endl;
			}
			else{
			cout << a <<  " no  es casi igual " << endl;
			}
			
		archivo >> a;
		}
	
	archivo.close();
	}
}
		