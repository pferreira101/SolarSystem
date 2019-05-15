#ifndef MATRIX_OP
#define MATRIX_OP

#include <math.h>

void cross(float *a, float *b, float *res);
void normalize(float *a);
float length(float *v);
void multMatrixVector(float *m, float *v, float *res);
void multVectorMatrix(float *v, float *m, float *res);
void multMatrixMatrix(float *m1, float *m2, float *res);
void buildRotTransMatrix(float *x, float *y, float *z, float *pos, float *m);
void multLVectorCVector(float *lv, float *cv, float *res);
void normalizePlane(float *p);

#endif