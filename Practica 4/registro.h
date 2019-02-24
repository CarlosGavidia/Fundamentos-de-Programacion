#ifndef registro_h //proteccion para inclusiones multiples
#define registro_h

/*Biblioteca incluida*/
#include <iostream >

/*Constante utilizada */
const int MAX_REG = 25;

/*Estructura utilizada*/
typedef struct
{
	std::string id;
	bool leido;

}tRegCorreo;

/*Ficha donde se almancena un id y un leido por ficha*/
typedef  tRegCorreo tFicha1[MAX_REG];

/*Segundo struct para almacenar cada ficha y el contador */
typedef struct
{
	tFicha1 ficha1;
	int contador;

}tListaRegCorreo;

/*Prototipos de las funciones defidas  */
void inicializar(tListaRegCorreo &listaReg);
void cargar(tListaRegCorreo &listaReg, std:: ifstream& archivo);
void guardar(const tListaRegCorreo &listaReg,std:: ofstream& archivo1);
bool insertar(tListaRegCorreo &listaReg, tRegCorreo registro);
bool borrar(tListaRegCorreo &listaReg, std::string id);
bool correoLeido(tListaRegCorreo &listaReg,std:: string id);
int buscar(const tListaRegCorreo &listaReg, std::string id);

#endif