#ifndef TRANSLATE_OP
#define TRANSLATE_OP

#include "operation.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "glut.h"
#endif


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

class Translate : public Operation {
    float x, y, z;
    
    public:
        Translate(double xx, double yy, double zz) {
			x = xx;
			y = yy;
			z = zz;
        }
    
        void transformacao(){

            glTranslatef(x, y, z);
        }

	
};

class DynamicTranslate : public Operation {
	float time;
	vector<Point> pontos_curva;

public:
	DynamicTranslate(double t, vector<Point> pts) {
		time = t;
		pontos_curva = pts;
	}

	void transformacao() {

		//glTranslatef(x, y, z);
	}


};

#pragma GCC diagnostic pop
#endif

