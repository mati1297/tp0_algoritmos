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
    matriz[i].resize(COLUMNAS_DEF, VALOR_DEF);
}

Imagen::Imagen(int filas_, int columnas_, int intensidad_, int valor_){
  filas = filas_;
  columnas = columnas_;
  intensidad = intensidad_;
  if(valor_ > intensidad)
    valor_ = VALOR_DEF;
  try{
    matriz.resize(filas_);
  }
  catch(std::bad_alloc &err){
    matriz.resize(FILAS_DEF);
  }
  for(int i = 0; i < filas_; i++){
    try{
      matriz[i].resize(columnas_, valor_);
    }
    catch(std::bad_alloc &err){
      matriz[i].resize(COLUMNAS_DEF, valor_);
    }
  }
}

Imagen::Imagen(const Imagen& original){
  filas = original.filas;
  columnas = original.columnas;
  intensidad = original.intensidad;
  matriz = original.matriz;
}

Imagen::~Imagen(){
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

bool Imagen::operator==(const Imagen& right) const{
  if(right.matriz == matriz && right.intensidad == intensidad)
    return true;
  return false;
}

bool Imagen::operator!=(const Imagen & right) const{
  if(right.matriz != matriz || right.intensidad != intensidad)
    return true;
  return false;
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

Imagen Imagen::transformar(funcion_t f) const{
  switch(f) {
    case Z:
      return this->transf_z();
      break;
    case EXPONENCIAL:
      return this->transf_exp();
      break;
    case CUADRADO:
      return this->transf_cuadrado();
      break;
    default:
      return this->transf_z(); //si pasan una funcion que no existe, devuelve la misma imagen
      break;
    break;
      return *this;
  }
}

Imagen Imagen::transf_z() const{
  Imagen aux = *this;
  return aux;
}


Imagen Imagen::transf_exp() const{
  Imagen aux = Imagen(filas, columnas, intensidad, VALOR_DEF);
  double x_0, y_0, x, y;
  x_0 = columnas/2;
  y_0 = filas/2;

  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
        x = x_0 * (1 + (exp(j/x_0-1)*cos(1-i/y_0)));
        y = y_0 *  (1 - (exp(j/x_0-1)*sin(1-i/y_0)));

        if ((x < 0) || (x >= columnas) || (y < 0) || (y >= filas)) {
          aux.matriz[i][j] = 0;  // Si cae fuera del rango la pongo en 0 (negro.)
        }

        else
          aux.matriz[i][j] = matriz[y][x];
    }
  }

  return aux;
}


Imagen Imagen::transf_cuadrado() const{
  Imagen aux = Imagen(filas, columnas, intensidad, VALOR_DEF);
  double x_0, y_0, x, y;
  x_0 = columnas/2;
  y_0 = filas/2;

  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      x = x_0 * (1 + ((j/x_0-1)*(j/x_0-1)-(1-i/y_0)*(1-i/y_0)));
       y = y_0 *  (1 - (2*(j/x_0-1)*(1-i/y_0)));

      if ((x < 0) || (x >= columnas) || (y < 0) || (y >= filas))
        aux.matriz[i][j] = 0;  // Si cae fuera del rango la pongo en 0 (negro.)
      else {
        aux.matriz[i][j] = this->matriz[y][x];}
    }
  }

  return aux;
}

int Imagen::setIntensidad(std::string& input){
  size_t lectura;
  try{
    intensidad = stoi(input, &lectura);
  }
  catch(std::invalid_argument& err){
	std::cerr << MSJ_ERROR_INTENSIDAD<< std::endl;
	return 1;
  }
  if(intensidad <= 0){
	std::cerr << MSJ_ERROR_INTENSIDAD_INVALIDA << std::endl;
	return 1;
  }
  input = input.substr(lectura);
  return 0;
}

int Imagen::setColumnas(std::string& input){
  size_t lectura;
  try{
    columnas = stoi(input, &lectura);
  }
  catch(std::invalid_argument& err){
	std::cerr << MSJ_ERROR_COLUMNAS << std::endl;
	return 1;
  }
  if(columnas <= 0){
	std::cerr << MSJ_ERROR_TAMANO_INVALIDO << std::endl;
	return 1;
  }
  input = input.substr(lectura);
  return 0;
}

int Imagen::setFilas(std::string& input){
  size_t lectura;
  try{
    filas = stoi(input, &lectura);
  }
  catch(std::invalid_argument& err){
	std::cerr << MSJ_ERROR_FILAS << std::endl;
	return 1;
  }
  if(filas<=0){
	std::cerr << MSJ_ERROR_TAMANO_INVALIDO << std::endl;
	return 1;
  }
  input = input.substr(lectura);
  return 0;
}

