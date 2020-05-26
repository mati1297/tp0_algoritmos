#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(){
	ifstream file;
	file.open("casos_prueba.txt");
	string line;
	while(getline(file, line)){
		system(line.c_str());
	}
	file.close();
}
