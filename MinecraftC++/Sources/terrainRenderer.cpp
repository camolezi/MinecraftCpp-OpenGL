#include <terrainRenderer.hpp>


terrainRenderer::terrainRenderer(int size, glm::vec3 renderPosStart) : cubes(terrainRenderer::compareInMap)
{

	this->size = size;

    loadSize = 350;
    renderPos = renderPosStart;

    generateSurfaceTerrain();

    renderPosX = renderPos.x;
    renderPosY = renderPos.y;
    renderPosZ = renderPos.z;

    frameCounter = 0;

    drawBufferActive = false;

    this->loadThread = new std::thread(&terrainRenderer::loadCubes,this);
    //loadCubes();
}

void terrainRenderer::draw(){

    renderPosX = renderPos.x;
    renderPosY = renderPos.y;
    renderPosZ = renderPos.z;

    loadMutex.lock();
    renderer.drawCubes(grassBlocks2.size(), &grassBlocks2.front() ,cubetype::grass);
    renderer.drawCubes(sandBlocks2.size(),&sandBlocks2.front(),cubetype::sand);
    renderer.drawCubes(woodBlocks2.size(), &woodBlocks2.front() ,cubetype::wood);
    renderer.drawCubes(leaveBlocks2.size(), &leaveBlocks2.front() ,cubetype::treeGrass);
    renderer.drawCubes(waterBlocks2.size(),&waterBlocks2.front(),cubetype::water);
    loadMutex.unlock();

    frameCounter++;
}


void terrainRenderer::loadCubes(){

    while(true){

        int startRenderX = renderPosX - size/2;
        int endRenderX = renderPosX + size/2;

        int startRenderZ = renderPosZ - size/2;
        int endRenderZ = renderPosZ + size/2;


        //Need to improve this logic and dont reload all the cubes, only the necessary?
        sandBlocks.clear();
        grassBlocks.clear();
        woodBlocks.clear();
        leaveBlocks.clear();
        waterBlocks.clear();
        dirtBlocks.clear();


        auto initialIt = cubes.lower_bound(glm::vec3(startRenderX,0.0,startRenderZ));
        auto it = initialIt;


        for(int x = startRenderX; x < endRenderX; x++){

            it = cubes.lower_bound(glm::vec3(x,0.0,startRenderZ));

            for(int z = startRenderZ; z < endRenderZ; z++){

                while(it->first.z == z){
                    //Verify the need of rendering
                    if(it->second.render == true){

                        switch(it->second.type){
                            case cubetype::grass:
                                grassBlocks.push_back(it->first);
                                break;

                            case cubetype::sand:
                                sandBlocks.push_back(it->first);
                                break;

                            case cubetype::water:
                                waterBlocks.push_back(it->first);
                                break;

                            case cubetype::wood:
                                woodBlocks.push_back(it->first);
                                break;

                            case cubetype::treeGrass:
                                leaveBlocks.push_back(it->first);
                                break;

                            default:
                                //std::cout << std::endl << "Tring to render Cube without a type" << std::endl;
                                break;
                        };

                        
                    } 

                    it++;
                }

            }
        }


        loadMutex.lock();
            grassBlocks2 = grassBlocks;
            sandBlocks2 = sandBlocks;
            waterBlocks2 = waterBlocks;
            woodBlocks2 = woodBlocks;
            leaveBlocks2 = leaveBlocks;
        loadMutex.unlock();  

        if(frameCounter >= 120){
            //generateSurfaceTerrain();
            frameCounter = 0;
        }

    }//End While

}



