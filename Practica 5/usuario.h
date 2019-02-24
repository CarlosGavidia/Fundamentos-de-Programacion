#ifndef usuario_h // proteccion para inclusiones multiples
#define usuario_h

#include <iostream >
#include "registro.h" // se incluye la lista de tListaRegCorreo que en cada una tiene el id y el booleano de si lo ha leido o no

//estructura de tUsuario, contiene el nombre de usuario, contraseña y la entrada y la salida de cada usuario
typedef struct
{
	std:: string nombre;
	std:: string contraseña;
	tListaRegCorreo entrada;
	tListaRegCorreo salida ;

}tUsuario;

/*Puntero a usuario*/
typedef tUsuario *tPtrUsuario;

/*Prototipos de las funciones defidas */
bool cargar(tUsuario& usuario, std ::ifstream& archivo);
void guardar(const tUsuario& usuario,std :: ofstream& archivo1);
void inicializar(tUsuario& usuario, std ::string id, std ::string contrasenia);
bool validarContrasenia(const tUsuario &usuario,std :: string contrasenia);

#endif 