#include <iostream >
#include <fstream >
#include <iomanip>
#include < string >
#include < cmath >
using namespace std;


int main (){
	int numero;
	cin >> numero;
	for (int i = 2 ; i <= numero-1; i++){
		if (numero%i==0){
			cout << "no es primo" << endl;
		}
		else {
			
			if (i == numero -1){
				cout << " es primo " << endl;
			}
			i++;
		}
	}
	



}