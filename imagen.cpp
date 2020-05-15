#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include "imagen.h"



Imagen::Imagen(){
	columnas = COLUMNAS_DEF;
	filas = FILAS_DEF;
	intensidad = INTENSIDAD_DEF;
	for(int i = 0; i < filas; i++)
		matriz[i].resize(columnas, VALOR_DEF);
}

Imagen::Imagen(int fil, int col, int intens, int value){
	filas = fil;
	columnas = col;
	intensidad = intens;
	matriz.resize(fil);
	for(int i = 0; i < fil; i++){
		matriz[i].resize(col, value);
	}
}


Imagen::Imagen(std::ifstream& input){
	this->readPGM(input);
}


void Imagen::readPGM(std::ifstream& input){
	std::string line;
	int pos_space;
	
	while(getline(input, line)){
		if(line[0] == PGM_COMENTARIO)
			continue;
		if(!line.compare(PGM_INDICADOR))
			//RETURN ERROR
			
		break;
	}
	
	
	
	while(getline(input, line)){
		if(quitarCharInicio(line, ' ')[0] == PGM_COMENTARIO)
			continue;
			
		//Llena valores columnas y filas y hace el resize.
		pos_space = line.find(' ');
		
		columnas = std::stoi(line.substr(0, pos_space));
		filas = std::stoi(line.substr(pos_space + 1));
		matriz.resize(filas);
		for(int i = 0; i < filas; i++)
			matriz[i].resize(columnas, VALOR_DEF);
		break;
		//validar
	}
	
	

	while(getline(input, line)){
		if(quitarCharInicio(line, ' ')[0] == PGM_COMENTARIO)
			continue;
		intensidad = stoi(line);
		//VALIDAR
		break;
	}
	
	
	
	while(getline(input, line)){
		if(quitarCharInicio(line, ' ')[0] == PGM_COMENTARIO)
			continue;
			
		for(int i = 0; i < filas; i++){
			for(int j = 0; j < columnas; j++){
				line = quitarCharInicio(line, ' ');
				pos_space = line.find(' ');
				if(pos_space!=-1){
					matriz[i][j] = std::stoi(line.substr(0, pos_space));
					line = line.substr(pos_space);
				}
				else{
					if(line.size())
						matriz[i][j] = std::stoi(line);
					else
						j--;
					getline(input, line);
				}
			
				//VALIDAR
			}
			//getline(input, line);
			//validar comentarios entre lineas de la imagen
		}
		break;
	}
}


std::string quitarCharInicio(std::string input, char caracter){
	int i;
	for(i = 0; i < int(input.length()); i++){
		if(input[i] != caracter)
			break;
	}
	return input.substr(i);
}

void Imagen::savePGM(std::ofstream& output){
	output << PGM_INDICADOR << std::endl
		   << PGM_COMENTARIO << MENSAJE << std::endl
		   << columnas << ' ' << filas << std::endl
		   << intensidad << std::endl;
	int contador_renglon = 0;
	for(int i = 0; i < filas; i++){
		for(int j = 0; j < columnas; j++){
			output << matriz[i][j] << " ";
			contador_renglon++;
			if (contador_renglon == NUMEROS_RENGLON_SALIDA){
				output << std::endl;
				contador_renglon = 0;
			}
		}
		output << std::endl;
	}
		   
	//ver si se puede mejorar
	//ver tema espacios
}


/*
Imagen::Imagen(int fil, int col, int intens){
  int ** matriz = new int * [fil];

  for (int i = 0; i < filas; i++){
      *matriz = new int [col];
  }
  this->ptr = matriz;
  this->filas = fil;
  this->columnas = col;
  this->intensidad = intens;
}
* */

Imagen::~Imagen(){

}

int Imagen::getFilas() const{
  return filas;
}

int Imagen::getColumnas() const{
  return columnas;
}

int Imagen::getIntensidad() const{
  return intensidad;
}

void Imagen::transformar(const Imagen & imagen_1,  funcion f){
// Verificar que sean iguales de tamaño
  switch(f) {

    case z:
      transf_z(imagen_1);
      break;
    case exponencial:
      transf_exp(imagen_1);
      break;

  }
}
void Imagen::transf_z(const Imagen & imagen_1){
  for (int i = 0; i < imagen_1.filas; i++) {
    for (int j = 0; j < imagen_1.columnas; j++)
        matriz[i][j] = imagen_1.matriz[i][j];
  }
}

void Imagen::transf_exp(const Imagen & imagen_1){
  int x_0, y_0, x, y;
	double mod, factor_pi =  imagen_1.filas / (2 * PI);
  x_0 = imagen_1.columnas/2;
  y_0 = imagen_1.filas/2;

	std::cout << x_0 << "," <<y_0 << std::endl;
  for (int i = 0; i < imagen_1.filas; i++) {
    for (int j = 0; j < imagen_1.columnas; j++) {
				j = -j;
				mod = (i-x_0)*(i-x_0) + (j+y_0)*(j+y_0);
				x = log(mod)/2 + x_0;

				if ((i == x_0) && (j = -y_0)) {
					break; // temporal
					y = -y_0; // La fase en 0 la defino como 0
				} else if ((i - x_0) > 0) {
					if ((j + y_0) > 0) {
						y = factor_pi * atan((j + y_0)/(i - x_0)) - y_0;
					} else {
						y = (-factor_pi) * atan((j + y_0)/(i - x_0)) - y_0;
					}
				} else {
					if ((j + y_0) < 0) {
						y = factor_pi * atan((j + y_0)/(i - x_0)) - 2 * y_0;
					} else {
						y = - factor_pi * atan((j + y_0)/(i - x_0)) ;
					}
				}
				std::cout << i << "," << j << std::endl;
				j = -j;
				if ((x < 0) || (x > imagen_1.columnas) || (y < 0) || (y > imagen_1.filas)) {
          matriz[i][j] = 0;  // Si cae fuera del rango la pongo en 0 (negro.)
        } else {
					matriz[i][j] = imagen_1.matriz[y][x];
				}

    }
  }
}
