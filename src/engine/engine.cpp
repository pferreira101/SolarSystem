#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "glut.h"
#endif

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <tinyxml2.h>
#include <string>
#include <vector>
#include <group.h>
#include <operation.h>
#include <translate.h>
#include <rotate.h>
#include <scale.h>
#include <hash.h>
#include <figure.h>
#include <xmlHandler.h>

#define _USE_MATH_DEFINES
#include <math.h>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"


using namespace std;


/**
Variável global com a lista de figuras a desenhar
*/
vector<Group> groups;

/**
Função que desenha um figura recebida como parâmetro
*/
void drawModel(Figure f) {
    int color=0;
	vector<Triangle> triangles = f.get_triangles();
	glBegin(GL_TRIANGLES);
	for (vector<Triangle>::iterator it = triangles.begin(); it != triangles.end(); ++it) {
		Triangle t = *it;
        
        if(color==0)
            glColor3f(0.49,0.51,0.53);
        else
            glColor3f(0.2,0.2,0.2);
        
		glVertex3d(t.getOne().getX(), t.getOne().getY(), t.getOne().getZ());
		glVertex3d(t.getTwo().getX(), t.getTwo().getY(), t.getTwo().getZ());
		glVertex3d(t.getThree().getX(), t.getThree().getY(), t.getThree().getZ());
        
        
        color = abs(color-1);
	}
	glEnd();
}





// GLUT ------------------------------------------------------------------------------------
void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0) h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void drawCoordinates() {

	glBegin(GL_LINES);
		// x
		glColor3f(1.0, 0.0, 0.0); // red x	
		glVertex3f(-40.0, 0.0f, 0.0f);
		glVertex3f(40.0, 0.0f, 0.0f);


		// y 
		glColor3f(0.0, 1.0, 0.0); // green y
		glBegin(GL_LINES);
		glVertex3f(0.0, -40.0f, 0.0f);
		glVertex3f(0.0, 40.0f, 0.0f);


		// z 
		glColor3f(0.0, 0.0, 1.0); // blue z
		glVertex3f(0.0, 0.0f, -40.0f);
		glVertex3f(0.0, 0.0f, 40.0f);

	glEnd();
}

float alpha = M_PI/3.4;
float beta = M_PI/6;
float radius = 200;

void renderGroup(vector<Figure> figs, vector<Operation*> ops, vector<Group> subGroups) {
	glPushMatrix();

    for (Operation* o : ops) {
        o->transformacao();
	}
	for (vector<Figure>::iterator it = figs.begin(); it != figs.end(); ++it) {
		Figure f = *it;
		drawModel(f);
	}
	for (vector<Group>::iterator it = subGroups.begin(); it != subGroups.end(); ++it) {
		Group g = *it;
		vector<Operation*> g_ops = g.getOperations();
		vector<Figure> g_figs = g.getFigures();
		vector<Group> g_sub_groups = g.getSubGroups();
		renderGroup(g_figs, g_ops, g_sub_groups);
	}

	glPopMatrix();
}

void renderScene(void) {

	glClearColor(20.0f, 20.0f, 20.0f, 1);
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
    gluLookAt(radius*cos(beta)*cos(alpha), radius*sin(beta), radius*cos(beta)*sin(alpha),
              0.0, 0.0, 0.0,
              0.0f, 1.0f, 0.0f);

	glColor3b(0, 5, 20);
	
	for (vector<Group>::iterator it = groups.begin(); it != groups.end(); ++it) {
		Group g = *it;
		vector<Operation*> ops = g.getOperations();
		vector<Figure> figs = g.getFigures();
		vector<Group> subGroups = g.getSubGroups();
		renderGroup(figs, ops, subGroups);
	}

	drawCoordinates();

	// End of frame
	glutSwapBuffers();
}


void processCamera(unsigned char key, int x, int y) {

	switch (key) {
	case 'A' | 'a':
		alpha += 0.1;
		break;
	case 'D' | 'd':
		alpha -= 0.1;
		break;
	case 'W' | 'w':
		if (beta < 1.5) beta += 0.1;
		break;
	case 'S' | 's':
		if (beta > -1.5) beta -= 0.1;
		break;
	case 'Q' | 'q':
		radius += 20;
		break;
	case 'E' | 'e':
		radius -= 20;
		break;
	}

	glutPostRedisplay();
}

int main(int argc, char **argv) {

	if (argc == 1) {
		printf("Por favor insira todos os parâmetros necessários. \n");
		return -1;
	}

	if (readXML(argv[1], &groups) == XML_SUCCESS){
		// init GLUT and the window
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowPosition(100, 100);
		glutInitWindowSize(800, 800);
		glutCreateWindow("solar-system");

		// Required callback registry 
		glutDisplayFunc(renderScene);
		glutReshapeFunc(changeSize);

		// Callback registration for keyboard processing
		glutKeyboardFunc(processCamera);

		//  OpenGL settings
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		// enter GLUT's main cycle
		glutMainLoop();

		return 1;
	}

	else return 0;
}


#pragma GCC diagnostic pop
