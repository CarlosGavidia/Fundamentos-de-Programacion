#ifndef correo_h // proteccion para inclusiones multiples
#define correo_h

/*Biblioteca incluida*/
#include <iostream >

/*Enumerado incluido*/
typedef time_t tFecha; 

//estructura de tCorreo, contine el id, el emisor del correos, el destinatario, el asunto , el cuerpo del correo y la fecha 
typedef struct 
{
	std:: string id;
	std::string emisor;
	std::string destinatario;
	std:: string asunto;
	std:: string cuerpo;
	tFecha fecha;

} tCorreo;

/*Prototipos de las funciones defidas  */
void correoNuevo(tCorreo &correo,  std:: string emisor);
void correoContestacion(const tCorreo &correoOriginal, tCorreo &correo, std:: string emisor);
std:: string aCadena(const tCorreo &correo);
std:: string obtenerCabecera(const tCorreo &correo);
bool cargar(tCorreo &correo, std:: ifstream& archivo);
void guardar(const tCorreo &correo,std:: ofstream& archivo1);
std:: string mostrarFecha(tFecha fecha);
std:: string mostrarSoloDia(tFecha fecha);

#endif