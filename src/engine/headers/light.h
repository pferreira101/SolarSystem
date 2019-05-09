#ifndef LIGHT
#define LIGHT

#include <string>

class Light {
	


public:
	float* pos;
	float* diff;
	float* amb;



	Light(float* p, float* d, float* a) {
		pos = p;
		diff = d;
		amb = a;
	}

	virtual void turnOn(GLenum) {}
	virtual void toString() {}


};


class LightDirectional : public Light {

public:
	LightDirectional(float* p, float* d, float* a) : Light(p, d, a) {
		
	}
	


	void turnOn(GLenum light) {

		glLightfv(light, GL_POSITION, pos);
		glLightfv(light, GL_AMBIENT, amb);
		glLightfv(light, GL_DIFFUSE, diff);
	}
};


class LightPoint : public Light {
	float attenuation;


public:
	LightPoint(float* p, float* d, float* a, float at) : Light(p, d, a) {
		attenuation = at; // at é o fator, aplicar formula depois
	}

	void turnOn(GLenum light) {

		glLightfv(light, GL_POSITION, pos);
		glLightfv(light, GL_AMBIENT, amb);
		glLightfv(light, GL_DIFFUSE, diff);
		//glLightfv(light, GL_QUADRATIC_ATTENUATION, &attenuation);
	}

	void toString() {
		printf("POINT: \n");
		printf("\t POS: (%f, %f, %f, %f) \n", pos[0], pos[1], pos[2], pos[3]);
		printf("\t ATTENUATION: %f \n", attenuation);

	}

};


class LightSpot : public Light {
	float *spot_dir; 
	float cutoff_angle, spot_exponent;

public:
	LightSpot(float* p, float* d, float* a, float* dir, float angle, float exp) : Light(p, d, a) {
		spot_dir = dir;
		cutoff_angle = angle;
		spot_exponent = exp;
	}

	void turnOn(GLenum light) {

		glLightfv(light, GL_POSITION, pos);
		glLightfv(light, GL_AMBIENT, amb);
		glLightfv(light, GL_DIFFUSE, diff);
		glLightfv(light, GL_SPOT_DIRECTION, spot_dir);
		//glLightfv(light, GL_SPOT_CUTOFF, &cutoff_angle);
		//glLightfv(light, GL_SPOT_EXPONENT, &spot_exponent);
	}

	void toString() {
		printf("SPOT: \n");
		printf("\t POS: (%f, %f, %f, %f) \n", pos[0], pos[1], pos[2], pos[3]);
		printf("\t DIR: (%f, %f, %f) \n", spot_dir[0], spot_dir[1], spot_dir[2]);
		printf("\t ANGLE: %f \n", cutoff_angle);
	}
};

#endif