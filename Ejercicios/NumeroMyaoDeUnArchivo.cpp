#include <iostream >
#include <fstream>
#include <iomanip>
using namespace std;
int main (){
	int a, contador=0;
	const int N=3;
	typedef int tNumero [N];
	tNumero numero;
	ifstream archivo;
	archivo.open("domingo.txt");
	if (archivo.is_open()){
	archivo >> a;
		while ((a!=-1) && (contador < N)){
		numero [contador ]= a;
		if (numero[contador] > 40 ){
			cout << "zii" << a ;
			}
		contador ++;
		
		archivo >> a;
			
			
	}
	archivo.close();
	}


	}
	
	
	
	

	
	