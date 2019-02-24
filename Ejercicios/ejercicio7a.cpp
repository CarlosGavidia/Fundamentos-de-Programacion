#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int main() {
	int numero, total = 0;
	ifstream archivo;
	archivo.open("borrar.txt");
	if (archivo.is_open()){
		archivo >> numero;
		while (numero!= -1){
			for (int i = 1 ; i < numero; i++ ){
				if ( numero % i == 0){
					total = total + i;
				}
			
			}
			if (total == numero){
				cout << total  << "no  es perfecto "<< endl;
			}
			else {
				cout << numero << " es perfecto "<< endl;
			}
			archivo >> numero;
		}
		archivo.close();
		
	}
	system("pause");
}