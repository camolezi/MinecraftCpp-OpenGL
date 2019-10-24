#include "camera.hpp"


camera::camera(float renderDistance){

	cameraPos = glm::vec3(0,0,0);
	cameraFront = glm::vec3(0,0,0);

	projMatrix = glm::perspective(glm::radians(60.0f),(float)WindowWidth/(float)WindowHeight,0.5f,renderDistance);

	pitch = 0;
	yaw = -90;
	cursorX = input::getCursorX();
	cursorY = input::getCursorY();
}


glm::mat4 camera::lookAt(){
	moveAim();	
	movePos();
	//Atualize all the parameters of the camera

	glm::mat4 lookAtMatrix = glm::lookAt(cameraPos,cameraPos + cameraFront,glm::vec3(0.0,1.0f,0.0f));
	lookAtMatrix =  projMatrix * lookAtMatrix;
	return lookAtMatrix;
}


void camera::setPos(glm::vec3 newPos){
	cameraPos = newPos;
}

glm::vec3 camera::getPos(){
	return cameraPos;
}



void camera::attProjMatrix(){
	projMatrix = glm::perspective(glm::radians(60.0f),(float)WindowWidth/(float)WindowHeight,0.5f,256.0f);
}


void camera::movePos(){

	glm::vec3 deltaPos = cameraFront;

	//Movement to camera front
	deltaPos.y = 0;

	glm::vec3 movementFront = (deltaPos * input::getAxisY());

	glm::vec3 deltaSide = glm::cross(deltaPos,glm::vec3(0.0,1.0f,0.0f));
	glm::vec3 movementSide = (deltaSide * input::getAxisX());

	deltaPos = movementSide + movementFront;
	if(glm::length(deltaPos) > 1){
		deltaPos = glm::normalize(deltaPos);
	}
	cameraPos += (movementSpeed * input::deltaTimeFrame * deltaPos);

	//Modo Criativo
	deltaPos = glm::vec3(0.0f,1.0f,0.0f) * input::getAxisUp();
	cameraPos += (1.5f * movementSpeed * input::deltaTimeFrame * deltaPos);

}




void camera::moveAim(){

	double newCursorX = input::getCursorX();
	double newCursorY = input::getCursorY();

	double deltaCursorX = newCursorX - cursorX;
	double deltaCursorY = newCursorY - cursorY; 

	cursorX = newCursorX;
	cursorY = newCursorY;
	//Inverse
	deltaCursorY = -deltaCursorY;
	
	pitch = pitch + (sensibility * deltaCursorY);
	yaw = yaw + (sensibility * deltaCursorX);	

	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(front);

	//Limit of camera
	if(pitch > 89.0f){
		pitch = 89.0f;
	}else if(pitch < -89.0f){
		pitch = -89.0f;
	}

	
}




void camera::colisionDetection(){

}

