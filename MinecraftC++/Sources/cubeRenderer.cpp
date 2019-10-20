#include <cubeRenderer.hpp>

cubeRenderer::cubeRenderer(){
	 //Pos.x,Pos.y,Pos.z, Texture.x, Texture.y
    float vertices[] = {

	    -0.5f, -0.5f, -0.5f, //0
	     0.5f, -0.5f, -0.5f, //1
	     0.5f,  0.5f, -0.5f,  //2
	    -0.5f,  0.5f, -0.5f,  //3

	    -0.5f, -0.5f,  0.5f,  //4
	     0.5f, -0.5f,  0.5f, 
	     0.5f,  0.5f,  0.5f, 
	    -0.5f,  0.5f,  0.5f,  //7

	            //Y     //X
	    -0.5f,  0.5f,  0.5f, //8
	    -0.5f,  0.5f, -0.5f,
	    -0.5f, -0.5f, -0.5f,
	    -0.5f, -0.5f,  0.5f,//11
	    
	     0.5f,  0.5f,  0.5f, //12
	     0.5f,  0.5f, -0.5f,
	     0.5f, -0.5f, -0.5f,
	     0.5f, -0.5f,  0.5f, //15
	    
	     //X            //-Y
	    -0.5f, -0.5f, -0.5f,//16
	     0.5f, -0.5f, -0.5f,
	     0.5f, -0.5f,  0.5f,
	    -0.5f, -0.5f,  0.5f,//19

	   
	    -0.5f,  0.5f, -0.5f,//16
	     0.5f,  0.5f, -0.5f,
	     0.5f,  0.5f,  0.5f,
	    -0.5f,  0.5f,  0.5f,//19

    };



    unsigned int indices[] = {

        0, 1, 2,   // first triangle
        0, 2, 3,    // second triangle
        4, 5, 6,
        4, 6, 7,
        8, 9, 10,
        8, 10, 11,
        12, 13, 14,
        12, 14, 15,
        16, 17, 18,
        16, 18, 19,
        20, 21, 22,
        20, 22, 23
    };

    _maxCubesPerFrame = 1;

    //Load textures
    cubeLoader loader;
	texturesId = loader.getCubesTextures();

    unsigned int VBO, VAO, EBO, instanceVBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &instanceVBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //geometry buffer
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices, GL_STATIC_DRAW);   
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*) 0);
    glBindBuffer(GL_ARRAY_BUFFER,0);


    //Instance buffer
    glBindBuffer(GL_ARRAY_BUFFER,instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * _maxCubesPerFrame,NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*) 0);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribDivisor(1, 1);  

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    this->idVAO = VAO;
    this->idInstanceVBO = instanceVBO;

    //Depois veer como fica os shaders
    //createShader();
}



void cubeRenderer::drawCubes(int numberCubes, void * cubos,cubetype type){

    glBindBuffer(GL_ARRAY_BUFFER,idInstanceVBO);

	if(numberCubes > _maxCubesPerFrame){
		_maxCubesPerFrame = numberCubes;
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * _maxCubesPerFrame,NULL, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0 , (numberCubes) * sizeof(glm::vec3), cubos);
	}else{
        glBufferSubData(GL_ARRAY_BUFFER, 0 , (numberCubes) * sizeof(glm::vec3), cubos);
    }

	loadTexture(type);
	prepareDraw();
	glDrawElementsInstanced(GL_TRIANGLES,36,GL_UNSIGNED_INT,0,  numberCubes);
	
}


void cubeRenderer::prepareDraw(){

	//cubeProgram.runShader();
	glBindVertexArray(idVAO);
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP,idTexture);
}

void cubeRenderer::loadTexture(cubetype type){
	idTexture = texturesId.at(type);
	return;
}

//Need to rethink this
void cubeRenderer::createShader(){
	 //Loading shaders
    shaderProgram program;
    program.adicionarShader(GL_VERTEX_SHADER,"/home/Camolezi/Desktop/CG/Minecraft/Glitter/Glitter/Shaders/cubeVertexShader.txt");
    program.adicionarShader(GL_FRAGMENT_SHADER,"/home/Camolezi/Desktop/CG/Minecraft/Glitter/Glitter/Shaders/cubeFragmentShader.txt");

    program.link();
    program.runShader();

    program.setUniform("textureImage",0);
    cubeProgram= program;
}
