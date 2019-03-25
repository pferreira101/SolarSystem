#ifndef SCALE_OP
#define SCALE_OP

#include "operation.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "glut.h"
#endif


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

class Scale : public Operation{
    float x, y, z;
    
    public:
        Scale(float xx, float yy, float zz) {
            x = xx;
            y = yy;
            z = zz;
        }
    
        void transformacao(){

            glScalef(x,y,z);
        }
};

#pragma GCC diagnostic pop
#endif