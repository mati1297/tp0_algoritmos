#include <iostream>
#include <fstream>
#include "imagen.h"

#include "cmdline.h"
#include "argumentos_cmdline.h"

using namespace std;

int main(int argc, char * const argv[]) {

	//cmdline cmdl(options);
	//cmdl.parse(argc, argv);

	ifstream file;
	ofstream f_salida;
	file.open("imagenes_prueba/baboon.pgm");
	Imagen entrada(file);
	file.close();
	Imagen salida = Imagen();
	salida = entrada.transformar(exponencial);
	f_salida.open("salida.pgm");
	salida.savePGM(f_salida);
	f_salida.close();
	// if (error) -> return 1;
	return 0;
}
