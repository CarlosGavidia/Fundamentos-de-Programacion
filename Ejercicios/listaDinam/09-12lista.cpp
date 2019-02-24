// Ejercicio 12 del Tema 9 - 09-12lista.cpp

#include <iostream>
using namespace std;
#include "09-12lista.h"

// Funciones internas
void desplazarDcha(tPlantilla &plantilla);
void desplazarIzda(tPlantilla &plantilla);
void redimensionar(tPlantilla &plantilla, int incremento);

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
   plantilla.empleados = new tEmpleado[N];
	plantilla.numEmpleados = 0;
	plantilla.capacidad = N;
}

void redimensionar(tPlantilla &plantilla, int incremento) {
   tPtrEmp aux = new tEmpleado[plantilla.capacidad + incremento];
	for (int i = 0; i < plantilla.numEmpleados; i++) {
		aux[i] = plantilla.empleados[i];
   }
	delete [] plantilla.empleados;
	plantilla.empleados = aux;
	plantilla.capacidad = plantilla.capacidad + incremento;
}

void insertarUltimo(tPlantilla &plantilla, tEmpleado empleado) {
	if (plantilla.numEmpleados == plantilla.capacidad) {
      redimensionar(plantilla, N);
	}
   plantilla.empleados[plantilla.numEmpleados] = empleado;
   plantilla.numEmpleados++;
}

void insertarPrimero(tPlantilla &plantilla, tEmpleado empleado) {
	if (plantilla.numEmpleados == plantilla.capacidad) {
      redimensionar(plantilla, N);
	}
   desplazarDcha(plantilla);
   plantilla.empleados[0] = empleado;
   plantilla.numEmpleados++;
}

void eliminarUltimo(tPlantilla &plantilla) {
	if (plantilla.numEmpleados > 0) {
		plantilla.numEmpleados--;
   }
   if (plantilla.numEmpleados < plantilla.capacidad - 2 * N) {
      redimensionar(plantilla, -N);
   }
}

void eliminarPrimero(tPlantilla &plantilla) {
	if (plantilla.numEmpleados > 0) {
		desplazarIzda(plantilla);
		plantilla.numEmpleados--;
	}
   if (plantilla.numEmpleados < plantilla.capacidad - 2 * N) {
      redimensionar(plantilla, -N);
   }
}

void eliminarTodos(tPlantilla &plantilla) {
   delete [] plantilla.empleados;
	plantilla.numEmpleados = 0;
	plantilla.capacidad = 0;
}

void mostrar(tPlantilla plantilla) {
   cout << "Plantilla:" << endl;
   for (int i = 0; i < plantilla.numEmpleados; i++) {
      mostrar(plantilla.empleados[i]);
   }
   cout << "Capacidad: " << plantilla.capacidad << endl;
}
