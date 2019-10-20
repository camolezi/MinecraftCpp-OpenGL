#ifndef	CUBOBASE
#define CUBOBASE

#include <string>
#include <glm/glm.hpp>
#include <vector>
#include "shaderProgram.hpp"
#include "noise.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

//Class that contains all the information about one specific kind of cube
//(the shared information of a cube is in the cubeRenderer class)

class baseCube{

public:

	baseCube(const std::vector<string> &texturesSrc);
	unsigned int getTextureID();	

private:

	unsigned int idTexture;
};

#endif