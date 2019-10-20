#include <cubeLoader.hpp>

//Need to change here when a new cube type is added to the game
void cubeLoader::loadAllTextures(){
	for(auto &it : texturesId){

		switch(it.first){

			case cubetype::grass:
				it.second = loadCube("Textures/grass_side.png",
						"Textures/grass_top2.png",
						"Textures/dirt.png");
				break;
				//teste

			case cubetype::dirt:
				it.second = loadCube("Textures/dirt.png");
				break;

			case cubetype::wood:
				it.second = loadCube("Textures/log_oak.png",
						 "Textures/log_oak_top.png");
				break;

			case cubetype::treeGrass:
				it.second = loadCube("Textures/pinkLeafs.png");
				break;

			case cubetype::water:
				it.second = loadCube("Textures/Water.png");
				break;

			case cubetype::sand:
				it.second = loadCube("Textures/sand.png");
				break;

			case cubetype::tnt:
				it.second = loadCube("Textures/tnt_side.png");
				break;

			default:
				break;
		};
	}

	return;
}

std::unordered_map<cubetype,unsigned int> cubeLoader::getCubesTextures(){
	return texturesId;
}



cubeLoader::cubeLoader(){

	//Load all possible cubes of the game
	int iterator;
	for(iterator = (cubetype::begin + 1); iterator != cubetype::end; ++iterator){
		texturesId.emplace( (cubetype)iterator ,(unsigned int )0);
	}

	loadAllTextures();
}


unsigned int cubeLoader::loadCube(string SideTexture,string TopTexture, string BotTexture){

	std::vector<string> cubeSrc;
	
	cubeSrc.push_back(SideTexture);
	cubeSrc.push_back(SideTexture);
	cubeSrc.push_back(TopTexture);
	cubeSrc.push_back(BotTexture);
	cubeSrc.push_back(SideTexture);
	cubeSrc.push_back(SideTexture);

	baseCube cube(cubeSrc);

	unsigned int ID = cube.getTextureID();
	return ID;

}

unsigned int cubeLoader::loadCube(string Texture){
	return loadCube(Texture,Texture,Texture);
}
unsigned int cubeLoader::loadCube(string SideTexture,string TopTexture){
	return loadCube(SideTexture,TopTexture,TopTexture);
}
