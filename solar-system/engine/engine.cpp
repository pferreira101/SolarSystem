/*#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
*/

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "tinyxml2.h"
#include <string>
#include <vector>
using namespace std;
using namespace tinyxml2;

/**
Classe que guarda as coordenadas X, Y, Z de um ponto
*/
class Point {
	float x, y, z;
public:

	void set_values(float a, float b, float c) {
		x = a;
		y = b;
		z = c;
	}
	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
	float getZ() {
		return z;
	}
};

/**
Classe que guarda os três pontos de um triângulo
*/
class Triangle {
	Point one, two, three;

public:

	void set_values(Point x, Point y, Point z) {
		one = x;
		two = y;
		three = z;
	}
	Point getOne() {
		return one;
	}
	Point getTwo() {
		return two;
	}
	Point getThree() {
		return three;
	}
};


/**
Classe que guarda a lista de triângulos que compõe uma figura
*/
class Figure {
	vector<Triangle> triangles;
public:

	void set_values(vector<Triangle> ts) {
		triangles = ts;
	}

	vector<Triangle> get_values() {
		return triangles;
	}
};


/**
Função que, partindo de um ficheiro gerado pelo generator, devolve a lista dos pontos existentes nesse ficheiro.
*/
vector<Point> getPoints(const char *name) {
	string point;
	ifstream file;
	file.open(name);

	string delimiter = ", ";
	int delim_len = delimiter.length();

	vector<Point> points;
	

	while (!file.eof()) { // To get you all the lines.

		getline(file, point); // Saves the line in STRING.

		string token;
		float coord[3];
		int i = 0;

		int pos_start = 0,pos_end;

		while (i<3) {
			pos_end = point.find(delimiter, pos_start);
			token = point.substr(pos_start, pos_end-pos_start);
			coord[i++] = stof(token);
			pos_start = pos_end + delim_len;
		}

		Point p;
		p.set_values(coord[0], coord[1], coord[2]);
		points.push_back(p);
		
	}
	file.close();

	return points;
}

/**
Função que constrói uma lista de triângulos consoante a lista de pontos que recebe como parâmetro
*/
vector<Triangle> getTriangles(vector<Point> points) {	
	vector<Triangle> triangles;
	Point pts[3];
	int i = 0;

	for (vector<Point>::const_iterator it = points.begin(); it != points.end(); ++it) {

		if (i == 3) i = 0;
		
		pts[i] = (*it);

		if (i == 2) { // ver se é o 3o ponto e formar triangulo
			Triangle t;
			t.set_values(pts[0], pts[1], pts[2]);
			triangles.push_back(t);
		}

		i++;
	}

	return triangles;
}

/**
Função que desenha um figura recebida como parâmetro
*/
/*void drawModel(Figure f) {
	vector<Triangle> triangles;
	triangles = f.get_values();
	glBegin(GL_TRIANGLES);
	for (vector<Triangle>::iterator it = triangles.begin(); it != triangles.end(); ++it) {
		Triangle t = *it;
		glVertex3d(t.getOne().getX(), t.getOne().getY(), t.getOne().getZ());
		glVertex3d(t.getTwo().getX(), t.getTwo().getY(), t.getTwo().getZ());
		glVertex3d(t.getThree().getX(), t.getThree().getY(), t.getThree().getZ());
	}
	glEnd();
}*/

/**
Função que interpreta um cenário gráfico em XML
*/
int readXML(const char *filename) {

	XMLDocument doc;
	XMLError error = doc.LoadFile(filename);
	if (error != XML_SUCCESS) { printf("Error: %i\n", error); return error; }

	XMLNode * scene = doc.FirstChild();
	if (scene == nullptr) return XML_ERROR_FILE_READ_ERROR;

	XMLElement *models = scene->FirstChildElement("model");

	while (models != nullptr) {

		const char * fileName = nullptr;
		fileName = models->Attribute("file");

		if (fileName == nullptr) return XML_ERROR_PARSING_ATTRIBUTE;
		
		Figure f;
		f.set_values(getTriangles(getPoints(fileName)));
		
		drawModel(f);

		models = models->NextSiblingElement("model");
	}


	return XML_SUCCESS;
}


int main(int argc, char** argv) {

	if (argc == 1) return -1;

	else {
		return readXML(argv[1]);
	}
}
