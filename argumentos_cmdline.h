#ifndef ARGUMENTOS_CMDLINE__H
#define ARGUMENTOS_CMDLINE__H
#include <iostream>
#include <fstream>
#include "cmdline.h"
#include "imagen.h"

#define MSJ_ERROR_LECTURA_ENTRADA "Error al leer el archivo de entrada"
#define MSJ_ERROR_LECTURA_SALIDA "Error al leer el archivo de salida"
#define MSJ_ERROR_FUNCION "Funcion incorrecta"
#define MSJ_ERROR_HELP "Archivo help.txt no encontrado"
#define ARCHIVO_HELP "help.txt"

#define CMD_Z "z"
#define CMD_EXPONENCIAL "exp"
#define CMD_CUADRADO "cuadrado"

#define OPTIONS_CANT 4


using namespace std;

funcion_t leer_argumentos(int argc, char * const [], istream*&, ostream*&, ifstream*&, ofstream*&);
void cargar_vector_argumentos(option_t*);


#endif
