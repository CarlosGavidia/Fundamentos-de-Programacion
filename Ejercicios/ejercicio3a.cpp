#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
void otro(int &a, int &b, int &c, int &d);
int main() {
	int a = 1, b = 2 , c = 3 , d = 4, suma  ;
	suma = a +b+c+d;
	cout <<  a << b << c << d  <<  suma << endl;
	otro( a,  b,  c,  d);
	suma = a +b+c+d;
	cout <<  a << b << c << d  <<  suma << endl;
	system("pause");
}
void otro(int &a, int &b, int &c, int &d){
	a = b;
	b= d ;
	c = 2+ d ;
	d= d + d ;
}