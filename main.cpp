#include <iostream>
#include <fstream>
#include "imagen.h"

using namespace std;

int main() {
	ifstream file;
	ofstream f_salida;
	file.open("hola.pgm");
	Imagen entrada(file);
	Imagen salida(entrada.getFilas(), entrada.getColumnas(), entrada.getIntensidad(), 0);
	salida.transformar(entrada, z);
	
	f_salida.open("salida.pgm");
	salida.savePGM(f_salida);
	file.close();
	f_salida.close();
}
