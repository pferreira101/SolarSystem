#ifndef FRUSTUM
#define FRUSTUM

#include <matrixOperations.h>
#include <stdlib.h>

int sphereInFrustum(float** planes, float* center, float radius);
float distance(float* plane, float* point);
float** getFrustumPlanes(float* a);

#endif