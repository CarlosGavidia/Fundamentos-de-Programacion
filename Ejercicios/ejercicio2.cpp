#include <iostream>
using namespace std;

int main ()
{
	double radio = 14.5 , altura = 26.79, volumen ;
	const double Pi = 3.131692;
	
	volumen = (Pi * (radio*radio)* altura)/3;
	cout << "volumen del cono" << endl;
	cout << volumen << endl;
	
	return 0;
	} 
	