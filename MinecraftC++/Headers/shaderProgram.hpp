#ifndef SHADERPROGRAM
#define SHADERPROGRAM

#include <list>
#include <string>
#include "shaderClass.hpp"


class shaderProgram{

public:
	 shaderProgram();
	 ~shaderProgram();

	 bool adicionarShader( unsigned int shaderType , string shaderSrc );
	 bool link();
	 void runShader();

	 void setUniform(string uniformName, float x, float y , float z, float w);
	 void setUniform(string uniformName, float x, float y , float z);
	 void setUniform(string uniformName, float * matriz);
	 void setUniform(string uniformName, int valor);


private:
	unsigned int programID;
	list< shaderClass * > shaders;
	void deleteShaders();

};

#endif
