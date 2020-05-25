#include <iostream>
#include "cmdline.h"
#include "argumentos_cmdline.h"
#include "imagen.h"

using namespace std;


/* Declaro las funciones aca ya que sino el main las incluye y
 * como no las encuentra declaradas da un warning */
static void opt_input(string const &);
static void opt_output(string const &);
static void opt_funcion(string const &);
static void opt_help(string const &);


/* Variables globales de parámetros */
static istream *input = 0;
static ostream *output = 0;
static ifstream input_file;
static ofstream output_file;
static funcion_t funcion;


/* Funcion a la que se le pasan variables con los argumentos. Llama a las
 * distintas funciones que leen e interpretan los argumentos y luego los devuelve
 * por las variables pasadas. Devuelve la funcion a realizar elegida por nombre.*/
funcion_t leer_argumentos(int argc, char * const argv[], istream*& input_, ostream*& output_, ifstream*& input_file_, ofstream*& output_file_){
	static option_t options[OPTIONS_CANT];
	cargar_vector_argumentos(options);
	cmdline cmdl(options);
	cmdl.parse(argc, argv);
	
	input_ = input;
	output_ = output;
	input_file_ = &input_file;
	output_file_ = &output_file;
	
	return funcion;
} 

void cargar_vector_argumentos(option_t* options){
	options[0] = {1, "i", "input", "-", opt_input, OPT_DEFAULT};
	options[1] = {1, "o", "output", "-", opt_output, OPT_DEFAULT};
	options[2] = {1, "f", "funcion", "-", opt_funcion, OPT_DEFAULT};
	options[3] = {0, "h", "help", NULL, opt_help, OPT_DEFAULT};
}



static void opt_input(string const & arg) {
	if(arg == "-")
		input = &cin;
	else{
		input_file.open(arg.c_str(), ios::in);
		input = &input_file;
	}
	if(!input->good()){
		cout << MSJ_ERROR_LECTURA_ENTRADA << endl;
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
		cout << MSJ_ERROR_LECTURA_SALIDA << endl;
		exit(EXIT_FAILURE);
	}
}
static void opt_funcion(string const & arg) {
	if(arg == "-" || arg == CMD_Z)
		funcion = Z;
	else if(arg == CMD_EXPONENCIAL)
		funcion = EXPONENCIAL;
	else if(arg == CMD_CUADRADO)
		funcion = CUADRADO;
	else{
		cout << MSJ_ERROR_FUNCION << endl;
		exit(EXIT_FAILURE);
	}
}
static void opt_help(string const & arg) {
	string line;
	ifstream archivo_help;
	archivo_help.open(ARCHIVO_HELP);
	if(!archivo_help.good())
		cout << MSJ_ERROR_HELP << endl;
	while(getline(archivo_help, line))
		cout << line << endl;
	archivo_help.close();
	exit(EXIT_SUCCESS);
}
