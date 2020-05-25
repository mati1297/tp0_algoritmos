#include <iostream>
#include <string>
#include <ctype.h>
#include "aux_functions.h"


using namespace std;


/* Se lee una cadena y se remueven todos los espacios del principio,
 * se devuelve la nueva cadena. */
string quitarEspaciosInicio(string input){
	int i;
	for(i = 0; i < int(input.length()); i++){
		if(!isspace(input[i]))
			break;
	}
	return input.substr(i);
}

/* Se lee una cadena y se devuelve la posicion del primer espacio de
 * la cadena. */
int encontrarEspacio(string input){
	int i;
	for(i = 0; i < int(input.length()); i++){
		if(isspace(input[i]))
			return i;
	}
	return -1;
}
