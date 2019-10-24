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
	cameraPos += (2.6f * movementSpeed * input::deltaTimeFrame * deltaPos);

	//Modo survival

	float gravity = 25.0f;
	deltaPos = glm::vec3(0.0f,1.0f,0.0f);
	cameraPos += (-gravity * input::deltaTimeFrame * deltaPos);

	//cameraPos += (1.5f * movementSpeed * input::deltaTimeFrame * deltaPos);
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



// A test for colision Detection. Still need to think how to put this in the architecture right 
void camera::colisionDetection(terrainRenderer * render){

	glm::vec3 colisionPos = cameraPos;

	//height player
	float playerHeight = 2.0f;
	float playerSide = 0.5f;
	colisionPos.y = cameraPos.y - playerHeight;
	
	colisionPos.y = ((int) colisionPos.y) + 0.5f; //Find the center

	colisionPos.x = (int) colisionPos.x;
	colisionPos.z = (int) colisionPos.z;

	float deltaX = cameraPos.x - colisionPos.x;
	float deltaY = 0.5f - (cameraPos.y - colisionPos.y);
	float deltaZ = cameraPos.z - colisionPos.z;

	if(render->getCubeAt(colisionPos) != cubetype::end ||
		render->getCubeAt(colisionPos + glm::vec3(0,1.0f,0)) != cubetype::end ||
		render->getCubeAt(colisionPos + glm::vec3(0,1.0f,0)) != cubetype::end){
		//cameraPos.y = colisionPos.y + 0.5f;
		//cameraPos.x =  (deltaX >= 0) ? (colisionPos.x + 1.0f) : (colisionPos.x); 		
		cameraPos.y = (colisionPos.y + playerHeight) + 0.5f;
		//cameraPos.z  =  (deltaZ >= 0) ? (colisionPos.z + 1.0f) : (colisionPos.z); 		
	}

	//
}

