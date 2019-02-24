#include <iostream>
#include <cctype>
using namespace std;
int main () {
	int numero= 0;
	char letra;
	cin >> letra;
	while ( letra != '.'){
		if (isalnum (letra))  {
		numero++;
		cout << " total "<< numero << endl;
		cin >> letra;
		}
		}
		
}

 //termina cuando pongas . y se suman todos los que metas