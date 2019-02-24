#include <iostream>
using namespace std;
int main()
{
	double operando1,resultado1, resultado2 ; 
	cin >> operando1;
	cout << "Tiempo transucrrido en minutos" << endl;
	
	resultado1 = operando1 /60 ;
	cout << resultado1 << endl;
	cout << "Timepo transcurrido en segundos " << endl;
	resultado2 = resultado1 / 60 ;
	cout << resultado2 << endl;
	return 0;
	}