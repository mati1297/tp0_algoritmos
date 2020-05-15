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

bool igual_tamano(const Imagen & referencia) {
	if (referencia.filas == filas) {
		if (referencia.columnas == columnas) {
			return true
		}
	}
	return false
}
// Devuelve true si las matrices de las imagenes son distintas y no NULL
bool distintas_imagen (const Imagen & referencia) {
	if (referencia.matriz != matriz) {
		if ((matriz) && (referencia.matriz)){
			return true
		}
	}
	return flase
}

/*
Imagen & Imagen::operator=(const Imagen &) {
	// Para que queres este operador Mati???
}
*/
void Imagen::transformar(const Imagen & imagen_1,  FUNCION f){
	// Verificar que no sean ptr nulos o iguales, esta bien asi == ?
	if (distintas_imagen(imagen_1) && igual_tamano(imagen_1)) {
		switch(f) {
			case z:
				transf_z(imagen_1);
				break;
			case exponencial:
				transf_exp(imagen_1);
				break;
			/*case cuadrado:
				transf_cuadrado(imagen_1);
				break;*/
		}
	}
}


void Imagen::transf_z(const Imagen & imagen_1){
  for (int i = 0; i < imagen_1.filas; i++) {
    for (int j = 0; j < imagen_1.columnas; j++)
        matriz[i][j] = imagen_1.matriz[i][j];
  }
}

void Imagen::transf_exp(const Imagen & imagen_1){
  double x_0, y_0, x, y;
	x_0 = imagen_1.columnas/2;
  y_0 = imagen_1.filas/2;

  for (int i = 0; i < imagen_1.filas; i++) {
    for (int j = 0; j < imagen_1.columnas; j++) {

				x = x_0 * (1 + (exp(j/x_0-1)*cos(1-i/y_0)));
				y = y_0 *  (1 - (exp(j/x_0-1)*sin(1-i/y_0)));

				if ((x < 0) || (x > imagen_1.columnas) || (y < 0) || (y > imagen_1.filas)) {
          matriz[i][j] = 0;  // Si cae fuera del rango la pongo en 0 (negro.)
        } else {
					matriz[i][j] = imagen_1.matriz[y][x];
				}
    }
  }
}
/*
void Imagen::transf_cuadrado(const Imagen & imagen_1){
	int x, y;
	double x_0, y_0;
	x_0 = imagen_1.columnas/2;
  y_0 = imagen_1.filas/2;

  for (int i = 0; i < imagen_1.filas; i++) {
    for (int j = 0; j < imagen_1.columnas; j++) {

				x = x_0 * (1 + (((j/x_0-1)*(j/x_0-1))-((1-i/y_0)*(1-i/y_0))));
				y = y_0 *  (1 - (2*((j/x_0-1)*(1-i/y_0))));
				std::cout << x << "," << y << std::endl;
				std::cout << i << "," << j << std::endl;
				if ((x < 0) || (x > imagen_1.columnas) || (y < 0) || (y > imagen_1.filas)) {
					std::cout << "no va" << std::endl;
          matriz[i][j] = 0;  // Si cae fuera del rango la pongo en 0 (negro.)
        } else {
					std::cout << "va" << std::endl;
					matriz[i][j] = imagen_1.matriz[y][x];
				}
    }
  }
	std::cout << 2*x_0 << "," << 2*y_0 << std::endl;
}
*/
