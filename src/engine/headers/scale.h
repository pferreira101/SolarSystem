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
    float x, y, z, scale;
    
    public:
        Scale(float xx, float yy, float zz) {
            x = xx;
            y = yy;
            z = zz;
            scale = xx;
        }
        
        void print(){
            printf("scale - %f %f %f\n",x,y,z );
        }

        float getScale(){
            return scale;
        }

        void transformacao(){

            glScalef(x,y,z);
        }
};

#pragma GCC diagnostic pop
#endif