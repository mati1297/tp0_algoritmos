#include <iostream>
#include <fstream>
#include "imagen.h"
#include "cmdline.h"
#include "argumentos_cmdline.h"


using namespace std;



int main(int argc, char * const argv[]) {
	/*Variables que se llenan con la funcion leer_argumentos
	 * a partir de los parametros pasados por cmdline*/
	istream *input_ = 0;
	ostream *output_ = 0;
	ifstream *input_file_ = 0; 
	ofstream *output_file_ = 0;
	funcion_t funcion;
	
	
	funcion = leer_argumentos(argc, argv, input_, output_, input_file_, output_file_);
	
	
	Imagen imagen_input = Imagen(); //Se crea una nueva imagen
	if(imagen_input.readPGM(*input_)){//Se carga con la lectura del archivo PGM
		input_file_->close();
		output_file_->close();
		exit(EXIT_FAILURE);
	}
	
	
	/* Se transforma la imagen de entrada y se guarda en una nueva imagen
	 * de salida (constructor por copia) */
	Imagen imagen_output = imagen_input.transformar(funcion);

	imagen_output.savePGM(*output_);//Se guarda la nueva imagen en un pgm.
	input_file_->close(); //Se cierran los archivos.
	output_file_->close();
	
	
	return(EXIT_SUCCESS); //Se termina el programa correctamente.
}



