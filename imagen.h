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

#define PGM_COMENTARIO '#'
#define PGM_INDICADOR "P2"
#define MENSAJE "Hecho con el programa del grupo"

#define CONV_RAD_DEG 57.2957795131
#ifndef PI
#define PI 3.14159265358979323846
#endif

enum funcion { z = 0,  exponencial};

class Imagen{
private:
  int filas;
  int columnas;
  int intensidad; //poner algo como intensidad maxima
  std::vector<std::vector<int> > matriz = std::vector<std::vector<int> >(FILAS_DEF);
  void transf_z(const Imagen & imagen_1);
  void transf_exp(const Imagen & imagen_1);
public:
  Imagen();
  Imagen(int fil, int col, int intens, int value); //hacer lo que comente por wpp
  Imagen(std::ifstream&);
  void transformar(const Imagen & imagen_1, funcion f);
  ~Imagen();
  int getFilas() const;//cambiar filas y columnas para mi
  int getColumnas() const;
  int getIntensidad() const;

  void readPGM(std::ifstream&);
  void savePGM(std::ofstream&);

};

std::string quitarCharInicio(std::string input, char caracter);




#endif // IMAGEN_H
