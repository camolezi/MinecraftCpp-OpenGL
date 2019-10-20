#ifndef CUBERENDERER
#define CUBERENDERER

#include <string>
#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>
#include "shaderProgram.hpp"
#include "noise.hpp"
#include "cuboBase.hpp"

#include "cubeLoader.hpp"


class cubeRenderer{

public:

	cubeRenderer();
	void drawCubes(int numberOfCubes, void * cubos, cubetype type);

private:

	//Map with the textures ID for each type of cube
	std::unordered_map<cubetype,unsigned int> texturesId;

    void loadTexture(cubetype type);
	void createShader();
	void prepareDraw();

	shaderProgram cubeProgram;

	unsigned int idVAO;
	unsigned int idTexture;
	unsigned int idInstanceVBO;


	int _maxCubesPerFrame;

};


#endif
