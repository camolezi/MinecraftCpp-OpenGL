#ifndef NOISE
#define NOISE


#include <time.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>


class noise{

public:

	noise();

	static float lerp(float a, float b, float t);
	static float lerp(float c00, float c10, float c01, float c11, float tx, float ty);

	inline float noise2D(float x, float y, float freq, float amp);

 	float valueNoise(float x, float y);
 	void setValueNoiseParameters(float numOctaves, float attenuation, float lacunarity);

private:

	static const unsigned int ress = 256;

	void printMatrix();  
    float noise2D(float x,float y);

	int numOctaves = 3;
	float attenuation = 0.65f;
	float lacunarity = 1.5f;

	float randomMatrix[ress][ress];
	float maxValue;
};







#endif