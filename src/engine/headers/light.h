#ifndef LIGHT
#define LIGHT

#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

class Light {
	
public:
	float* pos;
	float* diff;
	float* amb;
	float* spec;



	Light(float* p, float* d, float* a, float* s) {
		pos = p;
		diff = d;
		amb = a;
		spec = s;
	}

	virtual void turnOn(GLenum) {}
	virtual void toString() {}


};


class LightDirectional : public Light {

public:
	LightDirectional(float* pos, float* diff, float* amb, float* spec) : Light(pos, diff, amb, spec) {
		
	}
	


	void turnOn(GLenum light) {

		glLightfv(light, GL_POSITION, pos);
		glLightfv(light, GL_AMBIENT, amb);
		glLightfv(light, GL_DIFFUSE, diff);
		glLightfv(light, GL_SPECULAR, spec);
	}
};


class LightPoint : public Light {
	float attenuation;


public:
	LightPoint(float* pos, float* diff, float* amb, float* spec, float at) : Light(pos, diff, amb, spec) {
		attenuation = at; // at é o fator, aplicar formula depois
	}

	void turnOn(GLenum light) {

		glLightfv(light, GL_POSITION, pos);
		glLightfv(light, GL_AMBIENT, amb);
		glLightfv(light, GL_DIFFUSE, diff);
		glLightfv(light, GL_SPECULAR, spec);

		glLightfv(light, GL_LINEAR_ATTENUATION, &attenuation);
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
	LightSpot(float* pos, float* diff, float* amb, float* spec, float* dir, float angle, float exp) : Light(pos, diff, amb, spec) {
		spot_dir = dir;
		cutoff_angle = angle;
		spot_exponent = exp;
	}

	void turnOn(GLenum light) {

		glLightfv(light, GL_POSITION, pos);
		glLightfv(light, GL_AMBIENT, amb);
		glLightfv(light, GL_DIFFUSE, diff);
		glLightfv(light, GL_SPECULAR, spec);

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

#pragma GCC diagnostic pop
#endif