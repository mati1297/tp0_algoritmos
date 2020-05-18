#ifndef IMAGEN_H
#define IMAGEN_H

#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

#define FILAS_DEF 20
#define COLUMNAS_DEF 20
#define INTENSIDAD_DEF 5
#define VALOR_DEF 0
#define NUMEROS_RENGLON_SALIDA 19

#define PGM_COMENTARIO '#'
#define PGM_INDICADOR "P2"
#define MENSAJE "Hecho con el programa del grupo Charrut Cabeza"
/*
#define CONV_RAD_DEG 57.2957795131
#ifndef PI
#define PI 3.14159265358979323846
#endif
*/
enum FUNCION { z = 0,  exponencial}; // Agregar cuadrado

class Imagen{
private:
  int filas;
  int columnas;
  int intensidad; //poner algo como intensidad maxima
  std::vector<std::vector<int> > matriz = std::vector<std::vector<int> >(FILAS_DEF);
  Imagen transf_z() const;
  Imagen transf_exp() const;
  //void transf_cuadrado(const Imagen & imagen_1); futura implementacion

public:
  Imagen();
  Imagen(int fil, int col, int intens, int value); //hacer lo que comente por wpp
  Imagen(std::istream&);
  Imagen& operator=(const Imagen&);
  bool operator==(const Imagen&) const;  // Para que queres esta??, porque no usar la de abajo.
  bool igual_tamano(const Imagen & referencia);
  bool operator!=(const Imagen & right) const;
  Imagen transformar(FUNCION) const;
  ~Imagen();
  int getFilas() const;//cambiar filas y columnas para mi
  int getColumnas() const;
  int getIntensidad() const;

  void readPGM(std::istream&);
  void savePGM(std::ostream&);

};

std::string quitarCharInicio(std::string input, char caracter);




#endif // IMAGEN_H
