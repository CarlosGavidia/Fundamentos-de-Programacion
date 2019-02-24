#include <iostream>
using namespace std;
int main()
{
	double dato1, dato2,dato3,dato4,dato5, dato6,resultado;
	cout << "Notas de Practicas" << endl;
	cin >> dato1;
	if (dato1 < 5) {
	cout << "no se hace evaluacion " << endl;
	}
	
	cout << "Nota de examen de dicimebre" << endl;
	cin >> dato2;
	cout << "Nota de examen de febrero" << endl;
	cin >> dato3;
	cout << "Nota de examen de abril" << endl;
	cin >> dato4;
	cout << "Nota de examen de junio" << endl;
	cin >> dato5;
	
	if (dato4 < 4){
	cout << "no se hace evaluacion" << endl;
	}
	
	cout << "Nota de actividad adicional" << endl;
	cin >> dato6;
	cout << "CALIFICACION TOTAL" << endl;
	resultado = ((dato1*0.2)+ (dato2*0.05)+(dato3*0.10)+(dato4*0.10)+(dato5*0.45)+(dato6*0.1)) ;
	cout << resultado << endl;
	}
	