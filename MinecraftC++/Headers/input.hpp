#ifndef INPUT
#define INPUT

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

class input{

public:
	input();

	static void processInput();
	static float getAxisX();
	static float getAxisY();
	static float getAxisUp();
	static void setWindow(GLFWwindow * window);
	static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
	static double getCursorX();
	static double getCursorY();

	
	static float deltaTimeFrame;
	static void fpsCounter();

private:
	static GLFWwindow * window;
	static double cursorX;
	static double cursorY;


};



#endif