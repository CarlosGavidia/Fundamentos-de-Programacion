#ifndef gestor_h // proteccion para inclusiones multiples
#define gestor_h

/*Biblioteca incluida*/
#include <iostream >
#include "lista_correo.h" //esta la lista de correos
#include "lista_usuario.h"// esta la lista de usuarios

/*Estructura utilizada ,contiene el dominio , la posicion de quien a iniciado la aplicacion y las lista de correos y las de usuarios*/
typedef struct
{
	std:: string dominio;
	tListaCorreos correos;
	tListaUsuarios usuarios;
	int posicion;

}tGestor;

/*Prototipos de las funciones defidas  */
bool arrancar(tGestor& gestor, std:: string dominio);
void apagar( tGestor &gestor);
bool crearCuenta(tGestor &gestor, std::string& id);
bool iniciarSesion(tGestor &gestor, std::string& id);
void leerCorreo(tGestor& gestor, tListaRegCorreo& listaReg, bool entrada);
void enviarCorreo(tGestor& gestor, const tCorreo &correo);
void borrarCorreo(tGestor& gestor, tListaRegCorreo& listaReg,  bool entrada);
void lecturaRapida(tGestor& gestor, tListaRegCorreo& listaReg,  bool entrada);
void inicializar(tGestor &gestor, std::string dominio);
int menu();
int menuBandeja(tGestor &gestor, bool entrada, std:: string& nombre);
void ejecutarMenuBandeja(tGestor &gestor,int opcion, bool &entrada);
void borrar (tGestor &gestor);// para la parte opcional (explicado en el modulo)
void ini (tGestor &gestor,std::string dominio);

#endif