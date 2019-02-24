/*Biblioteca incluidas */
#include <iostream >
#include <iomanip >
#include <ctime >
#include <string >
#include <fstream >
#include <sstream>  
#include "correo.h" // esta el struct y los prototipos de las funciones

/*Espacios de nombres usados*/
using namespace std;

/*main(), comentado despues de probar todas las funciones y su funcionamiento */
/*int main (){
	tCorreo correo;
	tCorreo correoOriginal;
	
	tFecha fecha;
	ifstream archivo; 
	archivo.open ("arturo@fdimail.com_correos.txt" );

	ofstream archivo1;
	archivo1.open ("yo@fdimail.com.txt");
	string emisor= "yo@fdimail.com";

	//correoNuevo(correo,emisor);
	/*if (archivo.is_open()){
	cargar(correo,  archivo);
	}
	//guardar(correo, archivo1);
	//cargar(correo,  archivo);
	//guardar(correo, archivo1);
	//cargar(correo,  archivo);
	//guardar(correo, archivo1);
	//cargar(correo,  archivo);
	//guardar(correo, archivo1);
	//correoOriginal = correo;
	//correoContestacion(correoOriginal, correo,emisor);
	//cout << aCadena(correo);
	//cout << obtenerCabecera(correo);
	system ("pause");
}*/

/*
*Funcion para obtener el emisor, el asunto , y la fecha  de cuando fue enviado.
*Devuelve un string con dicha informacion.
*Esta funcion sirve para la bandeja de entrada como la de salida.
*Recibe cont tCorreo para no ser modificado
*/

string obtenerCabecera(const tCorreo &correo)
{
	string cabecera;
	stringstream flujo;
	tFecha fecha;
	fecha= correo.fecha;
	
	flujo << left << setw(23) << correo.emisor  << setw(25) << correo.asunto <<  right <<  mostrarSoloDia(fecha) ;

	cabecera =flujo.str();
	
	return cabecera;

}

/*
*El cometido de esta funcion es de mostrar por patalla el contenido de un correo.
*Devuelve un string con toda esta informacion.
*Recibe cont tCorreo para no ser modificado
*/

string aCadena(const tCorreo &correo)
{

	string resultado;
	stringstream flujo;
	tFecha fecha;
	fecha= correo.fecha;
	
	flujo << "De: " << correo.emisor  <<  "                                  "  << mostrarFecha(fecha)<< endl;
	flujo << "Para : " << correo.destinatario << endl;
	flujo << "Asunto : " << correo.asunto << endl;
	flujo << endl;
	flujo << correo.cuerpo << endl;

	resultado=flujo.str();

	return resultado;

}

/*
*Esta funcion recibe un emisor y un correoOriginal(que sera el correo incial), y devulve todos los datos de un correo que ha contestado el destinatario.
*Se pediran solo los datos del asunto y el cuerpo, ya que el emisor, sera el destinatario del correo inicial, el destinatario sera el emisor del correoOriginal , la fecha se calculara automaticamnete.
*Los datos del correo anterior tambien estaran presentes en el nuevo correo.
*Recibe el emisor del correo que sera el que haya inciado la sesion.
*Se crea un nuevo correo, tCorreo correo, y el correo anterior se llamara correoOriginal
*/

void correoContestacion(const tCorreo &correoOriginal, tCorreo &correo, string emisor)
{ 
		
	tFecha fecha;
	string asunto, cuerpo;
	stringstream flujo, flujo1, flujo2;
	
	//primero se rellenan los datos del emisor, el destinatario y fecha en este nuevo correo
	correo.emisor= emisor; 
	correo.destinatario= correoOriginal.emisor;
	correo.fecha =  time(0);
	fecha= correo.fecha;
	
	//se muestran por pantalla estos datos 
	cout << "De: " << correo.emisor << "                                  " << mostrarFecha( fecha) << endl; 
	cout << "Para: " << correo.destinatario << endl;
	
	//tambien se muestra el asunto , que sera el mismo pero a�adiendo "Re:" delante
	flujo << "Re:"  << correoOriginal.asunto << endl;

	asunto=flujo.str();
	correo.asunto = asunto;// el asunto del correo nuevo se pasa al asunto(string), y se muestra por pantalla
	cout << correo.asunto << endl;
	
	//se pide que el usuario esciba el cuepo del correo
	cout << "Escribe el cuerpo del correo (X para terminar) " << endl;
	getline (cin, correo.cuerpo);

	//hasta que el usuario no marque una X no acabara
		while (correo.cuerpo !="X")
		{
			flujo1 << correo.cuerpo << endl;
			getline (cin, correo.cuerpo);
		}

	//los siguintes datos son los datos del correoOriginal separados por unas lineas para separar
	flujo1 << "--------------------------------------------------------------------------" << endl;
	fecha= correoOriginal.fecha;
	mostrarFecha( fecha);
	flujo1 << correoOriginal.emisor << "                                      " << mostrarFecha(fecha)  << endl;
	flujo1 << correoOriginal.destinatario << endl;
	flujo1 << correoOriginal.asunto << endl;
	
	cuerpo=flujo1.str();
	correo.cuerpo = cuerpo;//se guarda en el cuerpo

	//se guarda em el correo id la suma del emisor y la fecha
	flujo2 << correo.emisor << "_" << correo.fecha ;
	correo.id= flujo2.str();


}

