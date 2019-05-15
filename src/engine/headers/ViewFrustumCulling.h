#ifndef FRUSTUM
#define FRUSTUM

#include <matrixOperations.h>

int sphereInFrustum(float* mpMatrix, float* center, float radius);
float distance(float* plane, float* point);

#endif