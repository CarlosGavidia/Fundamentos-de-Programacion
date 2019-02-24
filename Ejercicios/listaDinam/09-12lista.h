// Ejercicio 12 del Tema 9 - 09-12lista.h

#ifndef lista09_12_h
#define lista09_12_h

#include "09-12reg.h"

const int N = 10;

typedef struct {
	int numEmpleados;
   int capacidad;
	tPtrEmp empleados;
} tPlantilla;

void inicializar(tPlantilla &plantilla);
void insertarUltimo(tPlantilla &plantilla, tEmpleado empleado);
void insertarPrimero(tPlantilla &plantilla, tEmpleado empleado);
void eliminarUltimo(tPlantilla &plantilla);
void eliminarPrimero(tPlantilla &plantilla);
void eliminarTodos(tPlantilla &plantilla);
void mostrar(tPlantilla plantilla);

#endif