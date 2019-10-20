#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/noise.hpp>


//int WindowHeight = 950;
//int WindowWidth = 1800;

//1280 × 720
int WindowWidth = 1280 ;
int WindowHeight = 720;



#include "cuboBase.cpp"
#include "shaderProgram.cpp"
#include "shaderClass.cpp"
#include "camera.cpp"
#include "input.cpp"
#include "noise.cpp"
#include "cubeRenderer.cpp"
#include "cubeLoader.cpp"
#include "terrainRenderer.cpp"
#include "player.cpp"


/*
#include "cuboBase.hpp"
#include "shaderProgram.hpp"
#include "shaderClass.hpp"
#include "camera.hpp"
#include "input.hpp"
#include "noise.hpp"
#include "cubeRenderer.hpp"
#include "cubeLoader.hpp"
#include "terrainRenderer.hpp"
#include "player.hpp"
*/


//Funçẽos
void error_callback(int error, const char* description);
void fpsCounter(float frameTime, GLFWwindow * window);
void generateCubesPos(glm::vec3 * cubos);
void window_resize(GLFWwindow* window, int width, int height);


//export vblank_mode=0

int main(){


    //GLFW STUFF
    if(!glfwInit()){
        std::cout << "\n GLFW Failure. \n";
        glfwTerminate();
        return -1;
    }

    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);

    GLFWwindow * window = glfwCreateWindow(WindowWidth, WindowHeight, "Minecraft", NULL,NULL);
    if(window == NULL){
        std::cout << "\n Open Window Failure. \n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window,window_resize);

    //config input
    input::setWindow(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, input::cursor_pos_callback);

    //GLAD STUFF
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    } 

   
    //OpenGL config
    glViewport(0,0,WindowWidth,WindowHeight);

     //Loading Screen
    glClearColor(0.2f,0.5f,0.2f,0.5f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);


    glClearColor(0.2f,0.2f,0.2f,1.0f);
    glEnable(GL_DEPTH_TEST);


    //Face culling
   // glEnable(GL_CULL_FACE);
   // glCullFace(GL_BACK);
   // glFrontFace(GL_CCW);  

    srand(time(NULL));

    //Create the cubes
    terrainRenderer renderer(256, glm::vec3(100000.0f,0,1000.0f));
    //Loading shaders
    shaderProgram program;
    program.adicionarShader(GL_VERTEX_SHADER,"Shaders/cubeVertexShader.txt");
    program.adicionarShader(GL_FRAGMENT_SHADER,"Shaders/cubeFragmentShader.txt");

    program.link();
    program.runShader();

    program.setUniform("textureImage",0);

    //Transformações
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 viewProj;



    camera sceneCamera;
    sceneCamera.setPos(glm::vec3(100000.0f,50.0f,1000.0f));

    player mainPlayer(sceneCamera.getPos());

    //Game Loop
    while(!glfwWindowShouldClose(window)){

        float startTime = glfwGetTime();
        //Input
        glfwPollEvents();
        input::processInput();


        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

         //StartRendering
        program.runShader();

       // grassCube.drawCubes(int numberCubes, glm::vec3 * cubos,cubetype::grass);
        //modelMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-55.0f * startTime), glm::vec3(1.0f,0,0));
        //modelMatrix = glm::rotate(modelMatrix, glm::radians(25.0f), glm::vec3(0,1.0f,0));
        program.setUniform("model",glm::value_ptr(modelMatrix));

        sceneCamera.attProjMatrix();
        viewProj = sceneCamera.lookAt();
        program.setUniform("viewProjection",glm::value_ptr(viewProj));
        
        renderer.renderPos = sceneCamera.getPos();
        mainPlayer.pos = sceneCamera.getPos();
        renderer.draw();

        //endRendering
        glfwSwapBuffers(window);

        //Fps timer
        float endTime = glfwGetTime();
        input::deltaTimeFrame = endTime - startTime;
        input::fpsCounter();
    }


    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}



void error_callback(int error, const char* description){
    std::cout << std::endl<< error <<": " << description << std::endl;
}


void window_resize(GLFWwindow* window, int width, int height){
    if(window != NULL){
        WindowHeight = height;
        WindowWidth = width;
        glViewport(0,0,WindowWidth,WindowHeight);
    }
}