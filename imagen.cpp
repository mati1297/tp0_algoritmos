#include "imagen.h"

#include <cmath>
#include <vector>
#include <fstream>
#include <string>




Imagen::Imagen(){
	columnas = COLUMNAS_DEF;
	filas = FILAS_DEF;
	intensidad = INTENSIDAD_DEF;
	matriz.resize(FILAS_DEF);
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


Imagen::Imagen(std::istream& input){
	this->readPGM(input);
}


void Imagen::readPGM(std::istream& input){
	std::string line;
	int pos_space;
	
	
	while(getline(input, line)){
		if(quitarCharInicio(line, ' ')[0] == PGM_COMENTARIO)
			continue;
		if(line.compare(PGM_INDICADOR)){
			std::cout<<ERROR_PGM_INDICADOR<<std::endl;
			exit(EXIT_FAILURE);
		}
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

void Imagen::savePGM(std::ostream& output){
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

// Creo que esto no hace falta
bool Imagen::igual_tamano(const Imagen & referencia) {
	if ((referencia.filas) == filas) {
		if ((referencia.columnas) == columnas) {
			return true;
		}
	}
	return false;
}
// Devuelve true si las matrices de las imagenes son distintas y no NULL
bool Imagen::operator!=(const Imagen & right) const{
	if(right.matriz != matriz || right.intensidad != intensidad)
		return true;
	return false;
}

bool Imagen::operator==(const Imagen& right) const{
	if(right.matriz == matriz && right.intensidad == intensidad)
		return true;
	return false;
}


Imagen& Imagen::operator=(const Imagen& right){
	if(*this == right)
		return *this;
	filas = right.filas;
	columnas = right.columnas;
	intensidad = right.intensidad;
	matriz = right.matriz;
	return *this;
}

Imagen Imagen::transformar(funcion_t f) const{
	// Verificar que no sean ptr nulos o iguales, esta bien asi == ? No hace falta!!
	switch(f) {
		case Z:
			return this->transf_z();
			break;
		case EXPONENCIAL:
			return this->transf_exp();
			break;
		/*case cuadrado:
			transf_cuadrado(imagen_1);
			break;*/
		default:
		//error
		//break
			return *this;
	}
}


Imagen Imagen::transf_z() const{
	Imagen aux = *this;
	return aux;
}

//arreglar los tabs de esta funcion
Imagen Imagen::transf_exp() const{
	Imagen aux = Imagen(filas, columnas, intensidad, VALOR_DEF);
  double x_0, y_0, x, y;
  x_0 = columnas/2;
  y_0 = filas/2;

  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {

				x = x_0 * (1 + (exp(j/x_0-1)*cos(1-i/y_0)));
				y = y_0 *  (1 - (exp(j/x_0-1)*sin(1-i/y_0)));

				if ((x < 0) || (x > columnas) || (y < 0) || (y > filas)) {
          aux.matriz[i][j] = 0;  // Si cae fuera del rango la pongo en 0 (negro.)
        } else {
					aux.matriz[i][j] = matriz[y][x];
				}
    }
  }
  
  return aux;
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
