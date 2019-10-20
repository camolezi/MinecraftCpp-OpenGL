#include "input.hpp"

GLFWwindow * input::window = NULL;
double input::cursorX = 0;
double input::cursorY = 0;
float input::deltaTimeFrame = 0;

input::input(){
}


void input::setWindow(GLFWwindow * window){
	input::window = window;
}


void input::processInput(){

	if (glfwGetKey(input::window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}

float input::getAxisX(){

	float axisValue = 0.0f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
    	axisValue -= 1.0f;
    }

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		axisValue += 1.0f;	
	}

	return axisValue;
}

float input::getAxisY(){

	float axisValue = 0.0f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
    	axisValue -= 1.0f;
    }

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		axisValue += 1.0f;	
	}

	return axisValue;
}


float input::getAxisUp(){

	float axisValue = 0.0f;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
    	axisValue -= 1.0f;
    }

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
		axisValue += 1.0f;	
	}

	return axisValue;
}

void input::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos){
	if(window != NULL && window == input::window){
		cursorX = xpos;
		cursorY = ypos;	
	}
}

double input::getCursorX(){
	return cursorX;
}

double input::getCursorY(){
	return cursorY;
}



void input::fpsCounter(){
    static int frameCounter = 0;
    static float timePassed = 0;

    timePassed += deltaTimeFrame;
    frameCounter++;
    if(timePassed >= 1.0f){
        glfwSetWindowTitle(window, ("Minecraft - FPS: " + std::to_string(frameCounter)).c_str());
        timePassed = 0;
        frameCounter = 0;
    }
}
