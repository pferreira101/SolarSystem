#include <ViewFrustumCulling.h>
#include <stdio.h>

float** getFrustumPlanes(float* a){
	float ** planes = (float **) malloc(sizeof(float*)*6);
	for(int i=0; i<6; i++){
		planes[i] = (float*) malloc(sizeof(float)*4);
	}

	//near
	planes[0][0] = a[2] + a[3];
	planes[0][1] = a[6] + a[7];
	planes[0][2] = a[10] + a[11];
	planes[0][3] = a[14] + a[15];

	//far
	planes[1][0] = -a[2] + a[3];
	planes[1][1] = -a[6] + a[7];
	planes[1][2] = -a[10] + a[11];
	planes[1][3] = -a[14] + a[15];

	//bottom
	planes[2][0] = a[1] + a[3];
	planes[2][1] = a[5] + a[7];
	planes[2][2] = a[9] + a[11];
	planes[2][3] = a[13] + a[15];

	//top
	planes[3][0] = -a[1] + a[3];
	planes[3][1] = -a[5] + a[7];
	planes[3][2] = -a[9] + a[11];
	planes[3][3] = -a[13] + a[15];

	//left
	planes[4][0] = a[0] + a[3];
	planes[4][1] = a[4] + a[7];
	planes[4][2] = a[8] + a[11];
	planes[4][3] = a[12] + a[15];

	//right
	planes[5][0] = -a[0] + a[3];
	planes[5][1] = -a[4] + a[7];
	planes[5][2] = -a[8] + a[11];
	planes[5][3] = -a[12] + a[15];

	
	normalizePlane(planes[0]);
	normalizePlane(planes[1]);
	normalizePlane(planes[2]);
	normalizePlane(planes[3]);
	normalizePlane(planes[4]);
	normalizePlane(planes[5]);

	return planes;		
}

int sphereInFrustum(float** planes, float* center, float radius){
	
	float dist;
	int result = 1;
	for(int i=0; i < 6; i++) {
		dist = distance(planes[i], center);
		if (dist < -radius) {
			return 0;

		}
		else if (dist < radius)
			result = 2;
	}

	return result;
}

float distance(float* plane, float* point){
	return plane[0]*point[0] + plane[1]*point[1] +  plane[2]*point[2] + plane[3];
}

