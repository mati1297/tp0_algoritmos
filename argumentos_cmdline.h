#ifndef ARGUMENTOS_CMDLINE_INCLUDED_H
#define ARGUMENTOS_CMDLINE_INCLUDED_H

#include <string>
#include "cmdline.h"

using namespace std;

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_funcion(string const &);
static void opt_help(string const &);

static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "f", "funcion", NULL, opt_funcion, OPT_MANDATORY},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
};

// De aca para abajo estaba en argumentos_cmdline.cpp pero se rompia
static void opt_input(string const & arg) {
  cout << "llame al input" << endl;
  exit(EXIT_SUCCESS);
}
static void opt_output(string const & arg) {
  cout << "llame al ouput" << endl;
  exit(EXIT_SUCCESS);
}
static void opt_funcion(string const & arg) {
  cout << "llame a funcion" << endl;
  exit(EXIT_SUCCESS);
}
static void opt_help(string const & arg) {
  cout << "cmdline -f funcion [-i file] [-o file]" << endl;
  exit(EXIT_SUCCESS);
}

#endif
