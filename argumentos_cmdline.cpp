#include <iostream>
#include "cmdline.h"
#include "argumentos_cmdline.h"
#include "imagen.h"

using namespace std;


//Declaro acá ya que sino el main incluye el .h y tira warning porque
//porque están declaradas pero no definidas.
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


//Variables globales
static istream *input = 0;
static ostream *output = 0;
static ifstream input_file;
static ofstream output_file;
static funcion_t funcion;





funcion_t leer_argumentos(int argc, char * const argv[], istream*& input_, ostream*& output_, ifstream*& input_file_, ofstream*& output_file_){
	cmdline cmdl(options);
	cmdl.parse(argc, argv);
	
	
	
	input_ = input;
	output_ = output;
	input_file_ = &input_file;
	output_file_ = &output_file;
	
	
	return funcion;
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
		funcion = Z;
	else if(arg == "exp")
		funcion = EXPONENCIAL;
	else{
		cout << "Error funcion" << endl;
		exit(EXIT_FAILURE);
	}
}
static void opt_help(string const & arg) {
  cout << "cmdline -f funcion [-i file] [-o file]" << endl;
  exit(EXIT_SUCCESS);
}
