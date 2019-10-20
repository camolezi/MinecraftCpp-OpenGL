#include "cuboBase.hpp"

baseCube::baseCube(const std::vector<string> &texturesSrc){
    
    unsigned int cubeTexture;
    glGenTextures(1, &cubeTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP,cubeTexture);

    //Config texture
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    for (int i = 0; i < texturesSrc.size(); i++){

        int texWidth,texHeight, nChanel;
      //  stbi_set_flip_vertically_on_load(true);  
        unsigned char *data = stbi_load(texturesSrc.at(i).c_str(),&texWidth,&texHeight,&nChanel,0);

        if(data == NULL){
            std::cout << std::endl << "Erro ao carregar a textura";
        }

        if(nChanel == 4){
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,0,GL_RGB,texWidth,texHeight,0,GL_RGBA, GL_UNSIGNED_BYTE, data);
        }else if(nChanel == 3){
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,0,GL_RGB,texWidth,texHeight,0,GL_RGB, GL_UNSIGNED_BYTE, data);
        }
       
        stbi_image_free(data);        
    }

    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    glBindTexture(GL_TEXTURE_CUBE_MAP,0);
    idTexture = cubeTexture;

}

unsigned int baseCube::getTextureID(){
    return idTexture;
}


