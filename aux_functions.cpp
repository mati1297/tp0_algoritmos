#include <iostream>
#include "string.h"
#include "aux_functions.h"
#include <ctype.h>

using namespace std;


string quitarCharInicio(string input, char caracter){
	int i;
	for(i = 0; i < int(input.length()); i++){
		if(input[i] != caracter)
			break;
	}
	return input.substr(i);
}

string quitarEspaciosInicio(string input){
	int i;
	for(i = 0; i < int(input.length()); i++){
		if(!isspace(input[i]))
			break;
	}
	return input.substr(i);
}
