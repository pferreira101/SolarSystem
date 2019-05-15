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
		attenuation = at;
	}

	void turnOn(GLenum light) {

		glLightfv(light, GL_POSITION, pos);
		glLightfv(light, GL_AMBIENT, amb);
		glLightfv(light, GL_DIFFUSE, diff);
		glLightfv(light, GL_SPECULAR, spec);

		glLightfv(light, GL_LINEAR_ATTENUATION, &attenuation);
	}
};


class LightSpot : public Light {
	float *spot_dir; 
	float cutoff_angle, spot_exponent;

public:
	LightSpot(float* pos, float* diff, float* amb, 
		      float* spec, float* dir, float angle, float exp) : Light(pos, diff, amb, spec) {
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
		glLightfv(light, GL_SPOT_CUTOFF, &cutoff_angle);
		glLightfv(light, GL_SPOT_EXPONENT, &spot_exponent);
	}
};

#pragma GCC diagnostic pop
#endif