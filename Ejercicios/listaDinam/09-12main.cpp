// Ejercicio 12 del Tema 9 - 09-12main.cpp

#include <iostream>
using namespace std;
#include "09-12reg.h"
#include "09-12lista.h"

int main() { // Pruébalo con N = 3
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
   
   construir("Reg4", 22, Bachillerato, Practicas, reg);
   insertarPrimero(plantilla, reg);
   mostrar(plantilla);
   
   construir("Reg5", 23, Bachillerato, Becario, reg);
   insertarPrimero(plantilla, reg);
   mostrar(plantilla);
   
   construir("Reg6", 20, ESO, Practicas, reg);
   insertarPrimero(plantilla, reg);
   mostrar(plantilla);
   
   construir("Reg7", 25, Grado, Fijo, reg);
   insertarPrimero(plantilla, reg);
   mostrar(plantilla);
   
   eliminarPrimero(plantilla);
   mostrar(plantilla);
   
   eliminarUltimo(plantilla);
   mostrar(plantilla);
   
   eliminarUltimo(plantilla);
   mostrar(plantilla);
   
   eliminarUltimo(plantilla);
   mostrar(plantilla);
   
   eliminarUltimo(plantilla);
   mostrar(plantilla);
   
   construir("Reg8", 23, Bachillerato, Eventual, reg);
   insertarPrimero(plantilla, reg);
   mostrar(plantilla);
   
   eliminarTodos(plantilla);
   mostrar(plantilla);

   return 0;
}
