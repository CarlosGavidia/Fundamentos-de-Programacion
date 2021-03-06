// Ejercicio 10 del Tema 9 - 09-10reg.h

#ifndef reg09_10_h
#define reg09_10_h

typedef enum {
	ESO, Bachillerato, FP_Medio, FP_Superior, Grado, Master, Doctor
} tEstudios;

typedef enum {
	Fijo, Practicas, Eventual, Becario
} tTipoContrato;

typedef struct {
	string nombre;
	int edad;
	tEstudios estudios;
	tTipoContrato contrato;
} tEmpleado;

typedef tEmpleado *tPtrEmp;

void mostrar(tEmpleado empleado);
void construir(string nombre, int edad, tEstudios est, tTipoContrato cont, tEmpleado &empleado);

#endif