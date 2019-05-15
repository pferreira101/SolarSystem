#include <matrixOperations.h>
#include <stdio.h>
void cross(float *a, float *b, float *res) {

	res[0] = a[1] * b[2] - a[2] * b[1];
	res[1] = a[2] * b[0] - a[0] * b[2];
	res[2] = a[0] * b[1] - a[1] * b[0];
}

void normalizePlane(float *p){
	float l = length(p);
	normalize(p);
	if(l != 0) p[3] = p[3]/l; // divide d
}


void normalize(float *a) {

	float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);

	if(l != 0){
		a[0] = a[0] / l;
		a[1] = a[1] / l;
		a[2] = a[2] / l;
 	} 
}


float length(float *v) {

	float res = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	return res;

}

void multMatrixVector(float *m, float *v, float *res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}

}

void multVectorMatrix(float *v, float *m, float *res) {
	for (int i = 0; i < 4; ++i) {
		res[i] = 0;
		for (int j = 0; j < 4; ++j) {
			res[i] += v[j] * m[j * 4 + i];
		}
	}
}

void multMatrixMatrix(float *m1, float *m2, float *res) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			res[i * 4 + j] = 0.0f;
			for (int k = 0; k < 4; ++k)
				res[i * 4 + j] += m1[i * 4 + k] * m2[k * 4 + j];
		}
	}
}

void buildRotTransMatrix(float *x, float *y, float *z, float *pos, float *m) {
	// matriz transposta 
	m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
	m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
	m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
	m[12] = pos[0]; m[13] = pos[1]; m[14] = pos[2]; m[15] = 1; // ao usar o ponto calculado podemos aplicar a translacao atraves da matriz
}




void multLVectorCVector(float *lv, float *cv, float *res) {
	(*res) = 0;
	for (int j = 0; j < 4; ++j) {
		(*res) += cv[j] * lv[j];
	}
}






















