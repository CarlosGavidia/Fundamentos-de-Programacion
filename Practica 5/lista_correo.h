#ifndef lista_correo_h // proteccion para inclusiones multiples
#define lista_correo_h

/*Bibliotecas incluidas*/
#include <iostream >
#include "correo.h" //incluye el struct de tCorreo con el puntero mas los prototipos de las funciones

/*Constantes utilizadas*/
const int MAX_CORREOS = 6;

/*Estructura en cada ficha estan todos los datos del correo
*Y el tListaCorreos esta incluido el contador , el array dinamico del correo y la capacidad maxima que puede tener 
*/

typedef struct
{
	tPtrCorreo ficha;
	int contador;
	int capacidad;

}tListaCorreos;

/*Prototipos de las funciones defidas */
void inicializar(tListaCorreos &correos);
bool cargar(tListaCorreos &correos, std:: string dominio);
void guardar(const tListaCorreos &correos, std::  string dominio1);
bool insertar(tListaCorreos &correos, const tCorreo &correo);
bool buscar(const tListaCorreos &correos, std:: string id, int &pos);
void ordenar_AF(tListaCorreos &correos);
bool operator<(const tCorreo opIzq,const  tCorreo opDer);
void eliminar (tListaCorreos &correos);
void redimensionar(tListaCorreos &correos, int incremento);

#endif