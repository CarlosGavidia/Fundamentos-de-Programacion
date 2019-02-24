#ifndef lista_usuario_h // proteccion para inclusiones multiples
#define lista_usuario_h

/*Biblioteca incluida*/
#include <iostream>
#include "usuario.h" // en el h esta el struct y los prototipos de las funciones 

/*Constantes utilizadas*/
const int MAX_USUARIOS = 4;

/*Enumerado array estatico de datos dinamicos*/
typedef tPtrUsuario tFicha2[MAX_USUARIOS];

//estructura de tListaUsuarios , con el contador
typedef struct
{
	tFicha2 ficha2;
	int contador;

}tListaUsuarios;

/*Prototipos de las funciones defidas  */
void inicializar(tListaUsuarios &usuarios);
bool cargar(tListaUsuarios& usuarios,std:: string dominio);
void guardar(const tListaUsuarios& usuarios,std:: string dominio1);
bool aniadir(tListaUsuarios& usuarios, const tUsuario& usuario);
bool buscarUsuario(const tListaUsuarios& usuarios, std::string id, int& posicion);
void destruir (tListaUsuarios & usuarios);

#endif