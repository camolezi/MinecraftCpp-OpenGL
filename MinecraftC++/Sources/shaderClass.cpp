#include "shaderClass.hpp"


//Construtor
shaderClass::shaderClass(unsigned int shaderType){

	this->_shaderType = shaderType;	
	//Cria o shader
	_shaderID = glCreateShader(shaderType); 
}


//Destrutor
shaderClass::~shaderClass(){
	 glDeleteShader(_shaderID);
}


bool shaderClass::setSrc(string nome){
		//Carrega o texto
		string codigo = carregarCodigo(nome);
		if(codigo.empty()){
			return false;
		}
		
		const char * stdCodigo = codigo.c_str();
		glShaderSource(_shaderID,1,&(stdCodigo),NULL);

		//COmpila o shader e checa erros
		if(!compilar()){
			return false;
		}
		return true;
}



bool shaderClass::compilar(){
	glCompileShader(_shaderID);

	int compilado;	
    glGetShaderiv(_shaderID, GL_COMPILE_STATUS, &compilado);
    if(!compilado){
    	if(_shaderType == GL_VERTEX_SHADER){
        	std::cout << "\n Vertex Shader aprensetou erro na compilação: \n";
    	}else if(_shaderType == GL_FRAGMENT_SHADER){
    		std::cout << "\n Fragment Shader aprensetou erro na compilação: \n";
    	}
        char erro[513];
        glGetShaderInfoLog(_shaderID, 512, NULL, erro);
        std::cout << erro;
        return false;
    }
    return true;
}


string shaderClass::carregarCodigo(string nome){
	
	ifstream arquivo;
    arquivo.open(nome);
    string src = "";

    if(arquivo.is_open()){

   		string line;
    
        while (getline (arquivo,line)){
            src += line + "\n";
        }
        arquivo.close();

    }else{
        cout << endl <<"Arquivo de shader não encontrado" << endl;
        src.clear();
    }

    return src;
}

unsigned int shaderClass::getID(){
	return _shaderID;
}