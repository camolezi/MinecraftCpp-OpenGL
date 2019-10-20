#ifndef	CUBOLOADER
#define CUBOLOADER

#include<cuboBase.hpp>
#include <vector>
#include <unordered_map>

enum cubetype {begin,grass,dirt,wood,treeGrass,water,sand,tnt,end};


class cubeLoader{

public:

	cubeLoader();
	std::unordered_map<cubetype,unsigned int> getCubesTextures();

private:

	std::unordered_map<cubetype,unsigned int> texturesId; 

	unsigned int loadCube(string Texture);
	unsigned int loadCube(string SideTexture,string TopTexture);
	unsigned int loadCube(string SideTexture,string TopTexture, string BotTexture);

	void loadAllTextures();
	
};






#endif