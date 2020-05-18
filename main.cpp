#include <iostream>
#include <fstream>
#include "imagen.h"

#include "cmdline.h"

using namespace std;

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_funcion(string const &);
static void opt_help(string const &);

static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "f", "funcion", "-", opt_funcion, OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
};

static istream *input = 0;
static ostream *output = 0;
static ifstream input_file;
static ofstream output_file;
static FUNCION funcion;


int main(int argc, char * const argv[]) {

	cmdline cmdl(options);
	cmdl.parse(argc, argv);

	Imagen imagen_input(*input);
	
	Imagen imagen_output = imagen_input.transformar(funcion);
	imagen_output.savePGM(*output);
	input_file.close();
	output_file.close();
	return(EXIT_SUCCESS);
}


static void opt_input(string const & arg) {
	if(arg == "-")
		input = &cin;
	else{
		input_file.open(arg.c_str(), ios::in);
		input = &input_file;
	}
	if(!input->good()){
		cout << "Error al leer" << endl;
		exit(EXIT_FAILURE);
	}
}
static void opt_output(string const & arg) {
	if(arg == "-")
		output = &cout;
	else{
		output_file.open(arg.c_str(), ios::out);
		output = &output_file;
	}
	if(!output->good()){
		cout << "Error al leer" << endl;
		exit(EXIT_FAILURE);
	}
}
static void opt_funcion(string const & arg) {
	if(arg == "-" || arg == "z")
		funcion = z;
	else if(arg == "exp")
		funcion = exponencial;
	else{
		cout << "Error funcion" << endl;
		exit(EXIT_FAILURE);
	}
}
static void opt_help(string const & arg) {
  cout << "cmdline -f funcion [-i file] [-o file]" << endl;
  exit(EXIT_SUCCESS);
}
