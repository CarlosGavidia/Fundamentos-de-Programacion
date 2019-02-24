#include <iostream>
#include <cmath>
using namespace std ;
int main()

{
	double x, y , f ;
	const double e = 2.71, pi = 3.141592;
	cout << "x" << endl;
	cin >> x;
	cout << "y" << endl;
	cin >> y;
	
	f = sqrt (1.531 pow (x+y) + (abs (pow( e, x))-(pow (e, y))*(sin(x) - tan(y)) )/(log10(y) * (pow (pi,x)))) ;
	cout << f << endl;
	return 0;
	}
	