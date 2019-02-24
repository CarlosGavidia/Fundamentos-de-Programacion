// Ejercicio 10 del Tema 9 - 09-10main.cpp

#include <iostream>
using namespace std;
#include "09-10reg.h"
#include "09-10lista.h"

int main() {
   tPlantilla plantilla;
   tEmpleado reg;
   
   inicializar(plantilla);
   
   construir("Reg1", 21, Bachillerato, Fijo, reg);
   insertarPrimero(plantilla, reg);
   mostrar(plantilla);
   
   construir("Reg2", 29, Doctor, Becario, reg);
   insertarPrimero(plantilla, reg);
   mostrar(plantilla);
   
   construir("Reg3", 24, Grado, Eventual, reg);
   insertarUltimo(plantilla, reg);
   mostrar(plantilla);
   
   eliminarPrimero(plantilla);
   mostrar(plantilla);
   
   eliminarUltimo(plantilla);
   mostrar(plantilla);
   
   construir("Reg4", 22, Bachillerato, Practicas, reg);
   insertarPrimero(plantilla, reg);
   mostrar(plantilla);
   
   eliminarTodos(plantilla);
   mostrar(plantilla);

   return 0;
}
