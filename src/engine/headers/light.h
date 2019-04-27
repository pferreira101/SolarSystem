#ifndef LIGHT
#define LIGHT

#include <string>

class Light {
	float* pos;
	float* diff;
	int type;

	GLenum numbers[8] = {GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7};

public:
	Light(int t, float* p, float* d) {
		type = t;
		pos = p;
		diff = d;
	}

	virtual bool instanceOf(string t) { return false; }


	GLenum getNumber(int i) {
		return numbers[i];
	}

	float* getPos() {
		return pos;
	}

	float* getDiff() {
		return diff;
	}

	int getType() {
		return type;
	}

	void toString() {
		printf("POSICAO = (%f, %f, %f)\n", pos[0], pos[1], pos[2]);
		printf("DIFF = (%f, %f, %f)\n", diff[0], diff[1], diff[2]);
	}
};


class LightDirectional : public Light {
	float* amb;

public:
	LightDirectional(int t, float* p, float* d, float* a) : Light(t, p, d) {
		amb = a;
	}

	float* getAmb() {
		return amb;
	}
};


class LightPoint : public Light {
	float attenuation;
	float* amb;

public:
	LightPoint(int t, float* p, float* d, float* a, float at) : Light(t, p, d) {
		amb = a;
		attenuation = at;
	}

	float* getAmb() {
		return amb;
	}

};


class LightSpot : public Light {
	float* spot_dir;
	float cutoff_angle, spot_exponent;

public:
	LightSpot(int t, float* p, float* d, float* dir, float angle, float exp) : Light(t, p, d) {
		spot_dir = dir;
		cutoff_angle = angle;
		spot_exponent = exp;
	}

};

#endif