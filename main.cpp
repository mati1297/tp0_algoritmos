#include <iostream>
#include <fstream>
#include "imagen.h"
#include "cmdline.h"
#include "argumentos_cmdline.h"


using namespace std;



int main(int argc, char * const argv[]) {
	istream *input_ = 0;
	ostream *output_ = 0;
	ifstream *input_file_ = 0; 
	ofstream *output_file_ = 0;
	funcion_t funcion;
	
	
	funcion = leer_argumentos(argc, argv, input_, output_, input_file_, output_file_);
	
	
	
	Imagen imagen_input(*input_);
	Imagen imagen_output = imagen_input.transformar(funcion);
	imagen_output.savePGM(*output_);
	input_file_->close();
	output_file_->close();
	return(EXIT_SUCCESS);
}



