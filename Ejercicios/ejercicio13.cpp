#include <iostream>
using namespace std;
int main()
{
	int a, b ,c;
	cin >> a >> b >> c ;
	if (a < b ) { 
		if (a > c ){
		mayor = b;
		intermedio = a;
		menor = c ;
		}
		else {
		menor = a;
		
		if (b < c ){
		intermedio = b;
		mayor = c;
		}
		else {
		intermedio =c;
		mayor = b ;
		}
		}
		}
		}
	else {
		if (c < b) {
		mayor = a;
		intermedio= b;
		menor = c;
		}
		
		else {
		menor b;
		if (a > c){
		mayor = a ;
		intermedio = c;
		else {
		intermedio= a ;
		mayor = c ;
		}
		}
		}
		
	cout << menor "," << intermedio "," << mayor "," << endl;
		}
		
		
	
		
		
		
	
	