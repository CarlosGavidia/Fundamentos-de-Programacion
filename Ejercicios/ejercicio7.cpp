#include <iostream>
using namespace std;
int main()
{
	const int x = 12;
	const double sigma = 2.1836;
	const int y= 3;
	const double lambda = 1.11695;
	const double alfa = 328.67;
	double f;
	f = 3* ( x+(sigma*y)/(x*x) - (y*y) )- (lambda*(alfa-13.7)) ;
	cout << f << endl;
	}
	
