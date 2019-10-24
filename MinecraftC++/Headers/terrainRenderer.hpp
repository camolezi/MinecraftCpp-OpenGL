#ifndef TERRAINRENDERER
#define TERRAINRENDERER

#include <cubeRenderer.hpp>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <map>
#include <thread>         
#include <mutex> 
#include <atomic>


class terrainRenderer{

	typedef class cubesRenderInfo{

	public:

		cubesRenderInfo(cubetype type, bool render = false){
			this->type = type;
			this->render = render;
		}

		cubetype type;
		bool render;

	}cubeInfo;


public:

	terrainRenderer(int size, glm::vec3 renderPosStart);
	void draw();
	inline cubetype getCubeAt(glm::vec3 pos);
	glm::vec3 renderPos;

private:

	void drawTree();
	void grassBiomeGeneration();
	void desertBiomeGeneration();
	void generateSurfaceTerrain();
	void loadCubes();

	inline void renderCube(cubetype type);
	static bool compareInMap(const glm::vec3& a,const glm::vec3& b);

	//Size to render
	int size;
	int loadSize;

	//Renderer
	cubeRenderer renderer;

	//Noises
	noise terrainNoise;
	noise biomeNoise;

	//One vector for each type for cube (Can use a map if the number of differnt types of blocks is very large)
	std::vector<glm::vec3> grassBlocks;
	std::vector<glm::vec3> sandBlocks;
	std::vector<glm::vec3> woodBlocks;
	std::vector<glm::vec3> leaveBlocks;
	std::vector<glm::vec3> waterBlocks;
	std::vector<glm::vec3> tntBlocks;
	std::vector<glm::vec3> dirtBlocks;



	std::vector<glm::vec3> grassBlocks2;
	std::vector<glm::vec3> sandBlocks2;
	std::vector<glm::vec3> woodBlocks2;
	std::vector<glm::vec3> leaveBlocks2;
	std::vector<glm::vec3> waterBlocks2;


	//Map with all cubes of the scene
	std::map<glm::vec3,cubeInfo,bool(*)(const glm::vec3&,const glm::vec3&)> cubes; 

	//Mult thread variables
	std::mutex loadMutex;
	std::thread * loadThread;
	
	std::atomic<float> renderPosX;
	std::atomic<float> renderPosY;
	std::atomic<float> renderPosZ;

	std::atomic<bool> drawBufferActive;

	std::atomic<int> frameCounter;


};

#endif