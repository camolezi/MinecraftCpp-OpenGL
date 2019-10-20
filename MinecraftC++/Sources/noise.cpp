#include "noise.hpp"



noise::noise(){

	for(unsigned int x = 0; x < ress; x++){
		for (unsigned int y = 0; y < ress; y++){
			randomMatrix[x][y] = (float)rand() / (float)RAND_MAX;
		}
	}

	maxValue = 0;
	for (int x = 0; x < numOctaves; x++){
		maxValue += (1.0f* pow(attenuation,x));
	}

}


float noise::noise2D(float x,float y){

	x = abs(x);
	y = abs(y);

	int xMin = (int) x;
	int yMin = (int) y;


	float tx = x - xMin; //Values for linear interpolation
	float ty = y - yMin;

	xMin = xMin % ress; //Make the noise periodic
	yMin = yMin % ress; 

	int xNext = (xMin == ress-1)? 0 : xMin + 1;
	int yNext = (yMin == ress-1)? 0 : yMin + 1;


	float c00 = randomMatrix[xMin][yMin];
	float c10 = randomMatrix[xNext][yMin];
	float c01 = randomMatrix[xMin][yNext];
	float c11 = randomMatrix[xNext][yNext];

	return lerp(c00,c10,c01,c11,tx,ty);
}


inline float noise::noise2D(float x, float y, float freq, float amp){
	return (amp*noise2D(x*freq,y*freq));
}


float noise::lerp(float a, float b, float t){
	return (a*(1-t)) + (b*t);
}



float noise::valueNoise(float a, float b){

	float result = 0;
	float freq = 1.0f;
	float amp = 1.0f;
	//numOctaves
	for(int x = 0; x < numOctaves; x++){
		result += noise2D(a,b,freq,amp);
		freq = freq * lacunarity;
		amp = amp * attenuation;
	}

	//return result;
	return result/maxValue;

}


float noise::lerp(float c00, float c10, float c01, float c11, float tx, float ty){

	float a = lerp(c00,c10,tx);
	float b = lerp(c01,c11,tx);

	float result = lerp(a,b,ty);

	return result;
}


void noise::printMatrix(){

	for(unsigned int x = 0; x < ress; x++){
		for (unsigned int y = 0; y < ress; y++){
			std::cout <<  " " <<randomMatrix[x][y];
		}
		std::cout << std::endl;
	}
}


void noise::setValueNoiseParameters(float numOctaves, float attenuation, float lacunarity){
	this->numOctaves = numOctaves;
	this->attenuation = attenuation;
	this->lacunarity = lacunarity;
}