int Imagen::setMatriz(std::istream& input){
	/*Se leen los datos de cada pixel de la imagen del archivo .pgm. No permite
   * comentarios entre lineas. No importa la cantidad de pixeles que
   * haya por linea, se leen de corrido hasta que se complete la fila.
   * Si hay menos pixeles de los indicados, el programa termina con
   * un error, si hay mas, los ignora. */
   
   size_t lectura;
   std::string line;
   
  while(getline(input, line)){
    if(line.find_first_not_of(SPACE) == std::string::npos){
      std::cerr << MSJ_ERROR_LINEA_VACIA << std::endl;
	  return 1;
	}
    line = line.substr(line.find_first_not_of(SPACE));
    if(line[0] != PGM_COMENTARIO)
      break;
  }
  
  for(int i = 0; i < filas; i++){
	for(int j = 0; j < columnas; j++){
	  if(line.find_first_not_of(SPACE) == std::string::npos){
	    if(!getline(input, line)){
		  std::cerr << MSJ_ERROR_TAMANO << std::endl;
          return 1;
	    }
        if(line.find_first_not_of(SPACE) == std::string::npos){ //Hay una linea vacia
		  std::cerr << MSJ_ERROR_LINEA_VACIA << std::endl;
		  return 1;
		}
	  }
	  try{
        matriz[i][j] = std::stoi(line, &lectura);
      }
      catch(std::invalid_argument &err){
        std::cerr << MSJ_ERROR_PIXELES << std::endl;
        return 1;
      }
      if(matriz[i][j] > intensidad){
        std::cerr << MSJ_ERROR_INTENSIDAD_MAX << std::endl;
        return 1;
      }
      if(matriz[i][j] < 0){
        std::cerr << MSJ_ERROR_INTENSIDAD_MIN << std::endl;
        return 1;
      }
      line = line.substr(lectura);
    }
  }
  
  return 0;

}

int Imagen::resizeMatriz(){
  try{
    matriz.resize(filas);
  }
  catch(std::bad_alloc &err){
    std::cerr << MSJ_ERROR_MEMORIA << std::endl;
    return 1;
  }

  for(int i = 0; i < filas; i++){
    try{
      matriz[i].resize(columnas);
    }
    catch(std::bad_alloc &err){
      std::cerr << MSJ_ERROR_MEMORIA << std::endl;
      return 1;
    }
  }
  return 0;
}





int Imagen::readPGM(std::istream& input){
  std::string line;

  /*Verificación de que el archivo tiene el header
   * "P2", que es el formato que se desea leer.*/
  while(getline(input, line)){
    if(line.find_first_not_of(SPACE) == std::string::npos){
      std::cerr << MSJ_ERROR_LINEA_VACIA << std::endl;
	  return EXIT_FAILURE;
	}
    line = line.substr(line.find_first_not_of(SPACE));
    if(line[0] != PGM_COMENTARIO)
      break;
  }

  if((line != PGM_INDICADOR) && (line != PGM_INDICADOR_WIN)){
      std::cerr<<MSJ_ERROR_PGM_INDICADOR<<std::endl;
      return(EXIT_FAILURE);
  }

  /* Se leen datos de cantidad de filas y columnas (ambos en
   * una misma linea en el archivo .pgm), luego se cambia el
   * tamaño de la matriz del objeto Imagen para poder alojar
   * la imagen correctamente.*/
  while(getline(input, line)){
    if(line.find_first_not_of(SPACE) == std::string::npos){
      std::cerr << MSJ_ERROR_LINEA_VACIA << std::endl;
	  return EXIT_FAILURE;
	}
    line = line.substr(line.find_first_not_of(SPACE));
    if(line[0] != PGM_COMENTARIO)
      break;
  }

  if(setColumnas(line))
	return EXIT_FAILURE;
  
  if(setFilas(line))
	return EXIT_FAILURE;
 
  if(resizeMatriz())
	return EXIT_FAILURE;


  /*Lee el valor de intensidad dado en el archivo .pgm*/
  while(getline(input, line)){
    if(line.find_first_not_of(SPACE) == std::string::npos){
      std::cerr << MSJ_ERROR_LINEA_VACIA << std::endl;
	  return EXIT_FAILURE;
	}
    line = line.substr(line.find_first_not_of(SPACE));
    if(line[0] != PGM_COMENTARIO)
      break;
  }

  if(setIntensidad(line))
    return EXIT_FAILURE;


  /* Se lee la matriz, se le pasa directamente el puntero istream*/
  
  if(setMatriz(input)){
	  return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}


void Imagen::savePGM(std::ostream& output){
  output << PGM_INDICADOR << std::endl
       << PGM_COMENTARIO << COMENTARIO << std::endl
       << columnas << ' ' << filas << std::endl
       << intensidad << std::endl;
  int contador_linea = 0;
  for(int i = 0; i < filas; i++){
    for(int j = 0; j < columnas; j++){
      output << matriz[i][j] << " ";
      contador_linea++;
      if (contador_linea == NUMEROS_LINEA_SALIDA){
        output << std::endl;
        contador_linea = 0;
      }
    }
  }
}

