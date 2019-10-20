#include "shaderProgram.hpp"

shaderProgram::shaderProgram(){
	programID = glCreateProgram();
}



shaderProgram::~shaderProgram(){
	deleteShaders();
	glUseProgram(0);
	glDeleteProgram(programID);
}


bool shaderProgram::adicionarShader( unsigned int shaderType , string shaderSrc){

	shaderClass * newShader = new shaderClass(shaderType);

	if(!newShader->setSrc(shaderSrc)){
		return false;
	}

	glAttachShader(programID,newShader->getID());
	shaders.push_back(newShader);

	return true;
}

bool shaderProgram::link(){

	glLinkProgram(programID);

	int compilado;
    glGetProgramiv(programID,GL_LINK_STATUS,&compilado);
    if(!compilado){
        std::cout << "\n Linking Shaders aprensetou erro na compilação: \n";
        char erro[513];
        glGetProgramInfoLog(programID, 512, NULL, erro);
        std::cout << erro;
        return false;
    }
    return true;
}

void shaderProgram::runShader(){
	 glUseProgram(programID);
	 deleteShaders();
}

void shaderProgram::deleteShaders(){
	for (int x = 0; x < (int)shaders.size() ; x++){
		delete shaders.front();
		shaders.pop_front();
	}
}

void shaderProgram::setUniform(string uniformName, float x, float y , float z, float w){
	int vertexLocation = glGetUniformLocation(programID, uniformName.c_str() );	
	glUniform4f(vertexLocation, x, y, z, w);

}

void shaderProgram::setUniform(string uniformName, float x, float y , float z){
	int vertexLocation = glGetUniformLocation(programID, uniformName.c_str() );	
	glUniform3f(vertexLocation, x, y, z);

}

void shaderProgram::setUniform(string uniformName, float * matriz){
	int uniformLoc = glGetUniformLocation(programID,  uniformName.c_str());
	glUniformMatrix4fv(uniformLoc,1,GL_FALSE, matriz);
}

void shaderProgram::setUniform(string uniformName, int valor){
	int uniformLoc = glGetUniformLocation(programID,  uniformName.c_str());
	glUniform1i(uniformLoc,valor);
}



