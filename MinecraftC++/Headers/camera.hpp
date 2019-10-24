#ifndef CAMERA
#define CAMERA

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "input.hpp"


class camera{

public:

	camera(float renderDistance);

	glm::mat4 lookAt();
	void setPos(glm::vec3 newPos);
	glm::vec3 getPos();
	void moveAim();
	void attProjMatrix();

	//Depois colocar isso no player
	void movePos();

private:


	void colisionDetection();

	//Orientaion variables
	double cursorX;
	double cursorY;
	double pitch;
	double yaw;

	glm::vec3 cameraPos;
	glm::vec3 cameraFront;

	glm::mat4 projMatrix;

	float sensibility = 0.04f;
	float movementSpeed = 40.0f;

};


#endif