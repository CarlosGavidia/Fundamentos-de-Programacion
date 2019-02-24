// Ejercicio 10 del Tema 9 - 09-10reg.cpp

#include <iostream>
using namespace std;
#include "09-10lista.h"

// Funciones internas
void desplazarDcha(tPlantilla &plantilla);
void desplazarIzda(tPlantilla &plantilla);

void desplazarDcha(tPlantilla &plantilla) {
	// Asume que hay hueco
	for (int i = plantilla.numEmpleados; i > 0; i--) {
		plantilla.empleados[i] = plantilla.empleados[i - 1];
   }
}

void desplazarIzda(tPlantilla &plantilla) {
	// El primero se sobreescribe
	for (int i = 0; i < plantilla.numEmpleados - 1; i++) {
		plantilla.empleados[i] = plantilla.empleados[i + 1];
   }
}

void inicializar(tPlantilla &plantilla) {
   plantilla.numEmpleados = 0;
}

void insertarUltimo(tPlantilla &plantilla, tEmpleado empleado) {
	if (plantilla.numEmpleados < MAX_EMPLEADOS) {
      tPtrEmp p = new tEmpleado(empleado);
		plantilla.empleados[plantilla.numEmpleados] = p;
		plantilla.numEmpleados++;
	}
   else {
		cout << "Plantilla llena" << endl;
   }
}

void insertarPrimero(tPlantilla &plantilla, tEmpleado empleado) {
	if (plantilla.numEmpleados < MAX_EMPLEADOS) {
		desplazarDcha(plantilla);
      tPtrEmp p = new tEmpleado(empleado);
		plantilla.empleados[0] = p;
		plantilla.numEmpleados++;
	}
   else {
		cout << "Plantilla llena" << endl;
   }
}

void eliminarUltimo(tPlantilla &plantilla) {
	if (plantilla.numEmpleados > 0) {
		plantilla.numEmpleados--;
      delete plantilla.empleados[plantilla.numEmpleados];
   }
	else {
		cout << "Plantilla vacía";
   }
}

void eliminarPrimero(tPlantilla &plantilla) {
	if (plantilla.numEmpleados > 0) {
      delete plantilla.empleados[0];
		desplazarIzda(plantilla);
		plantilla.numEmpleados--;
	}
   else {
		cout << "Plantilla vacía";
   }
}

void eliminarTodos(tPlantilla &plantilla) {
   for (int i = 0; i < plantilla.numEmpleados; i++) {
      delete plantilla.empleados[i];
   }
	plantilla.numEmpleados = 0;
}

void mostrar(tPlantilla plantilla) {
   cout << "Plantilla:" << endl;
   for (int i = 0; i < plantilla.numEmpleados; i++) {
      mostrar(*plantilla.empleados[i]);
   }
}