/*
*Funcion para para mostrar la fecha entera,incluida el dia, los minutos, y los segundos
*Devuelve un string con estos datos
*/

string mostrarFecha(tFecha fecha)
{
	stringstream resultado;
	tm ltm;
	localtime_s(&ltm, &fecha);
	resultado << 1900 + ltm.tm_year << "/" << 1 + ltm.tm_mon <<"/"<< ltm.tm_mday;
	resultado<<" ("<<ltm.tm_hour<< ":" <<ltm.tm_min<< ":" << ltm.tm_sec << ")";
	return resultado.str();
}

/*
*Funcion para mostrar solo la fecha del a�o el dia y el mes
*Devuelve un string con estos datos
*/

string mostrarSoloDia(tFecha fecha)
{
	stringstream resultado;
	tm ltm;
	localtime_s(&ltm, &fecha);
	resultado  << "           "<< 1900 + ltm.tm_year << "/" << 1 + ltm.tm_mon <<"/"<< ltm.tm_mday;
	return resultado.str();
}

/*
*Funcion para cargar los datos de un fichero de uno en uno(al no haber contador en este modulo)
*Leera el dato hasta que sea X que significara que habra leido un correo entero y no llera mas cuando llege a XXX
*Leera todos los datos necesarios para rellenar los datos de un correo
*Solo leera un destinatario
*/

bool cargar(tCorreo &correo,  ifstream & archivo)
{

	bool ok= true;
	char aux;
	string aux2;
	stringstream flujo;
	string resultado;
	
	//leera el primer dato, si es XXX no leera mas , siginfica que ya ya leido todo lo que habia en el el txt y devuelve false
	archivo >> aux2;

		if (aux2== "XXX")
		{
			ok = false;
		}

		if (ok == true)
		{
			//va guardando los datos el el struct
			correo.id= aux2;
			archivo >> correo.fecha;
			archivo >> correo.emisor;
			archivo >> correo.destinatario;
			archivo.get(aux);
			getline (archivo, correo.asunto);
			getline (archivo, correo.cuerpo);

			//hasta que no sea X que siga leyendo
			while (correo.cuerpo !="X")
			{
				flujo << correo.cuerpo << endl;
				getline (archivo, correo.cuerpo);
			}

			resultado=flujo.str();
			correo.cuerpo = resultado;// el resultado sera todo el cuerpo que ha leido hasta la X 	
			
		}

	//devulve si ha acabado de leer todo el txt(XXX)= false, si no true
	return ok;

}

/*
*Funcion para crear un correo nuevo, desde 0
*Y lo almacen el correo todos los datos
*/

void correoNuevo(tCorreo &correo,  string emisor)
{

	string resultado, aux2;
	stringstream flujo,flujo1;
	tFecha fecha;
	
	correo.emisor= emisor;
	correo.fecha =  time(0);
	fecha= correo.fecha;
	mostrarFecha(fecha);// se hace automaticamnete
	
	// se muestra por pantalla
	cout << "De : " << correo.emisor <<  "                                  "  << mostrarFecha( fecha)<<   endl;
	cout << "Destinatario : ";
	cin.sync();
	getline ( cin, correo.destinatario);// le dice al usuario que destinatario ha que quiere enviarle

	//luego el asunto
	cout << "Asunto (una linea ): ";
	getline (cin, correo.asunto);

	// el cuerpo del correo
	cout << "Escribe el cuerpo del correo (X para terminar) " << endl;
	cout << endl;
	getline (cin, correo.cuerpo);
		
		//hasta que el usuario introduzca X
		while (correo.cuerpo !="X")
		{
			flujo << correo.cuerpo << endl;
			getline (cin, correo.cuerpo);
		}

	resultado=flujo.str();
	correo.cuerpo = resultado;

	flujo1 << correo.emisor << "_" << correo.fecha ;
	correo.id= flujo1.str();//el id es la suma de emisor + la fecha
	
}

/*
*Guarda en un archivo ya abierto los datos de un correo finalizando con X
*/

void guardar(const tCorreo &correo,ofstream& archivo1)
{

	
		archivo1 << correo.id << endl;
		archivo1 << correo.fecha << endl;
		archivo1 << correo.emisor << endl;
		archivo1 << correo.destinatario << endl;
		archivo1 << correo.asunto << endl;
		archivo1 << correo.cuerpo;
		archivo1 << "X"  << endl;
		
	
}