//Generate the terrain Heights, Biomes and render logic
void terrainRenderer::generateSurfaceTerrain(){

    cubes.clear();

    int startRenderX = renderPos.x - loadSize/2;
    int endRenderX = renderPos.x + loadSize/2;

    int startRenderZ = renderPos.z - loadSize/2;
    int endRenderZ = renderPos.z + loadSize/2;

    float biomeValue = 0;

    //Ŧrees
    float treesMax = 0.985f;
    float height = 0;

    int depth = 3;

    glm::vec3 cubePos;
    cubetype typeCube;

    for(int i = startRenderX; i < endRenderX; i++){
        for(int j = startRenderZ; j < endRenderZ; j++){

            biomeValue = biomeNoise.valueNoise((float)(i)/200.0f,(float)(j)/200.0f);

            //DESERT BIOME
            if(biomeValue <= 0.45f){

                typeCube = cubetype::sand;

                terrainNoise.setValueNoiseParameters(3,0.7f,1.8f);
                height = terrainNoise.valueNoise((float)(i)/85.0f,(float)(j)/85.0f);

                //Interpolate Biomes
                if(biomeValue >= 0.425f){

                    terrainNoise.setValueNoiseParameters(3,0.65f,1.5f);
                    float grassheight = terrainNoise.valueNoise((float)(i)/85.0f,(float)(j)/85.0f);
                    height = noise::lerp((height*40),(grassheight*77), 20*(biomeValue - 0.425));
                }else{
                    height = height * 40;
                }

            //GRASS BIOME
            }else if(biomeValue <=0.65f){

                typeCube = cubetype::grass;

                terrainNoise.setValueNoiseParameters(3,0.65f,1.5f);
                height = terrainNoise.valueNoise((float)(i)/85.0f,(float)(j)/85.0f);
                //Interpolate biomes
                if(biomeValue <= 0.475f ){

                    terrainNoise.setValueNoiseParameters(3,0.7f,1.8f);
                    float Sandheight = terrainNoise.valueNoise((float)(i)/85.0f,(float)(j)/85.0f);
                    height = noise::lerp((Sandheight*40),(height*77), 20*(biomeValue - 0.425));
                    
                }else if(biomeValue >= 0.6){

                    terrainNoise.setValueNoiseParameters(2,0.8f,2.0f);
                    float Oceanheight = terrainNoise.valueNoise((float)(i)/85.0f,(float)(j)/85.0f);
                    height = noise::lerp((height*77),(Oceanheight*15), 20*(biomeValue - 0.6));

                }else{                    
                    height = height*77;
                }

                //ŦREES
                if(terrainNoise.noise2D(i,j,3.5f,1) >= treesMax){
                    for(int tronco = 0; tronco < 3 ; tronco++){
                        cubes.emplace(glm::vec3(i ,(int)height + 1.5f + tronco , j),cubeInfo(cubetype::wood));    
                    }


                    for(int x = -2; x < 3; x++){
                        for(int y = -2; y < 3; y++){
                            for(int altura = 0; altura < 3; altura++){
                                cubes.emplace(glm::vec3(i + x ,(int)height + 4.5f + altura  , j + y),cubeInfo(cubetype::treeGrass));
                            } 
                        }
                    }
                }

            //OCEAN
            }else{

                typeCube = cubetype::water;
                terrainNoise.setValueNoiseParameters(2,0.8f,2.0f);
                height = terrainNoise.valueNoise((float)(i)/85.0f,(float)(j)/85.0f);
                height = height*15;
            }

            cubes.emplace(glm::vec3(i, (int)height + 0.5f , j) ,cubeInfo(typeCube,false)); 

            if(typeCube == cubetype::grass || typeCube == cubetype::sand){
                for(int heightAux = 1; heightAux <= depth; heightAux++){
                    cubes.emplace(glm::vec3(i, (int)height + 0.5f - heightAux , j) ,cubeInfo(typeCube,false));  
                }
            }
            
        }
    }

    //Visible blocks only
    for(auto& cube :  cubes){

        if( getCubeAt(glm::vec3(cube.first.x , cube.first.y  + 1.0f , cube.first.z )) == cubetype::end ||
            getCubeAt(glm::vec3(cube.first.x , cube.first.y  - 1.0f , cube.first.z )) == cubetype::end ||
            getCubeAt(glm::vec3(cube.first.x + 1.0f , cube.first.y  , cube.first.z )) == cubetype::end ||
            getCubeAt(glm::vec3(cube.first.x - 1.0f , cube.first.y  , cube.first.z )) == cubetype::end ||
            getCubeAt(glm::vec3(cube.first.x , cube.first.y , cube.first.z + 1.0f  )) == cubetype::end ||
            getCubeAt(glm::vec3(cube.first.x , cube.first.y , cube.first.z - 1.0f  )) == cubetype::end ){


            cube.second.render = true;
 
        }
    }


}

inline cubetype terrainRenderer::getCubeAt(glm::vec3 pos){
    auto it = cubes.find(pos);
    if(it == cubes.end()){
        return cubetype::end;
    }else{
        return it->second.type;
    }
}


//Retuirn true if a < b
bool terrainRenderer::compareInMap(const glm::vec3& a,const glm::vec3& b){
    
    if(a.x < b.x){
        return true;
    }else if(a.x > b.x){
        return false;
    }else{

        if(a.z < b.z){
            return true;
        }else if(a.z > b.z){
            return false;
        }else{

            if(a.y < b.y){
                return true;
            }else if(a.y > b.y){
                return false;
            }else{
                return false;
            }
        }
    }
}

