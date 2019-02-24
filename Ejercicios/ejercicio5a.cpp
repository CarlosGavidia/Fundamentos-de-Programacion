#include <iostream >
#include <fstream >
#include <string >
using namespace std;
const int N = 100;
typedef struct{
	int codigo;
	string nombre;
}tCoches;
typedef tCoches tFicha[N];
typedef struct{
	tFicha ficha;
	int contador ;
}tLista;

typedef struct{
	int codigo;
	string fecha ;
	int dias ;
}tAlquiler;
typedef tAlquiler tFicha1 [N];
typedef struct{
	tFicha1 ficha1;
	int contador1;
}tLista1;
void leerModelos(tLista &lista);
void leerAlquileres(tLista1 &lista1);
void ordenar(tLista1 &lista1);
void buscar(tLista &lista,tLista1 &lista1);
int main (){
	tLista lista;
	tLista1 lista1;
	leerModelos(lista);
	leerAlquileres(lista1);
	ordenar(lista1);
	buscar(lista,lista1);
system ("pause");
}
void leerModelos(tLista &lista){
	tCoches coches;
	lista.contador=0;
	ifstream archivo;
	archivo.open ("coches.txt");
	if (archivo.is_open()){
		archivo >> coches.codigo;
		while (coches.codigo !=-1){
			getline (archivo, coches.nombre);
			lista.ficha[lista.contador]= coches;
			lista.contador++;
			archivo >> coches.codigo;
		}
		archivo.close();
	}
}
void leerAlquileres(tLista1 &lista1){
	tAlquiler alquiler;
	lista1.contador1=0;
	ifstream archivo;
	archivo.open ("alquiler.txt");
	if (archivo.is_open()){
		archivo >> alquiler.codigo;
		while (alquiler.codigo !=-1){
			archivo >> alquiler.fecha;
			archivo >> alquiler.dias;
			lista1.ficha1[lista1.contador1]= alquiler;
			lista1.contador1++;
			archivo >> alquiler.codigo;
		}
		archivo.close();
	}
}
void ordenar(tLista1 &lista1){
	tAlquiler alquiler;
	int  pos;
	tAlquiler tmp;
	
	for (int i =0; i < lista1.contador1; i++){
		lista1.ficha1[i].fecha.erase(2,1);
		lista1.ficha1[i].fecha.erase(4,1);
	}
	for (int i =1; i <lista1.contador1; i++){
		pos =i;
		while ((pos >0)&& !(lista1.ficha1[pos-1].fecha > lista1.ficha1[pos].fecha )){
			tmp = lista1.ficha1[pos];
			 lista1.ficha1[pos]=  lista1.ficha1[pos-1];
			 lista1.ficha1[pos-1]= tmp;
			 pos--;
		}
	}
	

}
void buscar(tLista &lista,tLista1 &lista1){
	tAlquiler alquiler;
	tCoches coches;

	for (int i =0; i <lista1.contador1 ; i++){
		lista1.ficha1[i].fecha.insert(2,"/");
		lista1.ficha1[i].fecha.insert(5,"/");
	}


	for (int i =0; i <lista.contador ; i++){
		for (int j =0; j < lista1.contador1; j++){
			if (lista.ficha[i].codigo == lista1.ficha1[j].codigo){
				cout << lista1.ficha1[j].fecha << "  " << lista.ficha[i].nombre  << "               " << lista1.ficha1[j].dias << " dia(s)" << endl;
			}
		}
	}
}