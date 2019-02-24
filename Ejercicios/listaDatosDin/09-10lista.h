// Ejercicio 10 del Tema 9 - 09-10lista.h

#ifndef lista09_10_h
#define lista09_10_h

#include "09-10reg.h"

const int MAX_EMPLEADOS = 100;

typedef struct {
	int numEmpleados;
	tPtrEmp empleados[MAX_EMPLEADOS];
} tPlantilla;

void inicializar(tPlantilla &plantilla);
void insertarUltimo(tPlantilla &plantilla, tEmpleado empleado);
void insertarPrimero(tPlantilla &plantilla, tEmpleado empleado);
void eliminarUltimo(tPlantilla &plantilla);
void eliminarPrimero(tPlantilla &plantilla);
void eliminarTodos(tPlantilla &plantilla);
void mostrar(tPlantilla plantilla);

#endif