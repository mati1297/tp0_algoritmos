#ifndef IMAGEN_H
#define IMAGEN_H

#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include "aux_functions.h"

#define FILAS_DEF 10
#define COLUMNAS_DEF 10
#define INTENSIDAD_DEF 5
#define VALOR_DEF 0
#define NUMEROS_LINEA_SALIDA 19

#define PGM_COMENTARIO '#'
#define PGM_INDICADOR "P2"
#define COMENTARIO "TP0 Algoritmos y Programacion 2. Fiuba. 2020"
#define SPACE ' '


#define MSJ_ERROR_PGM_INDICADOR "Error al leer (indicador distinto de P2)"
#define MSJ_ERROR_FILAS "Error al leer (filas)"
#define MSJ_ERROR_COLUMNAS "Error al leer (columnas)"
#define MSJ_ERROR_INTENSIDAD "Error al leer (intensidad)"
#define MSJ_ERROR_PIXELES "Error al leer (pixeles)"
#define MSJ_ERROR_TAMANO "Error al leer (el tamaño de la imagen es menor que el declarado)"
#define MSJ_ERROR_MEMORIA "Error al cambiar el tamaño de la matriz de la imagen"
#define MSJ_ERROR_INTENSIDAD_MAX "Error al leer lo pixeles, la intensidad supera a la declarada"
#define MSJ_ERROR_INTENSIDAD_MIN "Error al leer los pixeles, la intensidad es menor que 0"
#define MSJ_ERROR_INTENSIDAD_INVALIDA "Error en intensidad máxima, debe ser mayor que 0"
#define MSJ_ERROR_TAMANO_INVALIDO "Error en el tamaño, uno de los ejes es 0 o menor"

/* Clase Imagen
 * Clase que reprensenta a una imagen PGM. Con sus atributos:
 * filas, columnas, intensidad, y la propia imagen,
 * un vector de vectores que forman una matriz con los valores de la 
 * imagen para cada pixel.
*/
enum funcion_t { Z = 0,  EXPONENCIAL, CUADRADO};

class Imagen{
private:
	int filas;
	int columnas;
	int intensidad;
	std::vector<std::vector<int> > matriz = std::vector<std::vector<int> >(FILAS_DEF);
  	Imagen transf_z() const;
	Imagen transf_exp() const;
	Imagen transf_cuadrado() const;

public:
	Imagen();
	Imagen(int, int, int, int);
	Imagen(const Imagen&);
	~Imagen();
	Imagen& operator=(const Imagen&);
	bool operator==(const Imagen&) const; 
	bool operator!=(const Imagen&) const;
	int getFilas() const;	
	int getColumnas() const;
	int getIntensidad() const;
	Imagen transformar(funcion_t) const;
	void readPGM(std::istream&);
	void savePGM(std::ostream&);


};





#endif // IMAGEN_H
