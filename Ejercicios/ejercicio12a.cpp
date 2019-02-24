#include <iostream >
#include <string >
using namespace std;


int main(){
	
	string cad;
	cin >> cad;
	
	while (cad != "X"){
		int i =cad.size()-1;
			if (cad.at(i) == 'a' || cad.at(i) == 'u' || cad.at(i) == 'o' || cad.at(i) == 'i' || cad.at(i) == 'e' ){
				cout << cad << "s" << endl;
			}
			else {
				cout << cad << "es" << endl;
			}
			cin >> cad;
	}

	system ("pause");
}