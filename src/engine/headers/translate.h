#ifndef TRANSLATE_OP
#define TRANSLATE_OP

#include "operation.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "glut.h"
#endif
#include <math.h> 
#include <utility>
#include <matrixOperations.h>  

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

class Translate : public Operation {
    float x, y, z;
    float position[3];

    
    public:
        Translate(double xx, double yy, double zz) {
			x = xx;
			y = yy;
			z = zz;
			position[0] = xx; position[1] = yy; position[2] = zz;
        }

        void print(){
            printf("Translate - %f %f %f\n",x,y,z);
    	}
    	
    	float* getPosition(){
    		return position;
    	}

        void transformacao(){

            glTranslatef(x, y, z);
        }

	
};

class DynamicTranslate : public Operation {
	float time;
	vector<Point> points;
	int n_points;
	float vector_y[3] = {0,1,0};
	float position[3];

public:
	DynamicTranslate(double t, vector<Point> pts) {
		time = t;
		points = pts;
		n_points = pts.size();
	}

	void print(){
            printf("DynamicTranslate - %f %f %f\n",position[0],position[1],position[2] );
    }

    float* getPosition(){
    	return position;
    }

	void transformacao() {
		drawCurve();
		processCatmullRomCurve();
	}

	

	pair<Point*,Point*> getCatmullRomPoint(float t, Point p0, Point p1, Point p2, Point p3) {
		float pos[3], deriv[3];

		// catmull-rom matrix
		float m[4][4] = {	{-0.5f,  1.5f, -1.5f,  0.5f},
							{ 1.0f, -2.5f,  2.0f, -0.5f},
							{-0.5f,  0.0f,  0.5f,  0.0f},
							{ 0.0f,  1.0f,  0.0f,  0.0f}};
	
		// vetores t e t'
		float vt[4] = {t*t*t, t*t, t, 1};
		float vdt[4] = {3*t*t, 2*t, 1, 0};

		// matriz A
		float ax[4], ay[4], az[4];

		// matriz P0,P1,P2,P3 (ordenada por colunas)
		float px[4] = {p0.getX(), p1.getX(), p2.getX(), p3.getX()};
		float py[4] = {p0.getY(), p1.getY(), p2.getY(), p3.getY()};
		float pz[4] = {p0.getZ(), p1.getZ(), p2.getZ(), p3.getZ()};


		// Compute A = M * P
		multMatrixVector(*m, px, ax);
		multMatrixVector(*m, py, ay);
		multMatrixVector(*m, pz, az);

		// Compute pos = T * A
		multLVectorCVector(vt,ax,pos);
		multLVectorCVector(vt,ay,pos+1);
		multLVectorCVector(vt,az,pos+2);

		// compute deriv = T' * A
		multLVectorCVector(vdt,ax,deriv);
		multLVectorCVector(vdt,ay,deriv+1);
		multLVectorCVector(vdt,az,deriv+2);

		pair <Point*, Point*> to_return = make_pair( new Point(pos[0], pos[1], pos[2]),  new Point(deriv[0], deriv[1], deriv[2]));
		return to_return;
	}

	pair<Point*,Point*> getGlobalCatmullRomPoint(float gt) {
		float t1 = gt * n_points; // this is the real global t
		int index = floor(t1);  // which segment
		float t = t1 - index; // where within  the segment

		// indices store the points
		int indices[4]; 
		indices[0] = (index + n_points-1)%n_points;	
		indices[1] = (indices[0]+1)%n_points;
		indices[2] = (indices[1]+1)%n_points; 
		indices[3] = (indices[2]+1)%n_points;

		return getCatmullRomPoint(t, points.at(indices[0]), points.at(indices[1]), points.at(indices[2]), points.at(indices[3]));
	}
 
	void processCatmullRomCurve(){

		float gt = glutGet(GLUT_ELAPSED_TIME)/(time*1000);
		gt -= floor(gt); // gt in [0,1[

		pair<Point*,Point*> pts = getGlobalCatmullRomPoint(gt);

		Point pos = *pts.first;
		float pos_aux[3] = {pos.getX(), pos.getY(), pos.getZ()};
		// atualizar posicao para ser possivel saber onde estará o centro da figura
		position[0] = pos.getX(); position[1] = pos.getY(); position[2] = pos.getZ();

		Point deriv = *pts.second;
		float deriv_aux[3] = {deriv.getX(), deriv.getY(), deriv.getZ()};
		normalize(deriv_aux);

		float vector_z[3];
		cross(deriv_aux, vector_y, vector_z);
		normalize(vector_z);

		cross(vector_z, deriv_aux, vector_y);
		normalize(vector_y);

		float m[16];
		buildRotTransMatrix(deriv_aux, vector_y, vector_z, pos_aux, m);

		glMultMatrixf(m);
		
		delete pts.first; 
		delete pts.second;
	}

	void drawCurve() {
		int num_segmentos = 150;
		float inc = (float )1 / num_segmentos;
		float t = 0;
		glColor3f(1,1,1);
		glBegin(GL_LINE_LOOP);
		for(int i=0; i < num_segmentos; i++){
			pair<Point*, Point*> pts = (getGlobalCatmullRomPoint(t));

			glVertex3f((*pts.first).getX(), (*pts.first).getY(), (*pts.first).getZ());
			t += inc;
			delete pts.first;
			delete pts.second;
		}
		glEnd();

	}



};

#pragma GCC diagnostic pop
#endif

