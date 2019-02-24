#ifndef lista_correo_h // proteccion para inclusiones multiples
#define lista_correo_h

/*Bibliotecas incluidas*/
#include <iostream >
#include "correo.h" //incluyeel struct de tCorreo mas los prototipos de las funciones

/*Constantes utilizadas*/
const int MAX_CORREOS = 25;

/*Estructura en cada ficha estan todos los datos del correo
*Y el tListaCorreos esta incluido el contador y la ficha con esos correos
*/
typedef tCorreo tFicha[MAX_CORREOS];
typedef struct
{
	tFicha ficha;
	int contador;

}tListaCorreos;

/*Prototipos de las funciones defidas */
void inicializar(tListaCorreos &correos);
bool cargar(tListaCorreos &correos, std:: string dominio);
void guardar(const tListaCorreos &correos, std::  string dominio1);
bool insertar(tListaCorreos &correos, const tCorreo &correo);
bool buscar(const tListaCorreos &correos, std:: string id, int &pos);
void ordenar_AF(tListaCorreos &correos);
bool operator<(tCorreo opIzq, tCorreo opDer);

#endif