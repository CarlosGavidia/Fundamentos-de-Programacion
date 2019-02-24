#include <iostream>
using namespace std;
int main() {
	int numero;
	cout << "Introduce un numero " ;
	cin >> numero;
	while (numero < 0 || numero > 100 ) {
	cout << "Introduce un numero " ;
	cin >> numero;
	}
	if(numero > 0 || numero < 100) {
	cout << "1 x " << numero << " = " << 1 * numero;

}
}	
	
	
	
	
	
	