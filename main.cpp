#include <iostream>
#include <fstream>
#include "imagen.h"

#include "cmdline.h"
#include "argumentos_cmdline.h"

using namespace std;

int main(int argc, char * const argv[]) {

	cmdline cmdl(options);
	cmdl.parse(argc, argv);

	ifstream file;
	ofstream f_salida;
	file.open("hola_1.pgm");
	Imagen entrada(file);
	Imagen salida(entrada.getFilas(), entrada.getColumnas(), entrada.getIntensidad(), 0);
	salida.transformar(entrada, exponencial);
	f_salida.open("salida.pgm");
	salida.savePGM(f_salida);
	file.close();
	f_salida.close();
	// if (error) -> return 1;
	return 0;
}
