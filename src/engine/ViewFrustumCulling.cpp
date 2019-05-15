#include <ViewFrustumCulling.h>
#include <stdio.h>

int sphereInFrustum(float* a, float* center, float radius){
	/*
	float near[4] = {a[8] + a[12], 
					 a[9] + a[13],
					 a[10] + a[14],
					 a[11] + a[15]
					};

	float far[4] = {-a[8] + a[12], 
					-a[9] + a[13],
					-a[10] + a[14],
					-a[11] + a[15]};

	float bottom[4] = {a[4] + a[12], 
					   a[5] + a[13],
					   a[6] + a[14],
					   a[7] + a[15]};

 	float top[4] = {-a[4] + a[12], 
					-a[5] + a[13],
					-a[6] + a[14],
					-a[7] + a[15]};

	float left[4] = {a[0] + a[12], 
					 a[1] + a[13],
					 a[2] + a[14],
					 a[3] + a[15]};

	float right[4] = {-a[0] + a[12], 
					 -a[1] + a[13],
					 -a[2] + a[14],
					 -a[3] + a[15]};
	*/

	float near[4] = {a[2] + a[3], 
					 a[6] + a[7],
					 a[10] + a[11],
					 a[14] + a[15]
					};

	float far[4] = {-a[2] + a[3], 
					-a[6] + a[7],
					-a[10] + a[11],
					-a[14] + a[15]};

	float bottom[4] = {a[1] + a[3], 
					   a[5] + a[7],
					   a[9] + a[11],
					   a[13] + a[15]};

 	float top[4] = {-a[1] + a[3], 
					-a[5] + a[7],
					-a[9] + a[11],
					-a[13] + a[15]};

	float left[4] = {a[0] + a[3], 
					 a[4] + a[7],
					 a[8] + a[11],
					 a[12] + a[15]};

	float right[4] = {-a[0] + a[3], 
					 -a[4] + a[7],
					 -a[8] + a[11],
					 -a[12] + a[15]};	
					 		 

	printf("NEAR %f, %f, %f, %f,\n",near[0],near[1],near[2],near[3]);
	printf("FAR %f, %f, %f, %f,\n",far[0],far[1],far[2],far[3]);
	printf("BOTTOM %f, %f, %f, %f,\n",bottom[0],bottom[1],bottom[2],bottom[3]);
	printf("TOP %f, %f, %f, %f,\n",top[0],top[1],top[2],top[3]);
	printf("LEFT %f, %f, %f, %f,\n",left[0],left[1],left[2],left[3]);
	printf("RIGHT %f, %f, %f, %f,\n",right[0],right[1],right[2],right[3]);
	
	
	normalizePlane(near);
	normalizePlane(far);
	normalizePlane(bottom);
	normalizePlane(top);
	normalizePlane(left);
	normalizePlane(right);
	
	printf("NORMALIZED NEAR %f, %f, %f, %f,\n",near[0],near[1],near[2],near[3]);
	printf("NORMALIZED FAR %f, %f, %f, %f,\n",far[0],far[1],far[2],far[3]);
	printf("NORMALIZED BOTTOM %f, %f, %f, %f,\n",bottom[0],bottom[1],bottom[2],bottom[3]);
	printf("NORMALIZED TOP %f, %f, %f, %f,\n",top[0],top[1],top[2],top[3]);
	printf("NORMALIZED LEFT %f, %f, %f, %f,\n",left[0],left[1],left[2],left[3]);
	printf("NORMALIZED RIGHT %f, %f, %f, %f,\n",right[0],right[1],right[2],right[3]);

	float* planes[6] = {near, far, bottom, top, left, right};			
	float dist;
	int result = 1;
	for(int i=0; i < 6; i++) {
		dist = distance(planes[i], center);
		if (dist < -radius)
			return 0;
		else if (dist < radius)
			result = 2;
	}

	if(result == 0)
		printf("a esfera encontra-se fora\n");
	if(result == 1)
		printf("a esfera encontra-se dentro\n");
	if(result == 2)
		printf("a esfera encontra-se ????\n");
	return result;
}

float distance(float* plane, float* point){
	return plane[0]*point[0] + plane[1]*point[1] +  plane[2]*point[2] + plane[3];
}

