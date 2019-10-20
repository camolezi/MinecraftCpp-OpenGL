#ifndef SHADER
#define SHADER

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <fstream>      


using namespace std;


class shaderClass{

public:
	shaderClass(unsigned int shaderType);
	~shaderClass();

	bool setSrc(string nome);

	unsigned int getID();

private:

	string carregarCodigo(string nome);
	bool compilar();
	unsigned int _shaderID;
	unsigned int _shaderType;
};




#endif